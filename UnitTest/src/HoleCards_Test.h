/*
 * HoleCards_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_HOLECARDS_TEST_H_
#define SRC_HOLECARDS_TEST_H_
#include "gtest/gtest.h"
#include "../../Black_Jack_lib/src/HoleCards.h"
//
// Forward declarations
class Card;

class HoleCardsTest : public ::testing::Test
{
public:
	using pCard = std::unique_ptr<Card>;
//	void SetUp()
//	{
//		Test::SetUp();
//	}

//	void TearDown()
//	{
//		Test::TearDown();
//	}
	void Run_AddAndRemoveOneCard();
	void Run_RemoveCard_DEATH();
	void Run_OneStartCard_DEATH();
	void Run_OneStartCard();
	void Run_TwoStartCard_DEATH();
	void Run_TwoStartCard();
	void Run_GetValue();
	void Run_Pair();
	void Run_PairAces();
	void Run_BlackJack();
	void Run_SoftAces();


private:
	HoleCards _holeCards;

};



TEST_F(HoleCardsTest, AddAndRemoveOneCard)
{
	Run_AddAndRemoveOneCard();
}
//TEST_F(HoleCardsTest, RemoveCard_DEATH)
//{
//	Run_RemoveCard_DEATH();
//}

//TEST_F(HoleCardsTest, Run_OneStartCard_DEATH)
//{
//	Run_OneStartCard_DEATH();
//}
TEST_F(HoleCardsTest, OneStartCard)
{
	Run_OneStartCard();
}

//TEST_F(HoleCardsTest, TwoStartCard_DEATH)
//{
//	Run_TwoStartCard_DEATH();
//}

TEST_F(HoleCardsTest, TwoStartCard)
{
	Run_TwoStartCard();
}
TEST_F(HoleCardsTest, GetValue)
{
	Run_GetValue();
}

TEST_F(HoleCardsTest, Pair)
{
	Run_Pair();
}
TEST_F(HoleCardsTest, PairAces)
{
	Run_PairAces();
}
TEST_F(HoleCardsTest, BlackJack)
{
	Run_BlackJack();
}

TEST_F(HoleCardsTest, SoftAces)
{
	Run_SoftAces();
}



#endif /* SRC_HOLECARDS_TEST_H_ */
