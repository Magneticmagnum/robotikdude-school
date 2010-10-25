public class smart implements SortingAlgorithm {

   public static void main(String[] args) {
      smart sort = new smart();
      double[] array = {
         22, 7, 13, 18, 2, 17, 1, 14, 20, 6, 10, 24, 15, 9, 21, 3, 16, 19, 23,
         4, 11, 12, 5, 8, 5, 2, 7, 21, 78, 3, 0, 6, 3, 1, 4, 7, 9, 4, 2, 1, 5,
         8, 3, 93, 8, 3, 4, 7, 3, 7, 5, 2 };


      System.out.print("List Before: ");
      for (int i = 0; i < array.length - 1; i++) {
         System.out.print(array[i] + ", ");
      }
      System.out.println(array[array.length - 1]);

      sort.sort(array, 3);

      System.out.print("List After: ");
      for (int i = 0; i < array.length - 1; i++) {
         System.out.print(array[i] + ", ");
      }
      System.out.println(array[array.length - 1]);
   }

   @Override
   public void sort(double[] a, int p) {
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


      // select p-1 elements from each n/p subarray and use a
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
      double[] bucketSplits = new double[p - 1];
      double space = ((double) sample.length) / p;
      for (int i = 0; i < p - 1; i++) {
         bucketSplits[i] = sample[(int) ((i + 1) * space)];
      }


      // place the bucket splitters into each n/p subarray
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


      // read each bucket back into the array
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
