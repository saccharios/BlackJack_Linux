/*
 * HoleCards.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */
#include "../../Black_Jack_lib/src/HoleCards.h"

#include <memory>
#include <stdexcept>
#include "assert.h"
#include <sstream>
#include "../../Black_Jack_lib/src/Card.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"


HoleCards::HoleCards():
_areBlackJack(false),
_arePair(false),
_arePairAces(false),
_areBusted(false),
_value(0),
_numSoftAces(0),
_cardContainer()
{}

void HoleCards::StartCards(pCard card)
{
	// Start method for the dealer. Can only start if the hand is empty.
	assert(IsEmpty());
	AddCard(std::move(card));
}

void HoleCards::StartCards(pCard card1, pCard card2)
{
	// Start method for the player. Can only start if the hand if it is empty.
	// Save if the two start hands are paired or even paired aces
	assert(IsEmpty());
	AddCard(std::move(card1));
	AddCard(std::move(card2));
}

void HoleCards::AddCard(pCard card)
{
	// Adds card to the container
	_cardContainer.push_back(std::move(card));
	// Resset characteristics
	_areBlackJack = false;
	_areBusted = false;
	_arePairAces = false;
	_arePair = false;
	// Evaluate characteristics
	CalculateValue();
	auto value = GetValue();
	if( _cardContainer.size() == 2u )
	{
		if( value ==  21u)
		{
			_areBlackJack = true;
		}
		else if(_cardContainer.at(0)->GetFace() == _cardContainer.at(1)->GetFace())
		{
			_arePair = true;
			if ( _cardContainer.at(0)->IsAce())
			{
				_arePairAces = true;
			}
		}
	}
	else if ( value > 21u)
	{
		_areBusted = true;
	}

}

void HoleCards::CalculateValue()
{
	// Calculates the value of the cards in the container.
	// Stores the number of soft aces.
	_value = 0u;
	_numSoftAces = 0u;
	for( auto const & card : _cardContainer)
	{
		_value += card->GetValue();
		if(card->IsAce())
		{
			++_numSoftAces; // All aces are counted as soft
		}
	}
	// If the values is above 21 and there are soft aces,
	// transform as many soft aces into hard aces.
	while( _value > 21u && _numSoftAces > 0u)
	{
		_value -= 10;
		--_numSoftAces;
	}
}
unsigned int HoleCards::GetValue() const
{
	return _value;
}

void HoleCards::PrintCards() const
{
	std::stringstream strm;
	for(auto const & card : _cardContainer)
	{
		card->Print();
	}

	if( AreBlackJack() )
	{
		console.WriteString(", you have BLACKJACK.\n");
	}
	else if (AreBusted())
	{
		strm <<" you are BUSTED (" << GetValue() <<").\n";
		console.Write(strm);
	}
	else
	{
		strm << ", value is ";
		if( _numSoftAces > 0)
		{
			strm << "soft ";
		}
		strm << GetValue() << ".\n";
		console.Write(strm);
	}
}

void HoleCards::PrintNumCards() const
{
	std::stringstream strm;
	strm << "You have = " << _cardContainer.size() <<" Cards\n";
	console.Write(strm);
}

HoleCards::pCard HoleCards::RemoveLastCard()
{
	assert(!IsEmpty());
	auto Card =  std::move(_cardContainer.back());
	_cardContainer.pop_back();

	return Card;
}



