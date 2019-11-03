#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/val.h>
#include <emscripten/html5.h>
#include <iostream>

#include "Personne.hpp"
#include "Monde.hpp"
#include "Pays.hpp"
#include "Ville.hpp"
#include "Groupe.hpp"

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

void hideAll(){
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector",emscripten::val("#historique"))["style"].set("display","none");
	document.call<emscripten::val>("querySelector",emscripten::val("#politique"))["style"].set("display","none");
	document.call<emscripten::val>("querySelector",emscripten::val("#ecologie"))["style"].set("display","none");
	document.call<emscripten::val>("querySelector",emscripten::val("#calendrier"))["style"].set("display","none");
	document.call<emscripten::val>("querySelector",emscripten::val("#onglet_historique"))["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector",emscripten::val("#onglet_politique"))["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector",emscripten::val("#onglet_ecologie"))["style"].set("backgroundColor","white");
	document.call<emscripten::val>("querySelector",emscripten::val("#onglet_calendrier"))["style"].set("backgroundColor","white");
}

EM_BOOL onglet_click(int eventType,const EmscriptenMouseEvent* e,void* userData){
	//std::cout << std::string("#")+(char*)userData << ' ' << std::string("#onglet_")+(char*)userData << std::endl;
	hideAll();
	emscripten::val document = emscripten::val::global("document");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#")+(char*)userData))["style"].set("display","block");
	document.call<emscripten::val>("querySelector",emscripten::val(std::string("#onglet_")+(char*)userData))["style"].set("backgroundColor","yellow");
	return 0;
}

void mainLoop(){
}

char hist[] = "historique";
char pol[] = "politique";
char eco[] = "ecologie";
char cal[] = "calendrier";

int main(){
	emscripten::val document = emscripten::val::global("document");
	
	emscripten::val afficher = document.call<emscripten::val>("createElement",emscripten::val("div"));
	afficher.set("id","afficher");
	
	emscripten::val onglets = document.call<emscripten::val>("createElement",emscripten::val("span"));
	onglets["style"].set("position","fixed");
	onglets["style"].set("backgroundColor","white");
	onglets["style"].set("cursor","pointer");
	afficher.call<void>("append",onglets);
	
	emscripten::val ongletHistorique = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletHistorique.set("id","onglet_historique");
	ongletHistorique.set("textContent","Historique");
	ongletHistorique["style"].set("border","solid 1px black");
	ongletHistorique["style"].set("backgroundColor","yellow");
	onglets.call<void>("append",ongletHistorique);
	
	emscripten::val ongletPolitique = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletPolitique.set("id","onglet_politique");
	ongletPolitique.set("textContent","Politique");
	ongletPolitique["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletPolitique);
	
	emscripten::val ongletEcologie = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletEcologie.set("id","onglet_ecologie");
	ongletEcologie.set("textContent","Ecologie");
	ongletEcologie["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletEcologie);
	
	emscripten::val ongletCalendrier = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletCalendrier.set("id","onglet_calendrier");
	ongletCalendrier.set("textContent","Calendrier");
	ongletCalendrier["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletCalendrier);
	
	emscripten::val ongletPasserTemps = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletPasserTemps.set("id","passerTemps");
	ongletPasserTemps.set("textContent","Passer 10 ans");
	ongletPasserTemps["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletPasserTemps);
	
	emscripten::val ongletGenererMonde = document.call<emscripten::val>("createElement",emscripten::val("span"));
	ongletGenererMonde.set("id","genererMonde");
	ongletGenererMonde.set("textContent","Generer un nouveau monde");
	ongletGenererMonde["style"].set("border","solid 1px black");
	onglets.call<void>("append",ongletGenererMonde);
	
	emscripten::val historique = document.call<emscripten::val>("createElement",emscripten::val("div"));
	historique.set("id","historique");
	historique["style"].set("display","block");
	afficher.call<void>("append",historique);
	
	emscripten::val politique = document.call<emscripten::val>("createElement",emscripten::val("div"));
	politique.set("id","politique");
	politique["style"].set("display","none");
	afficher.call<void>("append",politique);
	
	emscripten::val ecologie = document.call<emscripten::val>("createElement",emscripten::val("div"));
	ecologie.set("id","ecologie");
	ecologie["style"].set("display","none");
	afficher.call<void>("append",ecologie);
	
	emscripten::val calendrier = document.call<emscripten::val>("createElement",emscripten::val("div"));
	calendrier.set("id","calendrier");
	calendrier["style"].set("display","none");
	afficher.call<void>("append",calendrier);
	
	document["body"].set("innerText","");
	document["body"].call<void>("append",afficher);
	
	std::cout << emscripten_set_mousedown_callback("#onglet_historique",hist,false,onglet_click) << std::endl;
	std::cout << emscripten_set_mousedown_callback("#onglet_politique",pol,false,onglet_click) << std::endl;
	std::cout << emscripten_set_mousedown_callback("#onglet_ecologie",eco,false,onglet_click) << std::endl;
	std::cout << emscripten_set_mousedown_callback("#onglet_calendrier",cal,false,onglet_click) << std::endl;
	
	//EM_ASM(Module['noExitRuntime'] = true);
	//emscripten::val::global("Module").set("noExitRuntime",true);
	emscripten_set_main_loop(mainLoop,-1,0);
	
	/*emscripten::val div = document.call<emscripten::val>("createElement",emscripten::val("div"));
	div["style"].set("position","absolute");
	div["style"].set("top",0);
	div["style"].set("left",0);
	div.set("textContent","COUCOU");
	document["body"].call<void>("append",div);*/
}