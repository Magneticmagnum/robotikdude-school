package sort.pivot;

/**
 * This interfaces specifies that the implementing class is capable of being
 * used as a pivot selector for quick sort.
 * 
 * @author Brian : 4332223 : norma272@umn.edu
 * 
 */
public interface PivotSelection {

   /**
    * Returns a pivot index from the sub-array that starts at start and ends at
    * end in the array a.
    * 
    * @param a
    *           the full array to find the pivot in
    * @param start
    *           the starting index of the sub-array
    * @param end
    *           the ending index of the sub-array
    * @return the pivot index from the sub array
    */
   public int selectPivot(double[] a, int start, int end);

}
