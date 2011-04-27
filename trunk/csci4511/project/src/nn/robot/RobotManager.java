package nn.robot;

import java.util.HashMap;

import robocode.DeathEvent;
import robocode.Event;
import robocode.Robot;
import robocode.RobotDeathEvent;
import robocode.ScannedRobotEvent;
import robocode.WinEvent;


// TODO comment class RobotManager
public class RobotManager {

   /**
    * Singleton instance. Only want one {@link RobotManager} floating around so we used the singleton pattern to achieve
    * this.
    */
   private static RobotManager instance_;

   /**
    * Creates and/or returns the singleton instance. If a {@link RobotManager} was created for another {@link Robot}
    * than that {@link RobotManager} will be returned.
    * 
    * @param robot
    *           the {@link Robot} this {@link DataManger} is for
    * @return the singleton instance of this {@link RobotManager}
    */
   public static RobotManager getInstance(Robot robot) {
      if (instance_ == null)
         instance_ = new RobotManager(robot);
      return instance_;
   }

   /**
    * Returns the singleton instance. If a {@link RobotManager} was created for another {@link Robot} than that
    * {@link RobotManager} will be returned. If no instance has been created yet, {@code null} will be returned.
    * 
    * @return the singleton instance of this {@link RobotManager}
    */
   public static RobotManager getInstance() {
      return instance_;
   }



   /**
    * The {@link Robot} this {@link RobotManager} is for. Provides information on number of enemies, size of
    * battlefield, etc.
    */
   protected Robot                      robot_;

   /**
    * A {@link HashMap} containing {@link RobotData} entries representing all the robots that are on the battlefield.
    */
   protected HashMap<String, RobotData> robots_;


   /**
    * Creates a new {@link RobotManager} for the given {@link Robot}. This constructor should only ever be called once.
    * If it is called a second time, a runtime error will be thrown.
    * 
    * @param robot
    */
   private RobotManager(Robot robot) {
      if (instance_ != null)
         throw new RuntimeException("Singleton class, connot create more than one instance.");

      this.robot_ = robot;
      this.robots_ = new HashMap<String, RobotData>(2 * robot_.getOthers());
   }


   /**
    * The way of passing information about the current round into the {@link RobotManager}. If certain events happen
    * during the round, they should be passed in using this method.<br>
    * <br>
    * The events that are currently handled are:<br>
    * - {@link ScannedRobotEvent}<br>
    * - {@link RobotDeathEvent}<br>
    * - {@link DeathEvent}<br>
    * - {@link WinEvent}<br>
    * <small>(Last updated 2009/12/26)</small>
    * 
    * @param e
    *           the current {@link Event} being processed.
    */
   public void inEvent(Event e) {
      if (e instanceof ScannedRobotEvent) {
         ScannedRobotEvent sre = (ScannedRobotEvent) e;
         handleScannedRobotEvent(sre);
      } else if (e instanceof RobotDeathEvent) {
         RobotDeathEvent rde = (RobotDeathEvent) e;
         handleRobotDeathEvent(rde);
      } else if (e instanceof DeathEvent) {
         DeathEvent de = (DeathEvent) e;
         handleDeathEvent(de);
      } else if (e instanceof WinEvent) {
         WinEvent we = (WinEvent) e;
         handleWinEvent(we);
      }
   }

   /**
    * A quick way of passing information about the current round into the {@link RobotManager}.
    * 
    * @param events
    *           the current {@link Event}s being processed.
    * @see #inEvent(Event)
    */
   public void inEvents(Iterable<Event> events) {
      for (Event e : events)
         inEvent(e);
   }

   /**
    * Properly processes a {@link ScannedRobotEvent} by add any unknown scanned robots or updating any known robots that
    * have been scanned.
    * 
    * @param sre
    *           {@link ScannedRobotEvent} to process
    */
   private void handleScannedRobotEvent(ScannedRobotEvent sre) {
      String name = sre.getName();
      if (robots_.containsKey(name)) {
         robots_.get(name).update(sre, robot_);
      } else {
         RobotData e = new RobotData(sre, robot_);
         robots_.put(name, e);
      }
   }

   /**
    * Properly processes a {@link RobotDeathEvent} by updating the status of the robot that died.
    * 
    * @param rde
    *           {@link RobotDeathEvent} to process
    */
   private void handleRobotDeathEvent(RobotDeathEvent rde) {
      String name = rde.getName();
      if (robots_.containsKey(name)) {
         RobotData r = robots_.get(name);
         r.setDeath();
      }
   }

   /**
    * Properly processes a {@link DeathEvent} by updating the status of all the robots to be dead. This allows each
    * robot to be updated correctly at the beginning of each round.
    * 
    * @param de
    *           {@link DeathEvent} to process
    */
   private void handleDeathEvent(DeathEvent de) {
      for (RobotData r : robots_.values()) {
         r.setDeath();
      }
   }

   /**
    * Properly processes a {@link WinEvent} by updating the status of all the robots to be dead. This allows each robot
    * to be updated correctly at the beginning of each round.
    * 
    * @param de
    *           {@link WinEvent} to process
    */
   private void handleWinEvent(WinEvent de) {
      for (RobotData r : robots_.values()) {
         r.setDeath();
      }
   }

   /**
    * Returns the {@link RobotData} object that corresponds to the robot with the given name. A default
    * {@link RobotData} object is returned if no robot is found with that name.
    * 
    * @param name
    *           the identifier {@link String}
    * @return the corresponding {@link RobotData}
    */
   public RobotData getRobot(String name) {
      RobotData r = robots_.get(name);
      return (r == null ? new RobotData() : r);
   }

}
