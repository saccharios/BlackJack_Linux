/*
 * PlayerStrategy_Test.h
 *
 *  Created on: 19.03.2017
 *      Author: Stefan
 */

#pragma once

#include "gtest/gtest.h"
#include <string>
#include "GlobalDeclarations.h"
#include "Dealer.h"
#include "Deck.h"
#include "PlayerStrategy.h"


class AIPlayer_OptimalTest : public ::testing::Test
{
	const double _initBalance = MAX_INIT_BALANCE;
	const unsigned int _numDecks = 1;
	const std::string _name = "Optimal";
public:
	AIPlayer_OptimalTest() : _deck(0), _dealer(_deck), _AIPlayer(_deck, _name, _initBalance, _dealer)
	{
		_deck.AddSets(_numDecks);
	}

	void Run_OptimalStrategy();
private:
	Deck _deck;
	Dealer _dealer;
	AIPlayer_Optimal _AIPlayer;

};



TEST_F(AIPlayer_OptimalTest, Optimal_Strategy)
{
	Run_OptimalStrategy();
}



