/*
 * Card.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "../../Black_Jack_lib/src/Card.h"

#include <array>
#include <string>
#include <algorithm>
#include "assert.h"
#include <sstream>
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"


Card::Card(std::string const & face, std::string const & suit):
_face(face),
_suit(suit)
{
// Because the constructor takes any string, it must be made sure that
// only those strings contained in FACE and SUIT are valid for a card.
	auto faceExists = (FACE.count(face) != 0);
	auto suitExists = std::any_of(std::begin(SUIT), std::end(SUIT), [&](std::string suit) { return suit == _suit; });

	assert(faceExists);
	assert(suitExists);

	_value = FACE.at(face);
}

void Card::Print() const
{
	std::stringstream strm;
	strm << _face << _suit;
	console.Write(strm);
}


