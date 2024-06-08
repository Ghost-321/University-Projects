public class Location {

    private static final String[] INACTIVE_SYMBOLS = { " ", "╴", "╷", "┐", "╶", "─", "┌", "┬", "╵", "┘", "│", "┤", "└", "┴", "├", "┼" };
	private static final String[] ACTIVE_SYMBOLS = { " ", "╸", "╻", "┓", "╺", "━", "┏", "┳", "╹", "┛", "┃", "┫", "┗", "┻", "┣", "╋" };


    private boolean north;
    private boolean east;
    private boolean south;
    private boolean west;
    private boolean exit; 
    private boolean here;

    public Location(boolean north, boolean east, boolean south, boolean west, boolean exit){
        this.north = north;
        this.east = east;
        this.south = south;
        this.west = west;
        this.exit = exit;
        this.here = false;
    }

    public boolean isExit() {
        return this.exit;
    }

    public boolean hasDirection(String direction) {
        switch (direction)  { 
            case "north":
            return this.north;
            case "east":
            return this.east;
            case "south":
            return this.south;
            case "west":
            return this.west;
            default:
            return false;

        }
    }
     @Override
    public String toString ()  {
        String string = "Available directions:\n";

        if (this.hasDirection("north")){
        string += "north\n";
        }
        if (this.hasDirection ("east")) {
            string += "east\n";
        }
        if (this.hasDirection("south")) {
            string += "south\n";
        }
        if (this.hasDirection ("west")) {
            string += "west\n";
        }
        return string;
    }

    public void togglePlayerHere() {
        if (this.here) {
            this.here = false;
        }
        else {
            this.here = true;
        }
    }

    public String mapRepresentation() {
        String symbol;
        
        String binary_str = "";
        if (this.hasDirection("north")) {
            binary_str += "1";
        }
        else {
            binary_str += "0";
        }
        if (this.hasDirection("east")) {
            binary_str += "1";
        }
        else {
            binary_str += "0";

        }
        if (this.hasDirection("south")) {
            binary_str += "1";
        }
        else {
            binary_str +="0";
        }
        if (this.hasDirection("west")) {
        binary_str += "1";

    }
    else {
        binary_str += "0";
    }
    if (this.here) {
        symbol = ACTIVE_SYMBOLS[Integer.parseInt(binary_str, 2)];

    }

    else {
        symbol = INACTIVE_SYMBOLS[Integer.parseInt(binary_str, 2)];
    }
    return symbol;
        }
    }
