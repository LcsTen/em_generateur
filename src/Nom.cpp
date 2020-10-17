#include "Nom.h"

Nom::Nom(std::string nom,Genre genre) : _nom(nom), _genre(genre)
{}

std::string Nom::getNom(){
	return _nom;
}

Genre Nom::getGenre(){
	return _genre;
}

std::ostream& Nom::print(std::ostream& out){
	return out << _nom;
}

std::ostream& operator<<(std::ostream& out,Nom n){
	return n.print(out);
}
