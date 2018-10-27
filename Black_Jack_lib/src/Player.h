/*
 * Player.h
 *
 *  Created on: 15.10.2016
 *      Author: Stefan
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include <set>

#include "../../Black_Jack_lib/src/Card.h"
#include "../../Black_Jack_lib/src/PlayerHand.h"

// Forward declaration to avoid #include
class Deck;

class Player {
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:

	Player(Deck & deck, std::string name, double balance);
	virtual ~Player(){} // Allow polymorphic deletion of players
	// Not allowed to copy or assign
	Player (Player const & player) = delete;
	Player & operator= (const Player & other) = delete;

	void Start();
	void Play();
	void PlayOneHand(pPlayerHand const & hand);
	void PlayAction(std::string action, pPlayerHand const & hand);
	std::set<std::string> GetAvailableActionSet(std::set<std::string> const & actionSet) const;
	void Evaluate(	bool const & dealerHasBlackJack, bool const & dealerIsBusted, unsigned int const & dealerValue);
	void PutCardsBack();
	void SetWagerUser ();
	void SetWager (double wager);
	void PrintWager () const;
	double GetBalance () const;
	void PrintBalance () const;
	std::string GetName() const;
	void PrintName () const;
	void Hit(pPlayerHand const & hand);
	void Split(pPlayerHand const & hand);
	void Double(pPlayerHand const & hand);
	void Stand(pPlayerHand const & hand);
	void AddToBalance(double value);
	void SubtractFromBalance(double value);
	unsigned int GetNumHands() {return _handManager.size();}
	void AddHand(pPlayerHand hand);
	virtual std::string Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const = 0;

	virtual void ResetBalance () = 0;
	virtual double GetTotalInvestedBalance () = 0;

private:
	double _balance;
	double _orignialWager;
	Deck & _deck;
	std::vector<pPlayerHand> _handManager;
	std::string _name;
};




#endif /* PLAYER_H_ */
