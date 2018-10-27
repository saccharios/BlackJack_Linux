/*
 * Deck_Tets.cpp
 *
 *  Created on: 02.02.2017
 *      Author: Stefan
 */

#include "Deck_Test.h"
#include <memory>
#include "gtest/gtest.h"
#include "../../BlackJack/src/Deck.h"
#include "../../BlackJack/src/Card.h"
#include "string"
#include "../../BlackJack/src/GlobalDeclarations.h"



void DeckTest::Run_AddAndRemoveOneCard()
{
	_deck.AddCard(std::make_unique<Card>("A","s"));
	EXPECT_EQ(1u, _deck.Size());
	_deck.Draw();
	EXPECT_EQ(0u, _deck.Size());
}

void DeckTest::Run_RemoveOneCard_EmptyDesk_DEATH()
{
	EXPECT_DEATH(_deck.Draw(), "");
	EXPECT_DEATH(_deck.Draw(1), "");
}

void DeckTest::Run_AddEigthSets()
{
	unsigned int NumDecks = 8;
	unsigned int NumCardsDeck = 52;
	_deck.AddSets(NumDecks);
	EXPECT_EQ(NumDecks*NumCardsDeck, _deck.Size());
	for(unsigned int i = 0; i < NumDecks*NumCardsDeck; ++i)
	{
		_deck.Draw();
	}
	EXPECT_EQ(0u, _deck.Size());
}
void DeckTest::Run_AddMAX1Sets_DEATH()
{
	unsigned int NumDecks = MAX_SETS +1 ;
	EXPECT_DEATH(_deck.AddSets(NumDecks),"");
}
void DeckTest::Run_AddZeroSets_DEATH()
{
	unsigned int NumDecks = 0;
	EXPECT_DEATH(_deck.AddSets(NumDecks),"");
}
