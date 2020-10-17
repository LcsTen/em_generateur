#include "Monde.h"

#include "Pays.h"
#include "general.h"

Monde::Monde(std::string nom,size_t lin,size_t col) : Entite(nom,*this), map(lin,col){
	int nbPays = randomInt(2,10);
	for(int i = 0;i < nbPays;i++){
		creerEnfant();
	}
}

Monde::Monde(std::string nom) : Monde(nom,24,24) {}

Monde::Monde(size_t lin,size_t col) : Monde(genererNom(10),lin,col) {}

Monde::Monde() : Monde(genererNom(10)) {}

Entite* Monde::creerEnfant(std::string nom){
	Pays* p = new Pays(nom,*this);
	enfants.push_back(p);
	return p;
}

Entite* Monde::creerEnfant(){
	return creerEnfant(genererNom(10));
} 

int Monde::getPopulation() const{
	int res = 0;
	for(unsigned int i = 0;i < enfants.size();i++){
		res += enfants[i]->getPopulation();
	}
	return res;
}

const Map& Monde::getMap() const{
	return map;
}

/*std::string Monde::toString() const{
	return "Monde(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+" pays.size(): "+std::to_string(pays.size())+", population: "+std::to_string(getPopulation())+')';
}*/

std::string Monde::toString() const{
	return "Monde"+Entite::toString();
}

/*std::ostream& Monde::print(std::ostream& out) const{
	return out << toString();
}

std::ostream& operator<<(std::ostream& out,const Monde m){
	return m.print(out);
}*/
