import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

import math.matrices.Vector;
import math.nn.NeuralNetwork;

public class pendigits {

   private static final int DEFAULT_HIDDEN_NODES = 10;

   public static void main(String[] args) throws FileNotFoundException {
      if (args.length < 2) {
         System.err.println("too few arguments");
         return;
      } else if (args.length > 3) {
         System.err.println("too many arguments");
         return;
      }

      File training = new File(args[0]);
      if (!training.isFile()) {
         System.err.println("training is not a file");
         return;
      } else if (!training.canRead()) {
         System.err.println("training cannot be read");
         return;
      }


      File testing = new File(args[1]);
      if (!testing.isFile()) {
         System.err.println("testing is not a file");
         return;
      } else if (!testing.canRead()) {
         System.err.println("testing cannot be read");
         return;
      }


      int hiddenNodes = DEFAULT_HIDDEN_NODES;
      if (args.length == 3) {
         hiddenNodes = Integer.parseInt(args[2]);
         if (hiddenNodes <= 0) {
            hiddenNodes = DEFAULT_HIDDEN_NODES;
            System.err.println("Using default of " + DEFAULT_HIDDEN_NODES);
         }
      }


      NeuralNetwork nn = NeuralNetwork.create(16, hiddenNodes, 10);
      // System.out.println("INITIAL:");
      // nn.printWeights();


      Vector zero = new Vector(new double[] { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 });
      Vector one = new Vector(new double[] { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 });
      Vector two = new Vector(new double[] { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 });
      Vector three = new Vector(new double[] { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 });
      Vector four = new Vector(new double[] { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 });
      Vector five = new Vector(new double[] { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 });
      Vector six = new Vector(new double[] { 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 });
      Vector seven = new Vector(new double[] { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 });
      Vector eight = new Vector(new double[] { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0 });
      Vector nine = new Vector(new double[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 });
      Vector[] classes = new Vector[] { zero, one, two, three, four, five, six, seven, eight, nine };


      Scanner file = new Scanner(training);
      int lineCount = 1;
      Scanner line;
      int feature;
      while (file.hasNextLine()) {
         String lineStr = file.nextLine().trim();
         line = new Scanner(lineStr);
         line.useDelimiter(", *");

         Vector input = new Vector(16);
         Vector output;

         feature = 0;
         while (feature < 16 && line.hasNextInt()) {
            input.set(feature, line.nextInt() / 100.0);
            feature++;
         }
         if (feature == 16 && line.hasNextInt()) {
            output = classes[line.nextInt()];

            nn.train(input, output, 1.0);
         } else {
            System.err.println("error reading file on line " + lineCount);
         }

         lineCount++;
      }


      // System.out.println("FINAL:");
      // nn.printWeights();

      int wrong = 0;

      file = new Scanner(testing);
      lineCount = 1;
      while (file.hasNextLine()) {
         String lineStr = file.nextLine().trim();
         line = new Scanner(lineStr);
         line.useDelimiter(", *");

         Vector input = new Vector(16);
         int expected;

         feature = 0;
         while (feature < 16 && line.hasNextInt()) {
            input.set(feature, line.nextInt() / 100.0);
            feature++;
         }
         if (feature == 16 && line.hasNextInt()) {
            expected = line.nextInt();

            Vector got = nn.get(input);

            double max = 0.0;
            int index = 0;
            for (int i = 0; i < 10; i++) {
               if (got.get(i) > max) {
                  max = got.get(i);
                  index = i;
               }
            }

            if (index != expected) {
               wrong++;
            }
         } else {
            System.err.println("error reading file on line " + lineCount);
         }
         lineCount++;
      }

      System.out.println("done, wrong = " + (double) wrong / lineCount);
      return;
   }
}
