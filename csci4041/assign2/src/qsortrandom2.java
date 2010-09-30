import sort.QuickSort;
import sort.Utils;
import sort.partition.EndingsPartitioning;
import sort.pivot.RandomPivot;

public class qsortrandom2 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new RandomPivot(),
            new EndingsPartitioning()));
   }

}
