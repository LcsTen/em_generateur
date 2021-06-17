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
#include "Backend.h"

Backend backend;

#if WEB != 0

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/html5.h>

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

void update(){
	emscripten::val document = emscripten::val::global("document");

	emscripten::val politics = document.call<emscripten::val>("querySelector","#politics"_val);
	politics.set("innerHTML",backend.politicsToString());

	emscripten::val spaceDiv = document.call<emscripten::val>("querySelector","#space"_val);
	spaceDiv.set("innerHTML",backend.spaceToString());

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

int main(int argc, char** argv){
	srand(time(NULL));
	QGuiApplication app(argc, argv);
	const QUrl url("qml/main.qml");
	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("Backend", &backend);
	engine.load(url);
	return app.exec();
}

#endif // QT != 0

#if CONSOLE != 0

int main(){
	srand(time(NULL));
	backend.generateWorld();
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
		}else if(argv[0] == "politics"){
			std::cout << backend.politicsToString() << std::endl;
		}else if(argv[0] == "gen"){
			backend.generateWorld();
		}else if(argv[0] == "help"){
			std::cout << "politics" << std::endl << "\tShow information about the world."
				<< std::endl << std::endl << "gen" << std::endl << "\tGenerate a new world."
				<< std::endl << std::endl << "map" << std::endl << "\tShow the world map."
				<< std::endl << std::endl << "space" << std::endl << "\tShow information about space."
				<< std::endl << std::endl << "stop" << std::endl << "\tExit the REPL."
				<< std::endl << std::endl << "help" << std::endl << "\tDisplay this help." << std::endl;
		}else if(argv[0] == "map"){
			std::cout << backend.mapToString() << std::endl;
		}else if(argv[0] == "space"){
			std::cout << backend.spaceToString() << std::endl;
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
