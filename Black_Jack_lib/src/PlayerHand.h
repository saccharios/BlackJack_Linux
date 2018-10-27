/*
 * PlayerHand.h
 *
 *  Created on: 07.01.2017
 *      Author: Stefan
 */

#ifndef PLAYERHAND_H_
#define PLAYERHAND_H_

#include <memory>
#include <set>

#include "../../Black_Jack_lib/src/HoleCards.h"
// Forward declaration to avoid #include
class Card;
class Deck;

// The PlayerHand is a wrapper class for the hole cards for a player.
// Note that a dealer is not a player, as a player has more options available.
// A dealer also has hole cards. In addition, this class lets you set wagers
// on hole cards, evaluate the payout, keeps track whether a player can keep playing
// and evaluates possible user actions.
class PlayerHand {
	using pCard = std::unique_ptr<Card>;
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	PlayerHand (Deck & deck, double const & wager, unsigned int const & handNumber);

	// Not allowed to copy or assign, because it contains a card container (which has unique_ptrs)
	PlayerHand (PlayerHand const & player) = delete;
	PlayerHand & operator= (const PlayerHand & other) = delete;

	void Start();
	void Start( pCard card1 );
	bool IsFirstAction() const { return (_holeCards.Size() == 2); }
	pPlayerHand ActionSplit();
	void ActionDouble();
	void ActionHit();
	void ActionStand();
	double const & GetWager() const { return _wager; }
	void PrintCards() const { _holeCards.PrintCards(); }
	unsigned int GetValue() const { return _holeCards.GetValue(); }
	bool const & IsPair() const { return _holeCards.ArePair(); }
	bool const & IsPairAces() const { return _holeCards.ArePairAces(); }
	bool const & IsBlackJack() const { return _holeCards.AreBlackJack(); }
	bool IsSoft() const { return _holeCards.AreSoft(); }
	bool IsEmpty() const { return _holeCards.IsEmpty(); }
	void PrintNumCards() const { _holeCards.PrintNumCards(); }
	double Evaluate(double const & dealerHasBlackJack, bool const & dealerIsBusted, unsigned int const & dealerValue) const;
	double PayoutPush () const;
	double PayoutLoose () const;
	double PayoutWin () const;
	double PayoutBlackJack () const;
	unsigned int const & GetHandNumber() const { return _handNumber; }
	void PrintHandNumber() const;
	bool const & IsPlayed() const { return _isPlayed; }
	HoleCards const & GetHoleCards() const { return _holeCards;}
	void PutCardsBack();
	std::set<std::string> GetAvailableActionSet() const;

private:
	Deck & _deck;
	HoleCards _holeCards;
	double _wager;
	const unsigned int _handNumber;
	bool _isPlayed;

};


#endif /* PLAYERHAND_H_ */
