import java.io.File;

/**
 * CSci4041 F2010 Assignment 3
 * section: 3
 * login: norma272
 * date: 10/25/10
 * name: Brian Norman
 * id: 4332223
 */
public class sssmart {

   public static void main(String[] args) {
      sssmart sorter = new sssmart();

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

      // **********************************************************************
      // Newtons method for finding roots
      // **********************************************************************
      // 4p^2 + 2n/p == heapSize => 4p^3 - heapSize*p + 2n == 0
      int p = 10000; // pick somewhere to start
      double eps = .01, d, f_p, fprime_p;
      // 4p^3 - heapSize*p + 2n
      f_p = 4 * p * p * p - heapSize * p + 2 * list.length;
      for (int i = 0; i < 100; i++) {
         // 12p^2 - heapSize
         fprime_p = 12 * p * p - heapSize;
         d = f_p / fprime_p;
         p -= d;
         // 4p^3 - heapSize*p + 2n
         f_p = 4 * p * p * p - heapSize * p + 2 * list.length;
         if (Math.abs(d) < eps) {
            break;
         }
      }
      // **********************************************************************
      System.out.println("Using a p value of: " + p);

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
      // size : n/p + 4*p
      PWayMerge[] ways = new PWayMerge[p];
      int[] splits = Utils.getSplitIndexes(a.length, p);
      for (int i = 0; i < p; i++) {
         qsort.sort(a, splits[i], splits[i + 1] - 1);
         ways[i] = new PWayMerge(splits[i], splits[i + 1] - 1);
         ways[i].spacing = (double) (splits[i + 1] - splits[i]) / p;
         ways[i].i = 1;
      }
      System.out.println("Time taken (sorting n/p): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");


      stime = System.currentTimeMillis();
      // select p-1 elements from each n/p subarray and use a
      // p-way merge to sort them into separate array
      // size : 4*p + p^2
      double[] sample = new double[p * (p - 1)];
      // build the heap
      for (int i = (ways.length - 1) / 2; i >= 0; i--) {
         Utils.heapify(ways, ways.length, i, a);
      }
      // merge the the subarrays into the separate array
      int heapSize = ways.length;
      for (int i = 0; i < sample.length; i++) {
         sample[i] = a[ways[0].index()];
         ways[0].i++;
         if (ways[0].index() > ways[0].end) {
            ways[0] = ways[heapSize - 1];
            heapSize--;
         }
         Utils.heapify(ways, heapSize, 0, a);
      }


      // select p-1 elements from that separate array
      // size : p^2 + p
      double[] bucketSplits = new double[p - 1];
      double space = ((double) sample.length) / p;
      for (int i = 0; i < p - 1; i++) {
         bucketSplits[i] = sample[(int) ((i + 1) * space)];
      }
      System.out.println("Time taken (sample): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");


      stime = System.currentTimeMillis();
      // place the bucket splitters into each n/p subarray
      // size : p + n/p + 4p^2
      PWayMerge[][] buckets = new PWayMerge[p][p];
      for (int i = 0; i < p; i++) {
         int privious = splits[i];
         for (int j = 0; j < p - 1; j++) {
            int next = Utils.binarySearch(a, splits[i], splits[i + 1] - 1,
                  bucketSplits[j]);

            if (next == privious) {
               System.out.println("ERROR");
               return;
            }

            buckets[j][i] = new PWayMerge(privious, next - 1);
            privious = next;
         }
         buckets[p - 1][i] = new PWayMerge(privious, splits[i + 1] - 1);
      }


      // place each element from the array into the
      // appropriate bucket using p-way merge
      // size : 4p^2 + 2n/p
      Link[] linkedBuckets = new Link[p];
      for (int i = 0; i < p; i++) {
         PWayMerge[] b = buckets[i];
         // build the heap
         for (int j = (b.length - 1) / 2; j >= 0; j--) {
            Utils.heapify(b, b.length, j, a);
         }
         // merge the the subarrays into the separate array
         int bheapSize = b.length;
         while (bheapSize > 0) {
            linkedBuckets[i] = new Link(a[b[0].index()], linkedBuckets[i]);
            b[0].i++;
            if (b[0].index() > b[0].end) {
               b[0] = b[bheapSize - 1];
               bheapSize--;
            }
            Utils.heapify(b, bheapSize, 0, a);
         }
      }
      System.out.println("Time taken (buckets): " + (System.currentTimeMillis() - stime)
            / 100.0 + " secs");


      // read each bucket back into the array
      // size : 2n/p
      int i = a.length - 1;
      for (int b = p - 1; b >= 0; b--) {
         Link l = linkedBuckets[b];
         while (l != null) {
            a[i--] = l.value;
            l = l.next;
         }
      }

   }
}
