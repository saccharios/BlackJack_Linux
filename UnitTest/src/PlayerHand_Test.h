/*
 * PlayerHand_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYERHAND_TEST_H_
#define SRC_PLAYERHAND_TEST_H_

#include "PlayerHand.h"
#include "gtest/gtest.h"
#include "Deck.h"

// Forward declaration
class Card;

class PlayerHandTest : public ::testing::Test
{
private:
	const double _wager = 10.0;
	const unsigned int _numDecks = 1;
public:
	using pCard = std::unique_ptr<Card>;
	PlayerHandTest() : _deck(0), _hand (_deck, _wager, 0)
	// Use seed 0 to always draw the same card.
	// The card drawn depends only on their order in the deck.
	{
		_deck.AddSets(_numDecks);
	}
	void Run_Payouts();
	void Run_ActionDouble();
	void Run_ActionHit();
	void Run_ActionStand();
	void Run_ActionSplit();
	void Run_ActionSplit_Aces();
	void Run_Wager();
	void Run_Start();
	void Run_IsBlackJack();
	void Run_EvaluateValue();
	void Run_EvaluateBlackJack();
	void Run_EvaluateBusted();
	void Run_PutCardsBack();
	void Run_GetAvailableActionSet();

private:
	Deck _deck;
	PlayerHand _hand;
};
TEST_F(PlayerHandTest, Payouts)
{
	Run_Payouts();
}
TEST_F(PlayerHandTest, ActionDouble)
{
	Run_ActionDouble();
}
TEST_F(PlayerHandTest, ActionHit)
{
	Run_ActionHit();
}
TEST_F(PlayerHandTest, ActionStand)
{
	Run_ActionStand();
}
TEST_F(PlayerHandTest, ActionSplit)
{
	Run_ActionSplit();
}
TEST_F(PlayerHandTest, ActionSplitAces)
{
	Run_ActionSplit_Aces();
}
TEST_F(PlayerHandTest, Wager)
{
	Run_Wager();
}

TEST_F(PlayerHandTest, Start)
{
	Run_Start();
}
TEST_F(PlayerHandTest, EvaluateValue)
{
	Run_EvaluateValue();
}
TEST_F(PlayerHandTest, EvaluateBlackJack)
{
	Run_EvaluateBlackJack();
}
TEST_F(PlayerHandTest, EvaluateBusted)
{
	Run_EvaluateBusted();
}
TEST_F(PlayerHandTest, PutCardsBack)
{
	Run_PutCardsBack();
}
TEST_F(PlayerHandTest, Run_GetAvailableActionSet)
{
	Run_GetAvailableActionSet();
}



#endif /* SRC_PLAYERHAND_TEST_H_ */
