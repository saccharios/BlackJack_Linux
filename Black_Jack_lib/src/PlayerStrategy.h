/*
 * PayerStrategy.h
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYERSTRATEGY_H_
#define SRC_PLAYERSTRATEGY_H_

#include <string>
#include <map>
#include "Console.h"
#include "Dealer.h"
#include "GlobalDeclarations.h"
#include "Player.h"
#include "PlayerHand.h"


class HumanPlayer : public Player{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	HumanPlayer(Deck & deck, std::string name, double balance) :
		Player(deck, name, balance)
{}

	std::string
	Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const override final
	{
		return console.ReadInAction(validActions);
	}

	void ResetBalance () override final {}
	double GetTotalInvestedBalance() override final {return 0;}
};


class AIPlayer : public Player {
	using Base = Player;
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer(Deck & deck, std::string name, double initialBalance) 	:
		Player(deck, name, initialBalance),
		_totalInvestedBalance(initialBalance),
		_initialBalance(initialBalance)
{}

	virtual std::string Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const  = 0;
	void ResetBalance () override final
	{
		auto difference = _initialBalance - Base::GetBalance();
		Base::AddToBalance(difference);
		_totalInvestedBalance += difference;
	}

	double GetTotalInvestedBalance() override final
	{
		return _totalInvestedBalance;
	}

private:
	double _totalInvestedBalance = 0;
	double _initialBalance;
};


class AIPlayer_Basic : public AIPlayer{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Basic(Deck & deck, std::string name, double balance) :
		AIPlayer(deck, name, balance)
{}

	// Play like the dealer
	std::string
	Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const override final
	{
		std::string action = STAND;
		if( hand->GetValue() < 17 )
		{
			action =  HIT;
		}
		// No need to check for validity of action, HIT and STAND are always valid.

		return action;
	}

};

class AIPlayer_Conservative : public AIPlayer{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Conservative(Deck & deck, std::string name, double balance) :
		AIPlayer(deck, name, balance)
{}

	// Always stand
	std::string
	Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const override final
	{
		// No need to check for validity of action, HIT and STAND are always valid.
		return STAND;
	}

};
class AIPlayer_Aggressive : public AIPlayer{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
public:
	AIPlayer_Aggressive(Deck & deck, std::string name, double balance) :
		AIPlayer(deck, name, balance)
{}

	// Always hit
	std::string
	Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const override final
	{
		// No need to check for validity of action, HIT and STAND are always valid.
		return HIT;
	}

};
class AIPlayer_Optimal: public AIPlayer{
	using pPlayerHand = std::unique_ptr<PlayerHand>;
	using Key = std::tuple<unsigned int, bool, bool, bool, unsigned int>;
	using MapElement = std::pair<Key,std::string>;
	using Base = Player;
public:
	AIPlayer_Optimal(Deck & deck, std::string name, double balance, Dealer & dealer) :
	AIPlayer(deck, name, balance),
	_dealer(dealer)
	{}

	static const std::map<Key,std::string> optimalStrategy;

	std::string
	Strategy(std::set<std::string> const & validActions, pPlayerHand const & hand) const override final
	{
		unsigned int value = hand->GetValue();
		bool isSoft = hand->IsSoft();
		bool isPair = hand->IsPair();
		bool isAces = hand->IsPairAces();
		std::string action = StrategyOptimal( value, isSoft, isPair, isAces, _dealer.GetValue());
		// Check if action double is valid
		if((action == DOUBLE) && (validActions.find(action) == validActions.end()))
		{
			action = HIT; // Turn double into a hit.
		}

		return action;
	}
	// Optimal strategy depends on the first card of the dealer.
	std::string
	StrategyOptimal(unsigned int value, bool isSoft, bool isPair, bool isAces, unsigned int dealerValue) const
	{
		Key key{value, isSoft, isPair, isAces, dealerValue};
		return optimalStrategy.at(key);
	}

private:
	Dealer & _dealer;
};

#endif /* SRC_PLAYERSTRATEGY_H_ */
