#include "Personne.h"

Personne::Personne(std::string prenom,std::string nom,int age){
	_prenom = prenom;
	_nom = nom;
	_age = age;
}

std::string Personne::sePresente() const{
	return "Bonjour, je m'appelle "+_prenom+' '+_nom+" et j'ai "+std::to_string(_age)+" ans.";
}

std::ostream& Personne::print(std::ostream& out) const{
	return out << "Personne(prenom: "+_prenom+", nom: "+_nom+", age: "+std::to_string(_age)+')';
}

std::ostream& operator<<(std::ostream& out,const Personne p){
	return p.print(out);
}