import java.util.Random;


public class QuickSort {

   private Random random;

   public QuickSort() {
      random = new Random(System.currentTimeMillis());
   }

   public void sort(double[] a) {
      sort(a, 0, a.length - 1);
   }

   public void sort(double[] a, int start, int end) {
      // select a pivot
      int pivotIndex = (int) (random.nextDouble() * (end - start) + start);

      // create L and R sub-arrays
      double pivotValue = a[pivotIndex];

      double temp = a[pivotIndex];
      a[pivotIndex] = a[end];
      a[end] = temp;

      int i = start;
      for (int j = start; j <= end - 1; j++) {
         if (a[j] < pivotValue) {
            // if ((increasing && a[j] <= pivotValue)
            // || (!increasing && a[j] > pivotValue)) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
         }
      }

      pivotIndex = i;

      temp = a[pivotIndex];
      a[pivotIndex] = a[end];
      a[end] = temp;


      // recursively call on L and R sub-arrays
      if (pivotIndex - start > 1)
         sort(a, start, pivotIndex - 1); // , increasing);
      if (end - pivotIndex > 1)
         sort(a, pivotIndex + 1, end); // , increasing);

      // The combining is done automatically as this is an in place sort.
   }
}
