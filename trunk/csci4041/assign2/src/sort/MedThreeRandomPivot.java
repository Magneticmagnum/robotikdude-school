package sort;

import java.util.Random;

public class MedThreeRandomPivot implements PivotSelection {

	private Random random;

	public MedThreeRandomPivot() {
		random = new Random(System.currentTimeMillis());
	}

	@Override
	public int selectPivot(int[] a, int start, int end) {
		int i1 = (int) Math.floor(random.nextDouble() * (end - start) + start);
		int i2 = (int) Math.floor(random.nextDouble() * (end - start) + start);
		int i3 = (int) Math.floor(random.nextDouble() * (end - start) + start);

		int min = Math.min(Math.min(a[i1], a[i2]), a[i3]);
		int max = Math.max(Math.max(a[i1], a[i2]), a[i3]);

		if (a[i1] != min && a[i1] != max) {
			return i1;
		} else if (a[i2] != min && a[i2] != max) {
			return i2;
		} else {
			return i3;
		}
	}

}
