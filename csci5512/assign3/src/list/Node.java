package list;

public class Node {

   private Test   test_;
   private Node   next_;
   private String value_;

   public Node(Test test, Node next, String value) {
      test_ = test;
      next_ = next;
      value_ = value;
   }

   public void print(String parent) {
      if (test_ != null) {
         String newParent = parent + ": (" + test_.getAttribute() + "=" + test_.getValue() + ")";
         System.out.println(newParent + ": " + value_);
         next_.print(newParent);
         // for (int i = 0; i < subNodes_.length; i++) {
         // subNodes_[i].print(newParent + "=" + splitter_.getPossible()[i] + ")");
         // }
      } else {
         System.out.println(parent + ": " + value_);
      }
   }

   public String get(String[] data) {
      if (next_ == null || test_.test(data)) {
         return value_;
      } else {
         return next_.get(data);
      }
   }
}
