package sort;


public class Assignment2 {

   public static void main(String[] args) {
      Utils.Options opts = Utils.processArgs(args);
      if (opts.HELP) {
         Utils.help(args);
         return;
      }

      double[] list = null;

      if (opts.FILE && !opts.CREATE && opts.LIST != null) {
         list = Utils.read(opts.LIST);
      } else if (!opts.FILE) {
         list = Utils.create(opts.SIZE);
      } else if (opts.LIST == null) {
         // error, no file location specified.
      } else {
         // error, options conflict
      }

      if (list != null) {
         SortingAlgorithm[] algorithms = {
            new Mergesort(),
            new Heapsort(),
            new QuickSort(new RandomPivot(), new BeginningPartitioning()),
            new QuickSort(new MedThreeRandomPivot(),
                  new BeginningPartitioning()),
            new QuickSort(new MedFiveRandomPivot(), new BeginningPartitioning()),
            new QuickSort(new RandomPivot(), new EndsPartitioning()),
            new QuickSort(new MedThreeRandomPivot(), new EndsPartitioning()),
            new QuickSort(new MedFiveRandomPivot(), new EndsPartitioning()) };

         SortingAlgorithm quick = new Mergesort();

         double[] a = { 2, 6, 1, 56, 9, 4, 21, 45, 9, 43, 5 };

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
   }
}
