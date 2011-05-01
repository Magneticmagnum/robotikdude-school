package nn.robot;

import java.awt.BasicStroke;
import java.awt.Color;
import java.util.ArrayDeque;
import java.util.ArrayList;

import nn.features.Feature;
import nn.graphics.DrawMenu;
import nn.graphics.RGraphics;
import nn.nnet.NeuralAdapter;
import nn.utils.Utils;
import nn.virtual.DataWave;
import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.Condition;
import robocode.Rules;

public class EnemyProfile {

   private AdvancedRobot            robot_;
   private RobotData                reference_;
   private RobotData                enemy_;
   private ArrayList<DataWave>      waves_;
   private ArrayList<DataWave>      bullets_;

   // private Space<GuessFactor, RobotData, RobotData> space = null;
   // private Comparison[] comparisons = null;
   // private int dataPerWave = 10;

   private static NeuralAdapter     nn_;
   private static Feature[]         features_;
   private static int               inputs_;
   private static int               outputs_;

   private ArrayDeque<Double>       lastHits_;

   private static NeuralAdapter     nn2_;
   private static ArrayList<Double> buffer_;

   public EnemyProfile(RobotData enemy, AdvancedRobot myRobot, Feature[] features, int buckets) {
      robot_ = myRobot;
      reference_ = new RobotData(robot_);
      enemy_ = enemy;
      robot_.addCustomEvent(new WaveWatcher(robot_.getTime()));
      waves_ = new ArrayList<DataWave>();
      bullets_ = new ArrayList<DataWave>();

      inputs_ = 0;
      for (Feature f : features) {
         inputs_ += f.getNumberOfFeatures();
      }
      outputs_ = buckets;
      features_ = features;
      nn_ = new NeuralAdapter(inputs_, outputs_);

      lastHits_ = new ArrayDeque<Double>(10);

      nn2_ = new NeuralAdapter(inputs_, outputs_);
      buffer_ = new ArrayList<Double>(200);
   }

   public void update(AdvancedRobot r) {
      reference_ = new RobotData(r);
      r.addCustomEvent(new WaveWatcher(r.getTime()));
      waves_ = new ArrayList<DataWave>();
      bullets_ = new ArrayList<DataWave>();
   }

   public double[] getInput(RobotData view, RobotData reference) {
      double[] input = new double[inputs_];
      int i = 0;
      for (Feature f : features_) {
         double[] features = f.getFeatures(view, reference);
         for (double d : features) {
            input[i++] = d;
         }
      }
      return input;
   }

   public double[] getOutput(double gf) {
      double[] output = new double[outputs_];

      double max = 1;
      for (int i = 0; i < output.length; i++) {
         output[i] += Math
               .max(0.0, 10.0 / (30.0 * Utils.sqr(Utils.getGuessFactor(i, output.length) - gf) + 1.0) - 4.99);
         max = Math.max(max, output[i]);
      }
      // System.out.print("EXPCT (" + robot_.getTime() + "): ");
      // for (int i = 0; i < outputs_; i++) {
      // output[i] /= max;
      // System.out.print(output[i] + " ");
      // }
      // System.out.println();

      return output;
   }

   public double[] getOutput() {
      return nn_.solution(getInput(enemy_, reference_));
   }

   public void fire(double power) {
      fire(null, power);
   }

   public void fire(Bullet bullet, double power) {
      power = Utils.limit(Rules.MIN_BULLET_POWER, power, Rules.MAX_BULLET_POWER);

      RobotData view = enemy_.copy();
      RobotData reference = this.reference_.copy();

      double[] data = getOutput();
      // System.out.print("DATA (" + robot_.getTime() + "): ");
      // for (int i = 0; i < outputs_; i++) {
      // // output[i] /= max;
      // System.out.print(data[i] + " ");
      // }
      // System.out.println();

      if (bullet != null)
         bullets_.add(new DataWave(reference, view, power, data, view, reference));
      else
         waves_.add(new DataWave(reference, view, power, data, view, reference));
   }

   public void draw(RGraphics grid) {
      if (!DrawMenu.getValue("Waves", "Targeting")) {
         return;
      }

      // for (DataWave w : waves_) {
      // w.draw(grid);
      // w.getReference().draw(grid);
      // w.getView().draw(grid);
      // }

      for (DataWave b : bullets_) {
         b.draw(grid);
         b.getReference().draw(grid);
         b.getView().draw(grid);

         if (b.getData() != null) {
            double dist = b.getDist(grid.getTime()) - 5.0;
            double[] data = b.getData();

            double max = 1;
            for (double d : data)
               max = Math.max(max, d);

            grid.setStroke(new BasicStroke(1.5f));
            float hue = 0.0f; // RED

            double heading = b.getHeading();
            double x = b.getStartX();
            double y = b.getStartY();
            RobotData view = b.getView();
            double d = Utils.getDirection(view.getHeading(), view.getVelocity(),
                  Utils.angle(x, y, view.getX(), view.getY()));
            double angle = d * Utils.getMaxEscapeAngle(b.getFirePower());

            double angleGF = heading + angle * Utils.getGuessFactor(0, data.length);

            double prevX = Utils.getX(x, dist, angleGF);
            double prevY = Utils.getY(y, dist, angleGF);
            for (int i = 1; i < data.length; i++) {
               if (i > data.length / 2) {
                  hue = (float) (75.0 / 240.0); // GREEN
               } else if (i == data.length / 2) {
                  hue = (float) (60.0 / 360.0); // YELLOW
               }
               float brightness = (float) (0.1 + 0.9 * data[i] / max);
               grid.setColor(Color.getHSBColor(hue, 1.0f, brightness));

               angleGF = heading + angle * Utils.getGuessFactor(i, data.length);
               grid.drawLine(prevX, prevY, prevX = Utils.getX(x, dist, angleGF), prevY = Utils.getY(y, dist, angleGF));
            }

         } // if (data != null)
      } // for (DataWave b : bullets_)
   }

   private class WaveWatcher extends Condition {

      private long time;

      public WaveWatcher(final long curTime) {
         this.time = curTime;
      }

      @Override
      public boolean test() {
         for (int i = 0; i < waves_.size(); i++) {
            DataWave w = waves_.get(i);
            if (w.testHit(enemy_.getX(), enemy_.getY(), reference_.getTime())) {
               double gf = Utils.getGuessFactor(w, w.getView(), enemy_);

               double[] input = getInput(w.getView(), w.getReference());

               nn_.train(input, getOutput(gf), 0.1);

               for (Double d : lastHits_) {
                  nn_.train(input, getOutput(d), 0.5);
               }

               // if (buffer_.size() < 200) {
               // buffer_.add(gf);
               // } else {
               // buffer_.add((int) (Math.random() * buffer_.size()), gf);
               // }
               //
               // for (int c = 0; c < 5 && c < buffer_.size(); c++) {
               // nn2_.train(input, getOutput(buffer_.get((int) (Math.random() * buffer_.size()))), 0.25);
               // }

               waves_.remove(i--);
            }
            if (w.getCreationTime() == time) {
               w.getReference().update(robot_);
            }
         }
         for (int i = 0; i < bullets_.size(); i++) {
            DataWave b = bullets_.get(i);
            if (b.testHit(enemy_.getX(), enemy_.getY(), reference_.getTime())) {
               double gf = Utils.getGuessFactor(b, b.getView(), enemy_);

               double[] input = getInput(b.getView(), b.getReference());

               nn_.train(input, getOutput(gf), 0.5);

               for (Double d : lastHits_) {
                  nn_.train(input, getOutput(d), 0.5);
               }

               lastHits_.addFirst(gf);
               if (lastHits_.size() > 5) {
                  lastHits_.removeLast();
               }

               // if (buffer_.size() < 200) {
               // buffer_.add(gf);
               // } else {
               // buffer_.add((int) (Math.random() * buffer_.size()), gf);
               // }
               //
               // for (int c = 0; c < 4 && c < buffer_.size(); c++) {
               // nn2_.train(input, getOutput(buffer_.get((int) (Math.random() * buffer_.size()))), 0.25);
               // }
               // nn2_.train(input, getOutput(gf), 0.25);

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
