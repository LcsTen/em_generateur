#include <iostream>
#include <vector>
#include <algorithm>

#include "Personne.h"
#include "Entite.h"
#include "Monde.h"
#include "Pays.h"
#include "Ville.h"
#include "Groupe.h"
#include "StarSystem.h"
#include "GasPlanet.h"
#include "TelluricPlanet.h"
#include "general.h"

#if WEB != 0

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/html5.h>

#include "Backend.h"

emscripten::val operator""_val(const char* s,size_t){
	return emscripten::val(s);
}

void hideAll(){
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector","#history"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#politics"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#ecology"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#calendar"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#space"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#history_tab"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#politics_tab"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#ecology_tab"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#calendar_tab"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#space_tab"_val)["style"].set("backgroundColor","white");
}

EM_BOOL onglet_click(int /*eventType*/,const EmscriptenMouseEvent* /*e*/,void* userData){
	hideAll();
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#")+(char*)userData))["style"].set("display","block");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#")+(char*)userData+"_tab"))["style"].set("backgroundColor","yellow");
	return 0;
}

void mainLoop(){}

char hist[] = "history";
char pol[] = "politics";
char eco[] = "ecology";
char cal[] = "calendar";
char spa[] = "space";

Backend backend;

void update(){
	emscripten::val document = emscripten::val::global("document");

	emscripten::val politics = document.call<emscripten::val>("querySelector","#politics"_val);
	politics.set("innerHTML",backend.politicsToHtml());

	emscripten::val spaceDiv = document.call<emscripten::val>("querySelector","#space"_val);
	spaceDiv.set("innerHTML",backend.spaceToHtml());

	emscripten::val::global("document").call<emscripten::val>("querySelector","#log"_val).set("innerHTML","");
}

void log(std::string s){
	emscripten::val document = emscripten::val::global("document");
	emscripten::val li = document.call<emscripten::val>("createElement","li"_val);
	li.set("innerHTML",s);
	document.call<emscripten::val>("querySelector","#log"_val).call<void>("append",li);
}

EM_BOOL generateWorld_click(int /*eventType*/,const EmscriptenMouseEvent* /*e*/,void* /*userData*/){
	backend.generateWorld();
	return 0;
}

emscripten::val createTab(std::string id,std::string textContent){
	emscripten::val document = emscripten::val::global("document");
	emscripten::val res = document.call<emscripten::val>("createElement","span"_val);
	res.set("id",id);
	res.set("textContent",textContent);
	res["style"].set("border","solid 1px black");
	return res;
}

emscripten::val createDiv(std::string id){
	emscripten::val document = emscripten::val::global("document");
	emscripten::val res = document.call<emscripten::val>("createElement","div"_val);
	res.set("id",id);
	res["style"].set("display","none");
	return res;
}

int main(){
	emscripten::val document = emscripten::val::global("document");
	
	document.set("title",std::string("Generateur"));
	
	emscripten::val display = document.call<emscripten::val>("createElement","div"_val);
	display.set("id","display");
	
	emscripten::val tabs = document.call<emscripten::val>("createElement","span"_val);
	tabs["style"].set("position","fixed");
	tabs["style"].set("backgroundColor","white");
	tabs["style"].set("cursor","pointer");
	tabs["style"].set("top",0);
	tabs["style"].set("userSelect","none");
	display.call<void>("append",tabs);
	emscripten::val historyTab = createTab("history_tab","History");
	historyTab["style"].set("backgroundColor","yellow");
	tabs.call<void>("append",historyTab);
	
	tabs.call<void>("append",createTab("politics_tab","Politics"));
	tabs.call<void>("append",createTab("ecology_tab","Ecology"));
	tabs.call<void>("append",createTab("calendar_tab","Calendar"));
	tabs.call<void>("append",createTab("space_tab","Space"));
	tabs.call<void>("append",createTab("skipTime","Skip 10 years"));
	tabs.call<void>("append",createTab("generateWorld","Generate a new world"));
	
	emscripten::val history = document.call<emscripten::val>("createElement","div"_val);
	history.set("id","history");
	history["style"].set("display","block");
	history["style"].set("marginTop","20px");
	emscripten::val ulLog = document.call<emscripten::val>("createElement","ul"_val);
	ulLog.set("id","log");
	history.call<void>("append",ulLog);
	display.call<void>("append",history);
	
	display.call<void>("append",createDiv("politics"));
	display.call<void>("append",createDiv("ecology"));
	display.call<void>("append",createDiv("calendar"));
	display.call<void>("append",createDiv("space"));
	
	document["body"].set("innerText","");
	document["body"].call<void>("append",display);
	
	emscripten_set_mousedown_callback("#history_tab",hist,false,onglet_click);
	emscripten_set_mousedown_callback("#politics_tab",pol,false,onglet_click);
	emscripten_set_mousedown_callback("#ecology_tab",eco,false,onglet_click);
	emscripten_set_mousedown_callback("#calendar_tab",cal,false,onglet_click);
	emscripten_set_mousedown_callback("#space_tab",spa,false,onglet_click);
	emscripten_set_mousedown_callback("#generateWorld",NULL,false,generateWorld_click);

	emscripten_set_main_loop(mainLoop,-1,0);
	
	srand(time(NULL));
	backend.onWorldChanged(update);
	backend.onLogPrinted(log);
	backend.generateWorld();
}

#endif // WEB != 1

#if QT != 0

#include <QGuiApplication>
#include <QUrl>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Backend.h"

int main(int argc, char** argv){
	srand(time(NULL));
	QGuiApplication app(argc, argv);
	const QUrl url("qml/main.qml");
	QQmlApplicationEngine engine;
	Backend backend;
	engine.rootContext()->setContextProperty("Backend", &backend);
	engine.load(url);
	return app.exec();
}

#endif // QT != 0

#if CONSOLE != 0

Monde* monde = nullptr;
StarSystem* space = nullptr;

void genererMonde(){
	if(monde != nullptr){
		delete monde;
	}
	if(space != nullptr){
		delete space;
	}
	space = new StarSystem();
	std::vector<World*> habitables = space->getHabitableWorlds();
	while(space->getHabitableWorlds().size() == 0){
		delete space;
		space = new StarSystem();
		habitables = space->getHabitableWorlds();
	}
	monde = new Monde(habitables[0]->getName());
	std::cout << *monde << std::endl;
}

void show(Ville* ville,int depth = 0){
	std::cout << std::string(depth,'\t') << ville->getNom() << " (" << ville->getPopulation() << ' ' << ville->getGent(MP) << ')' << std::endl;
}

void show(Pays* pays,int depth = 0){
	std::cout << std::string(depth,'\t') << pays->getNom() << std::endl << std::string(depth,'\t') << pays->getNom() << " est un pays composé de " << pays->getPopulation() << ' ' << pays->getGent(MP) << 
		" répartis dans " << pays->getNbEnfants() << " villes:" << std::endl;
	for(int i = 0;i < pays->getNbEnfants();i++){
		show((Ville*)pays->getEnfant(i),depth+1);
	}
}

void show(Monde* m,int depth = 0){
	std::cout << std::string(depth,'\t') << m->getNom() << std::endl << std::string(depth,'\t') << m->getNom() << " est un monde composé de " << m->getPopulation() << ' ' << m->getGent(MP) << 
		" répartis dans " << m->getNbEnfants() << " pays:" << std::endl;
	for(int i = 0;i < m->getNbEnfants();i++){
		show((Pays*)m->getEnfant(i),depth+1);
	}
}

void show(std::vector<std::string> const& argv){
	if(argv.size() == 1){
		show(monde);
	}else if(argv.size() == 2){
		int index = atoi(argv[1].c_str());
		if(index < monde->getNbEnfants()){
			show((Pays*)monde->getEnfant(index));
		}else{
			std::cout << "Erreur: monde n'a pas d'enfant " << index << std::endl;
		}
	}else if(argv.size() >= 3){
		int index1 = atoi(argv[1].c_str());
		if(index1 < monde->getNbEnfants()){
			int index2 = atoi(argv[2].c_str());
			if(index2 < monde->getEnfant(index1)->getNbEnfants()){
				show((Ville*)monde->getEnfant(index1)->getEnfant(index2));
			}else{
				std::cout << "Erreur: monde[" << index1 << "] n'a pas d'enfant " << index2 << std::endl;
			}
		}else{
			std::cout << "Erreur: monde n'a pas d'enfant " << index1 << std::endl;
		}
	}
}

void map(){
	for(unsigned int y = 0;y < monde->getMap().getLines();y++){
		for(unsigned int x = 0;x < monde->getMap().getColumns();x++){
			const Tile tile = monde->getMap()(x,y);
			std::cout << "\e[" << 90+(tile.getTemp()+100)/28 << "m" // Frontground color
				<< "\e[" << 100+(tile.getElev()+100)/28 << "m" // Background color
				<< tile.getHum()/11 << "\e[0m";
		}
		std::cout << std::endl;
	}
}

void show(GasPlanet* planet,int depth = 0){
	std::cout << std::string(depth,'\t') << planet->getName() << " (Gas)"
		<< std::endl;
}

void show(TelluricPlanet* planet,int depth = 0){
	TelluricPlanet* telluric = (TelluricPlanet*)planet;
	size_t hottest = telluric->getHottestTemperature();
	size_t coldest = telluric->getColdestTemperature();
	if(hottest > 175 && hottest < 371 && coldest > 175 && coldest < 371){
		// Temperature is always fine: planet is habitable
		std::cout << "\e[32m";
	}else if(hottest >= 371 && coldest <= 175){
		// Temperature is too extreme
		std::cout << "\e[35m";
	}else if(hottest >= 371 && coldest >= 371){
		// Temperature is always too hot
		std::cout << "\e[31m";
	}else if(hottest >= 371 && coldest <= 371){
		// Temperature is too hot in the hottest case
		std::cout << "\e[91m";
	}else if(coldest <= 175 && hottest <= 175){
		// Temperature is always too cold
		std::cout << "\e[34m";
	}else if(coldest <= 175 && hottest >= 175){
		// Temperature is too cold in the coldest case
		std::cout << "\e[36m";
	}
	std::cout << std::string(depth,'\t') << planet->getName()
		<< " (Telluric) [" << coldest << ';' << hottest << "]\e[0m"
		<< std::endl;
}

void showSpace(){
	std::vector<Star*> stars = space->getStars();
	std::vector<World*> worlds = space->getWorlds();
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
	
	std::cout << space->getName() << " is a stellar system with " << stars.size() << " stars:" << std::endl;
	for(size_t i = 0;i < stars.size();i++){
		std::string starClass;
		starClass += stars[i]->getStarClass()[0];
		starClass += stars[i]->getStarClass()[1];
		std::cout << '\t' << space->getName() << " " << (char)('A'+i) << " is a class "
			<< starClass << " star ("
			<< stars[i]->getTemperature() << "K)" << std::endl;
		for(size_t j = 0;j < planets[i].size();j++){
			World* planet = planets[i][j].second;
			size_t indexPlanet = planets[i][j].first;
			if(planet->isGasPlanet()){
				show((GasPlanet*)planet,2);
			}else{
				show((TelluricPlanet*)planet,2);
			}
			for(size_t k = 0;k < satellites[indexPlanet].size();k++){
				World* satellite = satellites[indexPlanet][k].second;
				show((TelluricPlanet*)satellite,3);
			}
		}
	}
	std::cout << std::endl;
	if(stars.size() > 1){
		std::cout << "Circumbinaries:" << std::endl;
	}
	for(size_t i = 0;i < circumbinaries.size();i++){
		World* planet = circumbinaries[i].second;
		size_t indexPlanet = circumbinaries[i].first;
		if(planet->isGasPlanet()){
			show((GasPlanet*)planet,1);
		}else{
			show((TelluricPlanet*)planet,1);
		}
		for(size_t j = 0;j < satellites[indexPlanet].size();j++){
			World* satellite = satellites[indexPlanet][j].second;
			show((TelluricPlanet*)satellite,2);
		}
	}
}

int main(){
	srand(time(NULL));
	genererMonde();
	bool stop = false;
	std::string arg;
	std::cout << "generateur$ ";
	while(!stop && std::getline(std::cin,arg)){
		std::vector<std::string> argv;
		unsigned int i = 0;
		while(arg[i] == ' ' && i++ < arg.size());
		argv.push_back("");
		for(;i < arg.size();i++){
			if(arg[i] == ' '){
				while(arg[i] == ' ' && i++ < arg.size());
				argv.push_back("");
			}
			argv.back() += arg[i];
		}
		if(argv.back().empty() || argv.back()[0] == 0){
			argv.pop_back();
		}
		if(argv[0] == "stop"){
			stop = true;
		}else if(argv[0] == "show"){
			show(argv);
		}else if(argv[0] == "gen"){
			genererMonde();
		}else if(argv[0] == "help"){
			std::cout << "show [id_country [id_city]]" << std::endl << "\tShow information about the world/country/city."
				<< std::endl << std::endl << "gen" << std::endl << "\tGenerate a new world."
				<< std::endl << std::endl << "map" << std::endl << "\tShow the world map."
				<< std::endl << std::endl << "space" << std::endl << "\tShow information about space."
				<< std::endl << std::endl << "stop" << std::endl << "\tExit the REPL."
				<< std::endl << std::endl << "help" << std::endl << "\tDisplay this help." << std::endl;
		}else if(argv[0] == "map"){
			map();
		}else if(argv[0] == "space"){
			showSpace();
		}else if(argv[0] != ""){
			std::cout << argv[0]+": unknown command." << std::endl;
		}
		if(!stop){
			std::cout << "generateur$ ";
		}
	}
	return 0;
}

#endif // CONSOLE != 0
