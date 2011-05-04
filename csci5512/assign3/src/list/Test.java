package list;

public class Test {

   private String attr_;
   private String value_;
   private int    index_;

   public Test(String attr, String value, int index) {
      attr_ = attr;
      value_ = value;
      index_ = index;
   }

   public boolean test(String[] data) {
      return value_.equals(data[index_]);
   }

   public String getAttribute() {
      return attr_;
   }

   public String getValue() {
      return value_;
   }

   public int getIndex() {
      return index_;
   }

   public int matches(String[][] data) {
      int matches = 0;
      String result = null;
      for (int i = 0; i < data.length; i++) {
         if (data[i][index_].equals(value_)) {
            if (result == null) {
               result = data[i][0];
               matches++;
            } else if (result.equals(data[i][0])) {
               matches++;
            } else {
               return -42;
            }
         }
      }
      return matches;
   }

   public String result(String[][] data) {
      int matches = 0;
      String result = null;
      for (int i = 0; i < data.length; i++) {
         if (data[i][index_].equals(value_)) {
            if (result == null) {
               result = data[i][0];
            } else if (result.equals(data[i][0])) {
               matches++;
            } else {
               return "NO MATCHES";
            }
         }
      }
      return result;
   }

   public String[][] remove(String[][] data) {
      int nonMatches = data.length - matches(data);
      String[][] newdata = new String[nonMatches][];
      int i = 0, j = 0;
      for (; i < data.length; i++) {
         if (!data[i][index_].equals(value_)) {
            newdata[j++] = data[i];
         }
      }
      if (j != nonMatches) {
         for (int n = 0; n < data.length; n++) {
            for (int m = 0; m < data[n].length; m++) {
               System.out.print(data[n][m] + ", ");
            }
            System.out.println();
         }
         System.out.println();
         return null;
      }
      return newdata;
   }

}
