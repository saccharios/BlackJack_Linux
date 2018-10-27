/*
 * Game.h
 *
 *  Created on: 30.12.2016
 *      Author: Stefan
 */

#include <memory>

#include "../../Black_Jack_lib/src/Dealer.h"
#include "../../Black_Jack_lib/src/Deck.h"
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"
#include "../../Black_Jack_lib/src/PlayerStrategy.h"

#ifndef GAME_H_
#define GAME_H_

// Class game is the glue code which binds all other classes together.
// It guides the game.
class Game {
	using pPlayer = std::unique_ptr<Player>;

public:
	Game () : _deck(), _dealer(_deck), _players() {}
	// Not allowed to copy or assign game
	Game(Game const &) = delete ;
	void operator=(Game const&) = delete;


	void PlayRound();
	virtual bool PlayAnotherRound () = 0;

	void PrintNumPlayers () const;


protected:
	virtual ~Game(){}; // Not allowed to polymorphic delete derivatives

	virtual void SetWagers() = 0;
	virtual void RemoveBrokePlayers() = 0;

	Deck _deck;
	Dealer _dealer;
	// Players are pointers to avoid issues with card pointers
	std::vector<pPlayer> _players;
private:
	void GetStartCards();
	void PlayCards();
	void Evaluate();
	void PutCardsBack();

};

#endif /* GAME_H_ */
