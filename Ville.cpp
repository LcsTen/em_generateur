#include "Ville.hpp"

#include "Groupe.hpp"

Ville::Ville(std::string nom,Pays& pays) : Entite(nom,pays) {
	int nbGroupes = randomInt(2,10);
	for(int i = 0;i < nbGroupes;i++){
		creerEnfant();
	}
}
		
Entite* Ville::creerEnfant(std::string nom){
	Groupe* g = new Groupe(nom,*this);
	enfants.push_back(g);
	return g;
}

Entite* Ville::creerEnfant(){
	return creerEnfant(genererNom(10));
}

int Ville::getPopulation() const{
	int res = 0;
	for(unsigned int i = 0;i < enfants.size();i++){
		res += enfants[i]->getPopulation();
	}
	return res;
}

std::string Ville::toString() const{
	//return "Ville(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+" groupes.size(): "+std::to_string(groupes.size())+", population: "+std::to_string(getPopulation())+')';
	return "Ville"+Entite::toString();
}

/*std::ostream& Ville::print(std::ostream& out) const{
	return out << toString();
}

std::ostream& operator<<(std::ostream& out,const Ville v){
	return v.print(out);
}*/