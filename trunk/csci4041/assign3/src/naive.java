public class naive implements SortingAlgorithm {

   public static void main(String[] args) {
   }



   @Override
   public void sort(double[] a, int p) {
      QuickSort qsort = new QuickSort();

      // split the array into p subarrays and sort them
      int[] splits = getSplitIndexes(a.length, p);
      for (int i = 0; i < p; i++) {
         qsort.sort(a, splits[i], splits[i + 1] - 1);
      }

      // select p-1 elements from each subarray and place
      // them into a separate array, sort that array
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
         int j = binarySearch(buckets, a[i]);
         linkedBuckets[j] = insertLink(linkedBuckets[j], a[i]);
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

   private int[] getSplitIndexes(int length, int p) {
      int[] splits = new int[p + 1];

      double n = length;
      double start = 0;
      for (int i = 0; i < splits.length; i++) {
         splits[i] = (int) start;
         start += n / p;
      }

      return splits;
   }

   private int binarySearch(double[] buckets, double value) {
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

   private Link insertLink(Link head, double value) {
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

}
