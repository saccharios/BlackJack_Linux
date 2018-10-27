/*
 * ConsoleTest.cpp
 *
 *  Created on: 13.02.2017
 *      Author: Stefan
 */

#include "ConsoleTest.h"
#include <set>

void Console_Test::Run_Write()
{
	std::string str = "The answer is 41.";
	// Actual tests
	std::stringstream strm;
	strm << str;
	_console.Write(strm);
	std::string readIn("");
	std::getline (_out_stream, readIn);
	EXPECT_EQ(str,readIn);
}
void Console_Test::Run_WriteString()
{
	std::string str = "The answer is 42.";
	// Actual tests
	_console.WriteString(str);
	std::string readIn("");
	std::getline (_out_stream, readIn);
	EXPECT_EQ(str,readIn);
}
void Console_Test::Run_PrintStringSet()
{
	std::set<std::string> stringSet = {"a","b", "cde"};
	_console.PrintStringSet(stringSet);
	std::string readIn("");
	std::getline (_out_stream, readIn);
	std::string result = " (a) (b) (cde) ";
	EXPECT_EQ(result, readIn);

}
void Console_Test::Run_ReadInNumber()
{
	_in_stream << "-10" << std::endl
			<< "0" << std::endl
			<< "1" << std::endl
			<< "5" << std::endl
			<< "11" << std::endl
			<< "10" << std::endl
			;
	double min = 1;
	double max = 10;
	// Actual tests
	// First test with -10, 0 ,1
	auto readIn = _console.ReadInNumber(min, max);
	double result = 1;
	EXPECT_EQ(result, readIn);
	// Second test with 5
	readIn = _console.ReadInNumber(min, max);
	result = 5;
	EXPECT_EQ(result, readIn);
	// Third test with 11, 10
	readIn = _console.ReadInNumber(min, max);
	result = 10;
	EXPECT_EQ(result, readIn);
}

void Console_Test::Run_ReadInAction()
{
	_in_stream << "d" << std::endl
			<< "q d" << std::endl
			<< "3" << std::endl
			<< "abc" << std::endl
			<< "p 5" << std::endl
			<< "p" << std::endl
			;
	std::set<std::string> stringSet = {"d","h", "s" ,"p"};
	// Actual tests
	// First test with "d"
	auto readIn = _console.ReadInAction(stringSet);
	std::string result = "d";
	EXPECT_EQ(result, readIn);
	// Second test with "q", "3", "abc", "p"
	readIn = _console.ReadInAction(stringSet);
	result = "p";
	EXPECT_EQ(result, readIn);
}
void Console_Test::Run_ReadInName()
{


	// Setup test file to be read in
	std::string gauss = "Gauss";
	std::string max = "Max Well";
	std::string einstein= "EinsteinStokesNewtonLeibnitzTuring";
	std::string tesla = "Tesla";
	std::string empty = "";
	std::string galileo = "Galileo";

	_in_stream << gauss << std::endl
			<< max <<std::endl
			<< einstein << std::endl
			<< " " << tesla << std::endl
			<< empty << std::endl
			<< galileo << std::endl
			;

	unsigned int numPlayer = 0;
	unsigned int const maxChars = 20;
	// Actual tests
	// First test with "Gauss"
	auto readIn = _console.ReadInName(++numPlayer, maxChars);

	EXPECT_EQ(gauss, readIn);
	// Second test with "Max Well"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	std::string result = "Max";
	EXPECT_EQ(result, readIn);
	// Third test with "EinsteinStokesNewtonLeibnitzTuring"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = einstein.substr( 0, maxChars );
	EXPECT_EQ(result, readIn);
	// Fourth test with " Tesla"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = tesla;
	EXPECT_EQ(result, readIn);
	// Fifth test with "", "Galileo"
	readIn = _console.ReadInName(++numPlayer, maxChars);
	result = galileo;
	EXPECT_EQ(result, readIn);

}
