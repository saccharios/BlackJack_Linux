/*
 * Player_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_PLAYER_TEST_H_
#define SRC_PLAYER_TEST_H_


#include "gtest/gtest.h"
#include "PlayerStrategy.h"
#include "Player.h"
#include "Deck.h"
class PlayerHand;

class PlayerTest : public ::testing::Test
{
private:
	const double _initBalance = 10.0;
	const unsigned int _numDecks = 1;
	const std::string _name = "Player_A";
	const double _originalWager = 1.0;
	const unsigned int handNr = 0;
public:
	using pHandManager = std::unique_ptr<PlayerHand>;
	using pCard = std::unique_ptr<Card>;
	PlayerTest() : _deck(0), _player(_deck, _name, _initBalance)
	// Use seed 0 to always draw the same card.
	// The card drawn depends only on their order in the deck.
	{
		_deck.AddSets(_numDecks);
		_hand = std::make_unique<PlayerHand>(_deck, _originalWager, handNr);
	}
//	void SetUp()
//	{
//		Test::SetUp();
//	}

//	void TearDown()
//	{
//		Test::TearDown();
//	}
	void Run_Create();
	void Run_Start();
	void Run_Hit();
	void Run_Stand();
	void Run_Split();
	void Run_Double();
	void Run_SetWager();
	void Run_SetWagerMin_DEATH();
	void Run_SetWagerMax_DEATH();
	void Run_AddToBalance();
	void Run_SubractFromBalance();
	void Run_PutCardsBack();
	void Run_GetAvailableActionSet();
	void Run_Play();
private:
	Deck _deck;
	HumanPlayer _player;
	pHandManager _hand;
};
TEST_F(PlayerTest, Create)
{
	Run_Create();
}
TEST_F(PlayerTest, Start)
{
	Run_Start();
}
TEST_F(PlayerTest, Hit)
{
	Run_Hit();
}
TEST_F(PlayerTest, Stand)
{
	Run_Stand();
}
TEST_F(PlayerTest, Split)
{
	Run_Split();
}
TEST_F(PlayerTest, Double)
{
	Run_Double();
}
TEST_F(PlayerTest, SetWager)
{
	Run_SetWager();
}
//TEST_F(PlayerTest, SetWagerMin_DEATH)
//{
//	Run_SetWagerMin_DEATH();
//}
//TEST_F(PlayerTest, SetWagerMax_DEATH)
//{
//	Run_SetWagerMax_DEATH();
//}
TEST_F(PlayerTest, AddToBalance)
{
	Run_AddToBalance();
}
TEST_F(PlayerTest, SubractFromBalance)
{
	Run_SubractFromBalance();
}
TEST_F(PlayerTest, PutCardsBack)
{
	Run_PutCardsBack();
}
TEST_F(PlayerTest, GetAvailableActionSet)
{
	Run_GetAvailableActionSet();
}

TEST_F(PlayerTest, Play)
{
	Run_Play();
}





#endif /* SRC_PLAYER_TEST_H_ */
