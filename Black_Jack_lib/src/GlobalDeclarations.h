/*
 * StaticDeclarations.h
 *
 *  Created on: 17.10.2016
 *      Author: Stefan
 */

#ifndef GLOBALDECLARATIONS_H_
#define GLOBALDECLARATIONS_H_
#include <map>
#include <set>

#include "../../Black_Jack_lib/src/Console.h"
// constexpr because all values are known at compile time
constexpr auto MIN_WAGER = 1.0;
constexpr auto MAX_WAGER = 500.0;
constexpr unsigned int MAX_SETS = 8;
constexpr unsigned int MAX_PLAYERS = 8;
constexpr auto MIN_INIT_BALANCE = 1.0;
constexpr auto MAX_INIT_BALANCE = 100000.0;
constexpr std::string::size_type MAX_CHARS = 20 ;

const std::set<std::string> SUIT{"h","d","c","s"};
// Face is a map, to make assigning the value to a card easy.
const std::map<std::string, unsigned int> FACE = {{"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9}, {"T", 10}, {"J", 10}, {"Q", 10}, {"K", 10}, {"A", 11}};

// The actions of a player are identified by a string.
static const std::string HIT = "h";
static const std::string DOUBLE = "d";
static const std::string SPLIT = "p";
static const std::string STAND = "s";

const std::set<std::string> ACTION_SPLIT_DOUBLE{HIT,STAND,DOUBLE, SPLIT};
const std::set<std::string> ACTION_DOUBLE{HIT,STAND, DOUBLE};
const std::set<std::string> ACTION_STANDARD{HIT,STAND};


static Console console(std::cout, std::cin);

#endif
