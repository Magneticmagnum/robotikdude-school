package nn;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import nn.features.Acceleration;
import nn.features.AdvancingVelocity;
import nn.features.Distance;
import nn.features.Feature;
import nn.features.LateralVelocity;
import nn.graphics.DrawMenu;
import nn.graphics.RGraphics;
import nn.move.GunMovement;
import nn.move.RadarMovement;
import nn.robot.EnemyProfile;
import nn.robot.RobotData;
import nn.utils.Utils;
import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.DeathEvent;
import robocode.RobotDeathEvent;
import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.WinEvent;

public class Shooter extends AdvancedRobot {

   // private RobotMovement robot_;
   private GunMovement         gun_;
   private RadarMovement       radar_;

   private static RobotData    enemy_;
   private static EnemyProfile profile_;

   // private RobotManager robots_;


   private Distance            distance          = new Distance(10, 100, 1000);
   private AdvancingVelocity   advancingVelocity = new AdvancingVelocity(17);
   private Acceleration        acceleration      = new Acceleration();
   private LateralVelocity     lateralVelocity   = new LateralVelocity(9);

   @Override
   public void run() {
      DrawMenu.load(getDataFile("menu.draw"));
      if (getOthers() > 1) {
         out.println("ERROR: Can only have one enemy robot!");
         return;
      }

      // robots_ = RobotManager.getInstance(this);
      gun_ = new GunMovement(this);
      radar_ = new RadarMovement(this);
      if (profile_ != null)
         profile_.update(this);

      while (true) {
         radar_.setSweep(enemy_, 20.0);

         double angle = getGunHeading();

         if (profile_ != null) {
            double[] data = profile_.getOutput();

            double[] sum = new double[data.length];
            for (int i = 0; i < sum.length; i++) {
               int b = Utils.limit(0, i - 1, data.length - 1);
               int a = Utils.limit(0, i + 1, data.length - 1);
               sum[i] = 0.2 * data[b] + 0.6 * data[i] + 0.2 * data[a];
            }

            double max = Double.NEGATIVE_INFINITY;
            int index = -1;
            for (int i = 0; i < sum.length; i++) {
               if (sum[i] > max) {
                  max = data[i];
                  index = i;
               }
            }
            angle = Utils.angle(getX(), getY(), enemy_.getX(), enemy_.getY())
                  + Utils.getAngleOffset(this, enemy_, Utils.getGuessFactor(index, data.length), 3.0);
         }

         gun_.setTurnTo(angle);
         setFire(3.0);
         execute();
      }
   }

   @Override
   public void setFire(double power) {
      if (enemy_ != null && !enemy_.isDead() && getGunTurnRemaining() < 2.0) {
         // Fire power range is from 0.1 to 3.0 unless the robots energy is less than 3.0.
         // In that case, the fire power is the robots energy level.
         power = Utils.limit(Rules.MIN_BULLET_POWER, power, Math.min(getEnergy(), Rules.MAX_BULLET_POWER));
         Bullet b = super.setFireBullet(power);
         profile_.fire(b, power);
      }
   }

   @Override
   public void onPaint(Graphics2D g) {
      RGraphics grid = new RGraphics(g, this);
      DrawMenu.draw(grid);
      if (enemy_ != null)
         enemy_.draw(grid);
      if (profile_ != null)
         profile_.draw(grid);

      grid.setColor(Color.RED);
      distance.draw(grid, enemy_, new RobotData(this), 20, 20, 20, 150);

      grid.setColor(Color.GREEN);
      advancingVelocity.draw(grid, enemy_, new RobotData(this), 200, 20, 20, 100);

      grid.setColor(Color.YELLOW);
      acceleration.draw(grid, enemy_, new RobotData(this), 320, 20, 20, 30);

      grid.setColor(Color.RED);
      lateralVelocity.draw(grid, enemy_, new RobotData(this), 370, 20, 20, 50);

   }

   @Override
   public void onMouseClicked(MouseEvent e) {
      DrawMenu.inMouseEvent(e);
   }

   @Override
   public void onScannedRobot(ScannedRobotEvent event) {
      if (enemy_ == null) {
         enemy_ = new RobotData(event, this);
         profile_ = new EnemyProfile(enemy_, this, new Feature[] { distance, advancingVelocity, acceleration,
               lateralVelocity }, 31);
      } else {
         enemy_.update(event, this);
      }
      // robots_.inEvent(event);
   }

   @Override
   public void onRobotDeath(RobotDeathEvent event) {
      enemy_.setDeath();
      // robots_.inEvent(event);
   }

   @Override
   public void onDeath(DeathEvent event) {
      enemy_.setDeath();
      // robots_.inEvent(event);
      DrawMenu.save(getDataFile("menu.draw"));
   }

   @Override
   public void onWin(WinEvent event) {
      enemy_.setDeath();
      // robots_.inEvent(event);
      DrawMenu.save(getDataFile("menu.draw"));
   }

}
