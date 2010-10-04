// simple abstraction for a partitioning scheme
// used so I could reuse partitioning schemes
public interface PartitioningScheme {

   public int partition(double[] a, int start, int end, int pivotIndex,
         boolean increasing);

}
