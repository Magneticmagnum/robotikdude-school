package nn.features;

import nn.robot.RobotData;
import nn.utils.Utils;

public class AdvancingVelocity extends Feature {
   private int      nFeatures;
   private double[] velocities;
   private double   minLat = -8;
   private double   maxLat = 8;
   private double   std;

   public AdvancingVelocity(int features) {
      nFeatures = features;
      velocities = new double[nFeatures];
      double dVel = (maxLat - minLat) / (nFeatures - 1);
      for (int i = 0; i < nFeatures; i++) {
         velocities[i] = minLat + dVel * i;
      }
      std = dVel;
   }

   @Override
   public int getNumberOfFeatures() {
      return nFeatures;
   }

   @Override
   public double[] getFeatures(RobotData view, RobotData reference) {
      double absAnlge = Utils.angle(reference, view);
      double advVelocity = -Utils.cos(view.getHeading() - absAnlge) * view.getVelocity();
      double[] features = new double[nFeatures];
      for (int i = 0; i < nFeatures; i++) {
         features[i] = Math.exp(-Utils.sqr(advVelocity - velocities[i]) / std);
      }
      return features;
   }
}
