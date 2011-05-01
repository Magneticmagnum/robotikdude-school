package nn.features;

import nn.robot.RobotData;
import nn.utils.Utils;

public class LateralVelocity extends Feature {
	private int nFeatures;
	private double[] velocities;
	private double minLat = 0;
	private double maxLat = 8;
	private double std;

	public LateralVelocity(int features) {
		nFeatures = features;
		velocities = new double[nFeatures];
		double dVel = (maxLat - minLat) / (nFeatures - 1);
		for (int i = 0; i < nFeatures; i++) {
			velocities[i] = maxLat + dVel * i;
		}
		std = Utils.sqr(dVel * dVel);

	}

	@Override
	public int getNumberOfFeatures() {
		return nFeatures;
	}

	@Override
	public double[] getFeatures(RobotData view, RobotData reference) {
		double eAbsBear = Utils.angle(reference, view);
		double enemyLat = view.getVelocity()
				* Utils.sin(view.getHeading() - eAbsBear);
		double[] features = new double[nFeatures];
		for (int i = 0; i < nFeatures; i++) {
			features[i] = Math.exp(-Utils.sqr(enemyLat - velocities[i]) / std);
		}
		return features;
	}
}
