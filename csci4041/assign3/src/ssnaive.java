import java.io.File;

/**
 * CSci4041 F2010 Assignment 3
 * section: 3
 * login: norma272
 * date: 10/25/10
 * name: Brian Norman
 * id: 4332223
 */
public class ssnaive {

   public static void main(String[] args) {
      ssnaive sorter = new ssnaive();

      File inFile;
      File outFile;
      int heapSize;
      double[] list;

      // **********************************************************************
      // start argument parsing
      // **********************************************************************
      if (args.length == 3) {
         inFile = new File(args[0]);
         if (!inFile.canRead()) {
            System.out
                  .println("ERROR: could not open the specified input file.");
            Utils.help("naive");
            return;
         }
         outFile = new File(args[1]);
         if (!outFile.canRead()) {
            System.out
                  .println("ERROR: could not open the specified output file.");
            Utils.help("naive");
            return;
         }
         try {
            heapSize = Integer.parseInt(args[2].trim());
         } catch (NumberFormatException e1) {
            Utils.help("naive");
            return;
         }
      } else {
         Utils.help("naive");
         return;
      }
      // **********************************************************************

      // either create or read the list
      list = Utils.read(inFile);

      int p = heapSize / list.length;

      // start timing and run the sort on the given list
      long stime = System.currentTimeMillis();
      sorter.sort(list, p);
      System.out.println("Time taken: " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");

      // write back out if read from a file
      Utils.write(outFile, list);
   }



   public void sort(double[] a, int p) {
      QuickSort qsort = new QuickSort();

      
      long stime = System.currentTimeMillis();
      // split the array into p subarrays and sort them
      // size : n/p
      int[] splits = Utils.getSplitIndexes(a.length, p);
      for (int i = 0; i < p; i++) {
         qsort.sort(a, splits[i], splits[i + 1] - 1);
      }
      System.out.println("Time taken (sorting n/p): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");


      stime = System.currentTimeMillis();
      // select p-1 elements from each subarray and place
      // them into a separate array, sort that array
      // size : 2*p^2
      double[] sample = new double[p * (p - 1)];
      int s = 0;
      for (int i = 0; i < p; i++) {
         double space = (double) (splits[i + 1] - splits[i]) / p;
         for (int j = 1; j < p; j++) {
            sample[s++] = a[(int) (splits[i] + j * space)];
         }
      }
      qsort.sort(sample);

      
      // select p-1 elements from that separate array
      // size : 2*p^2 + p
      double[] buckets = new double[p];
      double space = (double) sample.length / p;
      for (int i = 0; i < p - 1; i++) {
         buckets[i] = sample[(int) ((i + 1) * space)];
      }
      buckets[p - 1] = Double.POSITIVE_INFINITY;
      System.out.println("Time taken (sample): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");


      stime = System.currentTimeMillis();
      // place each element from the array into the
      // appropriate bucket using binary search
      // size : n
      Link[] linkedBuckets = new Link[p];
      for (int i = 0; i < a.length; i++) {
         int j = Utils.binarySearch(buckets, a[i]);
         linkedBuckets[j] = Utils.insertLink(linkedBuckets[j], a[i]);
      }
      System.out.println("Time taken (buckets): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");
      

      // read each bucket back into the array
      // size : n
      int i = 0;
      for (int bucket = 0; bucket < buckets.length; bucket++) {
         Link l = linkedBuckets[bucket];
         while (l != null) {
            a[i++] = l.value;
            l = l.next;
         }
      }

   }

}
