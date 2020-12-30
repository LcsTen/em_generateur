#include "Pays.h"

#include "Ville.h"
#include "general.h"

Pays::Pays(std::string nom,Monde& monde) : Entite(nom,monde) {
	int nbVilles = randomInt(2,10);
	for(int i = 0;i < nbVilles;i++){
		creerEnfant();
	}
}

Entite* Pays::creerEnfant(std::string nom){
	Ville* v = new Ville(nom,*this);
	enfants.push_back(v);
	return v;
}

Entite* Pays::creerEnfant(){
	return creerEnfant(generateName(10));
}

int Pays::getPopulation() const{
	int res = 0;
	for(unsigned int i = 0;i < enfants.size();i++){
		res += enfants[i]->getPopulation();
	}
	return res;
}

std::string Pays::toString() const{
	//return "Pays(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+" villes.size(): "+std::to_string(villes.size())+", population: "+std::to_string(getPopulation())+')';
	return "Pays"+Entite::toString();
}

/*std::ostream& Pays::print(std::ostream& out) const{
	return out << toString();
}

std::ostream& operator<<(std::ostream& out,const Pays p){
	return p.print(out);
}*/
