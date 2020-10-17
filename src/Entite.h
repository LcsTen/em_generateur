#ifndef entite_h
#define entite_h

#include <string>
#include <vector>
#include <iostream> // std::ostream

#include "Genre.h"

class Entite{
	private:
		std::string _nom;
		std::string ms;
		std::string mp;
		std::string fs;
		std::string fp;
		Entite& _parent;
	
	protected:
		std::vector<Entite*> enfants;
	
	public:
		Entite(std::string nom,Entite& parent);
		Entite(Entite& parent);
		virtual ~Entite();
		
		virtual Entite* creerEnfant(std::string nom) = 0;
		virtual Entite* creerEnfant() = 0;
		
		virtual int getPopulation() const = 0;
		Entite& getParent() const;
		std::string getNom() const;
		std::string getMs() const;
		std::string getMp() const;
		std::string getFs() const;
		std::string getFp() const;
		std::string getGent(Genre gp) const;
		int getNbEnfants() const;
		Entite* getEnfant(unsigned int n) const;
		
		virtual std::string toString() const;
		
		std::ostream& print(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out,const Entite& e);

#endif // entite_h
