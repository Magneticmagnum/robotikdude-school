package sort;

public class Mergesort implements SortingAlgorithm {

   @Override
   public void sort(int[] a) {
      recursive(a, 0, a.length - 1);
   }

   private void recursive(int[] a, int start, int end) {
      int mid = start + (end - start) / 2;
      if (mid != start)
         recursive(a, start, mid);
      if (mid != end)
         recursive(a, mid + 1, end);

      // combine
      int[] temp = new int[mid - start + 1];
      for (int i = 0; i < temp.length; i++)
         temp[i] = a[start + i];

      int i = start;
      int j = 0;
      int k = mid + 1;
      while (j < temp.length && k <= end) {
         if (a[k] < temp[j])
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
