package sort;
public class Assignment2 {

   public static void main(String[] args) {
      for (int i = 1; i < args.length; i++) {
         if (args[i].startsWith("--")) {
            if (args[i].equals("--help")) {
               
            }
         } else if (args[i].startsWith("-")) {

         }
      }
      SortingAlgorithm[] algorithms = { new Mergesort(), new Heapsort() };
   }

   private static void help(String[] args) {
      System.out.println("");
   }
}
