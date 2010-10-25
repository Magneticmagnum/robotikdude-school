public class samplesort implements SortingAlgorithm {

   public static void main(String[] args) {
      samplesort sort = new samplesort();
      double[] array = {
            22, 7, 13, 18, 2, 17, 1, 14, 20, 6, 10, 24, 15, 9, 21, 3, 16, 19,
            23, 4, 11, 12, 5, 8
      };


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
      int n = a.length;
      int[] splits = getSplitIndexes(a.length, p);

      System.out.print("List: ");
      for (int i = 0; i < p; i++) {
         qsort.sort(a, splits[i], splits[i + 1] - 1);

         for (int j = splits[i]; j < splits[i + 1] - 2; j++) {
            System.out.print(a[j] + ", ");
         }
         System.out.print(a[splits[i + 1] - 1]
               + (splits[i + 1] < n ? " | " : ""));
      }
      System.out.println();

      System.out.print("Sample: ");
      double[] sample = new double[p * (p - 1)];
      int s = 0;
      for (int i = 0; i < p; i++) {
         double space = (double) (splits[i + 1] - splits[i]) / p;
         for (int j = 1; j < p; j++) {
            sample[s++] = a[(int) (splits[i] + j * space)];
            System.out.print(sample[s - 1] + (s < sample.length ? ", " : ""));
         }
      }
      System.out.println();

      qsort.sort(sample);


      double[] buckets = new double[p];
      double space = (double) sample.length / p;
      for (int i = 0; i < p - 1; i++) {
         buckets[i] = sample[(int) ((i + 1) * space)];
      }
      buckets[p - 1] = Double.POSITIVE_INFINITY;

      System.out.print("Buckets: ");
      for (int i = 0; i < buckets.length; i++) {
         System.out.print(buckets[i] + (i + 1 < buckets.length ? ", " : ""));
      }
      System.out.println();

      Link[] linkedBuckets = new Link[p];
      for (int i = 0; i < a.length; i++) {
         int j = binarySearch(buckets, a[i]);
         linkedBuckets[j] = insertLink(linkedBuckets[j], a[i]);
         // for (int j = 0; j < buckets.length; j++) {
         // if (a[i] < buckets[j]) {
         // Link l = new Link();
         // l.value = a[i];
         // linkedBuckets[j] = insertLink(linkedBuckets[j], l);
         // // System.out.println(j + ": " + binarySearch(buckets, a[i]));
         // break;
         // }
         // }
      }

      for (int i = 0; i < p; i++) {
         System.out.print("Bucket " + i + ": ");
         Link l = linkedBuckets[i];
         while (l != null) {
            System.out.print(l.value + ", ");
            l = l.next;
         }
         System.out.println();
      }

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
      System.out.print("Splits (" + length + ", " + p + ") : ");

      double n = length;
      double start = 0;
      for (int i = 0; i < splits.length; i++) {
         splits[i] = (int) start;
         System.out.print(splits[i] + ", ");
         start += n / p;
      }
      System.out.println();

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
