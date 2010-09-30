import sort.QuickSort;
import sort.Utils;
import sort.partition.BeginningPartitioning;
import sort.pivot.MedThreeRandomPivot;

public class qsort3median1 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new MedThreeRandomPivot(),
            new BeginningPartitioning()));
   }

}
