package sort;


import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;
import java.util.LinkedList;
import java.util.NoSuchElementException;
import java.util.Random;
import java.util.Scanner;


public class Utils {

   public static class Options {
      public boolean HELP = false;
      public boolean FILE = false;
      public boolean CREATE = false;
      public boolean MEGABYTES = false;
      public boolean DISPLAY = false;

      public int SIZE = 10;
      public File LIST = null;
   }

   public static void swap(double[] a, int i, int j) {
      double temp = a[i];
      a[i] = a[j];
      a[j] = temp;
   }

   public static double[] create(int size) {
      Random generator = new Random(System.currentTimeMillis());
      double[] list = new double[size];
      for (int i = 0; i < size; i++) {
         list[i] = generator.nextDouble();
      }
      return list;
   }

   public static double[] read(File file) {
      int size = 0;
      Scanner scanner = null;
      try {
         scanner = new Scanner(file);
         while (scanner.hasNext()) {
            scanner.next();
            size++;
         }
         scanner.close();
      } catch (FileNotFoundException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      }

      double[] list = new double[size];
      try {
         scanner = new Scanner(file);
         int i = 0;
         while (scanner.hasNext()) {
            list[i++] = scanner.nextDouble();
         }
         scanner.close();
      } catch (FileNotFoundException e) {
         // TODO Auto-generated catch block
         e.printStackTrace();
      } catch (InputMismatchException e) {
         // error, non-double element found in file
         e.printStackTrace();
         scanner.close();
      }
      return list;
   }

   public static Utils.Options processArgs(String[] args) {
      Utils.Options opts = new Utils.Options();
      for (int i = 1; i < args.length; i++) {
         if (args[i].startsWith("--")) {

            if (args[i].equals("--help")) {
               opts.HELP = true;
            } else if (args[i].equals("--file")) {
               opts.FILE = true;
            } else if (args[i].equals("--create") || args[i].equals("--size")) {
               opts.CREATE = true;
            } else if (args[i].equals("--display")) {
               opts.DISPLAY = true;
            } else {
               // Unknown option
            }

         } else if (args[i].startsWith("-")) {
            for (int j = 1; j < args[i].length(); j++) {

               switch (args[i].charAt(j)) {
                  case 'h' :
                     opts.HELP = true;
                     break;
                  case 'f' :
                     opts.FILE = true;
                     break;
                  case 's' :
                  case 'c' :
                     opts.CREATE = true;
                     break;
                  case 'M' :
                     opts.MEGABYTES = true;
                     break;
                  case 'd' :
                  case 'D' :
                     opts.DISPLAY = true;
                     break;
                  default :
                     // Unknown option
               }

            }
         } else {
            try {

               int size = Integer.parseInt(args[i].trim());
               opts.SIZE = size;

            } catch (NumberFormatException e) {

               File file = new File(args[i]);
               if (file.canRead()) {
                  opts.LIST = file;
               }

            }
         }
      }
      return opts;
   }

   public static void help(String[] args) {
      System.out.println("");
   }

   public static void unknownOptionChar(String[] args, char option) {

   }
}
