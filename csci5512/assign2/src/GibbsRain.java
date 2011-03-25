/**
 * CSci5512 Spring '11 Homework 2
 * login: norma272
 * date: 3/23/2011
 * name: Brian Norman
 * id: 4332223
 * algorithm: Gibbs Rain
 */

import java.util.Random;

public class GibbsRain {

   // an enumeration of the system variables
   private static final int    CLOUDY    = 0;
   // private static final int SPRINKLER = 1;
   private static final int    RAIN      = 2;
   // private static final int WET_GRASS = 3;

   // the conditional probabilities needed
   private static final double P_c_rws   = 0.08;
   private static final double P_c_nrws  = 0.02;
   private static final double P_r_cws   = 0.792;
   private static final double P_r_ncws  = 0.198;

   private static final double P_nc_rws  = 0.1;
   private static final double P_nc_nrws = 0.4;
   private static final double P_nr_cws  = 0.18;
   private static final double P_nr_ncws = 0.72;


   public static void main(String[] args) {
      // make sure there are the current number of arguments
      if (args.length != 1) {
         System.out.println("ERROR: Wrong number of input variables.");
         System.out.println("USAGE: java GibbsRain <numSteps>");
         return;
      }
      // read number of steps and set up random number generator
      int numSteps = Integer.valueOf(args[0]);
      Random r = new Random(System.currentTimeMillis());

      
      // copied from page 537 of the book
      double[] N = new double[2];
      int[] Z = { CLOUDY, RAIN };
      // cloudy, sprinkler, rain, wet grass
      boolean[] x = { r.nextDouble() > 0.5, true, r.nextDouble() > 0.5, true };


      for (int j = 0; j < numSteps; j++) {
         for (int Zi : Z) {
            x[Zi] = r.nextDouble() < P(Zi, x);
            N[(x[Zi] ? 0 : 1)]++;
         }
      }
      System.out.println("N: [" + N[0] + " " + N[1] + "]");
      System.out.println("Normalized: [" + (N[0] / (N[0] + N[1])) + " " + (N[1] / (N[0] + N[1])) + "]");
   }

   // returns the correct probability for the conditionals
   private static double P(int X, boolean[] e) {
      if (X == CLOUDY) {
         if (e[CLOUDY]) {
            if (e[RAIN]) {
               return P_c_rws;
            } else {
               return P_c_nrws;
            }
         } else {
            if (e[RAIN]) {
               return P_nc_rws;
            } else {
               return P_nc_nrws;
            }
         }
      } else if (X == RAIN) {
         if (e[RAIN]) {
            if (e[CLOUDY]) {
               return P_r_cws;
            } else {
               return P_r_ncws;
            }
         } else {
            if (e[CLOUDY]) {
               return P_nr_cws;
            } else {
               return P_nr_ncws;
            }
         }
      } else {
         return 0.0;
      }
   }

}
