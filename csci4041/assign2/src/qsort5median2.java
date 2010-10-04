/* 
 * CSci4041 F2010 Assignment 2
 * section: 3
 * login: norma272
 * date: 10/4/19
 * name: Brian E Norman
 * id: 4332223
 */


public class qsort5median2 implements SortingAlgorithm {

   public static void main(String[] args) {
      // pass the the hard work off to a separate function
      Utils.runSort("qsort5median2", args, new qsort5median2());
   }


   // *************************************************************************
   // The following is the actual sorting method for this program
   // *************************************************************************

   // pivoting scheme has been abstracted for reusability
   private PivotSelection     selector    = new MedFiveRandomPivot();

   // partitioning scheme has been abstracted for reusability
   private PartitioningScheme partitioner = new EndingsPartitioning();

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
