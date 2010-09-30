package sort;

public class Heapsort implements SortingAlgorithm {

   @Override
   public void sort(double[] a, boolean increasing) {
      buildHeap(a, increasing);
      int heapSize = a.length;
      for (int i = a.length - 1; i >= 1; i--) {

         double temp = a[0];
         a[0] = a[i];
         a[i] = temp;

         heapSize--;
         heapify(a, heapSize, 0, increasing);
      }
   }

   private void buildHeap(double[] a, boolean increasing) {
      for (int i = (a.length - 1) / 2; i >= 0; i--) {
         heapify(a, a.length, i, increasing);
      }
   }

   private void heapify(double[] a, int heapSize, int i, boolean increasing) {
      int l = 2 * i;
      int r = l + 1;
      int largest;
      if (l < heapSize
            && ((increasing && a[l] > a[i]) || (!increasing && a[l] < a[i]))) {
         largest = l;
      } else {
         largest = i;
      }
      if (r < heapSize
            && ((increasing && a[r] > a[largest]) || (!increasing && a[r] < a[largest]))) {
         largest = r;
      }
      if (largest != i) {
         double temp = a[i];
         a[i] = a[largest];
         a[largest] = temp;

         heapify(a, heapSize, largest, increasing);
      }
   }

}
