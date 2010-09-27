package sort;

public class Heapsort implements SortingAlgorithm {

   @Override
   public void sort(int[] a) {
      buildMaxHeap(a);
      int heapSize = a.length;
      for (int i = a.length - 1; i >= 1; i--) {
         Utils.swap(a, 0, i);
         heapSize--;
         maxHeapify(a, heapSize, 0);
      }
   }

   private void buildMaxHeap(int[] a) {
      for (int i = (a.length - 1) / 2; i >= 0; i--) {
         maxHeapify(a, a.length, i);
      }
   }

   private void maxHeapify(int[] a, int heapSize, int i) {
      int l = left(i);
      int r = right(i);
      int largest;
      if (l < heapSize && a[l] > a[i]) {
         largest = l;
      } else {
         largest = i;
      }
      if (r < heapSize && a[r] > a[largest]) {
         largest = r;
      }
      if (largest != i) {
         Utils.swap(a, i, largest);
         maxHeapify(a, heapSize, largest);
      }
   }

   private int left(int i) {
      return 2 * i;
   }

   private int right(int i) {
      return 2 * i + 1;
   }

}
