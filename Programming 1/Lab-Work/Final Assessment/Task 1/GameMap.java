public class GameMap {
    
    private int height;
    private int width;

    private Location[][] map;

    public GameMap(int height, int width) {
        if (height >= 0) {
            this.height = height;
        }
        else {
            this.height = 0;
        }

        if (width >= 0) {
            this.width = width;
        }
        else {
            this.width = 0;
        }

        this.map = new Location[this.height][this.width];
    }

    public int getHeight() {
        return this.height;
    }

    public int getWidth() {
        return this.width;
    }

    public boolean setLocation(int row, int col, Location location) {
        boolean took_action;
        try {
            if (this.map[row][col] == null) {
                this.map[row][col] = location;
                took_action = true;
            }
            else {
                took_action = false;
            }
        }
        catch (IndexOutOfBoundsException e) {
            took_action = false;
        }
        return took_action;
    }
    
    public Location getLocation(int row, int col) {
        try {
            return map[row][col];
        }
        catch (IndexOutOfBoundsException e) {
            return null;
        }
    }

    @Override
    public String toString () {
        String map_str = "";
        for (int row = 0; row < this.height; row++) {
            for (int col = 0; col < this.width; col++) {
                map_str += this.map[row][col].mapRepresentation();
            }
            map_str += "\n";
        }
        return map_str;
    }
}
