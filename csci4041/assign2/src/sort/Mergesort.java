package sort;

public class Mergesort implements SortingAlgorithm {

   @Override
   public void sort(double[] a, boolean increasing) {
      recursive(a, 0, a.length - 1, increasing);
   }

   private void recursive(double[] a, int start, int end, boolean increasing) {
      int mid = start + (end - start) / 2;
      if (mid != start)
         recursive(a, start, mid, increasing);
      if (mid != end)
         recursive(a, mid + 1, end, increasing);

      // combine
      double[] temp = new double[mid - start + 1];
      for (int i = 0; i < temp.length; i++)
         temp[i] = a[start + i];

      int i = start;
      int j = 0;
      int k = mid + 1;
      while (j < temp.length && k <= end) {
         if ((increasing && a[k] < temp[j]) || (!increasing && a[k] > temp[j]))
            a[i++] = a[k++];
         else
            a[i++] = temp[j++];
      }
      if (j == temp.length) {
         while (k <= end)
            a[i++] = a[k++];
      } else {
         while (j < temp.length)
            a[i++] = temp[j++];
      }
   }
}
