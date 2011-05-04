import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Scanner;

import list.Node;
import list.Test;


public class dlist2 {

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
      ArrayList<Test> tests = new ArrayList<Test>(attrCount);

      dataScanner = new Scanner(dataFile);
      Scanner lineScanner = new Scanner(dataScanner.nextLine());
      lineScanner.useDelimiter("\\s*,\\s*");
      lineScanner.next();
      for (int i = 0; i < attrCount; i++) {
         String attr = lineScanner.next();
         for (int j = 0; j < attrValues[i].size(); j++) {
            tests.add(new Test(attr, attrValues[i].get(j), i + 1));
         }
      }

      Node root = buildList(data, tests, 4);

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

   public static Node buildList(String[][] data, ArrayList<Test> tests, int depth) {
      if (data.length <= 0) {
         return new Node(null, null, "NO DATA");
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
         return new Node(null, null, ans);
      }

      if (depth <= 0) {
         String best = mostPopular(data);
         return new Node(null, null, best + " ENDED");
      }

      Test best = null;
      int max = -42;
      for (Test t : tests) {
         int matches = t.matches(data);
         if (matches > max) {
            max = matches;
            best = t;
         }
      }
      tests.remove(best);
      Node next = buildList(best.remove(data), tests, depth - 2);
      return new Node(best, next, best.result(data));
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

}
