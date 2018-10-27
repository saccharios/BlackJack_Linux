/*
 * SimulationGame.cpp
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#include "SimulationGame.h"
#include "PlayerStrategy.h"
#include <ostream>
#include "assert.h"
#include <iostream>
#include <fstream>

SimulationGame::SimulationGame(Setup setup) : Game(), _simulationRounds(setup.N_Simulation_Steps)
{
	// Cant have more than MAX_PLAYERS
	assert((setup.N_Basic_AIPlayers + setup.N_Conservative_AIPlayers + setup.N_Aggressive_AIPlayers + setup.N_Optimal_AIPlayers )< MAX_PLAYERS );

	_deck.AddSets(setup.N_Sets);

	if(setup.initialBalance < _balanceLowLimit)
	{
		setup.initialBalance = _balanceLowLimit;
	}

	for( unsigned int i = 0; i < setup.N_Basic_AIPlayers; ++i )
	{
		std::ostringstream strm ;
		strm << "Basic_AIPlayer_" << i ;
		_players.push_back(std::move(std::make_unique<AIPlayer_Basic>(_deck, strm.str(), setup.initialBalance)));
	}
	for( unsigned int i = 0; i < setup.N_Conservative_AIPlayers; ++i )
	{
		std::ostringstream strm ;
		strm << "Conservative_AIPlayer_" << i ;
		_players.push_back(std::move(std::make_unique<AIPlayer_Conservative>(_deck, strm.str(), setup.initialBalance)));
	}
	for( unsigned int i = 0; i < setup.N_Aggressive_AIPlayers; ++i )
	{
		std::ostringstream strm ;
		strm << "Aggressive_AIPlayer_" << i ;
		_players.push_back(std::move(std::make_unique<AIPlayer_Aggressive>(_deck, strm.str(), setup.initialBalance)));
	}
	for( unsigned int i = 0; i < setup.N_Optimal_AIPlayers; ++i )
	{
		std::ostringstream strm ;
		strm << "Optimal_AIPlayer_" << i ;
		_players.push_back(std::move(std::make_unique<AIPlayer_Optimal>(_deck, strm.str(), setup.initialBalance, _dealer)));
	}
}

void
SimulationGame::SetWagers()
{
	console.WriteString("-------Set Wagers------\n");
	for(auto const & player : _players)
	{
		player->SetWager(_wager);
	}
}

bool SimulationGame::PlayAnotherRound ()
{
	for(auto const & player : _players)
	{
		if(player->GetBalance() < _balanceLowLimit)
		{
			player->ResetBalance();
			std::stringstream strm;
			strm << player->GetName()<< "'s balance is too low. Resetting to " << player->GetBalance() << "\n";
			console.Write(strm);
		}
	}

	return (++_currentRound < _simulationRounds);
}



void SimulationGame::PrintStatistics(std::ostream & ostrm)
{
	for(auto const & player : _players)
	{
		ostrm <<  player->GetName()<< "'s statistics:\n";
		ostrm << "Total investment = " << player->GetTotalInvestedBalance() << "\n";
		ostrm << "Balance at the end = " << player->GetBalance() << "\n";
		ostrm << "Hands played = " << _simulationRounds << "\n";
		double edge = (player->GetBalance() - player->GetTotalInvestedBalance()) / static_cast<double>(_simulationRounds) / _wager;
		ostrm << "Resulting edge = " << edge << "\n";
	}

}


void SimulationGame::Simulate()
{

    // Simple rederict std::cout buffer to a file. Is there a better solution to
    // reset the output stream of the console?
	std::ofstream out_file;
	out_file.open("simulation_output.txt");
	std::streambuf* coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out_file.rdbuf()); //redirect std::cout to output file
	// Run simulation
	do
	{
		PlayRound();
	}while ( PlayAnotherRound() );

	std::cout.rdbuf(coutbuf); //reset to standard output again
	out_file.close();
}
