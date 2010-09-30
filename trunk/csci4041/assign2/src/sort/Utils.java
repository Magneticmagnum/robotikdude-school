package sort;


import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.PrintStream;
import java.util.InputMismatchException;
import java.util.Random;
import java.util.Scanner;


public class Utils {

   private Utils() {
   }

   public static void runSort(String prog, String[] args,
         SortingAlgorithm sorter) {

      File file = null;
      int size = 100;
      boolean increasing = true;

      if (args.length == 0) {

      } else if (args.length == 1) {
         try {
            size = Integer.parseInt(args[0].trim());
         } catch (NumberFormatException e) {
            help(prog);
            return;
         }
      } else if (args.length == 2) {
         try {
            size = Integer.parseInt(args[0].trim());
            try {
               increasing = (Integer.parseInt(args[1].trim()) == 0);
            } catch (NumberFormatException e) {
               help(prog);
               return;
            }
         } catch (NumberFormatException e) {
            file = new File(args[0]);
            if (!file.canRead()) {
               help(prog);
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
         file = new File(args[0]);
         if (!file.canRead()) {
            help(prog);
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

      double[] list = null;
      if (file != null) {
         list = Utils.read(file, size);
      } else {
         list = Utils.create(size);
      }


      // Arrays.sort(list);
      long stime = System.currentTimeMillis();
      sorter.sort(list, increasing);
      System.out.println("Time taken: " + (System.currentTimeMillis() - stime) / 100.0 + " secs");
   }

   public static void help(String prog) {
      System.out.println("Usage: java " + prog + " file size incrasing");
      System.out.println("       java " + prog + " file size");
      System.out.println("       java " + prog + " size increasing");
      System.out.println("       java " + prog + " size");
      System.out.println("       java " + prog);
      System.out.println();
   }

   public static double[] create(int size) {
      Random generator = new Random(System.currentTimeMillis());
      double[] list = new double[size];
      for (int i = 0; i < size; i++) {
         list[i] = generator.nextDouble() * 100.0;
      }
      return list;
   }

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

         }
         e.printStackTrace();
         scanner.close();
      }
      return list;
   }

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
