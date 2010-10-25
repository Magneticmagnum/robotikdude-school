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
      File outFile = null;
      int heapSize = 100;
      double[] list = null;

      // **********************************************************************
      // start argument parsing
      // **********************************************************************
      if (args.length == 3) {
         // Usage: java prog file size increasing
         inFile = new File(args[0]);
         if (!inFile.canRead()) {
            System.out
                  .println("ERROR: could not open the specified input file.");
            return;
         }
         outFile = new File(args[1]);
         if (!outFile.canRead()) {
            System.out
                  .println("ERROR: could not open the specified output file.");
            return;
         }
         try {
            heapSize = Integer.parseInt(args[2].trim());
         } catch (NumberFormatException e1) {
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
      list = Utils.read(inFile);

      // start timing and run the sort on the given list
      long stime = System.currentTimeMillis();
      sorter.sort(list, heapSize);
      System.out.println("Time taken: " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");

      // write back out if read from a file
      write(outFile, list);
   }

   // prints out how to use this program
   public static void help(String prog) {
      System.out.println("Usage: java " + prog + " in_file out_file heap_size");
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
   public static double[] read(File file) {
      Scanner scanner = null;
      int size = 0;
      try {
         scanner = new Scanner(file);
         while (scanner.hasNext()) {
            size++;
         }
         scanner.close();
      } catch (FileNotFoundException e) {
         e.printStackTrace();
         return null;
      } catch (InputMismatchException e) {
         // error, non-double element found in file
         e.printStackTrace();
         scanner.close();
         return null;
      }

      double[] list = new double[size];
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
         return null;
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



   public static int[] getSplitIndexes(double n, int p) {
      int[] splits = new int[p + 1];
      double start = 0;
      for (int i = 0; i < splits.length; i++) {
         splits[i] = (int) start;
         start += n / p;
      }

      return splits;
   }

   public static int binarySearch(double[] buckets, double value) {
      int min = 0;
      int max = buckets.length;
      int mid = min + (max - min) / 2;
      while (mid != min) {
         if (buckets[mid] > value) {
            max = mid;
         } else {
            min = mid;
         }
         mid = min + (max - min) / 2;
      }

      if (buckets[mid] > value) {
         return mid;
      } else {
         return max;
      }
   }

   public static int binarySearch(double[] a, int min, int max, double value) {
      int mid = min + (max - min) / 2;
      while (mid != min) {
         if (a[mid] > value) {
            max = mid;
         } else {
            min = mid;
         }
         mid = min + (max - min) / 2;
      }

      if (a[mid] > value) {
         return mid;
      } else {
         return max;
      }
   }

   public static Link insertLink(Link head, double value) {
      Link iter = head;
      if (iter == null) {
         head = new Link(value);
      } else if (value < iter.value) {
         head = new Link(value, head);
      } else {
         while (iter.next != null && iter.next.value < value) {
            iter = iter.next;
         }
         iter.next = new Link(value, iter.next);
      }
      return head;
   }

   public static void heapify(PWayMerge[] heap, int heapSize, int i, double[] a) {
      int l = 2 * i;
      int r = l + 1;
      int smallest;
      if (l < heapSize && a[heap[l].index()] < a[heap[i].index()]) {
         smallest = l;
      } else {
         smallest = i;
      }
      if (r < heapSize && a[heap[r].index()] < a[heap[smallest].index()]) {
         smallest = r;
      }
      if (smallest != i) {
         PWayMerge temp = heap[i];
         heap[i] = heap[smallest];
         heap[smallest] = temp;

         heapify(heap, heapSize, smallest, a);
      }
   }

}
