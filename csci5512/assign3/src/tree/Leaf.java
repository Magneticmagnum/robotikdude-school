package tree;

public class Leaf extends Node {

   private String value_;

   public Leaf(String value) {
      super(null, null);
      value_ = value;
   }

   @Override
   public String getValue(String[] attributes) {
      return value_;
   }

   public void print(String parent) {
      System.out.println(parent + ": " + value_);
   }

   @Override
   public String get(String[] data) {
      return value_;
   }

}
