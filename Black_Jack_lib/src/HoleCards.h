/*
 * HoleCards.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef HOLECARDS_H_
#define HOLECARDS_H_

#include <memory>
#include <vector>

// Forward declaration to avoid #include
class Card;

// The difference between HoleCards and the deck is that they do not contain any cards
// at startup. During one round of play, cards will be added to the hole cards and at the end
// of a round removed again. It provides also game related functionality, f.ex. counting
// the value of the cards in the hole cards.
class HoleCards {
	using pCard = std::unique_ptr<Card>;
public:
	HoleCards();
	// Not allowed to copy or assign, because it contains a card container (which has unique_ptrs)
	HoleCards (HoleCards const & player) = delete;
	HoleCards & operator= (const HoleCards & other) = delete;

	void StartCards(pCard card); // Only used by dealer
	void StartCards(pCard card1, pCard card2); // Only used by player
	void AddCard(pCard card);
	pCard RemoveLastCard();
	void CalculateValue();
	unsigned int GetValue() const;
	bool const & AreBlackJack() const { return _areBlackJack; }
	bool const & ArePair() const { return _arePair; }
	bool const & ArePairAces() const { return _arePairAces; }
	bool const & AreBusted() const { return _areBusted; }
	bool AreSoft() const { return (_numSoftAces > 0 );}
	void PrintCards() const;
	void PrintNumCards() const;
	bool IsEmpty() const { return _cardContainer.empty(); }
	unsigned int Size() const { return _cardContainer.size(); }

private:
	bool _areBlackJack;
	bool _arePair;
	bool _arePairAces;
	bool _areBusted;
	unsigned int _value;
	unsigned int _numSoftAces;
	std::vector<pCard> _cardContainer;
};

#endif /* HOLECARDS_H_ */
