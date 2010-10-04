/* 
 * CSci4041 F2010 Assignment 2
 * section: 3
 * login: norma272
 * date: 10/4/19
 * name: Brian E Norman
 * id: 4332223
 */


public class msort implements SortingAlgorithm {

   public static void main(String[] args) {
      // pass the the hard work of to a separate function
      Utils.runSort("msort", args, new msort());
   }


   // *************************************************************************
   // The following is the actual sorting method for this program
   // *************************************************************************

   @Override
   public void sort(double[] a, boolean increasing) {
      recursive(a, 0, a.length - 1, increasing);
   }

   private void recursive(double[] a, int start, int end, boolean increasing) {
      int mid = start + (end - start) / 2;
      if (mid != start)
         recursive(a, start, mid, increasing);
      if (mid != end)
         recursive(a, mid + 1, end, increasing);

      // combine the left and right sub arrays into one array be copying the
      // first array into a temporary array
      double[] temp = new double[mid - start + 1];
      for (int i = 0; i < temp.length; i++)
         temp[i] = a[start + i];

      int i = start;
      int j = 0;
      int k = mid + 1;
      while (j < temp.length && k <= end) {
         if ((increasing && a[k] < temp[j]) || (!increasing && a[k] > temp[j]))
            a[i++] = a[k++];
         else
            a[i++] = temp[j++];
      }
      if (j == temp.length) {
         while (k <= end)
            a[i++] = a[k++];
      } else {
         while (j < temp.length)
            a[i++] = temp[j++];
      }
   }

}
