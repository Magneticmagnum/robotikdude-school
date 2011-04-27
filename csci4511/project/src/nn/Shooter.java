package nn;

import graphics.DrawMenu;
import graphics.RGraphics;

import java.awt.Graphics2D;
import java.awt.event.MouseEvent;

import move.GunMovement;
import move.RadarMovement;
import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.DeathEvent;
import robocode.RobotDeathEvent;
import robocode.Rules;
import robocode.ScannedRobotEvent;
import robocode.WinEvent;
import robot.EnemyProfile;
import robot.RobotData;
import utils.Utils;

public class Shooter extends AdvancedRobot {

   // private RobotMovement robot_;
   private GunMovement         gun_;
   private RadarMovement       radar_;

   private RobotData           enemy_;
   private static EnemyProfile profile_;

   // private RobotManager robots_;

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
