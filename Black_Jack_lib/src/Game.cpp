/*
 * Game.cpp
 *
 *  Created on: 11.01.2017
 *      Author: Stefan
 */

#include "../../Black_Jack_lib/src/Game.h"

#include <string>
#include <sstream>
#include <sstream>

#include "../../Black_Jack_lib/src/Console.h"
#include "../../Black_Jack_lib/src/Dealer.h"
#include "../../Black_Jack_lib/src/Deck.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
#include "../../Black_Jack_lib/src/Player.h"


void Game::PlayRound()
{
	// Play one round.
	console.WriteString("-------New Round------\n");
	SetWagers();
	GetStartCards();
	PlayCards();
	Evaluate();
	PutCardsBack();
	RemoveBrokePlayers();
}

void Game::GetStartCards()
{
	// Deal start cards to each player and the dealer
	console.WriteString("-------Dealing Start Cards------\n");
	for(auto const & player : _players)
	{
		player->Start();
	}
	_dealer.Start();
}
void Game::PlayCards()
{
	//	Let all players play, then the dealer
	console.WriteString("-------Players are playing------\n");
	for(auto const & player : _players)
	{
		player->Play();
	}
	_dealer.Play();

}
void Game::Evaluate()
{
	// Evaluate payout for each player
	console.WriteString("------Payout Time------\n");
	for(auto const & player : _players)
	{
		player->Evaluate(_dealer.HasBlackJack(),
				_dealer.IsBusted(),
				_dealer.GetValue());
		player->PrintBalance();
	}
}


void Game::PutCardsBack()
{
	// As you would in the real card game, at the end of a round all players and the dealer
	// put their cards back to the deck
	for(auto const & player : _players)
	{
		player->PutCardsBack();
	}
	_dealer.PutCardsBack();
}


void Game::PrintNumPlayers () const
{
	std::stringstream strm;
	strm << "There are " << _players.size() << " players in the game." << std::endl;
	console.Write(strm);
}



