import sort.QuickSort;
import sort.Utils;
import sort.partition.BeginningPartitioning;
import sort.pivot.MedFiveRandomPivot;

public class qsort5median1 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new MedFiveRandomPivot(),
            new BeginningPartitioning()));
   }

}
