import java.util.Scanner;

public class Association {
private Teams teams;
private Game game;
private Season season;
private Scanner scanner;
private boolean exit;

    public Association() {
        scanner = new Scanner(System.in);
        exit = false;
        teams = new Teams();

        Team suns = new Team("Suns");
        suns.addPlayer(new Player("Devin Booker", 2500.0, 26, 1, "Suns"));
        suns.addPlayer(new Player("Chris Paul", 1500.0, 37, 3, "Suns"));
        suns.addPlayer(new Player("Deandre Ayton", 2000.0, 24, 22, "Suns"));
        suns.addPlayer(new Player("Kevin Durant", 3000.0, 34, 35, "Suns"));
        suns.addPlayer(new Player("Terrence Ross", 1000.0, 32, 8, "Suns"));
        teams.getTeamsList().add(suns);

        Team bulls = new Team("Bulls");
        bulls.addPlayer(new Player("Andre Drummond", 1500.0, 29, 3, "Bulls"));
        bulls.addPlayer(new Player("Zach LaVine", 3000.0, 28, 8, "Bulls"));
        bulls.addPlayer(new Player("Dalen Terry", 900.0, 20, 25, "Bulls"));
        bulls.addPlayer(new Player("Terry Taylor", 1000.0, 23, 32, "Bulls"));
        bulls.addPlayer(new Player("Carlik Jones", 800.0, 25, 22, "Bulls"));
        teams.getTeamsList().add(bulls);

        Team hawks = new Team("Hawks");
        hawks.addPlayer(new Player("Trae Young", 2200.0, 24, 11, "Hawks"));
        hawks.addPlayer(new Player("John Collins", 2000.0, 25, 20, "Hawks"));
        hawks.addPlayer(new Player("Aaron Holiday", 800.0, 26, 3, "Hawks"));
        hawks.addPlayer(new Player("Jalen Johnson", 1000.0, 21, 1, "Hawks"));
        hawks.addPlayer(new Player("Trent Forrest", 1200.0, 24, 2, "Hawks"));
        teams.getTeamsList().add(hawks);

        Team nets = new Team("Nets");
        nets.addPlayer(new Player("Mikal Bridges", 2400.0, 26, 1, "Nets"));
        nets.addPlayer(new Player("Ben Simmons", 2000.0, 26, 10, "Nets"));
        nets.addPlayer(new Player("Patty Mills", 900.0, 34, 8, "Nets"));
        nets.addPlayer(new Player("Joe Harris", 1200.0, 31, 12, "Nets"));
        nets.addPlayer(new Player("Seth Curry", 1900.0, 32, 30, "Nets"));
        teams.getTeamsList().add(nets);
    }



public static void main(String[] args) {
    Association association = new Association();
    association.use();
    System.out.print("Done\n");
}

public void use() {
    while (!exit) {
        System.out.print("Welcome to the Association! Please make a selection from the menu:\n" +
                "1. Explore the teams.\n" +
                "2. Arrange a new season.\n" +
                "X. Exit the system.\n" +
                "Enter a choice: ");
        String option = scanner.nextLine();

        switch (option) {
            case "1":
                exploreTeams();
                break;
            case "2":
               arrangeNewSeason();
               break;
            case "X":
                exit = true;
                break;
            default:
                System.out.println("Please enter a number 1 or 2, or press X to exit.");
                break;
        }
    }
}

private void exploreTeams() {
    exit = false;
    while (!exit) {
        System.out.print("Welcome to the Teams Page! Please make a selection from the menu:\n" +
                "1. Display all teams.\n" +
                "2. Display all players.\n" +
                "3. Add a new team.\n" +
                "4. Manage an existing team.\n" +
                "5. Delete an existing team.\n" +
                "6. Display all players by an level.\n" +
                "R. Return to previous menu.\n" +
                "Enter a choice: ");
        String option = scanner.nextLine();

        switch (option) {
            case "1":
                displayTeams();
                break;
            case "2":
                displayPlayers();
                break;
            case "3":
                addTeam();
                break;
            case "4":
                manageTeam();
                break;
            case "5":
                deleteTeam();
                break;
            case "6":
                displayPlayersByLevel();
                break;
            case "R":
            case "r":
                use();
                break;
        }
    }
}

private void arrangeNewSeason() {
    season = new Season(teams.getTeamsList());
    game = new Game();
    exit = false;
    while (!exit) {
        System.out.print("Welcome to the season page! Please make a selection from the menu:\n" +
                "1. Add a team to the round.\n" +
                "2. Display the current round.\n" +
                "3. Play games.\n" +
                "4. Display the game result records.\n" +
                "R. Return to previous menu.\n" +
                "Enter a choice: ");
        String option = scanner.nextLine();

        switch (option) {
            case "1":
                addTeamToRound();
                break;
            case "2":
                displayCurrentRound();
                break;
            case "3":
                playGames();
                break;
            case "4":
                displayGameResultRecords();
                break;
            case "R":
                use();
                break;
            default :
                System.out.println("Please enter a number between 1 and 4 or press R to return to the previous menu.");
        }
    }
}

private void displayTeams() {
    Utils.teamsHeader();
    for(Team team : teams.getTeamsList()){
        System.out.format(
            Utils.teamsFormat,
            team.getNames(),
            team.getNumberPlayers(),
            team.getAveragePlayerCredit(),
            team.getAverageAge()
        );
    }
    Utils.teamTableEnd();

}

private void displayPlayers() {
    Utils.DisplayPlayerFromAllTeamsHeader();
    for (Team team : teams.getTeamsList()) {
        for (Player player : team.getPlayers()) {
            System.out.format(
                Utils.DisplayPlayerFromAllTeamsFormat,
                player.getName(),
                player.getCredit(),
                player.getLevel(),
                player.getAge(),
                player.getNumber(),
                player.getTeam() 
            );
        }
        Utils.DisplayPlayerFromAllTeamsEnd();
    }
}
private void addTeam() {
    boolean addedTeam = false;
    String teamToAdd = "";
    System.out.print("Please enter the name of the team: "); 
    while (!addedTeam) {
        teamToAdd = scanner.nextLine();
        boolean teamExists = false;

        for (Team team : teams.getTeamsList()) {
            if (teamToAdd.equalsIgnoreCase(team.getNames())) {
                System.out.print("Team " + teamToAdd + " already exist! Please enter a new name: ");
                teamExists = true;
                break;
            }
        }

        if (!teamExists) {
            Team newTeam = new Team(teamToAdd);
            teams.addTeam(newTeam);
            addedTeam = true;
            System.out.println("Team " + teamToAdd + " added!");
        }
    }

}

private void manageTeam() {
    String teamToManage = "";
    System.out.print("Please enter the team's name that you want to manage: ");
    teamToManage = scanner.nextLine();
    boolean teamExists = false;
    Team teamFound = null;

    for (Team team : teams.getTeamsList()) {
        if (teamToManage.equalsIgnoreCase(team.getNames())) {
            teamExists = true;
            teamFound = team;
            break;
        }
    }

    if (!teamExists) {
        System.out.println("Team does not exist!");
    } else {
        boolean manageTeam = true;
        while (manageTeam) {
            System.out.print("Welcome to the " + teamFound.getNames() + " 's Page! Please make a selection from the menu:\n" +
                    "1. Display team's players.\n" +
                    "2. Add a new player.\n" +
                    "3. Update an existing player.\n" +
                    "4. Delete an existing player.\n" +
                    "R. Return to previous menu.\n" +
                    "Enter a choice: ");
            String option = scanner.nextLine();

            switch (option) {
                case "1":
                    Utils.playerHeader();
                    for (Player player : teamFound.getPlayers()) {
                        System.out.format(
                                Utils.PlayerFormat,
                                player.getName(),
                                player.getCredit(),
                                player.getLevel(),
                                player.getNumber(),
                                player.getAge(),
                                player.getTeam()
                        );
                    }
                    Utils.playerTableEnd();
                    break;
                case "2":
                    System.out.print("Please enter the player's name: ");
                    String name = scanner.nextLine();
                    System.out.print("Please enter the player's credit: ");
                    double credit = Double.parseDouble(scanner.nextLine());
                    System.out.print("Please enter the player's age: ");
                    int age = Integer.parseInt(scanner.nextLine());
                    int number = 0;

                    boolean numberTaken;
                    System.out.print("Please enter the player's No: ");
                    do {
                        number = Integer.parseInt(scanner.nextLine());
                        numberTaken = false;
                        for (Player player : teamFound.getPlayers()) {
                            if (player.getNumber() == number) {
                                numberTaken = true;
                                System.out.print("This No has been occupied by: "+player.getName()+". Please re-enter the No: ");
                                break;
                            }
                        }
                    } while (numberTaken);

                    teamFound.addPlayer(new Player(name, credit, age, number, teamFound.getNames()));
                    System.out.println("Player "+name+" added!");

                    break;
                case "3":
                    System.out.print("Please enter the player's name: ");
                    String oldName = scanner.nextLine();
                    Player playerToUpdate = null;

                    for (Player player : teamFound.getPlayers()) {
                        if (oldName.equalsIgnoreCase(player.getName())) {
                            playerToUpdate = player;
                            break;
                        }
                    }


                    if (playerToUpdate != null) {
                        System.out.print("Please enter the name: ");
                        String newName = scanner.nextLine();
                        System.out.print("Please enter the credit: ");
                        double newCredit = scanner.nextDouble();
                        System.out.print("Please enter the age: ");
                        int newAge = scanner.nextInt();
                        scanner.nextLine();

                        boolean numberTakenUpdate;
                        int newNumber;
                        System.out.print("Please enter the No: ");
                        do {
                            newNumber = scanner.nextInt();
                            numberTakenUpdate = false;
                            for (Player player : teamFound.getPlayers()) {
                                if (player.getNumber() == newNumber && player != playerToUpdate) {
                                    numberTakenUpdate = true;
                                    System.out.print("This No has been occupied by: " + player.getName() + ". Please re-enter the No: ");
                                    break;
                                }
                            }
                        } while (numberTakenUpdate);

                        playerToUpdate.setName(newName);
                        playerToUpdate.setCredit(newCredit);
                        playerToUpdate.setAge(newAge);
                        playerToUpdate.setNumber(newNumber);
                        playerToUpdate.setLevel(newCredit);

                        System.out.println("Player information updated.");
                        scanner.nextLine();
                        break;
                    } else {
                        System.out.println("Player does not exist.");
                        break;
                    }

                case "4":
                    System.out.print("Please enter the player's name: ");
                    boolean PlayerExisting = false;
                    Player playerFound = null;
                    name = scanner.nextLine();
                    for (Player player : teamFound.getPlayers()) {
                        if (name.equals(player.getName())) {
                            PlayerExisting = true;
                            playerFound = player;
                            break;
                        }
                    }
                    if(PlayerExisting){
                        teamFound.deletePlayer(playerFound);
                        System.out.println("Player deleted.");
                    }
                    else{
                        System.out.println("Player does not exist.");
                    }

                    break;
                case "R":
                    manageTeam = false;
                    break;
                default:
                    System.out.println("Please enter a valid option or press R to return to the previous menu.");
                    break;
            }
        }
    }
}

private void deleteTeam() {
    boolean deletedTeam = false;
    String teamToDelete = "";
    System.out.print("Please enter the team's name that you want to delete: "); 
    while (!deletedTeam) {

        teamToDelete = scanner.nextLine();
        Team teamFound = null;
        for (Team team : teams.getTeamsList()) {
            if (teamToDelete.equalsIgnoreCase(team.getNames())) {
                teamFound = team;
                break;
            }
        }

        teams.deleteTeam(teamFound);
        deletedTeam = true;
        System.out.println("The team " + teamToDelete + " has been deleted.");
    }
}

private void displayPlayersByLevel() {

    String level = "";
    System.out.print("Please enter the player's level that you want to view: ");
    level = scanner.nextLine();
    while (!level.equals("Edge") && !level.equals("Common") && !level.equals("Core") && !level.equals("All Star")){
        System.out.print("No such level! Please re-enter the level: ");
        level = scanner.nextLine();
    }

    Utils.DisplayPlayerFromAllTeamsHeader();
    for (Team team : teams.getTeamsList()) {
        for (Player player : team.getPlayers()) {
            if (player.getLevel().equalsIgnoreCase(level)) {
                System.out.format(
                        Utils.DisplayPlayerFromAllTeamsFormat,
                        player.getName(),
                        player.getCredit(),
                        player.getLevel(),
                        player.getAge(),
                        player.getNumber(),
                        player.getTeam()
                );
            }
        }
    }
    Utils.DisplayPlayerFromAllTeamsEnd();
}

private void addTeamToRound() {

        int i = 0;
        while(i < teams.getTeamsList().size()){
        System.out.println("The existing teams are as follows: ");
        season.displayAvailableTeams();

        System.out.println("Please enter the team's name that you want to schedule: ");
        String teamName = scanner.nextLine();
        String result = season.addTeamToRound(teamName);
        if (!result.isEmpty()) {
        System.out.println(result);
        i++;
        } else {
        System.out.println("No such team! Please try again");
        }   
    }
}

private void displayCurrentRound() {
    season.displayCurrentRound();
}

private void playGames() {
    if (game.getResults().size() == 0){
        System.out.println("No game in the current round, please add teams to the round first!");
    }
    else {
        
    }
}

private void displayGameResultRecords() {
    System.out.println("Displaying the game result records");
}
    }
