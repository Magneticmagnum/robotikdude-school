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

   // returns the splitting indexes for an array of size n
   public static int[] getSplitIndexes(double n, int p) {
      int[] splits = new int[p + 1];
      double start = 0;
      for (int i = 0; i < splits.length; i++) {
         splits[i] = (int) start;
         start += n / p;
      }

      return splits;
   }

   // returns the resulting index from a binary search into an array
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

   // returns the resulting index between min and max from a binary search into an array
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

   // inserts, using insertion sort, a Link into the head of a linked-list
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

   // heapify method from heap sort, taken from the book
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
