/*
 * _holeCards_Test.cpp
 *
 *  Created on: 02.02.2017
 *      Author: Stefan
 */

#include "HoleCards_Test.h"
#include "gtest/gtest.h"
#include "../../Black_Jack_lib/src/Card.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
void HoleCardsTest::Run_AddAndRemoveOneCard()
{
	_holeCards.AddCard(std::make_unique<Card>("A","s"));
	EXPECT_EQ(1u, _holeCards.Size());
	_holeCards.RemoveLastCard();
	EXPECT_EQ(0u, _holeCards.Size());
}
void HoleCardsTest::Run_RemoveCard_DEATH()
{
//	 Remove on card from empty hole cards
	EXPECT_DEATH(_holeCards.RemoveLastCard(),"");
}


void HoleCardsTest::Run_OneStartCard_DEATH()
{
	_holeCards.AddCard(std::make_unique<Card>("A","s"));
	EXPECT_DEATH( _holeCards.StartCards(std::make_unique<Card>("K","s")), "");
}

void HoleCardsTest::Run_OneStartCard()
{
	 _holeCards.StartCards(std::make_unique<Card>("A","s"));
	EXPECT_EQ(1u, _holeCards.Size());
}
void HoleCardsTest::Run_TwoStartCard_DEATH()
{
	// Add 1 Card and then invoke StartCard(Card, Card), expect throw
	_holeCards.AddCard(std::make_unique<Card>("A","s"));
	EXPECT_DEATH( _holeCards.StartCards(std::make_unique<Card>("K","s"),std::make_unique<Card>("Q","s")),"");
}
void HoleCardsTest::Run_TwoStartCard()
{
	EXPECT_NO_THROW( _holeCards.StartCards(std::make_unique<Card>("K","s"),std::make_unique<Card>("Q","s")));
	EXPECT_EQ(2u, _holeCards.Size());
}
void HoleCardsTest::Run_GetValue()
{
	auto valueSum(0u);
	// Test Value for all cards of spades, handle the ace special
	for(const auto & face : FACE)
	{
		_holeCards.AddCard(std::make_unique<Card>(face.first,"s"));
		valueSum += face.second;
		if( face.first == "A" && valueSum > 21u)
		{
			valueSum -= 10u;
		}
		EXPECT_EQ(valueSum, _holeCards.GetValue());
	}
	// By now value is busted
	EXPECT_TRUE(_holeCards.AreBusted());
}
void HoleCardsTest::Run_Pair()
{
	// Add a pair
	_holeCards.StartCards(std::make_unique<Card>("K","s"),std::make_unique<Card>("K","d"));
	EXPECT_TRUE(_holeCards.ArePair());
	// Add another card, hole Cards are no longer pair
	_holeCards.AddCard(std::make_unique<Card>("2","s"));
	EXPECT_FALSE(_holeCards.ArePair());

}
void HoleCardsTest::Run_PairAces()
{
	// Add pair of aces
	_holeCards.StartCards(std::make_unique<Card>("A","s"),std::make_unique<Card>("A","d"));
	EXPECT_TRUE(_holeCards.ArePair());
	EXPECT_TRUE(_holeCards.ArePairAces());
	// Add another card, hole Cards are no longer pair
	_holeCards.AddCard(std::make_unique<Card>("2","s"));
	EXPECT_FALSE(_holeCards.ArePair());
	EXPECT_FALSE(_holeCards.ArePairAces());
}
void HoleCardsTest::Run_BlackJack()
{
	// Add BlackJack
	_holeCards.StartCards(std::make_unique<Card>("A","s"),std::make_unique<Card>("K","s"));
	EXPECT_TRUE(_holeCards.AreBlackJack());
	EXPECT_EQ(21u, _holeCards.GetValue());
	// Add another card (altough this cannot happen in the game)
	_holeCards.AddCard(std::make_unique<Card>("2","s"));
	EXPECT_FALSE(_holeCards.AreBlackJack());
}
void HoleCardsTest::Run_SoftAces()
{
	// Add 21 Aces
	for( auto i = 0u; i < 21u; ++i)
	{
		_holeCards.AddCard(std::make_unique<Card>("A","s"));
		if( i < 11 )
		{
			EXPECT_EQ(11u + i, _holeCards.GetValue()) <<" at " << i;
			EXPECT_TRUE(_holeCards.AreSoft());
		}
		else
		{
			EXPECT_EQ(i+1, _holeCards.GetValue()) << " at " << i;
			EXPECT_FALSE(_holeCards.AreSoft());
		}
	}
}

