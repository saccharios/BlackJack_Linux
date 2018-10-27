/*
 * PlayerHand.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */


#include "../../Black_Jack_lib/src/PlayerHand.h"

#include <memory>

#include "../../Black_Jack_lib/src/Card.h"
#include "../../Black_Jack_lib/src/Deck.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
#include "../../Black_Jack_lib/src/HoleCards.h"

PlayerHand::PlayerHand (Deck & deck, double const & wager, unsigned int const & handNumber):
_deck(deck),
_handNumber(handNumber),
_isPlayed(false)
{
	std::stringstream strm;
	// Make sure that the wager at the creation is within bounds. Hard force it.
	if( wager < MIN_WAGER)
	{
		_wager = MIN_WAGER;
		strm  << "Your wager is too low, setting to minimum wager (" << MIN_WAGER << ")\n";

	}
	else if (wager > MAX_WAGER)
	{
		strm << "Your wager is too high, setting to maximum wager (" << MAX_WAGER << ")\n";
		console.Write(strm);
		_wager = MAX_WAGER;
	}
	else
	{
		_wager = wager;
	}
}


void PlayerHand::Start()
{
	// Normal start function for the player
	auto card1 = _deck.Draw();
	auto card2 = _deck.Draw();

	_holeCards.StartCards(std::move(card1), std::move(card2));
	_isPlayed = false;
}

void PlayerHand::Start( pCard card1 )
{
	// Start function only used when one card is known, so during splitting
	console.WriteString("Draw second card: ");
	auto card2 = _deck.Draw();
	card2 ->Print();
	console.WriteString(" ");
	_holeCards.StartCards(std::move(card1), std::move(card2));
	PrintCards();
	_isPlayed = false;
}

PlayerHand::pPlayerHand PlayerHand::ActionSplit()
{
	// Save if pair is Aces for later
	auto wasAces = _holeCards.ArePairAces();
	// Remove the two cards from the current hand
	auto card1 = _holeCards.RemoveLastCard();
	auto cardForNewHand = _holeCards.RemoveLastCard();
	PrintHandNumber();
	// Restart the the current hand with one card
	Start(std::move(card1));
	// Create new hand with incremented hand number
	auto nextNr = GetHandNumber() + 1;
	auto newHand = std::make_unique<PlayerHand>(_deck, _wager,nextNr);

	newHand->PrintHandNumber();
	newHand->Start(std::move(cardForNewHand));
	// Don't allow to play if Aces were split
	if(wasAces)
	{
		_isPlayed = true;
		newHand->ActionStand();
	}

	return newHand;
}
void PlayerHand::ActionDouble()
{
	_wager *= 2.0;
	ActionHit();
	_isPlayed = true;
}
void PlayerHand::ActionHit()
{
	console.WriteString("Draw a card....\n");
	auto card = _deck.Draw();
	console.WriteString("The card drawn is the ");
	card->Print();
	console.WriteString(". ");
	_holeCards.AddCard(std::move(card));
	PrintHandNumber();
	PrintCards();
	_isPlayed = GetValue() > 20; // No need to keep playing if you have 21 points
}
void PlayerHand::ActionStand()
{
	_isPlayed = true; // Stops the actions
}

double PlayerHand::Evaluate(double const & dealerHasBlackJack,
		bool const & dealerIsBusted,
		unsigned int const & dealerValue) const
{
	// Returns winnings of the hand. Needs dealer status as input.
	PrintHandNumber();
	if( dealerHasBlackJack)
	{
		if(IsBlackJack())
		{
			return PayoutPush();
		}
		else
		{
			return PayoutLoose();
		}
	}
	else if ( IsBlackJack() )
	{
		return PayoutBlackJack();
	}
	else if ( _holeCards.AreBusted())
	{
		return PayoutLoose();
	}
	else if(dealerIsBusted)
	{
		return PayoutWin();
	}
	else if(GetValue() > dealerValue)
	{
		return PayoutWin();
	}
	else if(GetValue() < dealerValue)
	{
		return PayoutLoose();
	}
	else
	{
		return PayoutPush();
	}
}
double PlayerHand::PayoutPush () const
{
	console.WriteString("Push.\n");
	return GetWager();
}
double PlayerHand::PayoutLoose () const
{
	console.WriteString("Loose.\n");
	return 0.0;

}
double PlayerHand::PayoutWin () const
{
	console.WriteString("Win.\n");
	return 2.0*GetWager();
}
double PlayerHand::PayoutBlackJack () const
{
	console.WriteString("BlackJack pays 5 to 2\n");
	return 2.5*GetWager();
}


void PlayerHand::PrintHandNumber() const
{
	std::stringstream strm;
	strm << "Hand " << GetHandNumber() << ": ";
	console.Write(strm);
}

void PlayerHand::PutCardsBack()
{
	while(!IsEmpty())
	{
		_deck.AddCard(std::move(_holeCards.RemoveLastCard()));
	}
}
std::set<std::string>  PlayerHand::GetAvailableActionSet() const
{
	// Depending only on status of the hand, returns available actions
	if(IsFirstAction() )
	{
		if( IsPair())
		{
			return ACTION_SPLIT_DOUBLE;
		}
		else
		{
			return ACTION_DOUBLE;
		}
	}
	return ACTION_STANDARD;
}


