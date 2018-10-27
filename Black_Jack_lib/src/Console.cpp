/*
 * Console.cpp
 *
 *  Created on: 19.01.2017
 *      Author: Stefan
 */

#include "../../Black_Jack_lib/src/Console.h"

#include <iostream>
#include <string>
#include <sstream>

#include "../../Black_Jack_lib/src/GlobalDeclarations.h"


void Console::Write( std::stringstream const & strm )
{
	*_ostream << strm.str();
}
void Console::WriteString( std::string const & str )
{
	*_ostream << str;
}


void Console::PrintStringSet (std::set<std::string> const & stringSet)
{
	// Print possible user input strings defined in stringSet
	*_ostream << " ";
	for(auto const & str : stringSet)
	{
		*_ostream << "("<< str << ") ";
	}
	*_ostream<< "\n";
}
std::string Console::ReadInAction(std::set<std::string> const & stringSet)
{
	// Read in an action from user that is in stringSet
	std::string readIn("");
	auto i = 0u;
	do
	{
		if(++i > 1)
		{

			*_ostream << "You have entered "<< readIn << ". Enter";
		}
		PrintStringSet(stringSet);
		std::getline (*_istream, readIn);
	}while(stringSet.find(readIn) == stringSet.end());
	return readIn;
}


std::string Console::ReadInName(unsigned int const & numPlayer, unsigned int const & maxChars)
{
	// Read in user input name for current player with number numPlayer
	std::string name("");
	std::string readIn("");
	*_ostream << "Enter name of player " << numPlayer <<": " << std::endl;

	auto i = 0u;
	do
	{
		if(++i > 1)
		{
			*_ostream << "Do not enter an empty name.";
		}
		std::getline (*_istream, readIn);
		std::stringstream(readIn) >> name;
	}while(name.empty());

	if( name.size() > maxChars )
	{
		*_ostream << "Your name is too long, truncating after " << maxChars << " characters." << std::endl;
		name = name.substr( 0, maxChars ) ;
	}
	return name;
}
