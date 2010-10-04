import java.util.Random;

// selects a random element out of the list and returns that as the pivot
public class RandomPivot implements PivotSelection {

   private Random random;

   public RandomPivot() {
      random = new Random(System.currentTimeMillis());
   }

   @Override
   public int selectPivot(double[] a, int start, int end) {
      return (int) Math.floor(random.nextDouble() * (end - start) + start);
   }

}
