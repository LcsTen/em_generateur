#ifndef personne_h
#define personne_h

#include <string>
#include <iostream>

class Personne{
	private:
		std::string _prenom;
		std::string _nom;
		int _age;
		
	public:
		Personne(std::string prenom,std::string nom,int age);
		
		std::string sePresente() const;
		
		std::ostream& print(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out,const Personne p);

#endif // personne_h
