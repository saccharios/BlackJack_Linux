/*
 * PlayerStrategy_Test.cpp
 *
 *  Created on: 16.03.2017
 *      Author: Stefan
 */

#include "PlayerStrategy_Test.h"
#include "PlayerStrategy.h"
#include "GlobalDeclarations.h"
#include <string>

void AIPlayer_OptimalTest::Run_OptimalStrategy()
{
	std::string action = STAND;
	// Loop over all values and dealervalues, with no pair and no aces
	unsigned int value = 0;
	bool isSoft = false;
	bool isPair = false;
	bool isAces = false;
	unsigned int dealerValue = 0;
	for( value = 5; value <= 20; ++value )
	{
		for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
		{
			action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
			if(value >= 17)
			{
				EXPECT_EQ(STAND,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (16 >= value && value >= 13 ) && dealerValue <= 6)
			{
				EXPECT_EQ(STAND,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 12 && (4 <= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ(STAND,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 11 && dealerValue <= 10 )
			{
				EXPECT_EQ(DOUBLE,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 10 && dealerValue  <= 9)
			{
				EXPECT_EQ(DOUBLE,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if (value == 9 && (3 <= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ(DOUBLE,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
			else
			{
				EXPECT_EQ(HIT,action) << "Normal. Value = " <<value << ", dealer = " << dealerValue;
			}
		}
	}
//
	// Loop over all values and dealervalues, with soft ace
	isSoft = true;
	isPair = false;
	isAces = false;
	for( value = 13; value <= 20; ++value )
	{
		for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
		{
			action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
			if(value >= 19)
			{
				EXPECT_EQ(STAND,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( value == 18 &&  dealerValue  <= 8)
			{
				if( 3 <= dealerValue && dealerValue  <= 6)
				{
					EXPECT_EQ(DOUBLE,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
				}
				else
				{
					EXPECT_EQ(STAND,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
				}
			}
			else if (value == 17 && (3 <= dealerValue && dealerValue  <= 6))
			{
				EXPECT_EQ(DOUBLE,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (16 >= value && value >= 15 ) && (4 <= dealerValue && dealerValue  <= 6) )
			{
				EXPECT_EQ(DOUBLE,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else if ( (14 >= value && value >= 13 ) && (5 <= dealerValue && dealerValue  <= 6) )
			{
				EXPECT_EQ(DOUBLE,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
			else
			{
				EXPECT_EQ(HIT,action) << "Soft. Value = " <<value << ", dealer = " << dealerValue;
			}
		}
	}
	// Handle each pair separately, because pairs are more complicated.
	// Loop over all values and dealervalues, with pairs
	isSoft = true;
	isPair = true;
	// Pair of Aces
	isAces = true;
	value = 12;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ(SPLIT,action) << "Pair Aces. Value = " <<value << ", dealer = " << dealerValue;
	}
	isSoft = false;
	isAces = false;
	// Pair of Tens, Jacks, Queens, Kings
	value = 20;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ(STAND,action) << "Pair Tens, Jacks, Queens, Kings. Value = " <<value << ", dealer = " << dealerValue;
	}
	// Pair of Nines
	value = 18;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue <=6 || dealerValue == 8 || dealerValue == 9)
		{
			EXPECT_EQ(SPLIT,action) << "Pair Nines. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(STAND,action) << "Pair Nines. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Eights
	value = 16;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		EXPECT_EQ(SPLIT,action) << "Pair Eights. Value = " <<value << ", dealer = " << dealerValue;
	}
	// Pair of Sevens
	value = 14;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ(SPLIT,action) << "Pair Sevens. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Sevens. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Sixes
	value = 12;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 6 )
		{
			EXPECT_EQ(SPLIT,action) << "Pair Sixes. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Sixes. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
//	 Pair of Fives
	value = 10;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue <= 9 )
		{
			EXPECT_EQ(DOUBLE,action) << "Pair Fives. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Fives. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Fours
	value = 8;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if( dealerValue == 5 || dealerValue == 6 )
		{
			EXPECT_EQ(SPLIT,action) << "Pair Fours. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Fours. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Threes
	value = 6;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ(SPLIT,action) << "Pair Threes. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Threes. Value = " <<value << ", dealer = " << dealerValue;
		}
	}
	// Pair of Twos
	value = 4;
	for( dealerValue = 2; dealerValue <= 11; ++dealerValue )
	{
		action = _AIPlayer.StrategyOptimal(value, isSoft, isPair, isAces, dealerValue);
		if(dealerValue <= 7 )
		{
			EXPECT_EQ(SPLIT,action) << "Pair Twos. Value = " <<value << ", dealer = " << dealerValue;
		}
		else
		{
			EXPECT_EQ(HIT,action) << "Pair Twos. Value = " <<value << ", dealer = " << dealerValue;
		}
	}


}
