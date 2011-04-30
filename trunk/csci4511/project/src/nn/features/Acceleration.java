package nn.features;

import nn.robot.RobotData;
import nn.utils.Utils;

public class Acceleration extends Feature {

	public Acceleration() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public int getNumberOfFeatures() {
		// TODO Auto-generated method stub
		return 3;
	}

	@Override
	public double[] getFeatures(RobotData view, RobotData reference) {
		// TODO Auto-generated method stub
		double dVel = view.getDeltaVelocity() * Utils.sign(view.getVelocity());
		if (dVel < 0) {
			return new double[] { 1, 0, 0 };
		} else if (dVel > 0) {
			return new double[] { 0, 0, 1 };
		} else {
			return new double[] { 0, 1, 0 };

		}
	}
}
