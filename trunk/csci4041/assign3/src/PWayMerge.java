public class PWayMerge {
   public PWayMerge(int start, int end) {
      this.start = start;
      this.end = end;
      this.i = 0;
   }

   public int start;
   public int end;

   public int i;
   public double spacing = 1;

   public int index() {
      return start + (int) (i * spacing);
   }
}
