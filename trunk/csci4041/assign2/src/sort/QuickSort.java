package sort;

public class QuickSort implements SortingAlgorithm {

   private PivotSelection     selecter;
   private PartitioningScheme partitioner;

   public QuickSort(PivotSelection selector, PartitioningScheme partitioner) {
      this.selecter = selector;
      this.partitioner = partitioner;
   }

   @Override
   public void sort(int[] a) {
      recusive(a, 0, a.length - 1);
   }

   private void recusive(int[] a, int start, int end) {
      // select a pivot
      int pivotIndex = selecter.selectPivot(a, start, end);

      // create L and R sub-arrays
      pivotIndex = partitioner.partition(a, start, end, pivotIndex);

      // recursively call on L and R sub-arrays
      recusive(a, start, pivotIndex - 1);
      recusive(a, pivotIndex + 1, end);

      // The combining is done automatically as this is an in place sort.
   }

}
