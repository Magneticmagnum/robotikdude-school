package sort.partition;

public class BeginningPartitioning implements PartitioningScheme {

   @Override
   public int partition(double[] a, int start, int end, int pivotIndex,
         boolean increasing) {
      double pivotValue = a[pivotIndex];

      double temp = a[pivotIndex];
      a[pivotIndex] = a[end];
      a[end] = temp;

      int i = start - 1;
      for (int j = start; j <= end - 1; j++) {
         if ((increasing && a[j] <= pivotValue)
               || (!increasing && a[j] > pivotValue)) {
            i++;

            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
         }
      }

      temp = a[i + 1];
      a[i + 1] = a[end];
      a[end] = temp;

      return i + 1;
   }

}
