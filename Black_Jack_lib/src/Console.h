/*
 * Console.h
 *
 *  Created on: 19.01.2017
 *      Author: Stefan
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_
#include <set>
#include <string>
#include <iostream>
#include <sstream>
class Console{
public:
	Console (std::ostream & ostrm, std::istream & istrm) : _ostream(&ostrm), _istream(&istrm) {}
	void PrintStringSet (std::set<std::string> const & stringSet);
	std::string ReadInAction(std::set<std::string> const & stringSet);
	std::string ReadInName(unsigned int const & numPlayer, unsigned int const & maxChars);
	// Templated functions cannot be implemented in the .cpp file
	template<typename T>
	T ReadInNumber( T const & min, T const & max)
	{
		std::string readIn;
		T value;
		do
		{
			*_ostream << "Enter a number between " << min << " and " << max <<"."<<std::endl;
			std::getline (*_istream, readIn);
			std::stringstream(readIn) >> value;
		}while(value < min || value > max);
		*_ostream << "You have entered " << value << "."<<std::endl;
		return value;
	}
	void Write( std::stringstream const & strm );
	void WriteString( std::string const & str );
	void SetInputStream(std::istream & istrm) {_istream = &istrm;}

private:
	std::ostream* _ostream;
	std::istream* _istream;

};

#endif /* CONSOLE_H_ */
