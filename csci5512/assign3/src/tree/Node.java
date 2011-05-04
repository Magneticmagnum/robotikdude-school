package tree;

public class Node {

   private Node[]    subNodes_;
   private Attribute splitter_;

   public Node(Attribute splitter, Node[] subNodes) {
      splitter_ = splitter;
      subNodes_ = subNodes;
   }

   public String getValue(String[] attributes) {
      return subNodes_[splitter_.getIndex(attributes)].getValue(attributes);
   }

   public void print(String parent) {
      String newParent = parent + ": (" + splitter_.getName();
      // System.out.println(newParent);
      for (int i = 0; i < subNodes_.length; i++) {
         subNodes_[i].print(newParent + "=" + splitter_.getPossible()[i] + ")");
      }
   }

   public String get(String[] data) {
      return subNodes_[splitter_.getIndex(data)].get(data);
   }

}
