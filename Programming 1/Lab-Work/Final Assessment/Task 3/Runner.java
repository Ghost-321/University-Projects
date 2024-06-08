
public class Runner {

	public static void main(String[] args) {
		GameMap map = new GameMap(2, 2);
		Location tl = new Location(false, true, false, false, false);
		Location tr = new Location(false, false, true, true, false);
		Location bl = new Location(false, true, false, false, true);
		Location br = new Location(true, false, false, true, false);

		map.setLocation(0, 0, tl);
		map.setLocation(0, 1, tr);
		map.setLocation(1, 0, bl);
		map.setLocation(1, 1, br);

		Game game = new Game(map);
		
		game.playGame();
		
	}

}
