#include "Backend.h"

Backend::Backend(){
	generateWorld();
}

STRING_TYPE Backend::politicsToHtml(){
	std::string res = entiteToHtml(monde);
	#if QT == 0
		return res;
	#else
		return QString::fromStdString(res);
	#endif
}

STRING_TYPE Backend::spaceToHtml(){
	std::string res = spaceToHtml(space);
	#if QT == 0
		return res;
	#else
		return QString::fromStdString(res);
	#endif
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

std::string Backend::entiteToHtml(Ville* ville){
	return ville->getNom()+" ("+ville->getPopulation()+" "+ville->getGent(MP)+")";
}

std::string Backend::entiteToHtml(Pays* pays){
	std::string res = std::string("<h2>")+pays->getNom()+"</h2>"+pays->getNom()+" est un pays composé de "+pays->getPopulation()+' '+pays->getGent(MP)+" répartis dans "+pays->getNbEnfants()+" villes:<br>";
	for(int i = 0;i < pays->getNbEnfants();i++){
		res += entiteToHtml((Ville*)pays->getEnfant(i))+"<br>";
	}
	return res;
}

std::string Backend::entiteToHtml(Monde* m){
	std::string res = std::string("<h1>")+m->getNom()+"</h1>"+m->getNom()+" est un monde composé de "+m->getPopulation()+' '+m->getGent(MP)+" répartis dans "+m->getNbEnfants()+" pays:<br>";
	for(int i = 0;i < m->getNbEnfants();i++){
		res += entiteToHtml((Pays*)m->getEnfant(i))+"<br>";
	}
	return res;
}

std::string Backend::spaceToHtml(GasPlanet* g){
	return g->getName()+" (Gas)";
}

std::string Backend::spaceToHtml(TelluricPlanet* t){
	std::string res;
	size_t hottest = t->getHottestTemperature();
	size_t coldest = t->getColdestTemperature();
	if(hottest > 175 && hottest < 371 && coldest > 175 && coldest < 371){
		// Temperature is always fine: planet is habitable
		res += "<font color=\"green\">";
	}else if(hottest >= 371 && coldest <= 175){
		// Temperature is too extreme
		res += "<font color=\"darkmagenta\">";
	}else if(hottest >= 371 && coldest >= 371){
		// Temperature is always too hot
		res += "<font color=\"red\">";
	}else if(hottest >= 371 && coldest <= 371){
		// Temperature is too hot in the hottest case
		res += "<font color=\"#c80000\">";
	}else if(coldest <= 175 && hottest <= 175){
		// Temperature is always too cold
		res += "<font color=\"blue\">";
	}else if(coldest <= 175 && hottest >= 175){
		// Temperature is too cold in the coldest case
		res += "<font color=\"cyan\">";
	}
	res += t->getName()+" (Telluric) ["+coldest+';'+hottest+"]</font>";
	return res;
}

std::string Backend::spaceToHtml(World* w){
	if(w->isGasPlanet()){
		return spaceToHtml((GasPlanet*)w);
	}else{
		return spaceToHtml((TelluricPlanet*)w);
	}
}

std::string Backend::spaceToHtml(StarSystem* s){
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

	std::string res = std::string("<h1>")+s->getName()+"</h1>"+s->getName()+" is a stellar system with "+stars.size()+" stars:<ul>";
	for(size_t i = 0;i < stars.size();i++){
		res += "<li>"+s->getName()+" "+((char)('A'+i))+" is a class "+stars[i]->getStarClass()[0]+stars[i]->getStarClass()[1]+" star ("+stars[i]->getTemperature()+"K)<ul>";
		for(size_t j = 0;j < planets[i].size();j++){
			World* planet = planets[i][j].second;
			size_t planetIndex = planets[i][j].first;
			res += "<li>"+spaceToHtml(planet)+"<ul>";
			for(size_t k = 0;k < satellites[planetIndex].size();k++){
				World* satellite = satellites[planetIndex][k].second;
				res += "<li>"+spaceToHtml(satellite)+"</li>";
			}
			res += "</ul></li>";
		}
		res += "</ul></li>";
	}
	res += "</ul><br>";
	if(stars.size() > 1){
		res += "Circumbinaries:";
	}
	res += "<ul>";
	for(size_t i = 0;i < circumbinaries.size();i++){
		World* planet = circumbinaries[i].second;
		size_t planetIndex = circumbinaries[i].first;
		res += "<li>"+spaceToHtml(planet)+"<ul>";
		for(size_t j = 0;j < satellites[planetIndex].size();j++){
			World* satellite = satellites[planetIndex][j].second;
			res += "<li>"+spaceToHtml(satellite)+"</li>";
		}
		res += "</ul></li>";
	}
	res += "</ul>";
	return res;
}

#if QT != 0
	#include "Backend.moc"
#endif
