package sort;

import java.util.Random;

public class RandomPivot implements PivotSelection {
	
	private Random random;
	
	public RandomPivot() {
		random = new Random(System.currentTimeMillis());
	}

	@Override
	public int selectPivot(int[] a, int start, int end) {
		return (int) Math.floor(random.nextDouble() * (end - start) + start);
	}

}
