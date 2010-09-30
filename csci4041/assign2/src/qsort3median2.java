import sort.QuickSort;
import sort.Utils;
import sort.partition.EndingsPartitioning;
import sort.pivot.MedThreeRandomPivot;

public class qsort3median2 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new MedThreeRandomPivot(),
            new EndingsPartitioning()));
   }

}
