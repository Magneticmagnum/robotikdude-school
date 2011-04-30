package nn.features;

import nn.graphics.RGraphics;
import nn.robot.RobotData;

public abstract class Feature {

   public abstract int getNumberOfFeatures();

   public abstract double[] getFeatures(RobotData view, RobotData reference);

   public void draw(RGraphics grid, RobotData view, RobotData reference, double startX, double startY, double height,
         double width) {
      double dx = width / (getNumberOfFeatures() - 1);

      double[] features = getFeatures(view, reference);

      double x = startX;
      double px = x;
      double py = startY + height * features[0];
      x += dx;
      for (int i = 1; i < features.length; i++) {
         grid.drawLine(px, py, x, startY + height * features[i]);
         px = x;
         py = startY + height * features[i];
         x += dx;
      }
   }

}
