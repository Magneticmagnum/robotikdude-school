package nn.nnet;

import nn.matrices.Matrix;
import nn.matrices.Vector;
import nn.utils.Utils;

public class NeuralNetwork {

   private int      inputs_;
   private int      outputs_;
   // private int layers_;
   private Matrix[] weights_;

   private NeuralNetwork() {
   }

   /**
    * list of the number of nodes <br>
    * starts with input and ends with output <br>
    * ex: {4,5,2} would be 4 input, 5 hidden, and 2 output nodes
    */
   public static NeuralNetwork create(int[] nodes) {
      if (nodes.length < 2) {
         System.err.println("Cannot create a nerual network with both input and output nodes.");
         return null;
      }
      for (int i = 0; i < nodes.length; i++) {
         if (nodes[i] <= 0) {
            System.err.println("Cannot create a nerual network with a layer with zero or negative nodes.");
            return null;
         }
      }

      NeuralNetwork nn = new NeuralNetwork();
      nn.inputs_ = nodes[0];
      nn.outputs_ = nodes[nodes.length - 1];
      nn.weights_ = new Matrix[nodes.length - 1];
      for (int i = 0; i < nn.weights_.length; i++) {
         Matrix m = new Matrix(nodes[i + 1] + 1, nodes[i] + 1);

         for (int j = 0; j < m.getRows() - 1; j++) {
            for (int k = 0; k < m.getColumns(); k++) {
               m.set(j, k, Math.random() - 0.5);
            }
         }

         for (int j = 0; j < m.getColumns() - 1; j++) {
            m.set(nodes[i + 1], j, 0);
         }
         m.set(nodes[i + 1], nodes[i], 1);

         nn.weights_[i] = m;
      }

      return nn;
   }

   public static NeuralNetwork create(int inputs, int hiddenNodes, int outputs) {
      return create(new int[] { inputs, hiddenNodes, outputs });
   }

   public static NeuralNetwork create(int inputs, int outputs) {
      return create(new int[] { inputs, outputs });
   }


   public static void test() {
      NeuralNetwork nn = NeuralNetwork.create(new int[] { 2, 1 });
      double alpha = 1.0;
      Vector z = new Vector(new double[] { 0 });
      Vector o = new Vector(new double[] { 1 });
      Vector zz = new Vector(new double[] { 0, 0 });
      Vector zo = new Vector(new double[] { 0, 1 });
      Vector oz = new Vector(new double[] { 1, 0 });
      Vector oo = new Vector(new double[] { 1, 1 });

      for (int i = 0; i < 1000; i++) {
         nn.train(zz, z, alpha);
         nn.train(zo, o, alpha);
         nn.train(oz, o, alpha);
         nn.train(oo, o, alpha);
      }

      // nn.print = true;
      // System.out.println("zz, z");
      // nn.train(zz, z, alpha);
      // System.out.println("zo, z");
      // nn.train(zo, o, alpha);
      // System.out.println("oz, z");
      // nn.train(oz, o, alpha);
      // System.out.println("oo, o");
      // nn.train(oo, z, alpha);

      nn.weights_[0].print(7, 2);
      // nn.weights_[1].print(7, 2);
      nn.get(zz).print(5, 2);
      nn.get(zo).print(5, 2);
      nn.get(oz).print(5, 2);
      nn.get(oo).print(5, 2);
   }


   public Vector get(Vector input) {
      if (input.getLength() != inputs_) {
         System.err.println("Input size does not match number of input nodes.");
         return null;
      }

      Vector layer = new Vector(inputs_ + 1);
      layer.add(input);
      layer.set(inputs_, 0);

      for (Matrix m : weights_) {
         layer.set(sigmoid(Vector.multiply(m, layer)));
      }

      Vector output = new Vector(outputs_);
      for (int i = 0; i < outputs_; i++)
         output.set(i, layer.get(i));

      return output;
   }

   public boolean print = false;

   public int train(Vector input, Vector output, double alpha) {
      if (input.getLength() != inputs_) {
         System.err.println("Input size does not match number of input nodes.");
         return -1;
      } else if (output.getLength() != outputs_) {
         System.err.println("Output size does not match number of output nodes.");
         return -1;
      }

      int L = weights_.length;

      Vector y = new Vector(outputs_ + 1);
      y.add(output);
      y.set(outputs_, 0);

      Vector[] in = new Vector[L + 1];
      Vector[] a = new Vector[L + 1];

      in[0] = new Vector(inputs_ + 1);
      in[0].add(input);
      in[0].set(inputs_, 0);
      a[0] = in[0];

      if (print) {
         System.out.println("INPUT");
         in[0].print(5, 2);
      }

      if (print) {
         System.out.println("LAYERS");
      }

      for (int l = 1; l < L + 1; l++) {
         Matrix m = weights_[l - 1];
         in[l] = Vector.multiply(m, a[l - 1]);
         a[l] = sigmoid(in[l]);
         if (print) {
            in[l].print(5, 2);
            // a[l].print(5, 2);
         }
      }

      if (print) {
         System.out.println("OUTPUT");
         a[L].print(5, 2);
         System.out.println("EXPECTED");
         y.print(5, 2);
      }


      Vector delta[] = new Vector[L];
      delta[L - 1] = dsigmoid(in[L]).dotMultiply(Vector.subtract(y, a[L]));

      if (print) {
         System.out.println("DELTAS BACKWARDS");
         Vector.subtract(y, a[L]).print(5, 2);
         delta[L - 1].print(5, 2);
      }

      for (int l = L - 2; l >= 0; l--) {
         delta[l] = dsigmoid(in[l + 1]).dotMultiply(Vector.multiply(transpose(weights_[l + 1]), delta[l + 1]));
         delta[l].set(delta[l].getLength() - 1, 0.0);

         if (print) {
            Vector.multiply(transpose(weights_[l + 1]), delta[l + 1]).print(5, 2);
            delta[l].print(5, 2);
         }
      }

      if (print) {
         System.out.println("CHANGES w/o alpha");
      }
      for (int l = 0; l < L; l++) {
         Matrix m = Vector.outerProduct(delta[l], a[l]);
         weights_[l].add(Matrix.scale(alpha, m));

         if (print) {
            m.print(5, 2);
            weights_[l].print(5, 2);
         }
      }

      return 0;
   }

   public int train(Vector input, Vector output) {
      return train(input, output, 1.0);
   }

   private static double TAU = 1.0;

   public Vector sigmoid(Vector z) {
      Vector output = z.copy();
      for (int i = 0; i < output.getLength() - 1; i++) {
         output.set(i, Utils.sigmoid(z.get(i) * TAU));
      }
      return output;
   }

   public Vector dsigmoid(Vector z) {
      Vector output = z.copy();
      for (int i = 0; i < output.getLength() - 1; i++) {
         output.set(i, Utils.dsigmoid(z.get(i) * TAU));
      }
      return output;
   }

   public static Matrix transpose(Matrix m) {
      Matrix n = new Matrix(m.getColumns(), m.getRows());
      for (int i = 0; i < m.getRows(); i++) {
         for (int j = 0; j < m.getColumns(); j++) {
            n.set(j, i, m.get(i, j));
         }
      }
      return n;
   }

}
