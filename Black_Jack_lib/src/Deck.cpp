/*
 * Deck.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "Deck.h"

#include <memory>
#include <random>
#include <stdexcept>
#include "assert.h"
#include <sstream>
#include "Card.h"
#include "GlobalDeclarations.h"

void Deck::AddSets(unsigned int  N)
{
	// Can only have between 1 and MAX_SETS sets.
	assert(N <= MAX_SETS);
	assert(N > 0);

	for(unsigned int i = 0; i < N; ++i)
	{
		AddCompleteSet();
	}
}

void Deck::AddCompleteSet()
{
	// Adds single cards to the deck. The cards are owned by the desk unless it is drawn.
	for( const auto & suit : SUIT)
	{
		for(const auto & face : FACE)
		{
			_cardContainer.push_back(std::move(std::make_unique<Card>(face.first, suit)));
		}
	}
}


Deck::pCard Deck::Draw(unsigned int rnd_number)
{
	// Draw card at position number if it is within bounds and return it to the caller.
	assert(rnd_number < Size());
	assert(!_cardContainer.empty());

	auto Card =  std::move(_cardContainer.at(rnd_number));
	_cardContainer.erase(_cardContainer.begin()+rnd_number);
	return Card;
}

Deck::pCard Deck::Draw()
{
	// Draw random card from the deck
	std::uniform_int_distribution<int> uniformDist(0, _cardContainer.size()-1);
	auto random_integer = uniformDist(_rng);
	// Transfers ownership of the drawn card to the caller
	return Draw(random_integer);
}

void Deck::PrintNumCards() const
{
	std::stringstream strm;
	strm << "Cards in Deck = " << Size() << std::endl;
	console.Write(strm);
}










