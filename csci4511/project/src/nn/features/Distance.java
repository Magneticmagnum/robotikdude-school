package nn.features;

import nn.robot.RobotData;
import nn.utils.Utils;

public class Distance extends Feature {

   private int      nFeatures_;
   private double   minDist_;
   private double   maxDist_;

   private double[] distances_;

   private double   stdDev_;

   public Distance(int numberOfFeatures, double minDistance, double maxDistance) {
      nFeatures_ = numberOfFeatures;
      minDist_ = minDistance;
      maxDist_ = maxDistance;
      distances_ = new double[nFeatures_];

      double dDist = (maxDist_ - minDist_) / (nFeatures_ - 1);
      System.out.print("Distance Features: ");
      for (int i = 0; i < nFeatures_; i++) {
         distances_[i] = minDist_ + dDist * i;
         System.out.print(distances_[i] + ", ");
      }
      System.out.println();
      stdDev_ = dDist;
   }

   @Override
   public int getNumberOfFeatures() {
      return nFeatures_;
   }

   @Override
   public double[] getFeatures(RobotData view, RobotData reference) {
      double dist = Utils.dist(view.getX(), view.getY(), reference.getX(), reference.getY());
      double[] features = new double[nFeatures_];
      for (int i = 0; i < nFeatures_; i++) {
         features[i] = Math.exp(-Utils.sqr((dist - distances_[i]) / stdDev_));
      }
      return features;
   }
}
