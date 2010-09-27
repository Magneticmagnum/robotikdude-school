package sort;

public class Assignment2 {

   public static void main(String[] args) {
      // for (int i = 1; i < args.length; i++) {
      // if (args[i].startsWith("--")) {
      // if (args[i].equals("--help")) {
      //
      // }
      // } else if (args[i].startsWith("-")) {
      //
      // }
      // }
      SortingAlgorithm[] algorithms = {
         new Mergesort(),
         new Heapsort(),
         new QuickSort(new RandomPivot(), new BeginningPartitioning()),
         new QuickSort(new MedThreeRandomPivot(), new BeginningPartitioning()),
         new QuickSort(new MedFiveRandomPivot(), new BeginningPartitioning()),
         new QuickSort(new RandomPivot(), new EndsPartitioning()),
         new QuickSort(new MedThreeRandomPivot(), new EndsPartitioning()),
         new QuickSort(new MedFiveRandomPivot(), new EndsPartitioning()) };

      SortingAlgorithm quick = new Mergesort();

      int a[] = { 2, 6, 1, 56, 9, 4, 21, 45, 9, 43, 5 };

      System.out.print("A: ");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + ", ");
      System.out.println();

      quick.sort(a);

      System.out.print("A: ");
      for (int i = 0; i < a.length; i++)
         System.out.print(a[i] + ", ");
      System.out.println();
   }

   private static void help(String[] args) {
      System.out.println("");
   }
}
