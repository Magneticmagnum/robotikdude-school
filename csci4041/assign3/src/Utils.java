import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;

// a collection of helper functions that are used for convenience
public class Utils {

   // hah! can't create me!
   private Utils() {
   }

   // actually runs the sort test
   public static void runSort(String prog, String[] args,
         SortingAlgorithm sorter) {

      // defaults
      File inFile = null;
      int size = 100;
      boolean increasing = true;
      double[] list = null;

      // **********************************************************************
      // start argument parsing
      // **********************************************************************
      if (args.length == 1) {
         // Usage: java prog size
         try {
            size = Integer.parseInt(args[0].trim());
         } catch (NumberFormatException e) {
            help(prog);
            return;
         }
      } else if (args.length == 2) {
         try {
            // Usage: java prog size increasing
            size = Integer.parseInt(args[0].trim());
            try {
               increasing = (Integer.parseInt(args[1].trim()) == 0);
            } catch (NumberFormatException e) {
               help(prog);
               return;
            }
         } catch (NumberFormatException e) {
            // Usage: java prog file size
            inFile = new File(args[0]);
            if (!inFile.canRead()) {
               System.out.println("ERROR: could not open the specified file.");
               return;
            }
            try {
               size = Integer.parseInt(args[1].trim());
            } catch (NumberFormatException e1) {
               help(prog);
               return;
            }
         }
      } else if (args.length == 3) {
         // Usage: java prog file size increasing
         inFile = new File(args[0]);
         if (!inFile.canRead()) {
            System.out.println("ERROR: could not open the specified file.");
            return;
         }
         try {
            size = Integer.parseInt(args[1].trim());
         } catch (NumberFormatException e1) {
            help(prog);
            return;
         }
         try {
            increasing = (Integer.parseInt(args[2].trim()) == 0);
         } catch (NumberFormatException e) {
            help(prog);
            return;
         }
      } else {
         help(prog);
         return;
      }
      // **********************************************************************
      // end argument parsing
      // **********************************************************************

      // either create or read the list
      if (inFile != null) {
         list = Utils.read(inFile, size);
      } else {
         list = Utils.create(size);
      }

      // start timing and run the sort on the given list
      long stime = System.currentTimeMillis();
      // Arrays.sort(list); // used for testing the built in sort
      sorter.sort(list);
      System.out.println("Time taken: " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");

      // write back out if read from a file
      if (inFile != null) {
         File outFile = new File(inFile.getAbsolutePath() + ".srt");
         write(outFile, list);
      }
   }

   // prints out how to use this program
   public static void help(String prog) {
      System.out.println("Usage: java " + prog + " file size incrasing");
      System.out.println("       java " + prog + " file size");
      System.out.println("       java " + prog + " size increasing");
      System.out.println("       java " + prog + " size");
      System.out.println();
   }

   // creates a list of the given size
   public static double[] create(int size) {
      Random generator = new Random(System.currentTimeMillis());
      double[] list = new double[size];
      for (int i = 0; i < size; i++) {
         list[i] = generator.nextDouble() * 100.0;
      }
      return list;
   }

   // reads a list from the given file of the given size
   public static double[] read(File file, int size) {
      double[] list = new double[size];
      Scanner scanner = null;
      int i = 0;
      try {
         scanner = new Scanner(file);
         while (scanner.hasNext() && i < size) {
            list[i] = scanner.nextDouble();
            i++;
         }
         scanner.close();
      } catch (FileNotFoundException e) {
         e.printStackTrace();
      } catch (InputMismatchException e) {
         // error, non-double element found in file
         // fill rest of array with zeros
         for (; i < size; i++) {
            list[i] = 0.0;
         }
         e.printStackTrace();
         scanner.close();
      }
      return list;
   }

   // writes out the given list to the given file
   public static void write(File file, double[] list) {
      PrintStream out;
      try {
         out = new PrintStream(new BufferedOutputStream(new FileOutputStream(
               file)));
         for (int i = 0; i < list.length; i++) {
            out.println(list[i]);
         }
         out.close();
      } catch (FileNotFoundException e) {
         e.printStackTrace();
      }
   }

}
