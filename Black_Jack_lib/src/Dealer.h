/*
 * Dealer.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef DEALER_H_
#define DEALER_H_

#include <memory>

#include "HoleCards.h"

// Forward declaration to avoid #include
class Deck;

// The dealer is very different from a player, so they cannot have a common base class
// The dealer only has two actions, and their strategy is given.
class Dealer {
	using pCard = std::unique_ptr<Card>;
public:

	Dealer(Deck & deck);
	void Start();
	void Play();
	void ActionHit();
	void PutCardsBack();
	bool const & IsBusted () const { return _holeCards.AreBusted(); }
	bool const & HasBlackJack() const { return _holeCards.AreBlackJack(); }
	unsigned int GetValue () const { return _holeCards.GetValue(); }
	void PrintCards() const;
	auto const & GetHoleCards () const {return _holeCards;}

private:
	Deck & _deck;
	HoleCards _holeCards;

};

#endif /* DEALER_H_ */
