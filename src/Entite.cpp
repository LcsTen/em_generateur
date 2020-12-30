#include "Entite.h"

#include "general.h"

Entite::Entite(std::string nom,Entite& parent) : _nom(nom), _parent(parent) {
	genererGentile(nom,&ms,&mp,&fs,&fp);
}

Entite::Entite(Entite& parent) : Entite(generateName(10),parent) {}

Entite::~Entite(){
	for(unsigned int i = 0;i < enfants.size();i++){
		delete enfants[i];
	}
	enfants.clear();
}

Entite& Entite::getParent() const{
	return _parent;
}

std::string Entite::getNom() const{
	return _nom;
}
std::string Entite::getMs() const{
	return ms;
}
std::string Entite::getMp() const{
	return mp;
}
std::string Entite::getFs() const{
	return fs;
}
std::string Entite::getFp() const{
	return fp;
}
std::string Entite::getGent(Genre gp) const{
	switch(gp){
		case MS: return ms;
		case MP: return mp;
		case FS: return fs;
		default: return fp;
	}
}

int Entite::getNbEnfants() const{
	return enfants.size();
}

Entite* Entite::getEnfant(unsigned int n) const{
	if(n > enfants.size()){
		return NULL;
	}else{
		return enfants[n];
	}
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
