package math.matrices;

// BORED document: math.matrices.Vector
public class Vector extends Matrix {

   /**
    * Determines if a deserialized file is compatible with {@code this class}. <br>
    * <br>
    * Maintainers must change this value if and only if the new version of {@code this class} is not compatible with old
    * versions.
    */
   private static final long serialVersionUID = -4882635154030276051L;


   public Vector(int n) {
      this(new double[n]);
   }

   public Vector(double[] v) {
      set(v);
   }


   public Vector set(double[] v) {
      double[][] m = new double[v.length][1];
      for (int i = 0; i < v.length; i++)
         m[i][0] = v[i];
      return (Vector) super.set(m);
   }

   public void set(int i, double n) {
      super.set(i, 0, n);
   }


   public int getLength() {
      return super.getRows();
   }

   public double get(int i) {
      return super.get(i, 0);
   }

   protected double unsafeGet(int i) {
      return super.unsafeGet(i, 0);
   }

   public double abs() {
      return abs(this);
   }

   public static final double abs(Vector v) {
      double sqSum = 0.0;
      for (int i = 0; i < v.getLength(); i++)
         sqSum += v.unsafeGet(i) * v.unsafeGet(i);
      return Math.sqrt(sqSum);
   }


   @Override
   public Vector scale(double n) {
      for (int i = 0; i < getLength(); i++)
         set(i, n * get(i));
      return this;
   }

   public static final Vector scale(double n, Vector a) {
      if (a == null)
         throw new NullPointerException("Cannot scale a null vector.");
      Vector c = a.copy();
      for (int i = 0; i < c.getLength(); i++)
         c.set(i, n * c.get(i));
      return c;
   }


   public Vector add(Vector v) {
      if (v == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (getRows() != v.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: " + getRows()
               + " and " + v.getRows());

      for (int i = 0; i < getLength(); i++) {
         set(i, get(i) + v.get(i));
      }
      return this;
   }

   public static final Vector add(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: "
               + a.getRows() + " and " + b.getRows());

      Vector c = a.copy();
      for (int i = 0; i < a.getLength(); i++) {
         c.set(i, a.get(i) + b.get(i));
      }
      return c;
   }


   public Vector subtract(Vector v) {
      if (v == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (getRows() != v.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: " + getRows()
               + " and " + v.getRows());

      for (int i = 0; i < getLength(); i++) {
         set(i, get(i) - v.get(i));
      }
      return this;
   }

   public static final Vector subtract(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: "
               + a.getRows() + " and " + b.getRows());

      Vector c = a.copy();
      for (int i = 0; i < a.getLength(); i++) {
         c.set(i, a.get(i) - b.get(i));
      }
      return c;
   }


   public Vector dotMultiply(Vector v) {
      if (v == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (getRows() != v.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: " + getRows()
               + " and " + v.getRows());

      for (int i = 0; i < getLength(); i++) {
         set(i, get(i) * v.get(i));
      }
      return this;
   }

   public static final Vector dotMultiply(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: "
               + a.getRows() + " and " + b.getRows());

      Vector c = a.copy();
      for (int i = 0; i < a.getLength(); i++) {
         c.set(i, a.get(i) * b.get(i));
      }
      return c;
   }


   public Vector dotDivide(Vector v) {
      if (v == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (getRows() != v.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: " + getRows()
               + " and " + v.getRows());

      for (int i = 0; i < getLength(); i++) {
         set(i, get(i) / v.get(i));
      }
      return this;
   }

   public static final Vector dotDivide(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: "
               + a.getRows() + " and " + b.getRows());

      Vector c = a.copy();
      for (int i = 0; i < a.getLength(); i++) {
         c.set(i, a.get(i) / b.get(i));
      }
      return c;
   }


   public double innerProduct(Vector v) {
      return innerProduct(this, v);
   }

   public static final double innerProduct(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
         throw new MatrixDimensionException("Vector dimension exception: vector dimensions do not agree: "
               + a.getRows() + " and " + b.getRows());

      double prod = 0.0;
      for (int i = 0; i < a.getRows(); i++)
         prod += a.get(i) * b.get(i);
      return prod;
   }


   public Matrix outerProduct(Vector v) {
      return outerProduct(this, v);
   }

   public static final Matrix outerProduct(Vector a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");

      Matrix c = new Matrix(a.getLength(), b.getLength());
      for (int i = 0; i < c.getRows(); i++) {
         for (int j = 0; j < c.getColumns(); j++) {
            c.set(i, j, a.get(i) * b.get(j));
         }
      }
      return c;
   }


   public static final Vector multiply(Matrix a, Vector b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot multiply null matrices.");
      if (a.getColumns() != b.getRows())
         throw new MatrixDimensionException("Matrix dimension exception: matrix dimensions do not agree: "
               + a.getColumns() + " and " + b.getRows());

      Vector c = new Vector(a.getRows());
      for (int i = 0; i < c.getRows(); i++) {
         double sum = 0;
         for (int k = 0; k < b.getRows(); k++)
            sum += a.get(i, k) * b.get(k);
         c.set(i, sum);
      }
      return c;
   }


   @Override
   public Vector copy() {
      return new Vector(getColumn(0));
   }

}
