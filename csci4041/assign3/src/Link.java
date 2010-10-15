public class Link {

   Link next;
   double value;

   public Link(double value) {
      this.value = value;
   }

   public Link(double value, Link next) {
      this.value = value;
      this.next = next;
   }
}
