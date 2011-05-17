package nn.features;

import nn.graphics.RGraphics;
import nn.robot.RobotData;

public abstract class Feature {

   public abstract int getNumberOfFeatures();

   public abstract double[] getFeatures(RobotData view, RobotData reference);

   public void draw(RGraphics grid, RobotData view, RobotData reference, double startX, double startY, double width,
         double height) {
      double dx = width / (getNumberOfFeatures() - 1);

      double[] features = getFeatures(view, reference);

      double px = startX;
      double py = startY + height * features[0];

      double x, y;
      for (int i = 1; i < features.length; i++) {
         x = px + dx;
         y = startY + height * features[i];
         grid.drawLine(px, py, x, y);
         px = x;
         py = y;
      }
   }

}
