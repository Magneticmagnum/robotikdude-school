import java.util.Random;

// selects the median of five elements out of the list and returns that as the
// pivot
public class MedFiveRandomPivot implements PivotSelection {

   private Random random;

   public MedFiveRandomPivot() {
      random = new Random(System.currentTimeMillis());
   }

   @Override
   public int selectPivot(double[] a, int start, int end) {
      int[] pivots = new int[5];
      for (int i = 0; i < pivots.length; i++) {
         int newPivot = (int) Math.floor(random.nextDouble() * (end - start)
               + start);

         int j = 0;
         for (; j < i; j++) {
            if (a[pivots[j]] > a[newPivot]) {
               for (int k = i; k > j; k--) {
                  pivots[k] = pivots[k - 1];
               }
               break;
            }
         }
         pivots[j] = newPivot;
      }

      return pivots[2];
   }

}