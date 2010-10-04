/* 
 * CSci4041 F2010 Assignment 2
 * section: 3
 * login: norma272
 * date: 10/4/19
 * name: Brian E Norman
 * id: 4332223
 */


public class hsort implements SortingAlgorithm {

   public static void main(String[] args) {
      // pass the the hard work off to a separate function
      Utils.runSort("hsort", args, new hsort());
   }


   // *************************************************************************
   // The following is the actual sorting method for this program
   // *************************************************************************

   @Override
   public void sort(double[] a, boolean increasing) {
      // build the heap
      buildHeap(a, increasing);
      
      // iteratively select the top element of the heap and swap it with the
      // last element of the array and make the heap one element shorter
      int heapSize = a.length;
      for (int i = a.length - 1; i >= 1; i--) {

         double temp = a[0];
         a[0] = a[i];
         a[i] = temp;

         heapSize--;
         
         // cascade the first element down the heap if necessary
         heapify(a, heapSize, 0, increasing);
      }
   }

   private void buildHeap(double[] a, boolean increasing) {
      for (int i = (a.length - 1) / 2; i >= 0; i--) {
         heapify(a, a.length, i, increasing);
      }
   }

   private void heapify(double[] a, int heapSize, int i, boolean increasing) {
      int l = 2 * i;
      int r = l + 1;
      int largest;
      if (l < heapSize
            && ((increasing && a[l] > a[i]) || (!increasing && a[l] < a[i]))) {
         largest = l;
      } else {
         largest = i;
      }
      if (r < heapSize
            && ((increasing && a[r] > a[largest]) || (!increasing && a[r] < a[largest]))) {
         largest = r;
      }
      if (largest != i) {
         double temp = a[i];
         a[i] = a[largest];
         a[largest] = temp;

         heapify(a, heapSize, largest, increasing);
      }
   }

}
