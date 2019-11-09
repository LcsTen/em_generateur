#ifndef entite_hpp
#define entite_hpp

#include <string>
#include <vector>
#include <iostream>
#include "general.hpp"

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
		Entite& getParent();
		
		virtual std::string toString() const;
		
		std::ostream& print(std::ostream& out) const;
};

std::ostream& operator<<(std::ostream& out,const Entite& e);

#endif