package tree;

public class Attribute {

   private String   name_;
   private String[] values_;
   private int      index_;

   public Attribute(String name, String[] values, int index) {
      name_ = name;
      values_ = values;
      index_ = index;
   }

   public String getName() {
      return name_;
   }

   public int getNumPossible() {
      return values_.length;
   }

   public String[] getPossible() {
      return values_;
   }

   public int getIndex(String[] attributes) {
      for (int i = 0; i < values_.length; i++) {
         if (values_[i].equals(attributes[index_])) {
            return i;
         }
      }
      return -42;
   }

   public double entropy(String[][] data) {
      double[] countTotal = new double[values_.length];
      double[] countTrue = new double[values_.length];

      for (int i = 0; i < data.length; i++) {
         int index = getIndex(data[i]);
         countTotal[index]++;
         if (data[i][0].equals("T")) {
            countTrue[index]++;
         }
      }

      double entropy = 0.0;
      for (int i = 0; i < countTotal.length; i++) {
         double probT = countTrue[i] / countTotal[i];
         double probF = 1.0 - probT;
         double temp = 0.0;
         if (probT != 0.0) {
            temp -= probT * Math.log(probT) / Math.log(2.0);
         }
         if (probF != 0.0) {
            temp -= probF * Math.log(probF) / Math.log(2.0);
         }
         // System.out.println("   P(" + values_[i] + "): " + countTrue[i] + " / " + countTotal[i] + " = " + probT);
         if (countTotal[i] != 0.0) {
            entropy += countTotal[i] / data.length * temp;
         }
      }

      return entropy;
   }

   public int[] getCounts(String[][] data) {
      int[] counts = new int[values_.length];
      for (int i = 0; i < data.length; i++) {
         counts[getIndex(data[i])]++;
      }
      return counts;
   }

   public String[][][] getSplitData(String[][] data) {
      String[][][] split = new String[values_.length][][];
      int[] counts = getCounts(data);
      for (int i = 0; i < split.length; i++) {
         split[i] = new String[counts[i]][];
      }

      counts = new int[values_.length];
      for (int i = 0; i < data.length; i++) {
         int index = getIndex(data[i]);
         split[index][counts[index]++] = data[i];
      }
      return split;
   }
}
