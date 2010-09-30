package sort.partition;

/**
 * This interface specifies that the implementing class is capable of being used
 * as a partitioning scheme for quick sort.
 * 
 * @author Brian Norman : 4332223 : norma272@umn.edu
 * 
 */
public interface PartitioningScheme {

   /**
    * Partitions the array into a left sub-array and a right sub-array and
    * places the pivot between them. Everything that is greater then the pivot
    * value is placed in the right sub-array and everything less then the pivot
    * value is placed in the left sub-array. The new pivot index is returned.
    * 
    * @param a
    *           the array to partition
    * @param start
    *           the starting index of our array
    * @param end
    *           the last index of our array
    * @param pivotIndex
    *           the index where our pivot value is
    * @return the new pivot index
    */
   public int partition(double[] a, int start, int end, int pivotIndex, boolean increasing);

}
