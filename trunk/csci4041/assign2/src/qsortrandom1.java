import sort.QuickSort;
import sort.Utils;
import sort.partition.BeginningPartitioning;
import sort.pivot.RandomPivot;

public class qsortrandom1 {

   public static void main(String[] args) {
      Utils.runSort("hsort", args, new QuickSort(new RandomPivot(),
            new BeginningPartitioning()));
   }

}
