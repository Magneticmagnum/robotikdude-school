package nn;

import java.awt.Color;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import nn.features.Distance;
import nn.features.Velocity;
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

   private RobotData           enemy_;
   private static EnemyProfile profile_;

   // private RobotManager robots_;


   private Distance            distance = new Distance(10, 100, 1000);
   private Velocity            velocity = new Velocity(9, -8, 8);

   @Override
   public void run() {
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
         gun_.setTurnTo(enemy_);
         setFire(3.0);
         execute();
      }
   }

   @Override
   public void setFire(double power) {
      if (enemy_ != null && !enemy_.isDead() && getGunTurnRemaining() < 1.0) {
         // Fire power range is from 0.1 to 3.0 unless the robots energy is less than 3.0.
         // In that case, the fire power is the robots energy level.
         power = Utils.limit(Rules.MIN_BULLET_POWER, power, Math.min(getEnergy(), Rules.MAX_BULLET_POWER));
         Bullet b = super.setFireBullet(power);
         if (b != null) {
            profile_.fire(power);
         }
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
      velocity.draw(grid, enemy_, new RobotData(this), 200, 20, 20, 100);

   }

   @Override
   public void onMouseClicked(MouseEvent e) {
      DrawMenu.inMouseEvent(e);
   }

   @Override
   public void onScannedRobot(ScannedRobotEvent event) {
      if (enemy_ == null) {
         enemy_ = new RobotData(event, this);
         profile_ = new EnemyProfile(enemy_, this);
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
   }

   @Override
   public void onWin(WinEvent event) {
      enemy_.setDeath();
      // robots_.inEvent(event);
   }

}
