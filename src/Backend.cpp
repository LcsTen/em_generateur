#include "Backend.h"

#if QT != 0 || WEB != 0
	// HTML4-capable
	#define INDENT(depth) std::string("")
	#define H1(depth) "<h1>"
	#define _H1(depth) "</h1>"
	#define H2(depth) "<h2>"
	#define _H2(depth) "</h2>"
	#define BR "<br>"
	#define GREEN "<font color=\"green\">"
	#define DARKMAGENTA "<font color=\"darkmagenta\">"
	#define RED "<font color=\"red\">"
	#define DARKRED "<font color=\"#c80000\">"
	#define BLUE "<font color=\"blue\">"
	#define CYAN "<font color=\"cyan\">"
	#define _COLOR "</font>"
	#define UL "<ul>"
	#define _UL "</ul>"
	#define LI(depth) "<li>"
	#define _LI "</li>"
#elif CONSOLE != 0
	// ANSI-capable
	#define INDENT(depth) std::string(depth, '\t')
	#define H1(depth) INDENT(depth)
	#define _H1(depth) "\n"+INDENT(depth)
	#define H2(depth) INDENT(depth)
	#define _H2(depth) "\n"+INDENT(depth)
	#define BR "\n"
	#define GREEN "\e[32m"
	#define DARKMAGENTA "\e[35m"
	#define RED "\e[31m"
	#define DARKRED "\e[91m"
	#define BLUE "\e[34m"
	#define CYAN "\e[36m"
	#define _COLOR "\e[0m"
	#define UL ""
	#define _UL ""
	#define LI(depth) "\n"+INDENT(depth)
	#define _LI ""
#endif

Backend::Backend(){
	generateWorld();
}

STRING_TYPE Backend::politicsToString(){
	std::string res = entiteToString(monde);
	#if QT == 0
		return res;
	#else
		return QString::fromStdString(res);
	#endif
}

STRING_TYPE Backend::spaceToString(){
	std::string res = spaceToString(space);
	#if QT == 0
		return res;
	#else
		return QString::fromStdString(res);
	#endif
}

// TODO: Port to HTML4
std::string Backend::mapToString(){
	std::string res = "";
	for(unsigned int y = 0;y < monde->getMap().getLines();y++){
		for(unsigned int x = 0;x < monde->getMap().getColumns();x++){
			const Tile tile = monde->getMap()(x,y);
			res += std::string("\e[") + (90+(tile.getTemp()+100)/28) + "m" // Frontground color
				+ "\e[" + (100+(tile.getElev()+100)/28) + "m" // Background color
				+ (tile.getHum()/11) + "\e[0m";
		}
		res += '\n';
	}
	return res;
}

void Backend::generateWorld(){
	delete space;
	delete monde;
	space = new StarSystem();
	std::vector<World*> habitables = space->getHabitableWorlds();
	while(habitables.size() == 0){
		delete space;
		space = new StarSystem();
		habitables = space->getHabitableWorlds();
	}
	monde = new Monde(habitables[0]->getName());
	emit worldChanged();
	emit logPrinted(STRING_TYPE()+"1/1/1: The world "+monde->getNom()+" is created.");
}

void Backend::onWorldChanged(std::function<void()> f){
	worldChangedCallbacks.push_back(f);
}

void Backend::onLogPrinted(std::function<void(std::string)> f){
	logPrintedCallbacks.push_back(f);
}

#if QT == 0
void Backend::worldChanged(){
	for(std::function<void()> f : worldChangedCallbacks){
		f();
	}
}

void Backend::logPrinted(std::string log){
	for(std::function<void(std::string)> f : logPrintedCallbacks){
		f(log);
	}
}
#endif

std::string Backend::entiteToString(Ville* ville, int depth){
	(void)depth; // Silence unused depth parameter for non-CONSOLE builds
	return INDENT(depth)+ville->getNom()+" ("+ville->getPopulation()+" "+ville->getGent(MP)+")";
}

std::string Backend::entiteToString(Pays* pays, int depth){
	std::string res = H2(depth)+pays->getNom()+_H2(depth)+pays->getNom()+" est un pays composé de "+pays->getPopulation()+' '+pays->getGent(MP)+" répartis dans "+pays->getNbEnfants()+" villes:" BR;
	for(int i = 0;i < pays->getNbEnfants();i++){
		res += entiteToString((Ville*)pays->getEnfant(i), depth+1)+BR;
	}
	return res;
}

std::string Backend::entiteToString(Monde* m, int depth){
	std::string res = H1(depth)+m->getNom()+_H1(depth)+m->getNom()+" est un monde composé de "+m->getPopulation()+' '+m->getGent(MP)+" répartis dans "+m->getNbEnfants()+" pays:" BR;
	for(int i = 0;i < m->getNbEnfants();i++){
		res += entiteToString((Pays*)m->getEnfant(i), depth+1)+BR;
	}
	return res;
}

std::string Backend::spaceToString(GasPlanet* g){
	return g->getName()+" (Gas)";
}

std::string Backend::spaceToString(TelluricPlanet* t){
	std::string res;
	size_t hottest = t->getHottestTemperature();
	size_t coldest = t->getColdestTemperature();
	if(hottest > 175 && hottest < 371 && coldest > 175 && coldest < 371){
		// Temperature is always fine: planet is habitable
		res += GREEN;
	}else if(hottest >= 371 && coldest <= 175){
		// Temperature is too extreme
		res += DARKMAGENTA;
	}else if(hottest >= 371 && coldest >= 371){
		// Temperature is always too hot
		res += RED;
	}else if(hottest >= 371 && coldest <= 371){
		// Temperature is too hot in the hottest case
		res += DARKRED;
	}else if(coldest <= 175 && hottest <= 175){
		// Temperature is always too cold
		res += BLUE;
	}else if(coldest <= 175 && hottest >= 175){
		// Temperature is too cold in the coldest case
		res += CYAN;
	}
	res += t->getName()+" (Telluric) ["+coldest+';'+hottest+"]" _COLOR;
	return res;
}

std::string Backend::spaceToString(World* w){
	if(w->isGasPlanet()){
		return spaceToString((GasPlanet*)w);
	}else{
		return spaceToString((TelluricPlanet*)w);
	}
}

std::string Backend::spaceToString(StarSystem* s){
	std::vector<Star*> stars = s->getStars();
	std::vector<World*> worlds = s->getWorlds();
	std::vector<std::vector<std::pair<size_t,World*>>> planets(stars.size());
	std::vector<std::vector<std::pair<size_t,World*>>> satellites(worlds.size());
	std::vector<std::pair<size_t,World*>> circumbinaries;
	for(size_t i = 0;i < worlds.size();i++){
		AstralObject* orbiting = worlds[i]->getOrbiting();
		if(orbiting == nullptr){
			circumbinaries.push_back({i,worlds[i]});
		}else if(orbiting->isStar()){
			for(size_t j = 0;j < stars.size();j++){
				if(orbiting == stars[j]){
					planets[j].push_back({i,worlds[i]});
				}
			}
		}else{
			for(size_t j = 0;j < worlds.size();j++){
				if(orbiting == worlds[j]){
					satellites[j].push_back({i,worlds[i]});
				}
			}
		}
	}
	auto cmp = [](std::pair<size_t,World*>& a,std::pair<size_t,World*>& b){
		return a.second->getDistance() < b.second->getDistance();
	};
	for(size_t i = 0;i < planets.size();i++){
		std::sort(planets[i].begin(),planets[i].end(),cmp);
	}
	for(size_t i = 0;i < satellites.size();i++){
		std::sort(satellites[i].begin(),satellites[i].end(),cmp);
	}
	std::sort(circumbinaries.begin(),circumbinaries.end(),cmp);

	std::string res = H1(0)+s->getName()+_H1(0)+s->getName()+" is a stellar system with "+stars.size()+" stars:" UL;
	for(size_t i = 0;i < stars.size();i++){
		res += LI(1)+s->getName()+" "+((char)('A'+i))+" is a class "+stars[i]->getStarClass()[0]+stars[i]->getStarClass()[1]+" star ("+stars[i]->getTemperature()+"K)" UL;
		for(size_t j = 0;j < planets[i].size();j++){
			World* planet = planets[i][j].second;
			size_t planetIndex = planets[i][j].first;
			res += LI(2)+spaceToString(planet)+UL;
			for(size_t k = 0;k < satellites[planetIndex].size();k++){
				World* satellite = satellites[planetIndex][k].second;
				res += LI(3)+spaceToString(satellite)+_LI;
			}
			res += _UL _LI;
		}
		res += _UL _LI;
	}
	res += _UL BR;
	if(stars.size() > 1){
		res += "Circumbinaries:";
	}
	res += UL;
	for(size_t i = 0;i < circumbinaries.size();i++){
		World* planet = circumbinaries[i].second;
		size_t planetIndex = circumbinaries[i].first;
		res += LI(1)+spaceToString(planet)+UL;
		for(size_t j = 0;j < satellites[planetIndex].size();j++){
			World* satellite = satellites[planetIndex][j].second;
			res += LI(2)+spaceToString(satellite)+_LI;
		}
		res += _UL _LI;
	}
	res += _UL;
	return res;
}

#if QT != 0
	#include "Backend.moc"
#endif
