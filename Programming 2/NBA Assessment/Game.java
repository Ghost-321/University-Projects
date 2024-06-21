import java.util.ArrayList;

public class Game {
    private ArrayList<Team> teams;
    private ArrayList<Team> results;
    private Integer round;

    public Game() {
        this.round = 1;
        this.teams = new ArrayList<Team>();
        this.results = new ArrayList<Team>();
    }

    public ArrayList<Team> getTeams() {
        return teams;
    }

    public void setTeams(ArrayList<Team> teams) {
        this.teams = teams;
    }

    public ArrayList<Team> getResults() {
        return results;
    }

    public void setResults(ArrayList<Team> results) {
        this.results = results;
    }

    public Integer getRound() {
        return round;
    }

    public void setRound(Integer round) {
        this.round = round;
    }
}
