#include <iostream>
#include <vector>

#include "Personne.h"
#include "Entite.h"
#include "Monde.h"
#include "Pays.h"
#include "Ville.h"
#include "Groupe.h"

#if WEB == 1

#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/html5.h>

emscripten::val operator""_val(const char* s,size_t){
	return emscripten::val(s);
}

EMSCRIPTEN_BINDINGS(main){
	emscripten::class_<Personne>("Personne")
	.constructor<std::string,std::string,int>()
	.function("sePresente",&Personne::sePresente);
	
	emscripten::class_<Monde>("Monde")
	.constructor<std::string>()
	.constructor<>()
	.function("creerEnfant",emscripten::select_overload<Entite*()>(&Monde::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("creerEnfant_nom",emscripten::select_overload<Entite*(std::string)>(&Monde::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("getPopulation",&Monde::getPopulation)
	.function("toString",&Monde::toString);
	
	emscripten::class_<Pays>("Pays")
	.constructor<std::string,Monde&>()
	.function("creerEnfant",emscripten::select_overload<Entite*()>(&Pays::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("creerEnfant_nom",emscripten::select_overload<Entite*(std::string)>(&Pays::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("getPopulation",&Pays::getPopulation)
	.function("toString",&Pays::toString);
	
	emscripten::class_<Ville>("Ville")
	.constructor<std::string,Pays&>()
	.function("creerEnfant",emscripten::select_overload<Entite*()>(&Ville::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("creerEnfant_nom",emscripten::select_overload<Entite*(std::string)>(&Ville::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("getPopulation",&Ville::getPopulation)
	.function("toString",&Ville::toString);
	
	emscripten::class_<Groupe>("Groupe")
	.constructor<std::string,Ville&>()
	.function("getPopulation",&Groupe::getPopulation)
	.function("toString",&Groupe::toString);
	
	emscripten::class_<Entite>("Entite")
	.function("creerEnfant",emscripten::select_overload<Entite*()>(&Entite::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("creerEnfant_nom",emscripten::select_overload<Entite*(std::string)>(&Entite::creerEnfant),emscripten::allow_raw_pointer<Entite>())
	.function("getPopulation",&Entite::getPopulation)
	.function("toString",&Entite::toString);
}

std::string format(int a){
	char buf[1024];
	sprintf(buf,"%d",a);
	std::string res = "";
	int length = strlen(buf);
	for(int i = 0;i < length;i++){
		if(i % 3 == 0){
			res = ' '+res;
		}
		res = buf[length-i-1]+res;
	}
	return res;
}

std::string operator+(std::string a,int b){
	return a+format(b);
}

void hideAll(){
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector","#historique"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#politique"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#ecologie"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#calendrier"_val)["style"].set("display","none");
	document.call<emscripten::val>("querySelector","#onglet_historique"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#onglet_politique"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#onglet_ecologie"_val)["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector","#onglet_calendrier"_val)["style"].set("backgroundColor","white");
}

EM_BOOL onglet_click(int /*eventType*/,const EmscriptenMouseEvent* /*e*/,void* userData){
	//std::cout << std::string("#")+(char*)userData << ' ' << std::string("#onglet_")+(char*)userData << std::endl;
	hideAll();
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#")+(char*)userData))["style"].set("display","block");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#onglet_")+(char*)userData))["style"].set("backgroundColor","yellow");
	return 0;
}

void mainLoop(){}

char hist[] = "historique";
char pol[] = "politique";
char eco[] = "ecologie";
char cal[] = "calendrier";

Monde* monde = NULL;

std::string entiteToHtml(Ville* ville){
	return ville->getNom()+" ("+ville->getPopulation()+" "+ville->getGent(MP)+")";
}

std::string entiteToHtml(Pays* pays){
	std::string res = std::string("<h2>")+pays->getNom()+"</h2>"+pays->getNom()+" est un pays composé de "+pays->getPopulation()+' '+pays->getGent(MP)+" répartis dans "+pays->getNbEnfants()+" villes:<br>";
	for(int i = 0;i < pays->getNbEnfants();i++){
		res += entiteToHtml((Ville*)pays->getEnfant(i))+"<br>";
	}
	return res;
}

std::string entiteToHtml(Monde* m){
	std::string res = std::string("<h1>")+m->getNom()+"</h1>"+m->getNom()+" est un monde composé de "+m->getPopulation()+' '+m->getGent(MP)+" répartis dans "+m->getNbEnfants()+" pays:<br>";
	for(int i = 0;i < m->getNbEnfants();i++){
		res += entiteToHtml((Pays*)m->getEnfant(i))+"<br>";
	}
	return res;
}

void miseAJour(){
	emscripten::val document = emscripten::val::global("document");
	
	emscripten::val politique = document.call<emscripten::val>("querySelector","#politique"_val);
	politique.set("innerHTML",entiteToHtml(monde));
}

void log(std::string s,bool asHTML = false){
	emscripten::val document = emscripten::val::global("document");
	emscripten::val li = document.call<emscripten::val>("createElement","li"_val);
	if(asHTML){
		li.set("innerHTML",s);
	}else{
		li.set("innerText",s);
	}
	document.call<emscripten::val>("querySelector","#log"_val).call<void>("append",li);
}

void genererMonde(){
	if(monde != NULL){
		delete monde;
	}
	monde = new Monde();
	emscripten::val::global("document").call<emscripten::val>("querySelector","#log"_val).set("innerHTML","");
	log("1/1/1: Le monde est créé.");
	miseAJour();
}

EM_BOOL genererMonde_click(int /*eventType*/,const EmscriptenMouseEvent* /*e*/,void* /*userData*/){
	genererMonde();
	return 0;
}

int main(){
	emscripten::val document = emscripten::val::global("document");
	
	document.set("title",std::string("Générateur"));
	
	emscripten::val afficher = document.call<emscripten::val>("createElement","div"_val);
	afficher.set("id","afficher");
	
	emscripten::val onglets = document.call<emscripten::val>("createElement","span"_val);
	onglets["style"].set("position","fixed");
	onglets["style"].set("backgroundColor","white");
	onglets["style"].set("cursor","pointer");
	onglets["style"].set("top",0);
	onglets["style"].set("userSelect","none");
	afficher.call<void>("append",onglets);
	
	emscripten::val ongletHistorique = document.call<emscripten::val>("createElement","span"_val);
	ongletHistorique.set("id","onglet_historique");
	ongletHistorique.set("textContent","Historique");
	ongletHistorique["style"].set("border","solid 1px black");
	ongletHistorique["style"].set("backgroundColor","yellow");
	onglets.call<void>("append",ongletHistorique);
	
	emscripten::val ongletPolitique = document.call<emscripten::val>("createElement","span"_val);
	ongletPolitique.set("id","onglet_politique");
	ongletPolitique.set("textContent","Politique");
	ongletPolitique["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletPolitique);
	
	emscripten::val ongletEcologie = document.call<emscripten::val>("createElement","span"_val);
	ongletEcologie.set("id","onglet_ecologie");
	ongletEcologie.set("textContent","Ecologie");
	ongletEcologie["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletEcologie);
	
	emscripten::val ongletCalendrier = document.call<emscripten::val>("createElement","span"_val);
	ongletCalendrier.set("id","onglet_calendrier");
	ongletCalendrier.set("textContent","Calendrier");
	ongletCalendrier["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletCalendrier);
	
	emscripten::val ongletPasserTemps = document.call<emscripten::val>("createElement","span"_val);
	ongletPasserTemps.set("id","passerTemps");
	ongletPasserTemps.set("textContent","Passer 10 ans");
	ongletPasserTemps["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletPasserTemps);
	
	emscripten::val ongletGenererMonde = document.call<emscripten::val>("createElement","span"_val);
	ongletGenererMonde.set("id","genererMonde");
	ongletGenererMonde.set("textContent","Generer un nouveau monde");
	ongletGenererMonde["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletGenererMonde);
	
	emscripten::val historique = document.call<emscripten::val>("createElement","div"_val);
	historique.set("id","historique");
	historique["style"].set("display","block");
	historique["style"].set("marginTop","20px");
	emscripten::val ulLog = document.call<emscripten::val>("createElement","ul"_val);
	ulLog.set("id","log");
	historique.call<void>("append",ulLog);
	afficher.call<void>("append",historique);
	
	emscripten::val politique = document.call<emscripten::val>("createElement","div"_val);
	politique.set("id","politique");
	politique["style"].set("display","none");
	afficher.call<void>("append",politique);
	
	emscripten::val ecologie = document.call<emscripten::val>("createElement","div"_val);
	ecologie.set("id","ecologie");
	ecologie["style"].set("display","none");
	afficher.call<void>("append",ecologie);
	
	emscripten::val calendrier = document.call<emscripten::val>("createElement","div"_val);
	calendrier.set("id","calendrier");
	calendrier["style"].set("display","none");
	afficher.call<void>("append",calendrier);
	
	document["body"].set("innerText","");
	document["body"].call<void>("append",afficher);
	
	/*std::cout << */emscripten_set_mousedown_callback("#onglet_historique",hist,false,onglet_click)/* << std::endl*/;
	/*std::cout << */emscripten_set_mousedown_callback("#onglet_politique",pol,false,onglet_click)/* << std::endl*/;
	/*std::cout << */emscripten_set_mousedown_callback("#onglet_ecologie",eco,false,onglet_click)/* << std::endl*/;
	/*std::cout << */emscripten_set_mousedown_callback("#onglet_calendrier",cal,false,onglet_click)/* << std::endl*/;
	emscripten_set_mousedown_callback("#genererMonde",NULL,false,genererMonde_click);
	
	//EM_ASM(Module['noExitRuntime'] = true);
	//emscripten::val::global("Module").set("noExitRuntime",true);
	emscripten_set_main_loop(mainLoop,-1,0);
	
	srand(time(NULL));
	genererMonde();
	
	/*emscripten::val div = document.call<emscripten::val>("createElement",emscripten::val("div"));
	div["style"].set("position","absolute");
	div["style"].set("top",0);
	div["style"].set("left",0);
	div.set("textContent","COUCOU");
	document["body"].call<void>("append",div);*/
}

#else // if WEB == 0

Monde* monde = NULL;

void genererMonde(){
	if(monde != NULL){
		delete monde;
	}
	monde = new Monde();
	std::cout << *monde << std::endl;
}

/*std::ostream& operator<<(std::ostream& out,const wchar_t* s){
	return out << std::string(s);
}*/

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

int main(){
	srand(time(NULL));
	genererMonde();
	bool stop = false;
	while(!stop){
		std::cout << "generateur$ ";
		std::vector<std::string> argv;
		std::string arg;
		std::getline(std::cin,arg);
		/*while(std::cin >> arg){
			argv.push_back(arg);
		}*/
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
		/*std::cout << '{';
		for(unsigned int j = 0;j < argv.size();j++){
			if(j != 0){
				std::cout << ", ";
			}
			std::cout << '"' << argv[j] << '"';
		}
		std::cout << '}' << std::endl;*/
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
				<< std::endl << std::endl << "stop" << std::endl << "\tExit the REPL."
				<< std::endl << std::endl << "help" << std::endl << "\tDisplay this help." << std::endl;
		}else if(argv[0] == "map"){
			map();
		}else if(argv[0] != ""){
			std::cout << argv[0]+": unknown command." << std::endl;
		}
	}
	return 0;
}

#endif // WEB == 0
