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

void mainLoop(){}

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

EM_BOOL generate_world_click(int /*eventType*/,const EmscriptenMouseEvent* /*e*/,void* /*userData*/){
	backend.generateWorld();
	return 0;
}

int main(){
	emscripten_set_mousedown_callback("#generate_world",NULL,false,generate_world_click);

	emscripten_set_main_loop(mainLoop,-1,0);
	
	srand(time(NULL));
	backend.onWorldChanged(update);
	backend.onLogPrinted(log);
	backend.generateWorld();

	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector","#splash"_val)["style"].set("display", "none");
	document.call<emscripten::val>("querySelector","#display"_val)["style"].set("display", "block");
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
