/**
 * CSci5512 Spring '11 Homework 2
 * login: norma272
 * date: 3/23/2011
 * name: Brian Norman
 * id: 4332223
 * algorithm: MaxSeq
 */

import math.matrices.Vector;


public class MaxSeq {

   public static void main(String[] args) {
      int numEvidence = 0;

      if (args.length != 0) {
         numEvidence = Integer.valueOf(args[0]);
      }
      if (numEvidence == 0) {
         System.out.println("ERROR: No evidence, cannot compute smoothing.");
         System.out.println("USAGE: java SmoothHMM <numEvidence> <sequence of evidence>");
         return;
      } else if (args.length != numEvidence + 1) {
         System.out.println("ERROR: Evidence lengths do not match.");
         System.out.println("USAGE: java SmoothHMM <numEvidence> <sequence of evidence>");
         return;
      }

      Vector[] ev = new Vector[numEvidence];
      for (int i = 0; i < numEvidence; i++) {
         int evidence = Integer.valueOf(args[i + 1]);
         ev[i] = new Vector(new double[] { evidence, 1 - evidence });
      }

      Vector[] sv = SmoothHMM.getSmoothHMM(ev);

      System.out.print("Sequence = ");
      for (int i = 0; i < sv.length; i++) {
         System.out.print((sv[i].get(0) >= 0.5 ? "T" : "F") + (i + 1 != ev.length ? ", " : ""));
      }
      System.out.println();
   }

}
