// simple abstraction for a pivot selector
// used so I could reuse pivoting schemes
public interface PivotSelection {

   public int selectPivot(double[] a, int start, int end);

}
