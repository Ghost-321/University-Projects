import java.util.ArrayList;
public class Season {
    private ArrayList<Game> schedule;
    private ArrayList<Team> currentTeamList;
    private Integer round;
    private ArrayList<Record>  records;
    private ArrayList<Team> availableTeams;
    
    public Season(ArrayList<Team> teamsList) {
        this.availableTeams = teamsList; 
    }
    public void displayAvailableTeams() {
            System.out.println("Suns Bulls Hawks Nets");
    }
public String addTeamToRound(String teamName) {
    for (Team team : currentTeamList) {
        if (team.getNames().equals(teamName)) {
            return "Error: Team is already in the current round.";
        }
    }
    Team teamToAdd = null;
    for (Team team : availableTeams) {
        if (team.getNames().equals(teamName)) {
            teamToAdd = team;
            break;
        }
    }
    if (teamToAdd == null) {
        return "Error: Team not found in the list of available teams.";
    }
    currentTeamList.add(teamToAdd);
    return "Success: Team " + teamName + " added to the current round.";
}
    public void displayCurrentRound() {
    System.out.println("Current round: " + round);
    for (Game game : schedule) {
        if (game.getRound() == round) {
            System.out.println(game.toString());
        }
    }
}

}
