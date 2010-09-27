package sort;


public class EndsPartitioning implements PartitioningScheme {

   @Override
   public int partition(double[] a, int start, int end, int pivotIndex) {
      double pivotValue = a[pivotIndex];
      Utils.swap(a, pivotIndex, end);

      int i = start;
      int j = end;
      while (i < j) {
         while (a[i] < pivotValue && i < j)
            i++;
         while (a[j] >= pivotValue && i < j)
            j--;
         if (i < j)
            Utils.swap(a, i, j);
      }

      Utils.swap(a, j, end);
      return j;
   }

}
