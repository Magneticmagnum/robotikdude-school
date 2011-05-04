import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import tree.Attribute;
import tree.Leaf;
import tree.Node;


public class dtree4 {

   public static void main(String[] args) throws FileNotFoundException {
      if (args.length != 1) {
         System.err.println("not the right amount of argumnents");
         return;
      }

      File dataFile = new File(args[0]);
      if (!dataFile.isFile()) {
         System.err.println("data is not a file");
         return;
      } else if (!dataFile.canRead()) {
         System.err.println("data cannot be read");
         return;
      }


      // --------------------------------------------------
      // Get count of attributes and data
      // --------------------------------------------------
      int attrCount = -1;
      int dataCount = 0;

      Scanner dataScanner = new Scanner(dataFile);
      if (dataScanner.hasNextLine()) {
         Scanner lineScanner = new Scanner(dataScanner.nextLine());
         lineScanner.useDelimiter("\\s*,\\s*");
         while (lineScanner.hasNext()) {
            lineScanner.next();
            attrCount++;
         }
      }
      while (dataScanner.hasNextLine()) {
         dataScanner.nextLine();
         dataCount++;
      }


      // --------------------------------------------------
      // Load data and get different values for attributes
      // --------------------------------------------------
      ArrayList<String>[] attrValues = new ArrayList[attrCount];
      for (int i = 0; i < attrCount; i++) {
         attrValues[i] = new ArrayList<String>();
      }
      String[][] data = new String[dataCount][attrCount + 1];

      int dataIndex = 0;

      dataScanner = new Scanner(dataFile);
      dataScanner.nextLine(); // skip first line
      while (dataScanner.hasNextLine()) {
         Scanner lineScanner = new Scanner(dataScanner.nextLine());
         lineScanner.useDelimiter("\\s*,\\s*");

         int attrIndex = 0;
         while (lineScanner.hasNext()) {
            String piece = lineScanner.next();
            if (attrIndex != 0 && !attrValues[attrIndex - 1].contains(piece)) {
               attrValues[attrIndex - 1].add(piece);
            }
            data[dataIndex][attrIndex] = piece;
            attrIndex++;
         }
         dataIndex++;
      }


      // --------------------------------------------------
      // Build attribute list
      // --------------------------------------------------
      ArrayList<Attribute> attributes = new ArrayList<Attribute>(attrCount);

      dataScanner = new Scanner(dataFile);
      Scanner lineScanner = new Scanner(dataScanner.nextLine());
      lineScanner.useDelimiter("\\s*,\\s*");
      lineScanner.next();
      for (int i = 0; i < attrCount; i++) {
         attributes.add(new Attribute(lineScanner.next(), attrValues[i].toArray(new String[attrValues[i].size()]),
               i + 1));
      }

      Node root = buildTree(data, attributes, data, 4);

      root.print("root");

      double wrong = 0.0;
      for (int i = 0; i < data.length; i++) {
         if (!data[i][0].equals(root.get(data[i]))) {
            wrong++;
         }
      }
      System.out.println("wrong = " + wrong);
      System.out.println("percentage = " + wrong / data.length);
   }

   private static Node buildTree(String[][] data, ArrayList<Attribute> attributes, String[][] parentData, int depth) {
      if (data.length <= 0) {
         return new Leaf(mostPopular(parentData));
      }

      boolean allSame = true;
      String ans = data[0][0];
      for (String[] s : data) {
         if (!ans.equals(s[0])) {
            allSame = false;
            break;
         }
      }
      if (allSame) {
         return new Leaf(ans);
      }

      if (depth <= 0) {
         return new Leaf(mostPopular(data) + " ENDED");
      }

      Attribute a = bestAttribute(data, attributes);
      ArrayList<Attribute> subTreeAttributes = (ArrayList<Attribute>) attributes.clone();
      subTreeAttributes.remove(a);
      Node[] subTrees = new Node[a.getNumPossible()];
      String[][][] splitData = a.getSplitData(data);
      for (int i = 0; i < subTrees.length; i++) {
         subTrees[i] = buildTree(splitData[i], subTreeAttributes, data, depth - 1);
      }
      return new Node(a, subTrees);
   }

   private static String mostPopular(String[][] data) {
      HashMap<String, Integer> possible = new HashMap<String, Integer>();
      for (int i = 0; i < data.length; i++) {
         if (!possible.containsKey(data[i][0])) {
            possible.put(data[i][0], 1);
         } else {
            possible.put(data[i][0], possible.get(data[i][0]) + 1);
         }
      }
      int max = 0;
      String key = "NOT FOUND";
      for (String k : possible.keySet()) {
         if (possible.get(k) > max) {
            max = possible.get(k);
            key = k;
         }
      }
      return key;
   }

   private static Attribute bestAttribute(String[][] data, ArrayList<Attribute> attributes) {
      double min = Double.POSITIVE_INFINITY;
      int minIndex = -42;
      for (int i = 0; i < attributes.size(); i++) {
         double entropy = attributes.get(i).entropy(data);
         // System.out.println(attributes.get(i).getName() + ": " + entropy + ", ");
         // int[] counts = attributes.get(i).getCounts(data);
         // double entropy = 0;
         // for (int j = 0; j < counts.length; j++) {
         // double prob = (double) counts[j] / data.length;
         // entropy += -prob * Math.log(prob) / Math.log(2.0);
         // }
         if (entropy < min) {
            min = entropy;
            minIndex = i;
         }
      }
      // System.out.println(attributes.get(minIndex).getName() + " WINS!");
      // System.out.println();
      return attributes.get(minIndex);
   }

}
