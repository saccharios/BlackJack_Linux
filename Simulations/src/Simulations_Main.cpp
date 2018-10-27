/*
 * Simulations_BlackJack.cpp
 *
 *  Created on: 21.03.2017
 *      Author: Stefan
 */


#include <memory>
#include "SimulationGame.h"
#include "Card.h"
#include "GlobalDeclarations.h"
#include "HoleCards.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include <ctime>

int main(int argc, char ** argv)
{
    std::clock_t start;
    double duration;

    std::string statFileName = "statistics_output.txt";
    remove(statFileName.c_str());// Remove statistic file from previous run.

    start = std::clock();

	SimulationGame::Setup setup;

	setup.N_Simulation_Steps = 100;
	setup.initialBalance = MAX_INIT_BALANCE;
	setup.N_Sets = MAX_SETS;
	setup.N_Basic_AIPlayers = 0;
	setup.N_Conservative_AIPlayers = 0;
	setup.N_Aggressive_AIPlayers= 0;
	setup.N_Optimal_AIPlayers = 1;

	SimulationGame optimalGame(setup);
	optimalGame.Simulate();
	setup.N_Optimal_AIPlayers = 0;
	setup.N_Basic_AIPlayers = 1;
	SimulationGame basicGame(setup);
	basicGame.Simulate();
	setup.N_Basic_AIPlayers = 0;
	setup.N_Conservative_AIPlayers = 1;
	SimulationGame conservativeGame(setup);
	conservativeGame.Simulate();
	setup.N_Conservative_AIPlayers = 0;
	setup.N_Aggressive_AIPlayers = 1;
	SimulationGame aggresiveGame(setup);
	aggresiveGame.Simulate();


	std::ofstream stat_file;
	stat_file.open(statFileName);
	optimalGame.PrintStatistics(stat_file);
	basicGame.PrintStatistics(stat_file);
	conservativeGame.PrintStatistics(stat_file);
	aggresiveGame.PrintStatistics(stat_file);
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	stat_file <<"Total elapsed time: "<< duration << " sec.\n";
	stat_file.close();
	return 0;
}



