/*
 * ConsoleTest.h
 *
 *  Created on: 13.02.2017
 *      Author: Stefan
 */

#ifndef CONSOLETEST_H_
#define CONSOLETEST_H_
#include "gtest/gtest.h"
#include <string>
#include "../../BlackJack/src/GlobalDeclarations.h"
#include <sstream>
#include "../../BlackJack/src/Console.h"
#include <iostream>
#include <fstream>

class Console_Test : public ::testing::Test
{
	public:
	Console_Test() : _console(_out_stream, _in_stream)
	{
	}

	void Run_Write();
	void Run_WriteString();
	void Run_PrintStringSet();
	void Run_ReadInNumber();
	void Run_ReadInAction();
	void Run_ReadInName();
	private:
	std::stringstream _out_stream;
	std::stringstream _in_stream;
	Console _console;
	std::string in = "_in.txt";
	std::string out = "_out.txt";

	std::basic_streambuf<char,std::char_traits<char>> * _cinbuf = nullptr;
	std::basic_streambuf<char,std::char_traits<char>> * _coutbuf = nullptr;
};

TEST_F(Console_Test, Write)
{
	Run_Write();
}
TEST_F(Console_Test, WriteString)
{
	Run_WriteString();
}
TEST_F(Console_Test, PrintStringSet)
{
	Run_PrintStringSet();
}
TEST_F(Console_Test, ReadInNumber)
{
	Run_ReadInNumber();
}
TEST_F(Console_Test, ReadInAction)
{
	Run_ReadInAction();
}
TEST_F(Console_Test, ReadInName)
{
	Run_ReadInName();
}

#endif /* CONSOLETEST_H_ */
