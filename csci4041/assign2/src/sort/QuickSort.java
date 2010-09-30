package sort;

import sort.partition.PartitioningScheme;
import sort.pivot.PivotSelection;

public class QuickSort implements SortingAlgorithm {

   private PivotSelection     selector;
   private PartitioningScheme partitioner;

   public QuickSort(PivotSelection selector, PartitioningScheme partitioner) {
      this.selector = selector;
      this.partitioner = partitioner;
   }

   @Override
   public void sort(double[] a, boolean increasing) {
      recusive(a, 0, a.length - 1, increasing);
   }

   private void recusive(double[] a, int start, int end, boolean increasing) {
      // select a pivot
      int pivotIndex = selector.selectPivot(a, start, end);

      // create L and R sub-arrays
      pivotIndex = partitioner.partition(a, start, end, pivotIndex, increasing);

      // recursively call on L and R sub-arrays
      if (pivotIndex - start > 1)
         recusive(a, start, pivotIndex - 1, increasing);
      if (end - pivotIndex > 1)
         recusive(a, pivotIndex + 1, end, increasing);

      // The combining is done automatically as this is an in place sort.
   }

}
