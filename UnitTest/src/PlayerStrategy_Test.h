/*
 * PlayerStrategy_Test.h
 *
 *  Created on: 19.03.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYERSTRATEGY_TEST_H_
#define SRC_PLAYERSTRATEGY_TEST_H_

#include "gtest/gtest.h"
#include <string>
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
#include "../../Black_Jack_lib/src/Dealer.h"
#include "../../Black_Jack_lib/src/Deck.h"
#include "../../Black_Jack_lib/src/PlayerStrategy.h"


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



#endif /* SRC_PLAYERSTRATEGY_TEST_H_ */
