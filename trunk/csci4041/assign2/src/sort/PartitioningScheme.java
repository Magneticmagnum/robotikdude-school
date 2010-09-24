package sort;

public interface PartitioningScheme {

   /**
    * Partitions the array into a left sub-array and a right sub-array and places the pivot between them. Everything
    * that is greater then the pivot value is placed in the right sub-array and everything less then the pivot value is
    * placed in the left sub-array. The new pivot index is returned.
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
   public int partition(int[] a, int start, int end, int pivotIndex);

}
/**
 * <code>
 * partition(A, p, r)
 * x <- A[r]
 * i <- p - 1
 * for j <- p to r - 1
 *      do if A[j} <= x
 *              then i <- i + 1
 *                      exchange A[i] <-> A[j]
 * exchange A[i + 1} <-> A[r]
 * return i + 1
 * </code>
 */
