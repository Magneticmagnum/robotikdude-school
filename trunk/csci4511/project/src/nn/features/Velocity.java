package nn.features;

import nn.robot.RobotData;
import nn.utils.Utils;

public class Velocity extends Feature {

   private int      nFeatures_;
   private double   minVel_;
   private double   maxVel_;

   private double[] velocities_;

   private double   stdDev_;

   public Velocity(int numberOfFeatures) {
      nFeatures_ = numberOfFeatures;
      minVel_ = 0;
      maxVel_ = 8;
      velocities_ = new double[nFeatures_];

      double dVel = (maxVel_ - minVel_) / (nFeatures_ - 1);
      for (int i = 0; i < nFeatures_; i++) {
         velocities_[i] = minVel_ + dVel * i;
      }
      stdDev_ = dVel;
   }

   @Override
   public int getNumberOfFeatures() {
      return nFeatures_;
   }

   @Override
   public double[] getFeatures(RobotData view, RobotData reference) {
      double velocity = Utils.absolute(view.getVelocity());
      double[] features = new double[nFeatures_];
      for (int i = 0; i < nFeatures_; i++) {
         features[i] = Math.exp(-Utils.sqr(velocity - velocities_[i]) / stdDev_);
      }
      return features;
   }
}
