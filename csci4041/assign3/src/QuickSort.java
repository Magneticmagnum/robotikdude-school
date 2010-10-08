import java.util.Random;


public class QuickSort implements SortingAlgorithm {

   private Random random;

   public QuickSort() {
      random = new Random(System.currentTimeMillis());
   }

   @Override
   public void sort(double[] a) { // , boolean increasing) {
      recusive(a, 0, a.length - 1); // , increasing);
   }

   private void recusive(double[] a, int start, int end) { // , boolean
                                                           // increasing) {
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
         recusive(a, start, pivotIndex - 1); // , increasing);
      if (end - pivotIndex > 1)
         recusive(a, pivotIndex + 1, end); // , increasing);

      // The combining is done automatically as this is an in place sort.
   }
}
