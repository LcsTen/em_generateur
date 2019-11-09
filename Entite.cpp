#include "Entite.hpp"

Entite::Entite(std::string nom,Entite& parent) : _nom(nom), _parent(parent) {
	genererGentile(nom,&ms,&mp,&fs,&fp);
}

Entite::Entite(Entite& parent) : Entite(genererNom(10),parent) {}

Entite::~Entite(){
	for(unsigned int i = 0;i < enfants.size();i++){
		delete enfants[i];
	}
	enfants.clear();
}

Entite& Entite::getParent(){
	return _parent;
}

std::string Entite::toString() const{
	return "(nom: "+_nom+", ms: "+ms+", mp: "+mp+", fs: "+fs+", fp: "+fp+", enfants.size(): "+std::to_string(enfants.size())+", getPopulation(): "+std::to_string(getPopulation())+')';
}
		
std::ostream& Entite::print(std::ostream& out) const{
	return out << toString();
}
		
std::ostream& operator<<(std::ostream& out,const Entite& e){
	return e.print(out);
}