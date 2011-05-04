package math.matrices;

// BORED document: math.matrices.MatrixDimensionException
public class MatrixDimensionException extends RuntimeException {

   /**
    * Determines if a deserialized file is compatible with {@code this class}. <br>
    * <br>
    * Maintainers must change this value if and only if the new version of {@code this class} is not
    * compatible with old versions.
    */
   private static final long serialVersionUID = -4196177985686327090L;


   /**
    * Constructs a {@code MatrixDimensionException} with no detail message.
    */
   public MatrixDimensionException() {
      super();
   }

   /**
    * Constructs a {@code MatrixDimensionException} with the specified detail message.
    * 
    * @param s
    *           the detail message.
    */
   public MatrixDimensionException(String s) {
      super(s);
   }

}
