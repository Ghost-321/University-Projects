import java.util.Scanner;

public class Game {

    private GameMap map;
    private int col;
    private int row;
    private boolean [][] visited;

    public Game(GameMap map) {
        this.map = map;
        this.col = 0;
        this.row = 0;
        this.visited = new boolean[this.map.getHeight()][this.map.getWidth()];
        for (int e = 0; e != this.map.getHeight(); e++) {
            for (int i = 0; i != this.map.getWidth(); i++) {
                this.visited[e][i] = false; 
            }
        }
        this.visited [this.row][this.col] = true;
        this.map.getLocation(this.row, this.col).togglePlayerHere();
    }


    public void playGame () {
        Scanner sc = new Scanner (System.in);
        String dir;
        boolean approved;
        System.out.println("Welcome to the maze!");
        while (!this.map.getLocation(this.row, this.col).isExit()) {
            this.visited[this.row][this.col] = true;
            for (int e = 0; e != this.map.getHeight(); e++) {
                for (int i = 0; i != this.map.getWidth(); i++) {
                    if (this.visited[e][i]) {
                        System.out.print(this.map.getLocation(e, i).mapRepresentation());
                    }
                    else {
                        System.out.print(" ");
                    }
                }
                System.out.print("\n");
            }
            System.out.print(this.map.getLocation(this.row, this.col).toString());
            approved =false;
            while (!approved) {
                System.out.print("Which way would you like to go? ");
                dir = sc.nextLine();
                if (this.map.getLocation(this.row, this.col).hasDirection(dir)) {
                    approved = true;
                }
                if (!approved) {
                    System.out.println("You can't go that way! Try again.");
                }
                this.map.getLocation(this.row, this.col).togglePlayerHere();
                switch(dir) {
                    case "north":
                    if (this.map.getLocation(this.row, this.col).hasDirection(dir)) {
                        this.row -= 1;
                    }
                    break;
                    case "east":
                    if (this.map.getLocation(this.row, this.col).hasDirection(dir)) {
                        this.col += 1;
                    }
                    break;
                    case "south":
                    if (this.map.getLocation(this.row, this.col).hasDirection(dir)) {
                        this.row += 1;
                    }
                    break;
                    case "west" :
                    if (this.map.getLocation(this.row, this.col).hasDirection(dir)) {
                        this.col -= 1;
                    }
                    break;
                    default:
                    break;
                }
                this.map.getLocation(this.row, this.col).togglePlayerHere();
            }
        }
        this.visited[this.row][this.col] = true;
        for (int e = 0; e != this.map.getHeight(); e++) {
            for (int i = 0; i != this.map.getWidth(); i++) {
                if (this.visited[e][i]) {
                    System.out.print(this.map.getLocation (e, i).mapRepresentation());
                }
            }
            System.out.print("\n");
        }
        System.out.print("You made it to an exit. You have escaped!");
    }
}
