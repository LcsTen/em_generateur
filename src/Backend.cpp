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

#if QT == 0
	#define TO_STRING_TYPE(string) string
	#define FROM_STRING_TYPE(string) string
#else
	#define TO_STRING_TYPE(string) QString::fromStdString(string)
	#define FROM_STRING_TYPE(string) string.toStdString()
#endif

STRING_TYPE Backend::getText(STRING_TYPE message){
	return TO_STRING_TYPE(_(FROM_STRING_TYPE(message).c_str()));
}

STRING_TYPE Backend::politicsToString(int index_country, int index_city){
	if(monde == nullptr){
		return STRING_TYPE();
	}
	std::string res;
	if(index_country <= -1){
		res = entiteToString(monde);
	}else{
		if(index_country < monde->getNbEnfants()){
			Pays* country = (Pays*)monde->getEnfant(index_country);
			if(index_city <= -1){
				res = entiteToString(country);
			}else{
				if(index_city < country->getNbEnfants()){
					res = entiteToString((Ville*)country->getEnfant(index_city));
				}else{
					/*~ %1$d is the index of the country in
					    the list of countries of the world
					    and %2$d is the index of the city in
					    the list of cities of that country.
					    Both are integer numbers, not names. */
					res = _("Error: world[%1$d] has no city %2$d",
						index_country, index_city)+BR;
				}
			}
		}else{
			/*~ %d is the index of the country in the list of
			    countries of the world, it's a integer number, not a
			    name. */
			res = _("Error: the world has no country %d", index_country)+BR;
		}
	}
	return TO_STRING_TYPE(res);
}

STRING_TYPE Backend::spaceToString(){
	if(space == nullptr){
		return STRING_TYPE();
	}
	return TO_STRING_TYPE(spaceToString(space));
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
	/*~ %1$d is the day (which may exceed 31), %2$d is the month (which may
	    exceed 12) and %3$d is the year the world named %4$d is created. */
	std::string log = _("%1$d/%2$d/%3$d: The world %4$s is created.", 1, 1, 1, monde->getNom().c_str());
	emit logPrinted(TO_STRING_TYPE(log));
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
	/*~ %1$s is the name of the city, %2$d the population and %3$s the
	    gentilic. It may be preferable to keep this minimalist description. */
	return INDENT(depth)+_("%1$s (%2$d %3$s)", ville->getNom().c_str(),
			       ville->getPopulation(), ville->getGent(MP).c_str());
}

std::string Backend::entiteToString(Pays* pays, int depth){
	/*~ %1$s is the name of the country, %2$d is the population, %3$d is the
	    gentilic and %4$d is the number of cities. */
	std::string res = H2(depth)+pays->getNom()+_H2(depth)+_("%1$s is a country populated by %2$d %3$s split in %4$d cities",
		  pays->getNom().c_str(), pays->getPopulation(),
		  pays->getGent(MP).c_str(), pays->getNbEnfants())+':'+BR;
	for(int i = 0;i < pays->getNbEnfants();i++){
		res += entiteToString((Ville*)pays->getEnfant(i), depth+1)+BR;
	}
	return res;
}

std::string Backend::entiteToString(Monde* m, int depth){
	/*~ %1$ is the name of hte world, %2$d is the population, %3$d is the
	    gentilic and %4$d is the number of countries. */
	std::string res = H1(depth)+m->getNom()+_H1(depth)+_("%1$s is a world populated by %2$d %3$s split in %4$d countries",
		  m->getNom().c_str(), m->getPopulation(),
		  m->getGent(MP).c_str(), m->getNbEnfants())+':'+BR;
	for(int i = 0;i < m->getNbEnfants();i++){
		res += entiteToString((Pays*)m->getEnfant(i), depth+1)+BR;
	}
	return res;
}

std::string Backend::spaceToString(GasPlanet* g){
	/*~ %s is the name of the planet, and "Gas" refers to its type (here, a
	    gas giant). */
	return _("%s (Gas)", g->getName().c_str());
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
	/*~ %1$s is the name of the planet, "Telluric" refers to its type (here,
	    a telluric planet, %2$d is its temperature in Kelvin in the coldest
	    case and %3$d in the hottest case. */
	res += _("%1$s (Telluric) [%2$d;%3$d]", t->getName().c_str(), coldest,
		 hottest)+_COLOR;
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

	/*~ %1$s is the name of the stellar system, %2$d is the number of the
	    stars in this stellar system. */
	std::string res = H1(0)+s->getName()+_H1(0)+_("%1$s is a stellar system with %2$d stars",
		  s->getName().c_str(), stars.size())+':'+UL;
	for(size_t i = 0;i < stars.size();i++){
		/*~ %1$s is the name of the star, %2$c is an alphabetic
		    numbering (the first star is A, the second B...), %3$.2s is
		    the class of the star (for example, our Sun is a G2 star)
		    and %4$d is the temperature of the star in Kelvin. */
		res += LI(1)+_("%1$s %2$c is a class %3$.2s star (%4$dK)",
			       s->getName().c_str(), (char)('A'+i),
			       stars[i]->getStarClass(),
			       stars[i]->getTemperature())+UL;
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
		res += _("Circumbinaries")+":";
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
	#include "../mocs/Backend.moc"
#endif
