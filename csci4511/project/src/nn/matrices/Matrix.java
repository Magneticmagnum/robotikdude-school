package nn.matrices;

import java.io.PrintStream;
import java.io.Serializable;

// BORED document: math.matrices.Matrix
public class Matrix implements Cloneable, Serializable {

   /**
    * Determines if a deserialized file is compatible with {@code this class}. <br>
    * <br>
    * Maintainers must change this value if and only if the new version of {@code this class} is not compatible with old
    * versions.
    */
   private static final long serialVersionUID = 5433550198946185291L;

   private double[][]        matrix;
   private int               rows;
   private int               columns;


   public Matrix() {
      this(0, 0);
   }

   public Matrix(int rows, int columns) {
      this(new double[rows][columns]);
   }

   public Matrix(int rows, int columns, double fill) {
      this(new double[rows][columns]);
      this.add(fill);
   }

   public Matrix(double[][] a) {
      set(a);
   }


   public Matrix set(double[][] a) {
      rows = a.length;
      columns = (rows == 0 ? 0 : a[0].length);
      matrix = a; // FIXME code: address risks in this reference
      // matrix = new double[rows][columns];
      // for (int i = 0; i < rows; i++) {
      // for (int j = 0; j < columns; j++) {
      // matrix[i][j] = a[i][j];
      // }
      // }
      return this;
   }

   public Matrix set(Matrix a) {
      return set(a.matrix);
   }

   public Matrix setRow(int row, double[] values) {
      catchDimensions(row, 0);
      if (getColumns() != values.length)
         throw new MatrixDimensionException("Array length needs to be the same as the number of columns "
               + "in the matrix: " + getColumns());

      for (int i = 0; i < getColumns(); i++)
         matrix[row][i] = values[i];
      return this;
   }

   public Matrix setColumn(int column, double[] values) {
      catchDimensions(0, column);
      if (getRows() != values.length)
         throw new MatrixDimensionException("Matrix dimension exception: array length needs to be the same as the "
               + "number of rows in the matrix: " + getRows());

      for (int i = 0; i < getRows(); i++)
         matrix[i][column] = values[i];
      return this;
   }

   public void set(int row, int column, double n) {
      catchDimensions(row, column);
      matrix[row][column] = n;
   }


   public int getRows() {
      return rows;
   }

   public int getColumns() {
      return columns;
   }

   public double[] getRow(int row) {
      catchDimensions(row, 0);

      double[] matrixRow = new double[getColumns()];
      for (int i = 0; i < getColumns(); i++) {
         matrixRow[i] = get(row, i);
      }
      return matrixRow;
   }

   public double[] getColumn(int column) {
      catchDimensions(0, column);

      double[] matrixColumn = new double[getRows()];
      for (int i = 0; i < getRows(); i++) {
         matrixColumn[i] = get(i, column);
      }
      return matrixColumn;
   }

   public double get(int row, int column) {
      catchDimensions(row, column);
      return matrix[row][column];
   }


   public Matrix scale(double n) {
      set(scale(n, this));
      return this;
   }

   public static final Matrix scale(double n, Matrix a) {
      if (a == null)
         throw new NullPointerException("Cannot scale a null matrix.");
      Matrix c = a.copy();
      for (int i = 0; i < c.getRows(); i++) {
         for (int j = 0; j < c.getColumns(); j++) {
            c.set(i, j, n * c.get(i, j));
         }
      }
      return c;
   }


   public Matrix add(double n) {
      set(add(this, n));
      return this;
   }

   public static final Matrix add(Matrix a, double n) {
      if (a == null)
         throw new NullPointerException("Cannot add a null matrix.");

      Matrix c = a.copy();
      for (int i = 0; i < a.getRows(); i++) {
         for (int j = 0; j < a.getColumns(); j++) {
            c.set(i, j, a.get(i, j) + n);
         }
      }
      return c;
   }


   public Matrix add(Matrix a) {
      set(add(this, a));
      return this;
   }

   public static final Matrix add(Matrix a, Matrix b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
         throw new MatrixDimensionException("Matrix dimension exception: matrix dimensions do not agree: "
               + a.getRows() + "x" + a.getColumns() + " and " + b.getRows() + "x" + b.getColumns());

      Matrix c = a.copy();
      for (int i = 0; i < a.getRows(); i++) {
         for (int j = 0; j < a.getColumns(); j++) {
            c.set(i, j, a.get(i, j) + b.get(i, j));
         }
      }
      return c;
   }


   public Matrix subtract(Matrix a) {
      set(subtract(this, a));
      return this;
   }

   public static final Matrix subtract(Matrix a, Matrix b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot add null matrices.");
      if (a.getRows() != b.getRows() || a.getColumns() != b.getColumns())
         throw new MatrixDimensionException("Matrix dimension exception: matrix dimensions do not agree: "
               + a.getRows() + "x" + a.getColumns() + " and " + b.getRows() + "x" + b.getColumns());

      Matrix c = a.copy();
      for (int i = 0; i < a.getRows(); i++) {
         for (int j = 0; j < a.getColumns(); j++) {
            c.set(i, j, a.get(i, j) - b.get(i, j));
         }
      }
      return c;
   }


   public Matrix multiply(Matrix b) {
      set(multiply(this, b));
      return this;
   }

   public static final Matrix multiply(Matrix a, Matrix b) {
      if (a == null || b == null)
         throw new NullPointerException("Cannot multiply null matrices.");
      if (a.getColumns() != b.getRows())
         throw new MatrixDimensionException("Matrix dimension exception: matrix dimensions do not agree: "
               + a.getColumns() + " and " + b.getRows());

      Matrix c = new Matrix(a.getRows(), b.getColumns());
      for (int i = 0; i < c.getRows(); i++) {
         for (int j = 0; j < c.getColumns(); j++) {
            double sum = 0;
            for (int k = 0; k < b.getRows(); k++)
               sum += a.get(i, k) * b.get(k, j);
            c.set(i, j, sum);
         }
      }
      return c;
   }


   private void catchDimensions(int row, int column) {
      if ((row < 0 || row >= getRows()) && (column < 0 || column >= getColumns()))
         throw new MatrixDimensionException("Matrix dimension exception: row (" + row + ") and column (" + column
               + ") are not in the range of this matrix's dimensions (" + getRows() + ", " + getColumns() + ").");
      if (row < 0 || row >= getRows())
         throw new MatrixDimensionException("Matrix dimension exception: row (" + row
               + ") is not in the range of this matrix's dimensions (" + getRows() + ", " + getColumns() + ").");
      if (column < 0 || column >= getColumns())
         throw new MatrixDimensionException("Matrix dimension exception: column (" + column
               + ") is not in the range of this matrix's dimensions (" + getRows() + ", " + getColumns() + ").");
   }


   public void print() {
      print(System.out, 10, 1);
   }

   public void print(int spacing, int decimals) {
      print(System.out, spacing, decimals);
   }

   public void print(PrintStream os, int spacing, int decimals) {
      String format = "%" + spacing + "." + decimals + "f ";
      String print = new String();

      // os.print("-- ");
      print += "-- ";
      for (int j = 0; j < getColumns() * (spacing + 1) - 2; j++) {
         // os.print(" ");
         print += " ";
      }
      // os.println("--");
      print += "--\n";

      for (int i = 0; i < getRows(); i++) {
         // os.print("| ");
         print += "| ";
         for (int j = 0; j < getColumns(); j++) {
            // os.printf(format, get(i, j));
            print += String.format(format, get(i, j));
         }
         // os.println("|");
         print += "|\n";
      }

      // os.print("-- ");
      print += "-- ";
      for (int j = 0; j < getColumns() * (spacing + 1) - 2; j++) {
         // os.print(" ");
         print += " ";
      }
      // os.println("--");
      print += "--\n";

      os.print(print);
   }

   @Override
   public String toString() {
      return "Matrix: [" + getRows() + ", " + getColumns() + "]";
   }


   public Matrix copy() {
      // FIXME code: not need if set method copies matrix
      double[][] matrix = new double[rows][columns];
      for (int i = 0; i < rows; i++) {
         for (int j = 0; j < columns; j++) {
            matrix[i][j] = this.matrix[i][j];
         }
      }
      return new Matrix(matrix);
   }

   @Override
   protected Object clone() {
      return copy();
   }

   @Override
   public boolean equals(Object obj) {
      if (obj instanceof Matrix) {
         Matrix a = (Matrix) obj;
         boolean result = getRows() == a.getRows() && getColumns() == a.getColumns();
         for (int i = 0; i < getRows() && result; i++) {
            for (int j = 0; j < getColumns() && result; j++) {
               result = matrix[i][j] == a.matrix[i][j];
            }
         }
         return result;
      }
      return super.equals(obj);
   }

}
