public class samplesort {

   public static void main(String[] args) {
      QuickSort sort = new QuickSort();
      double[] array = {
            22, 7, 2, 67, 9, 3, 7, 32, 7, 12, 67, 5, 1, 17, 1
      };

      sort.sort(array);

      System.out.print("A: ");
      for (int i = 0; i < array.length; i++) {
         System.out.print(array[i] + ", ");
      }
      System.out.println();
   }

}
