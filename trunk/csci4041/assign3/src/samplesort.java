public class samplesort implements SortingAlgorithm {

   public static void main(String[] args) {
      samplesort sort = new samplesort(3);
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

   public samplesort(int p) {
      this.p = p;
   }

   @Override
   public void sort(double[] a) {
      QuickSort qsort = new QuickSort();
      int n = a.length;
      int[] splits = getSplitIndexes(a.length);

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
      double space = sample.length / p;
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
         for (int j = 0; j < buckets.length; j++) {
            if (a[i] < buckets[j]) {
               Link l = new Link();
               l.value = a[i];
               linkedBuckets[j] = insertLink(linkedBuckets[j], l);
               break;
            }
         }
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

   private int[] getSplitIndexes(int length) {
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

   private int binarySearch(double[] buckets, int value) {
      int min = 0;
      int max = buckets.length;
      int mid = (min + max) / 2;
      while (mid != min) {
         
      }

      return 0;
   }

   private Link insertLink(Link head, Link l) {
      Link iter = head;
      if (iter == null) {
         head = l;
      } else if (l.value < iter.value) {
         l.next = head;
         head = l;
      } else {
         while (iter.next != null && iter.next.value < l.value) {
            iter = iter.next;
         }
         l.next = iter.next;
         iter.next = l;
      }
      return head;
   }

   private class Link {
      Link next;
      double value;
   }
}
