import java.util.ArrayList;

public class Teams {
    private ArrayList<Team> teamsList;
         public Teams() {
        teamsList = new ArrayList<>();
    }

    public void addTeam(Team team) {
        teamsList.add(team);
    }

    public void removeTeam(Team team) {
        teamsList.remove(team);
    }

    public ArrayList<Team> getTeamsList() {
        return teamsList;
    }
    public void deleteTeam(Team team) {
    teamsList.remove(team);
}
}
