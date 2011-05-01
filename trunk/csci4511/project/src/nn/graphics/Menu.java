package nn.graphics;

import static nn.graphics.DrawMenu.ITEM_OFF;
import static nn.graphics.DrawMenu.ITEM_ON;
import static nn.graphics.DrawMenu.RECTANGLE_HEIGHT;
import static nn.graphics.DrawMenu.RECTANGLE_WIDTH;
import static nn.graphics.DrawMenu.STRING_OFFSET_X;
import static nn.graphics.DrawMenu.STRING_OFFSET_Y;

import java.awt.event.MouseEvent;
import java.util.HashMap;
import java.util.Set;

public class Menu {

	private String name;
	private boolean open;
	private HashMap<String, Boolean> items;

	public Menu(String name) {
		this.name = name;
		this.items = new HashMap<String, Boolean>();
	}

	public boolean getValue(String item, boolean def) {
		Boolean value = items.get(item);
		if (value == null) {
			items.put(item, value = def);
		}
		return value;
	}

	public String getName() {
		return name;
	}

	public boolean status() {
		return open;
	}

	public void open() {
		open = true;
	}

	public void close() {
		open = false;
	}

	public boolean inMouseEvent(MouseEvent e, double startX, double startY) {
		boolean found = false;
		if (open && e.getID() == MouseEvent.MOUSE_CLICKED) {
			double x = e.getX() - startX;
			double y = e.getY() - startY;
			if (x <= RECTANGLE_WIDTH && x >= 0.0D && y >= 0.0D) {
				for (int i = 0; i < items.keySet().size() && !found; i++) {
					if (y <= (i + 1.0D) * (RECTANGLE_HEIGHT + 1.0D)) {
						String s = (String) (items.keySet().toArray())[i];
						items.put(s, !items.get(s));
						found = true;
					}
				}
			}
		}
		return found;
	}

	public void draw(RGraphics grid, double startX, double startY) {
		if (open) {
			// FontMetrics fm = grid.getFontMetrics();
			// for (String s : items.keySet()) {
			// int width = fm.stringWidth(s) + 8;
			// RECTANGLE_WIDTH = Math.max(RECTANGLE_WIDTH, width);
			// }

			Object[] keys = items.keySet().toArray();
			for (int i = 0; i < keys.length; i++) {
				String s = (String) keys[i];
				grid.setColor(items.get(s) ? ITEM_ON : ITEM_OFF);
				grid.drawRect(startX, startY + i * (RECTANGLE_HEIGHT + 1.0D),
						RECTANGLE_WIDTH, RECTANGLE_HEIGHT);
				grid.drawString(s, startX + STRING_OFFSET_X, startY
						+ STRING_OFFSET_Y + i * (RECTANGLE_HEIGHT + 1.0D));
			}
		}
	}

	public Set<String> getItems() {
		// TODO Auto-generated method stub
		return items.keySet();
	}

}
