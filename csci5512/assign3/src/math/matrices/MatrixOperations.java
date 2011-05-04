package math.matrices;

import math.Utils;

public class MatrixOperations {

   public static double rowSumNorm(Matrix m) {
      double max = 0;
      for (int i = 0; i < m.getRows(); i++) {
         double sum = 0;
         for (int j = 0; j < m.getColumns(); j++) {
            sum += Math.abs(m.get(i, j));
         }
         max = Math.max(sum, max);
      }
      return max;
   }

   public static double oneNorm(Matrix m) {
      return columnSumNorm(m);
   }

   public static double columnSumNorm(Matrix m) {
      double max = 0;
      for (int i = 0; i < m.getColumns(); i++) {
         double sum = 0;
         for (int j = 0; j < m.getRows(); j++) {
            sum += Math.abs(m.get(j, i));
         }
         max = Math.max(sum, max);
      }
      return max;
   }

   public static double infNorm(Matrix m) {
      return columnSumNorm(m);
   }

   public static double pNorm(Vector v, int p) {
      double norm = 0;
      if (p > 0) {
         for (int i = 0; i < v.getLength(); i++) {
            norm += Utils.pow(v.get(i), p);
         }
         norm = Math.pow(norm, 1.0 / p);
      }
      return norm;

   }

   public static Matrix transpose(Matrix m) {
      // System.out.println("[" + m.getRows() + ", " + m.getColumns() + "]");
      Matrix n = new Matrix(m.getColumns(), m.getRows());
      // System.out.println("[" + n.getRows() + ", " + n.getColumns() + "]");
      for (int i = 0; i < m.getRows(); i++) {
         for (int j = 0; j < m.getColumns(); j++) {
            n.set(j, i, m.get(i, j));
         }
      }
      return n;
   }

}
