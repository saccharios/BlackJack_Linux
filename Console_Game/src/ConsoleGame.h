/*
 * ConsoleGame.h
 *
 *  Created on: 25.03.2017
 *      Author: Stefan
 */

#ifndef CONSOLEGAME_H_
#define CONSOLEGAME_H_

#include "Game.h"
#include "PlayerStrategy.h"
class ConsoleGame : public Game{
	using Base = Game;
	using pHumanPlayer = std::unique_ptr<HumanPlayer>;
public:
	void AddDecks();
	void AddHumanPlayers();
	void PrintRules();
	void SetWagers() override;
	bool PlayAnotherRound () override;
	void RemoveBrokePlayers() override;
};

#endif /* CONSOLEGAME_H_ */
