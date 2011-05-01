package nn.graphics;

import java.awt.Color;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Set;

import robocode.RobocodeFileWriter;

public class DrawMenu {

   public static double           START_X          = 0.0D;
   public static double           START_Y          = 1.0D;

   public static final double     RECTANGLE_WIDTH  = 70.0D;
   public static final double     RECTANGLE_HEIGHT = 12.0D;

   public static final double     STRING_OFFSET_X  = 2.0D;
   public static final double     STRING_OFFSET_Y  = 2.0D;

   public static final Color      MENU_OPEN        = Colors.TURQUOISE;
   public static final Color      MENU_CLOSED      = Colors.RED;

   public static final Color      ITEM_ON          = Colors.LIME_GREEN;
   public static final Color      ITEM_OFF         = Colors.RED;

   private static boolean         open             = false;

   private static ArrayList<Menu> menus            = new ArrayList<Menu>();

   public static boolean getValue(String item, String menu) {
      return getValue(item, menu, false);
   }

   public static boolean getValue(String item, String menu, boolean def) {
      Menu m = getMenu(menu);
      if (m == null) {
         menus.add(m = new Menu(menu));
      }
      return m.getValue(item, def);
   }

   public static void inMouseEvent(final MouseEvent e) {
      if (e.getID() == MouseEvent.MOUSE_CLICKED) {
         if (open) {
            boolean found = false;

            // finds item
            for (int i = 0; i < menus.size() && !found; i++)
               found = menus.get(i).inMouseEvent(e, START_X + (RECTANGLE_WIDTH + 1.0D),
                     START_Y + (i + 1.0D) * (RECTANGLE_HEIGHT + 1.0D));
            if (!found) {
               double x = e.getX() - START_X;
               double y = e.getY() - START_Y;
               if (x <= RECTANGLE_WIDTH && x >= 0.0D && y >= RECTANGLE_HEIGHT + 1.0D)
                  for (int i = 0; i < menus.size() && !found; i++) {
                     if (y <= (i + 2.0D) * (RECTANGLE_HEIGHT + 1.0D)) {
                        Menu menu = menus.get(i);
                        if (menu.status()) {
                           menu.close();
                        } else {
                           for (Menu m : menus)
                              m.close();
                           menu.open();
                        }
                        found = true;
                     }
                  }
               if (!found) {
                  open = false;
                  for (Menu m : menus)
                     m.close();
               }
            }
         } else {
            double x = e.getX() - START_X;
            double y = e.getY() - START_Y;
            if (x <= RECTANGLE_WIDTH && y <= (RECTANGLE_HEIGHT + 1.0D) && y >= 0.0D && x >= 0.0D)
               open = true;
         }
      }
   }

   public static void draw(final RGraphics grid) {
      grid.setColor(MENU_CLOSED);
      if (open) {
         for (int i = 0; i < menus.size(); i++) {
            Menu menu = menus.get(i);
            grid.setColor(menu.status() ? MENU_OPEN : MENU_CLOSED);
            grid.drawRect(START_X, START_Y + (i + 1.0D) * (RECTANGLE_HEIGHT + 1.0D), RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
            grid.drawString(menu.getName(), START_X + STRING_OFFSET_X, START_Y + STRING_OFFSET_Y + (i + 1.0D)
                  * (RECTANGLE_HEIGHT + 1.0D));
            menu.draw(grid, START_X + (RECTANGLE_WIDTH + 1.0D), START_Y + (i + 1.0D) * (RECTANGLE_HEIGHT + 1.0D));
         }
         grid.setColor(MENU_OPEN);
      }
      grid.drawRect(START_X, START_Y, RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
      grid.drawString("Draw Menu", START_X + STRING_OFFSET_X, START_Y + STRING_OFFSET_Y);
   }

   private static Menu getMenu(final String n) {
      for (Menu m : menus)
         if (m.getName().equals(n))
            return m;
      return null;
   }

   public static void save(File file) {
      try {
         PrintWriter out = new PrintWriter(new RobocodeFileWriter(file));
         for (Menu m : menus) {
            Set<String> items = m.getItems();
            for (String i : items)
               out.println(m.getName() + "," + i + "," + m.getValue(i, false));
         }
         out.close();
         System.out.println("DrawMenu saved to " + file.getName());
      } catch (IOException e) {
      }
   }

   public static void load(File file) {
      try {
         BufferedReader in = new BufferedReader(new FileReader(file));
         String l;
         while ((l = in.readLine()) != null) {
            String[] spl = l.split("\\s*,\\s*");
            String menu = spl[0];
            String item = spl[1];
            boolean bool = Boolean.parseBoolean(spl[2]);
            DrawMenu.getValue(item, menu, bool);
         }
         in.close();
         System.out.println("DrawMenu loaded from " + file.getName());
      } catch (IOException e) {
      }
   }
}
