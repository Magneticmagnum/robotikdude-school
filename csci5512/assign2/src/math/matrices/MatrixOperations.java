package math.matrices;

public class MatrixOperations {

   public static final double rowSumNorm(Matrix m) {
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

   public static final double columnSumNorm(Matrix m) {
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

   public static final double pNorm(Vector v, int p) {
      double norm = 0;
      if (p > 0) {
         for (int i = 0; i < v.getLength(); i++) {
            norm += Math.pow(v.get(i), p);
         }
         norm = Math.pow(norm, 1.0 / p);
      }
      return norm;

   }

}
