package nn.virtual;

import nn.graphics.RGraphics;
import nn.robot.RobotData;
import nn.utils.Utils;
import robocode.Bullet;
import robocode.Robot;

// TODO documentation: class

/**
 * @author Brian Norman
 * @version 0.0.1 beta
 */
public class DataWave<E> extends VirtualWave {

   private static final long serialVersionUID = 4650614154195009930L;

   protected E[]             data;
   protected RobotData       view;
   protected RobotData       reference;

   public DataWave(double startX, double startY, double heading, double firePower, long creationTime, E[] data,
         RobotData view, RobotData reference) {
      super(startX, startY, heading, firePower, creationTime);
      init(data, view, reference);
   }

   public DataWave(Bullet bullet, RobotData firer, RobotData target, E[] data, RobotData view, RobotData reference) {
      super(firer.getX(), firer.getY(), Utils.angle(firer.getX(), firer.getY(), target.getX(), target.getY()), bullet
            .getPower(), firer.getTime());
      init(data, view, reference);
   }

   public DataWave(RobotData firer, RobotData target, double firePower, E[] data, RobotData view, RobotData reference) {
      super(firer.getX(), firer.getY(), Utils.angle(firer.getX(), firer.getY(), target.getX(), target.getY()),
            firePower, firer.getTime());
      init(data, view, reference);
   }

   public DataWave(Robot firer, RobotData target, double firePower, E[] data, RobotData view, RobotData reference) {
      super(firer.getX(), firer.getY(), Utils.angle(firer.getX(), firer.getY(), target.getX(), target.getY()),
            firePower, firer.getTime());
      init(data, view, reference);
   }

   private void init(E[] data, RobotData view, RobotData reference) {
      this.data = data;
      this.view = view;
      this.reference = reference;
   }

   public E[] getData() {
      return data;
   }

   public RobotData getView() {
      return view;
   }

   public RobotData getReference() {
      return reference;
   }

   public void draw(RGraphics grid) {
      super.draw(grid);
   }

}