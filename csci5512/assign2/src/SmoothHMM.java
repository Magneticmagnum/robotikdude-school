/**
 * CSci5512 Spring '11 Homework 2
 * login: norma272
 * date: 3/23/2011
 * name: Brian Norman
 * id: 4332223
 * algorithm: SmoothHMM
 */

import math.matrices.Matrix;
import math.matrices.Vector;

public class SmoothHMM {

   private static final Matrix T  = new Matrix(new double[][] { { 0.66, 0.34 }, { 0.25, 0.75 } });
   private static final Matrix Tt = new Matrix(new double[][] { { 0.66, 0.25 }, { 0.34, 0.75 } });
   private static final Matrix E  = new Matrix(new double[][] { { 0.9, 0.1 }, { 0.2, 0.8 } });

   public static void main(String[] args) {
      int numEvidence = 0;

      if (args.length != 0) {
         numEvidence = Integer.valueOf(args[0]);
      }
      if (numEvidence == 0) {
         System.out.println("ERROR: No evidence, cannot compute smoothing.");
         System.out.println("USAGE: java SmoothHMM <numEvidence> <sequence of evidence>");
         return;
      } else if (args.length != numEvidence + 1) {
         System.out.println("ERROR: Evidence lengths do not match.");
         System.out.println("USAGE: java SmoothHMM <numEvidence> <sequence of evidence>");
         return;
      }

      System.out.println("T:");
      T.print(6, 4);
      System.out.println("E:");
      E.print(6, 4);

      Vector[] ev = new Vector[numEvidence];
      for (int i = 0; i < numEvidence; i++) {
         int evidence = Integer.valueOf(args[i + 1]);
         ev[i] = new Vector(new double[] { evidence, 1 - evidence });
      }

      Vector[] sv = getSmoothHMM(ev);

      for (int i = 0; i < sv.length; i++) {
         System.out.println("t = " + i);
         sv[i].print(6, 4);
      }
   }

   public static Vector[] getSmoothHMM(Vector[] ev) {
      int t = ev.length;
      Vector prior = new Vector(new double[] { 0.5, 0.5 });
      Vector[] fv = new Vector[t];
      Vector b = new Vector(new double[] { 1.0, 1.0 });
      Vector[] sv = new Vector[t];

      fv[0] = prior;
      for (int i = 1; i < t; i++) {
         fv[i] = forward(fv[i - 1], ev[i]);
      }
      for (int i = t - 1; i >= 0; i--) {
         sv[t - i - 1] = normalize(Vector.dotMultiply(fv[i], b));
         b = backward(b, ev[i]);
      }
      return sv;
   }

   private static Vector forward(Vector f, Vector e) {
      boolean evidence = (e.get(0) == 1);
      double PeT = E.get(0, (evidence ? 0 : 1));
      double PeF = E.get(1, (evidence ? 0 : 1));
      Matrix O = new Matrix(new double[][] { { PeT, 0 }, { 0, PeF } });

      return Vector.multiply(Matrix.multiply(O, Tt), f);
   }

   private static Vector backward(Vector b, Vector e) {
      boolean evidence = (e.get(0) == 1);
      double PeT = E.get(0, (evidence ? 0 : 1));
      double PeF = E.get(1, (evidence ? 0 : 1));
      Matrix O = new Matrix(new double[][] { { PeT, 0 }, { 0, PeF } });

      return Vector.multiply(Matrix.multiply(T, O), b);
   }

   private static Vector normalize(Vector v) {
      double sum = 0;
      for (int i = 0; i < v.getLength(); i++) {
         sum += v.get(i);
      }
      return Vector.scale(1.0 / sum, v);
   }

}
