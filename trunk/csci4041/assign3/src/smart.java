public class smart implements SortingAlgorithm {

   public static void main(String[] args) {
      smart sort = new smart(3);
      double[] array = {
            22, 7, 13, 18, 2, 17, 1, 14, 20, 6, 10, 24, 15, 9, 21, 3, 16, 19,
            23, 4, 11, 12, 5, 8
      };


      System.out.print("List Before: ");
      for (int i = 0; i < array.length - 1; i++) {
         System.out.print(array[i] + ", ");
      }
      System.out.println(array[array.length - 1]);

      sort.sort(array);

      System.out.print("List After: ");
      for (int i = 0; i < array.length - 1; i++) {
         System.out.print(array[i] + ", ");
      }
      System.out.println(array[array.length - 1]);
   }


   private int p;

   public smart(int p) {
      this.p = p;
   }

   @Override
   public void sort(double[] a) {
      QuickSort qsort = new QuickSort();


      // split the array into p subarrays and sort them
      PWayMerge[] ways = new PWayMerge[p];
      int[] splits = Utils.getSplitIndexes(a.length, p);
      for (int i = 0; i < p; i++) {
         qsort.sort(a, splits[i], splits[i + 1] - 1);
         ways[i] = new PWayMerge(splits[i], splits[i + 1] - 1);
         ways[i].spacing = (double) (splits[i + 1] - splits[i]) / p;
         ways[i].i = 1;
      }


      // select p-1 elements from each subarray and use a
      // p-way merge to sort them into separate array
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
      double[] buckets = new double[p];
      double space = (double) sample.length / p;
      for (int i = 0; i < p - 1; i++) {
         buckets[i] = sample[(int) ((i + 1) * space)];
      }
      buckets[p - 1] = Double.POSITIVE_INFINITY;


      // place each element from the array into the
      // appropriate bucket using binary search
      Link[] linkedBuckets = new Link[p];
      for (int i = 0; i < a.length; i++) {
         int j = Utils.binarySearch(buckets, a[i]);
         linkedBuckets[j] = Utils.insertLink(linkedBuckets[j], a[i]);
      }


      // read each bucket back into the array
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
