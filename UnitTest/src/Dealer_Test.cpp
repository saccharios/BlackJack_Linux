/*
 * Dealer_Test.cpp
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#include "Dealer_Test.h"
#include "Card.h"
void DealerTest::Run_Start()
{
	_dealer.Start();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
}
void DealerTest::Run_Play()
{
	_dealer.Play();
	// Depends on the order of the cards in the deck.
	EXPECT_EQ(23u, _dealer.GetValue());
	EXPECT_EQ(4u, _dealer.GetHoleCards().Size());
	_dealer.PrintCards();
}
void DealerTest::Run_ActionHit()
{

	_dealer.ActionHit();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u - 1, _deck.Size());
}


void DealerTest::Run_PutCardsBack()
{
	_dealer.ActionHit();
	EXPECT_EQ(1u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u - 1u, _deck.Size());
	_dealer.PutCardsBack();
	EXPECT_EQ(0u, _dealer.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52u, _deck.Size());
}
void DealerTest::Run_BlackJack()
{ // This test case is easier if the deck contains only {As, Ks}
	Deck deck(0);
	Dealer dealer(deck);
	deck.AddCard(std::make_unique<Card>("A","s"));
	deck.AddCard(std::make_unique<Card>("K","s"));
	dealer.Start();
	dealer.ActionHit();
	EXPECT_TRUE(dealer.HasBlackJack());
}
void DealerTest::Run_IsBusted()
{
	for(auto i = 0u; i < 7u; ++i)
	{
		_dealer.ActionHit();
	}
	EXPECT_TRUE(_dealer.IsBusted());
}
void DealerTest::Run_GetValue()
{
	auto sum = 0u;
	// Draw some cards
	_dealer.ActionHit();
	sum += 2;
	EXPECT_EQ(sum,_dealer.GetValue());
	_dealer.ActionHit();
	sum += 9;
	EXPECT_EQ(sum,_dealer.GetValue());
	sum += 2;
	_dealer.ActionHit();
	EXPECT_EQ(sum,_dealer.GetValue());
	sum += 10;
	_dealer.ActionHit();
	EXPECT_EQ(sum,_dealer.GetValue());

}
