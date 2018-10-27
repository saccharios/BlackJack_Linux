/*
 * Card_Test.cpp
 *
 *  Created on: 02.02.2017
 *      Author: Stefan
 */
#include "Card_Test.h"


void CardTest::Run_CreateCard_Face_DEATH()
{
	EXPECT_DEATH(Card card("P","s"),""); // False face
}
void CardTest::Run_CreateCard_Suit_DEATH()
{
	EXPECT_DEATH(Card card("A","l"),""); // False suit
}

void CardTest::Run_TestSuits()
{
	// Check if all suits are assigned correctly
	for( const auto & suit : SUIT)
	{
		Card card("A", suit);
		EXPECT_EQ(suit, card.GetSuit()) << "Error assigning suit " << suit;
	}
}

void CardTest::Run_TestFaces()
{
	// Check if all faces and values are assigned correctly
	for(const auto & face : FACE)
	{
		Card card(face.first, "s");
		EXPECT_EQ(face.first, card.GetFace()) << "Error assigning face " << face.first;
		EXPECT_EQ(face.second, card.GetValue()) << "Error assigning value " << face.second;
	}
}
