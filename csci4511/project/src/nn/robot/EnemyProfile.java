package nn.robot;

import java.awt.BasicStroke;
import java.awt.Color;
import java.util.ArrayList;

import nn.factor.GuessFactor;
import nn.graphics.DrawMenu;
import nn.graphics.RGraphics;
import nn.utils.Utils;
import nn.virtual.DataWave;

import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.Condition;
import robocode.Rules;

public class EnemyProfile {

   private AdvancedRobot                    robot_;
   private RobotData                        reference_;
   private RobotData                        enemy_;
   private ArrayList<DataWave<GuessFactor>> waves_;
   private ArrayList<DataWave<GuessFactor>> bullets_;

   // private Space<GuessFactor, RobotData, RobotData> space = null;
   // private Comparison[] comparisons = null;
   // private int dataPerWave = 10;

   public EnemyProfile(RobotData enemy, AdvancedRobot myRobot) {// , Comparison[] comparisons
      init(enemy, myRobot, -1);
   }

   public EnemyProfile(RobotData enemy, AdvancedRobot myRobot, int dataPerWave) { // , Comparison[] comparisons
      init(enemy, myRobot, dataPerWave);
   }

   private void init(RobotData e, AdvancedRobot r, int d) { // , Comparison[] c
      robot_ = r;
      reference_ = new RobotData(r);
      enemy_ = e;
      // comparisons = c;
      // if (d > 0)
      // dataPerWave = d;
      r.addCustomEvent(new WaveWatcher(r.getTime()));
      waves_ = new ArrayList<DataWave<GuessFactor>>();
      bullets_ = new ArrayList<DataWave<GuessFactor>>();
      // space = new Space<GuessFactor, RobotData, RobotData>(c);
   }

   public void update(AdvancedRobot r) {
      reference_ = new RobotData(r);
      r.addCustomEvent(new WaveWatcher(r.getTime()));
      waves_ = new ArrayList<DataWave<GuessFactor>>();
      bullets_ = new ArrayList<DataWave<GuessFactor>>();
   }

   public void fire(double power) {
      fire(null, power);
   }

   public void fire(Bullet bullet, double power) {
      power = Utils.limit(Rules.MIN_BULLET_POWER, power, Rules.MAX_BULLET_POWER);

      RobotData view = enemy_.copy();
      RobotData reference = this.reference_.copy();
      // GuessFactor[] data = space.getCluster(view, reference, dataPerWave).toArray(new GuessFactor[0]);

      waves_.add(new DataWave<GuessFactor>(reference, view, power, null, view, reference));
      if (bullet != null)
         bullets_.add(new DataWave<GuessFactor>(reference, view, power, null, view, reference));
   }

   public GuessFactor[] getCluster(int size) {
      // return space.getCluster(enemy, reference.copy(), size).toArray(new GuessFactor[0]);
      return null;
   }

   public void print() {
      // space.print(System.out);
   }

   public void draw(final RGraphics grid) {
      if (!DrawMenu.getValue("Waves", "Targeting")) {
         return;
      }

      for (DataWave<GuessFactor> w : waves_) {
         w.draw(grid);
         w.getReference().draw(grid);
         w.getView().draw(grid);

         if (w.getData() != null) {
            double dist = w.getDist(grid.getTime()) - 5.0;
            GuessFactor[] data = w.getData();
            double[] bins = new double[101];

            for (GuessFactor gf : data) {
               for (int i = 0; i < bins.length; i++) {
                  bins[i] += Utils
                        .limit(
                              0.0,
                              10.0 / (30.0 * Utils.sqr(Utils.getGuessFactor(i, bins.length) - gf.getGuessFactor()) + 1.0) - 4.99,
                              5.0);
               }
            }

            double max = 1;
            for (double i : bins)
               max = Math.max(max, i);

            grid.setStroke(new BasicStroke(1.5f));
            float hue = 0.0f; // RED
            hue = (float) (75.0 / 240.0); // GREEN

            double heading = w.getHeading();
            double x = w.getStartX();
            double y = w.getStartY();
            RobotData view = w.getView();
            double d = Utils.getDirection(view.getHeading(), view.getVelocity(),
                  Utils.angle(x, y, view.getX(), view.getY()));
            double angle = d * Utils.getMaxEscapeAngle(w.getFirePower());

            double angleGF = heading + angle * Utils.getGuessFactor(0, bins.length);

            double prevX = Utils.getX(x, dist, angleGF);
            double prevY = Utils.getY(y, dist, angleGF);
            for (int i = 1; i < bins.length; i++) {
               float brightness = (float) (0.1 + 0.9 * bins[i] / max);
               grid.setColor(Color.getHSBColor(hue, 1.0f, brightness));

               angleGF = heading + angle * Utils.getGuessFactor(i, bins.length);
               grid.drawLine(prevX, prevY, prevX = Utils.getX(x, dist, angleGF), prevY = Utils.getY(y, dist, angleGF));
            }

         } // if (data != null)
      } // for (DataWave<GuessFactor> w : waves)
   }

   private class WaveWatcher extends Condition {

      private long time;

      public WaveWatcher(final long curTime) {
         this.time = curTime;
      }

      @Override
      public boolean test() {
         for (int i = 0; i < waves_.size(); i++) {
            DataWave<GuessFactor> w = waves_.get(i);
            if (w.testHit(enemy_.getX(), enemy_.getY(), reference_.getTime())) {
               // GuessFactor gf = new GuessFactor(Utils.getGuessFactor(w, w.getView(), enemy));
               // space.add(gf, w.getView(), w.getReference());
               waves_.remove(i--);
            }
            if (w.getCreationTime() == time) {
               w.getReference().update(robot_);
            }
         }
         for (int i = 0; i < bullets_.size(); i++) {
            DataWave<GuessFactor> b = bullets_.get(i);
            if (b.testHit(enemy_.getX(), enemy_.getY(), reference_.getTime())) {
               // GuessFactor gf = new GuessFactor(Utils.getGuessFactor(w, w.getView(), enemy));
               // space.add(gf, w.getView(), w.getReference());
               bullets_.remove(i--);
            }
            if (b.getCreationTime() == time) {
               b.getReference().update(robot_);
            }
         }
         time++;
         reference_.update(robot_);
         return false;
      }
   }

}
