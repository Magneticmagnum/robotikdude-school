import sort.QuickSort;
import sort.Utils;
import sort.partition.EndingsPartitioning;
import sort.pivot.MedFiveRandomPivot;

public class qsort5median2 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new MedFiveRandomPivot(),
            new EndingsPartitioning()));
   }

}
