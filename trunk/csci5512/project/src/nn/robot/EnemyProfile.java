package nn.robot;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Stroke;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.LinkedList;

import nn.features.Feature;
import nn.graphics.DrawMenu;
import nn.graphics.RGraphics;
import nn.matrices.Vector;
import nn.nnet.NeuralNetwork;
import nn.utils.Utils;
import nn.virtual.DataWave;
import robocode.AdvancedRobot;
import robocode.Bullet;
import robocode.Condition;
import robocode.Rules;

public class EnemyProfile {

   private AdvancedRobot             robot_;
   private RobotData                 reference_;
   private RobotData                 enemy_;
   private LinkedList<DataWave>      waves_;
   private LinkedList<DataWave>      bullets_;

   // private Space<GuessFactor, RobotData, RobotData> space = null;
   // private Comparison[] comparisons = null;
   // private int dataPerWave = 10;

   private static NeuralNetwork      nn_;
   private static Feature[]          features_;
   private static int                inputs_;
   private static int                outputs_;

   private static ArrayDeque<Double> lastHits_;

   private static NeuralNetwork      nn2_;
   private static ArrayList<Double>  buffer_;

   public EnemyProfile(RobotData enemy, AdvancedRobot myRobot, Feature[] features, int buckets) {
      robot_ = myRobot;
      reference_ = new RobotData(robot_);
      enemy_ = enemy;
      robot_.addCustomEvent(new WaveWatcher(robot_.getTime()));
      waves_ = new LinkedList<DataWave>();
      bullets_ = new LinkedList<DataWave>();

      inputs_ = 0;
      for (Feature f : features) {
         inputs_ += f.getNumberOfFeatures();
      }
      outputs_ = buckets;
      features_ = features;
      nn_ = NeuralNetwork.create(inputs_, outputs_);

      lastHits_ = new ArrayDeque<Double>(10);

      nn2_ = NeuralNetwork.create(inputs_, outputs_);
      buffer_ = new ArrayList<Double>(300);
   }

   public void update(AdvancedRobot r) {
      reference_ = new RobotData(r);
      r.addCustomEvent(new WaveWatcher(r.getTime()));
      waves_ = new LinkedList<DataWave>();
      bullets_ = new LinkedList<DataWave>();
   }

   public Vector getInput(RobotData view, RobotData reference) {
      double[] input = new double[inputs_];
      int i = 0;
      for (Feature f : features_) {
         double[] features = f.getFeatures(view, reference);
         for (double d : features) {
            input[i++] = d;
         }
      }
      return new Vector(input);
   }

   public static Vector getOutput(double gf) {
      double[] output = new double[outputs_];

      // output[Utils.getIndex(gf, output.length)] = 1.0;

      // double max = 1;
      for (int i = 0; i < output.length; i++) {
         output[i] += Math.max(0.0, 1.0 / (50.0 * Utils.sqr(Utils.getGuessFactor(i, output.length) - gf) + 1.0) - 0.5);
         // max = Math.max(max, output[i]);
      }

      return new Vector(output);
   }

   public Vector getOutput() {
      Vector input = getInput(enemy_, reference_);
      // Vector nn = nn_.get(input);
      // Vector nn2 = nn2_.get(input);
      // double max_nn = 0.0;
      // double max_nn2 = 0.0;
      // for (int i = 0; i < outputs_; i++) {
      // max_nn = Math.max(max_nn, nn.get(i));
      // max_nn2 = Math.max(max_nn2, nn2.get(i));
      // }
      // return nn.scale(1.0 / max_nn).add(nn2.scale(1.0 / max_nn2));
      return nn_.get(input).add(nn2_.get(input));
   }

   public void fire(double power) {
      fire(null, power);
   }

   public void fire(Bullet bullet, double power) {
      power = Utils.limit(Rules.MIN_BULLET_POWER, power, Rules.MAX_BULLET_POWER);

      RobotData view = enemy_.copy();
      RobotData reference = this.reference_.copy();

      if (bullet != null) {
         // Vector data = getOutput();
         bullets_.add(new DataWave(reference, view, power, getOutput(), view, reference));
      } else if (reference.getEnergy() > 0 && bullets_.size() > 0) {
         waves_.add(new DataWave(reference, view, power, null, view, reference));
      }
   }

   public void draw(RGraphics grid) {
      if (DrawMenu.getValue("Waves", "Targeting")) {
         drawWaves(grid);
      }
      // if (DrawMenu.getValue("Graph", "Neural")) {
      drawGraph(grid);
      // }
   }

   private void drawGraph(RGraphics grid) {
      double startx = 10;
      double starty_nn = 100;
      double starty_nn2 = 200;
      double starty_out = 300;
      double dx = 5;
      double height = 50;

      Vector input = getInput(enemy_, reference_);
      Vector nn_output = nn_.get(input);
      Vector nn2_output = nn2_.get(input);
      Vector output = getOutput();
      // getOutput(((robot_.getTime() / 200.0) % 2.0) - 1.0);

      double max_nn = 0.0;
      for (int i = 0; i < nn_output.getLength(); i++)
         max_nn = Math.max(max_nn, nn_output.get(i));

      double max_nn2 = 0.0;
      for (int i = 0; i < nn2_output.getLength(); i++)
         max_nn2 = Math.max(max_nn2, nn2_output.get(i));

      double max_out = 0.0;
      for (int i = 0; i < output.getLength(); i++)
         max_out = Math.max(max_out, output.get(i));

      double px = startx;
      double py_nn = starty_nn + height * (nn_output.get(0) / max_nn);
      double py_nn2 = starty_nn2 + height * (nn2_output.get(0) / max_nn2);
      double py_out = starty_out + height * (output.get(0) / max_out);

      grid.setColor(Color.RED);
      for (int i = 1; i < output.getLength(); i++) {
         if (i == output.getLength() / 2 + 1) {
            grid.setColor(Color.YELLOW);
         } else if (i > output.getLength() / 2) {
            grid.setColor(Color.GREEN);
         }
         double x = px + dx;
         double y_nn = starty_nn + height * (nn_output.get(i) / max_nn);
         double y_nn2 = starty_nn2 + height * (nn2_output.get(i) / max_nn2);
         double y_out = starty_out + height * (output.get(i) / max_out);
         grid.drawLine(px, py_nn, x, y_nn);
         grid.drawLine(px, py_nn2, x, y_nn2);
         grid.drawLine(px, py_out, x, y_out);
         px = x;
         py_nn = y_nn;
         py_nn2 = y_nn2;
         py_out = y_out;
      }

      grid.setColor(Color.WHITE);
      grid.drawLine(startx, starty_nn, startx + output.getLength() * dx, starty_nn);
      grid.drawLine(startx, starty_nn2, startx + output.getLength() * dx, starty_nn2);
      grid.drawLine(startx, starty_out, startx + output.getLength() * dx, starty_out);

      grid.drawLine(startx, starty_nn, startx, starty_nn + height + 3);
      grid.drawLine(startx, starty_nn2, startx, starty_nn2 + height + 3);
      grid.drawLine(startx, starty_out, startx, starty_out + height + 3);

      grid.drawLine(startx - 5, starty_nn + height, startx + 5, starty_nn + height);
      grid.drawLine(startx - 5, starty_nn2 + height, startx + 5, starty_nn2 + height);
      grid.drawLine(startx - 5, starty_out + height, startx + 5, starty_out + height);

      grid.drawString("nn", startx + 10, starty_nn - 10);
      grid.drawString("nn2", startx + 10, starty_nn2 - 10);
      grid.drawString("out", startx + 10, starty_out - 10);

   }

   private void drawWaves(RGraphics grid) {
      Stroke prev = grid.getStroke();
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
            Vector data = b.getData();

            double max = 0.0;
            for (int i = 0; i < data.getLength(); i++)
               max = Math.max(max, data.get(i));

            grid.setStroke(new BasicStroke(1.5f));
            float hue = 0.0f; // RED

            double heading = b.getHeading();
            double x = b.getStartX();
            double y = b.getStartY();
            RobotData view = b.getView();
            double d = Utils.getDirection(view.getHeading(), view.getVelocity(),
                  Utils.angle(x, y, view.getX(), view.getY()));
            double angle = d * Utils.getMaxEscapeAngle(b.getFirePower());

            double angleGF = heading + angle * Utils.getGuessFactor(0, data.getLength());

            double prevX = Utils.getX(x, dist, angleGF);
            double prevY = Utils.getY(y, dist, angleGF);
            for (int i = 1; i < data.getLength(); i++) {
               if (i > data.getLength() / 2) {
                  hue = (float) (75.0 / 240.0); // GREEN
               } else if (i == data.getLength() / 2 + 1) {
                  hue = (float) (60.0 / 360.0); // YELLOW
               }
               float brightness = (float) (0.1 + 0.9 * data.get(i) / max);
               grid.setColor(Color.getHSBColor(hue, 1.0f, brightness));

               angleGF = heading + angle * Utils.getGuessFactor(i, data.getLength());
               grid.drawLine(prevX, prevY, prevX = Utils.getX(x, dist, angleGF), prevY = Utils.getY(y, dist, angleGF));
            }

         } // if (data != null)
      } // for (DataWave b : bullets_)
      grid.setStroke(prev);
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

               Vector input = getInput(w.getView(), w.getReference());

               nn_.train(input, getOutput(gf), 0.25);

               for (Double d : lastHits_) {
                  nn_.train(input, getOutput(d), 1.0);
               }

               if (buffer_.size() < 200) {
                  buffer_.add(gf);
               } else {
                  buffer_.set((int) (Math.random() * buffer_.size()), gf);
               }

               for (int c = 0; c < 5 && c < buffer_.size(); c++) {
                  nn2_.train(input, getOutput(buffer_.get((int) (Math.random() * buffer_.size()))), 1.0);
               }

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

               Vector input = getInput(b.getView(), b.getReference());

               nn_.train(input, getOutput(gf), 1.0);

               for (Double d : lastHits_) {
                  nn_.train(input, getOutput(d), 1.0);
               }

               lastHits_.addFirst(gf);
               if (lastHits_.size() > 5) {
                  lastHits_.removeLast();
               }

               if (buffer_.size() < 200) {
                  buffer_.add(gf);
               } else {
                  buffer_.set((int) (Math.random() * buffer_.size()), gf);
               }

               for (int c = 0; c < 4 && c < buffer_.size(); c++) {
                  nn2_.train(input, getOutput(buffer_.get((int) (Math.random() * buffer_.size()))), 1.0);
               }
               nn2_.train(input, getOutput(gf), 1.0);

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
