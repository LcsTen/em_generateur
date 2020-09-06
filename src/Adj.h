#ifndef ADJ_HPP
#define ADJ_HPP

#include <string>

#include "Genre.h"

class Adj {
	private:
		std::string _ms;
		std::string _mp;
		std::string _fs;
		std::string _fp;
		
	public:
		Adj(std::string ms,std::string mp = "",std::string fs = "",std::string fp = "");
		std::string getMs();
		std::string getMp();
		std::string getFs();
		std::string getFp();
		std::string get(Genre g);
		
		std::string operator[](Genre g);
};

#endif // ADJ_HPP