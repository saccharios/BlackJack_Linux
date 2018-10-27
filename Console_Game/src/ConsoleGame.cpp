/*
 * ConsoleGame.cpp
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#include "ConsoleGame.h"

#include "GlobalDeclarations.h"
#include "PlayerStrategy.h"

void ConsoleGame::AddDecks()
{
	// Adds sets to the deck
	console.WriteString("With how many decks do you want to play?\n");
	auto NSets = console.ReadInNumber(1u, MAX_SETS);
	_deck.AddSets(NSets);
}


void ConsoleGame::AddHumanPlayers()
{
	// Player creator function. Needs user input.
	console.WriteString("How many human players want to play?\n");
	auto NPlayers = console.ReadInNumber(1u,static_cast<unsigned int>( MAX_PLAYERS - Base::_players.size()));
	console.WriteString("Enter names and balances for each player:\n" );
	std::stringstream strm;
	for( unsigned int i = 0; i < NPlayers; ++i )
	{
		auto name = console.ReadInName(i, MAX_CHARS);
		strm << "Welcome " << name <<". Set your balance. "<< std::endl;
		console.Write(strm);
		auto balance = console.ReadInNumber( MIN_INIT_BALANCE, MAX_INIT_BALANCE);

		Base::_players.push_back(std::move(std::make_unique<HumanPlayer>(Base::_deck, name, balance)));
	}
}

void ConsoleGame::PrintRules()
{
	// Introduction text
	std::stringstream strm;
	strm
	<< "-------------WELCOME TO BLACKJACK---------------\n"
	<< "                                              	\n"
	<< "   The goal is:                               	\n"
	<< "                                              	\n"
	<< "   Get as close to 21 with your cards, but not	\n"
	<< "   over it. If you have more points than the  	\n"
	<< "   dealer, you win.						   	\n"
	<< "                                              	\n"
	<< "   The Rules are:                             	\n"
	<< "                                              	\n"
	<< "1) Each player places a wager at the beginning	\n"
	<< "   of a round. The minimum wager is "<<MIN_WAGER<<".\n"
	<< "                                              	\n"
	<< "2) Each player is dealt two cards. The dealer 	\n"
	<< "   receives one card. If you have 21 points	\n"
	<< "   with your two starting cards, you have		\n"
	<< "   BlackJack.           					   	\n"
	<< "                                              	\n"
	<< "3) The players play before the dealer. They have\n"
	<< "   the following actions:	   					\n"
	<< "                                              	\n"
	<< "   Stand (s). The player has finished his hand.	\n"
	<< "                                              	\n"
	<< "   Hit (h). Receive one card. If the sum of     \n"
	<< "   your cards exceeds 21, you have instantly    \n"
	<< "   lost otherwise the player chooses his next   \n"
	<< "   action.	             						\n"
	<< "                                              	\n"
	<< "   Double (d). Only available as your first     \n"
	<< "   action. Double your wager and receive		\n"
	<< "   exactly one more card. Finishes your turn.	\n"
	<< "                                              	\n"
	<< "   Split (p). Only available as your first    	\n"
	<< "   action if you have a pair.					\n"
	<< "   Splits your two cards into two hands and		\n"
	<< "   each hand receives one new card. The player 	\n"
	<< "   then continues with both hands.			 	\n"
	<< "   You are allowed to split again after you		\n"
	<< "   split your original hand. For each split,	\n"
	<< "   you need to have sufficient funds available,	\n"
	<< "   as you have to put the same wager on a    	\n"
	<< "   split hand.									\n"
	<< "   A pair of Aces is an exception. 				\n"
	<< "   On each split Ace, you receive exactly one 	\n"
	<< "   more card and your turn is over. 			\n"
	<< "                                              	\n"
	<< "4) The value of a cards is its number, face 	\n"
	<< "   cards are worth 10 points. Aces can either 	\n"
	<< "   be 11 or 1 point.				 			\n"
	<< "                                              	\n"
	<< "5) The dealer plays last. He must hit cards 	\n"
	<< "   until he has more than 16 points. If the		\n"
	<< "   dealer gets busted, every remaining player	\n"
	<< "   wins.										\n"
	<< "   												\n"
	<< "-------------------GOOD LUCK--------------------\n"
	<< "\n"
	;
	console.Write(strm);
}

bool ConsoleGame::PlayAnotherRound ()
{
	// Ask the user if they want to play another round if there are still players with enough money
	if ( Base::_players.size() < 1u)
	{
		console.WriteString("There are no more players left!\n");
		console.WriteString("--------------------BYE BYE--------------------\n");
		return false;
	}
	console.WriteString("Do you want to play another round?");
	auto yesOrNo = console.ReadInAction({"y","n"});
	if( yesOrNo == "y" )
	{
		return true;
	}
	else if( yesOrNo == "n" )
	{
		console.WriteString("--------------------BYE BYE--------------------\n");
		return false;
	}
	else
	{
		console.WriteString("ERROR! User Input failed!\n");
		return false;
	}

}

void ConsoleGame::SetWagers()
{
	// Set wager for each player
	console.WriteString("-------Set Wagers------\n");
	for(auto const & player : Base::_players)
	{
		player->SetWagerUser();
	}
}



void ConsoleGame::RemoveBrokePlayers()
{
	// If a player has less than the minimum wager, they are removed.
	// Conventional for-loop because it needs access to the index to remove it
	for( unsigned int i = 0; i <_players.size(); ++i)
	{
		if(_players[i]->GetBalance() < MIN_WAGER)
		{
			_players.erase(_players.begin()+i);
			--i; // Don't forget to decrement the counter as you just have removed player nr i
		}
	}
}
