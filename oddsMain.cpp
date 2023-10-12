/***
    Issues: cold simulation, SOW and OTW not separated

***/

// Include classes
#include "Team.h"
#include "Game.h"
#include "League.h"
#include "SimulationDB.h"

int main() {
    // Create Variables
    League nhl;
    char verbose;
    int numSimulations;

    // Load league data from csv files (Data provided by Sports Reference https://www.hockey-reference.com/leagues/NHL_2023_games.html)
    nhl.readTeams("nhlteams.csv");
    nhl.readSchedule("nhlschedule.csv");

    // Calculate odds based on the games already played in the schedule
    nhl.loadFromSchedule();
    nhl.pointsAndPercentCalcs();
    nhl.refreshTeams();

    // Create predictions for remaining games in schedule
    nhl.predict();


    // Ask user for input
    cout << "Verbose? [y/n]: ";
    cin >> verbose;
    cout << "Number of trials? ";
    cin >> numSimulations;

    if (numSimulations == 0) {
        //Set a default number of simulations
        numSimulations = 1000;
    }

    // Print info to screen if necessary
    if (verbose == 'y' || verbose == 'Y') {
        nhl.printPredictSchedule();
        nhl.printTeams();
    } else if (verbose == 'T') {
        //Run speed tests in future
    }


    // Create object for class that runs the Monte Carlo simulation
    SimulationDB MonteCarlo(numSimulations);

    // Run Monte Carlo Simulation
    MonteCarlo.simulate(nhl);

    // Print Results
    MonteCarlo.printSimulationResults();
    MonteCarlo.printSimulationResultsToFile("results.txt");

    return 0;
}
