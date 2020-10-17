#ifndef NOM_H
#define NOM_H

#include <string>
#include <ostream>

#include "Genre.h"

class Nom {
	private:
		std::string _nom;
		Genre _genre;
		
	public:
		Nom(std::string nom,Genre genre);
		std::string getNom();
		Genre getGenre();
		
		std::ostream& print(std::ostream& out);
};

std::ostream& operator<<(std::ostream& out,Nom n);

#endif // NOM_H
