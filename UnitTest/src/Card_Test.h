/*
 * Card_Test.h
 *
 *  Created on: 28.01.2017
 *      Author: Stefan
 */

#ifndef SRC_CARD_TEST_H_
#define SRC_CARD_TEST_H_

#include "gtest/gtest.h"
#include "../../Black_Jack_lib/src/Card.h"
#include <string>
#include "../../Black_Jack_lib/src/GlobalDeclarations.h"


class CardTest : public ::testing::Test
{
public:
	void Run_CreateCard_Face_DEATH();
	void Run_CreateCard_Suit_DEATH();
	void Run_TestSuits();
	void Run_TestFaces();
private:
};

using CardTestDeathTest = CardTest;

//TEST_F(CardTest, CreateCard_Face_DEATH)
//{
//	Run_CreateCard_Face_DEATH();
//}
//TEST_F(CardTestDeathTest, CreateCard_Suit_DEATH)
//{
//	Run_CreateCard_Suit_DEATH();
//}

TEST_F(CardTest, TestSuits)
{
	Run_TestSuits();
}

TEST_F(CardTest, TestFaces)
{
	Run_TestFaces();
}



#endif /* SRC_CARD_TEST_H_ */
