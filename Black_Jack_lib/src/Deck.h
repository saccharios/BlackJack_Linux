/*
 * Deck.h
 *
 *  Created on: 10.10.2016
 *      Author: Stefan
 */

#ifndef DECK_H_
#define DECK_H_

#include <cstdlib>
#include <memory>
#include <vector>
#include <chrono>
#include <random>
// Forward declaration to avoid #include
class Card;

class Deck
{
	using pCard = std::unique_ptr<Card>;
public:
	Deck() : _cardContainer(), _rng(_seed){}
	Deck(unsigned int seed ) : _cardContainer(), _seed(seed), _rng(_seed){}
	// Not allowed to copy or assign,
	Deck(Deck const &) = delete ;
	void operator=(Deck const&) = delete;

	void AddSets(unsigned int N);
	void AddCard( pCard  card) { _cardContainer.push_back(std::move(card)); }
	pCard Draw();
	pCard Draw(unsigned int number);
	void PrintNumCards() const;
	unsigned int Size() const {return _cardContainer.size();}
	void SetSeed(unsigned int seed) { _seed = seed; }
	std::stringstream GetNumCards() const;

private:
	void AddCompleteSet();
	std::vector<pCard> _cardContainer;
	unsigned int _seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine _rng;

};

#endif /* DECK_H_ */
