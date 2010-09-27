package sort;


public class BeginningPartitioning implements PartitioningScheme {

   @Override
   public int partition(double[] a, int start, int end, int pivotIndex) {
      double pivotValue = a[pivotIndex];
      Utils.swap(a, pivotIndex, end);

      int i = start - 1;
      for (int j = start; j <= end - 1; j++) {
         if (a[j] <= pivotValue) {
            i++;
            Utils.swap(a, i, j);
         }
      }
      Utils.swap(a, i + 1, end);

      return i + 1;
   }

}
