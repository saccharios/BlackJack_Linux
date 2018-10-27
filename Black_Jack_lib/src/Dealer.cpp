/*
 * Dealer.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */


#include "../../Black_Jack_lib/src/Dealer.h"

#include <memory>
#include <sstream>

#include "../../Black_Jack_lib/src/Card.h"
#include "../../Black_Jack_lib/src/Deck.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
#include "../../Black_Jack_lib/src/HoleCards.h"

Dealer::Dealer(Deck & deck) :
_deck(deck)
{}
void Dealer::Start()
{
	auto card = _deck.Draw();
	_holeCards.StartCards(std::move(card));
	PrintCards();
}

void Dealer::Play()
{
	// Dealer has to hit until their value is above 17
	console.WriteString("-------Dealer-------\n");

	while(_holeCards.GetValue() < 17) // Basic Strategy
	{
		ActionHit();
	}
}

void Dealer::ActionHit()
{
	console.WriteString("Draw a card.... The card drawn is the ");

	auto card = _deck.Draw();
	card->Print();

	console.WriteString("\n");
	_holeCards.AddCard(std::move(card));
	PrintCards();
}

void Dealer::PutCardsBack()
{
	while(!_holeCards.IsEmpty())
	{
		_deck.AddCard(_holeCards.RemoveLastCard());
	}
}


void Dealer::PrintCards() const
{
	std::stringstream strm;
	strm << "Dealer's Cards are: ";
	console.Write(strm);
	_holeCards.PrintCards();
}

