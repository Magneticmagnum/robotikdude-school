// starts on the ends of the sub list and iterates toward the center and swaps
// elements as needed
public class EndingsPartitioning implements PartitioningScheme {

   @Override
   public int partition(double[] a, int start, int end, int pivotIndex,
         boolean increasing) {
      double pivotValue = a[pivotIndex];

      double temp = a[pivotIndex];
      a[pivotIndex] = a[end];
      a[end] = temp;

      int i = start;
      int j = end;
      while (i < j) {
         while (((increasing && a[i] < pivotValue) || (!increasing && a[i] > pivotValue))
               && i < j)
            i++;
         while (((increasing && a[j] >= pivotValue) || (!increasing && a[j] <= pivotValue))
               && i < j)
            j--;
         if (i < j) {
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
         }
      }

      temp = a[j];
      a[j] = a[end];
      a[end] = temp;

      return j;
   }

}
