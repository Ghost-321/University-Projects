import java.util.ArrayList;
public class Team {
    private String name;
    private ArrayList<Player> players;

    public Team(String name) {
        this.name = name;
        this.players = new ArrayList<>();
    }
    public void addPlayer(Player player) {
    players.add(player);
}
    public ArrayList<Player> getPlayers() {
        return players;
}

    public String getNames() {
        return this.name;
    }

    public int getNumberPlayers() {
    return players.size();
}

    public double getAveragePlayerCredit() {
        if (players.size() == 0) {
            return 0;
        }
    double sum = 0;
    for (Player player : players) {
        sum += player.getCredit();
    }
    return sum / players.size();
}

    public double getAverageAge() {
        if (players.size() == 0) {
            return 0;
        }
    double sum = 0;
    for (Player player : players) {
        sum += player.getAge();
    }
    return sum / players.size();
}
    public void deletePlayer(Player player) {
        this.players.remove(player);
}
}
