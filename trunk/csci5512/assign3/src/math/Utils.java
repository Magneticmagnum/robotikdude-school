package math;


// BORED document class
public class Utils {

   private Utils() {
   }


   /**
    * The <code>double</code> value of one-third.
    */
   public static final double ONE_THIRD  = (1.0D / 3.0D);

   /**
    * The <code>double</code> value of two-thirds.
    */
   public static final double TWO_THIRDS = (2.0D / 3.0D);

   /**
    * Returns the square of the <code>double</code>. That is, the double multiplied be it's self once.
    * 
    * @param n
    *           the number whose square is to be calculated.
    * @return the square of the argument.
    */
   public static final double sqr(final double n) {
      return n * n;
   }

   /**
    * Returns the cube of a <code>double</code>. That is, the double multiplied be itself three times.
    * 
    * @param n
    *           the number whose cube is to be calculated.
    * @return the cube of the argument.
    */
   public static final double cube(final double n) {
      return n * n * n;
   }

   public static final int sign(final double n) {
      return (n < 0 ? -1 : 1);
   }

   public static double sigmoid(double z) {
      return 1.0 / (1.0 + 5.0 * Math.exp(-z));
   }

   public static double dsigmoid(double z) {
      double s = sigmoid(z);
      return s * (1 - s);
   }

   public static double sigmoid(double z, double tau) {
      return sigmoid(tau * z);
   }

   public static double dsigmoid(double z, double tau) {
      return dsigmoid(tau * z);
   }

   public static final double pow(double a, int n) {
      double t = 1;
      for (int i = Math.abs(n); i > 0; i--)
         t *= a;
      if (n < 0)
         t = 1.0 / t;
      return t;
   }

   public static final double pow(int a, int n) {
      if (n < 0)
         throw new ArithmeticException("Cannot raise an integer to a negative number.");
      int t = 1;
      for (int i = Math.abs(n); i > 0; i--)
         t *= a;
      return t;
   }

   public static final int factorial(int n) {
      if (n < 0)
         throw new ArithmeticException("Cannot take the factorial of a negative number.");
      int t = 1;
      for (int i = n; i > 1; i--)
         t *= i;
      return t;
   }

   // public static final int choose(int i, int j) {
   // return compination(i, j);
   // }
   //
   // public static final int permutation(int n, int r) {
   // if (n < 0 || r < 0)
   // throw new ArithmeticException("Cannot take the factorial of a negative number.");
   // int t = 1;
   // for (int i = n; i > n - r; i--)
   // t *= i;
   // return t;
   // }
   //
   // public static final int compination(int n, int r) {
   // return permutation(n, r) / factorial(r);
   // }
   //
   // public static final double sum(Function f, int start, int finish) {
   // double sum = 0;
   // if (start <= finish) {
   // for (int i = start; i <= finish; i++) {
   // sum += f.f(i);
   // }
   // }
   // return sum;
   // }
   //
   // public static final double sum(Function f, double start, double finish, double increment) {
   // double sum = 0;
   // if (start <= finish && increment > 0) {
   // for (double i = start; i <= finish; i += increment) {
   // sum += f.f(i);
   // }
   // }
   // return sum;
   // }
   //
   // public static final void sort(double[] x, double[] y) {
   // boolean sorted = false;
   // int pass = 1;
   //
   // while (pass < x.length && !sorted) {
   // sorted = true;
   // for (int i = 0; i < x.length - pass; i++)
   // if (x[i] > x[i + 1]) {
   // double temp = x[i];
   // x[i] = x[i + 1];
   // x[i + 1] = temp;
   //
   // temp = y[i];
   // y[i] = y[i + 1];
   // y[i + 1] = temp;
   //
   // sorted = false;
   // }
   // pass++;
   // }
   // }
   //
   // public static final void sort(Point2D[] points) {
   // boolean sorted = false;
   // int pass = 1;
   //
   // while (pass < points.length && !sorted) {
   // sorted = true;
   // for (int i = 0; i < points.length - pass; i++)
   // if (points[i].getX() > points[i + 1].getX()) {
   // Point2D temp = points[i];
   // points[i] = points[i + 1];
   // points[i + 1] = temp;
   // sorted = false;
   // }
   // pass++;
   // }
   // }


}
