/*
 * PlayerHand_Test.cpp
 *
 *  Created on: 29.01.2017
 *      Author: Stefan
 */

#include "gtest/gtest.h"
#include "GlobalDeclarations.h"
#include "Card.h"

#include "PlayerHand_Test.h"
void PlayerHandTest::Run_Payouts()
{
	EXPECT_EQ(_wager, _hand.PayoutPush ());
	EXPECT_EQ(0.0f, _hand.PayoutLoose ());
	EXPECT_EQ(_wager*2.0f, _hand.PayoutWin ());
	EXPECT_EQ(_wager*2.5f, _hand.PayoutBlackJack ());
}
void PlayerHandTest::Run_ActionDouble()
{
	_hand.ActionDouble();
	EXPECT_EQ(1u, _hand.GetHoleCards().Size());
	EXPECT_TRUE(_hand.IsPlayed());
	EXPECT_EQ(_wager*2.0f, _hand.GetWager() );
}
void PlayerHandTest::Run_ActionSplit()
{
	// To test spliting it does not matter whether it is a pair or not, the mechanism is the same.
	// Thus we can use the normal start method.
	_hand.Start();
	auto newHand = _hand.ActionSplit();
	EXPECT_EQ(2u, _hand.GetHoleCards().Size());
	EXPECT_FALSE(_hand.IsPlayed());
	EXPECT_EQ(2u, newHand->GetHoleCards().Size());
	EXPECT_EQ(_wager, newHand->GetWager());
	EXPECT_EQ(_hand.GetHandNumber() + 1, newHand->GetHandNumber());
	EXPECT_FALSE(newHand->IsPlayed());

}

void PlayerHandTest::Run_ActionSplit_Aces()
{
	// This is a special case and can best be tested with a special deck.
	// Thus the deck and playerHand are not the member variables.
	Deck deck;
	deck.AddCard(std::make_unique<Card>("A","s"));
	deck.AddCard(std::make_unique<Card>("A","d"));

	PlayerHand hand(deck,_wager, 0);
	hand.Start();
	// Add more cards to the deck, so spliting is ok
	deck.AddCard(std::make_unique<Card>("2","d"));
	deck.AddCard(std::make_unique<Card>("3","d"));
	auto newHand = hand.ActionSplit();
	EXPECT_TRUE( hand.IsPlayed());
	EXPECT_TRUE(newHand->IsPlayed());

}
void PlayerHandTest::Run_ActionHit()
{
	for(unsigned int i = 0; i < 10; ++i)
	{
		_hand.ActionHit();
		EXPECT_EQ(i+1u, _hand.GetHoleCards().Size());
		if(_hand.GetValue() > 20)
		{
			EXPECT_TRUE(_hand.IsPlayed());
		}
		else
		{
			EXPECT_FALSE(_hand.IsPlayed());
		}
	}
}
void PlayerHandTest::Run_ActionStand()
{
	_hand.ActionStand();
	EXPECT_TRUE(_hand.IsPlayed());
}
void PlayerHandTest::Run_Wager()
{
	// First test with member
	EXPECT_EQ(_wager, _hand.GetWager());
	// But this tests needs some more values for wager, but the wager can only be set at creation
	PlayerHand _handLow(_deck, MIN_WAGER - 1.0, 1);
	EXPECT_EQ(MIN_WAGER, _handLow.GetWager());
	PlayerHand _handHigh(_deck, MAX_WAGER + 1.0, 2);
	EXPECT_EQ(MAX_WAGER, _handHigh.GetWager());
}
void PlayerHandTest::Run_Start()
{
	_hand.Start();
	EXPECT_EQ(2u, _hand.GetHoleCards().Size());
	EXPECT_FALSE(_hand.IsPlayed());
}
void PlayerHandTest::Run_IsBlackJack()
{ // This test case is easier if the deck contains only {As, Ks}
	Deck deck(0);
	double wager = 10.0;
	PlayerHand hand (deck, wager, 0);
	deck.AddCard(std::make_unique<Card>("A","s"));
	deck.AddCard(std::make_unique<Card>("K","s"));
	hand.Start();
	EXPECT_TRUE(hand.IsBlackJack());
}

void PlayerHandTest::Run_EvaluateBlackJack()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	PlayerHand hand (deck, wager, 0);
	deck.AddCard(std::make_unique<Card>("A","s"));
	deck.AddCard(std::make_unique<Card>("K","s"));
	hand.Start(); // hand now holds BlackJack
	auto payout = hand.Evaluate(true, false, 21); // Dealer also has Black Jack
	EXPECT_EQ(wager, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(2.5*wager, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(2.5*wager, payout);
}
void PlayerHandTest::Run_EvaluateBusted()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	PlayerHand hand (deck, wager, 0);
	deck.AddCard(std::make_unique<Card>("K","s"));
	deck.AddCard(std::make_unique<Card>("K","s"));
	deck.AddCard(std::make_unique<Card>("6","s"));
	hand.Start(); // hand is busted
	hand.ActionHit();
	auto payout = hand.Evaluate(true, false, 21); // Dealer has Black Jack
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(0.0, payout);
}
void PlayerHandTest::Run_EvaluateValue()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	PlayerHand hand (deck, wager, 0);
	deck.AddCard(std::make_unique<Card>("6","s"));
	deck.AddCard(std::make_unique<Card>("6","s"));
	hand.Start(); // hand has 12 points
	auto payout = hand.Evaluate(true, false, 21); // Dealer has Black Jack
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, true, 22); // Dealer is busted
	EXPECT_EQ(2.0*wager, payout);
	payout = hand.Evaluate(false, false, 18); // Dealer has 18 points
	EXPECT_EQ(0.0, payout);
	payout = hand.Evaluate(false, false, 12); // Dealer has 12 points
	EXPECT_EQ(1.0*wager, payout);
	payout = hand.Evaluate(false, false, 10); // Dealer has 10 points
	EXPECT_EQ(2.0*wager, payout);
}
void PlayerHandTest::Run_PutCardsBack()
{
	_hand.Start();
	_hand.ActionHit();
	_hand.ActionHit();
	_hand.ActionHit();
	EXPECT_EQ(5u, _hand.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52 - 5u, _deck.Size());
	_hand.PutCardsBack();
	EXPECT_EQ(0u, _hand.GetHoleCards().Size());
	EXPECT_EQ(_numDecks*52, _deck.Size());
}

void PlayerHandTest::Run_GetAvailableActionSet()
{// This test case is easier if the deck contains only certain cards
	Deck deck(0);
	double wager = 10.0;
	PlayerHand hand (deck, wager, 0);
	deck.AddCard(std::make_unique<Card>("6","s"));
	deck.AddCard(std::make_unique<Card>("6","s"));
	hand.Start(); // hand has a pair
	EXPECT_EQ(ACTION_SPLIT_DOUBLE, hand.GetAvailableActionSet());
	deck.AddCard(std::make_unique<Card>("3","s"));
	hand.ActionHit(); // hand has a pair
	EXPECT_EQ(ACTION_STANDARD, hand.GetAvailableActionSet());
	deck.AddCard(std::make_unique<Card>("K","s"));
	deck.AddCard(std::make_unique<Card>("6","s"));
	hand.PutCardsBack();
	hand.Start(); // hand hols Ks6s
	EXPECT_EQ(ACTION_DOUBLE, hand.GetAvailableActionSet());
}
