/*
 * Dealer_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_DEALER_TEST_H_
#define SRC_DEALER_TEST_H_
#include "gtest/gtest.h"
#include "Dealer.h"
#include "Deck.h"
// Forward declaration
class Deck;

class DealerTest : public ::testing::Test
{
public:
	using pCard = std::unique_ptr<Card>;
	DealerTest() : _deck(0), _dealer(_deck)
	// Use seed 0 to always draw the same card.
	// The card drawn depends only on their order in the deck.
	{
		_deck.AddSets(_numDecks);
	}
//	void SetUp()
//	{
//		Test::SetUp();
//	}

//	void TearDown()
//	{
//		Test::TearDown();
//	}
	void Run_Start();
	void Run_Play();
	void Run_ActionHit();
	void Run_PutCardsBack();
	void Run_BlackJack();
	void Run_IsBusted();
	void Run_GetValue();


private:
	Deck _deck;
	Dealer _dealer;
	static constexpr unsigned int _numDecks = 1;

};
TEST_F(DealerTest, Start)
{
	Run_Start();
}
TEST_F(DealerTest, Play)
{
	Run_Play();
}
TEST_F(DealerTest, ActionHit)
{
	Run_ActionHit();
}

TEST_F(DealerTest, PutCardsBack)
{
	Run_PutCardsBack();
}
TEST_F(DealerTest, BlackJack)
{
	Run_BlackJack();
}
TEST_F(DealerTest, IsBusted)
{
	Run_IsBusted();
}
TEST_F(DealerTest, GetValue)
{
	Run_GetValue();
}
#endif /* SRC_DEALER_TEST_H_ */
