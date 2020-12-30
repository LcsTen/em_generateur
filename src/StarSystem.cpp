#include "StarSystem.h"

#include "general.h"
#include "GasPlanet.h"
#include "TelluricPlanet.h"

#include <math.h>
#include <iostream>

StarSystem::StarSystem(std::string n) : name(n){
	// Number of stars
	double proba = randouble();
	size_t nbStars = 0;
	while(proba < 1/std::pow(nbStars+1,2)){
		nbStars++;
	}
	
	// Type of stars
	for(size_t i = 0;i < nbStars;i++){
		proba = randouble();
		char starClassLetter;
		size_t tempMin;
		size_t tempMax;
		if(proba < 0.7645){
			starClassLetter = 'M';
			tempMin = 2400;
			tempMax = 3700;
		}else if(proba < 0.7645+0.121){
			starClassLetter = 'K';
			tempMin = 3700;
			tempMax = 5200;
		}else if(proba < 0.7645+0.121+0.076){
			starClassLetter = 'G';
			tempMin = 5200;
			tempMax = 6000;
		}else if(proba < 0.7645+0.121+0.076+0.03){
			starClassLetter = 'F';
			tempMin = 6000;
			tempMax = 7500;
		}else if(proba < 0.7645+0.121+0.076+0.03+0.006){
			starClassLetter = 'A';
			tempMin = 7500;
			tempMax = 10000;
		}else if(proba < 0.7645+0.121+0.076+0.03+0.006+0.0013){
			starClassLetter = 'B';
			tempMin = 10000;
			tempMax = 30000;
		}else{
			starClassLetter = 'O';
			tempMin = 30000;
			tempMax = 60000;
		}
		int subclass = randomInt(10);
		size_t temperature = tempMin+((tempMax-tempMin)/10)*subclass;
		char number = '0'+subclass;
		char starClass[] = {starClassLetter,number};
		stars.push_back(new Star(temperature,randomInt(70000,14000000),
					starClass));
	}
	for(size_t i = 0;i < nbStars;i++){
		for(size_t j = i+1;j < nbStars;j++){
			size_t maxRadius = std::max(stars[i]->getRadius(),stars[i]->getRadius());
			size_t distance = randomInt(2*maxRadius,3*maxRadius);
			stars[i]->addCompanion(stars[j],distance);
			stars[j]->addCompanion(stars[i],distance);
		}
	}
	
	// Planets
	for(size_t i = 0;i < 10;i++){
		// nullptr means circumbinary
		Star* orbiting = nullptr;
		World* world;
		size_t distance;
		if(nbStars == 1){
			distance = randomInt(60000000,200000000);
		}else{
			if(randomInt(2)){
				orbiting = stars[randomInt(stars.size())];
				size_t minDistance = -1;
				for(size_t j = 0;j < orbiting->getCompanions().size();j++){
					size_t dist = orbiting->getCompanions()[j].second;
					if(dist < minDistance){
						minDistance = dist;
					}
				}
				distance = randomInt(60000000,std::min(200000000lu,minDistance/2));
			}else{
				distance = randomInt(60000000,200000000);
			}
		}
		if(randomInt(2)){
			world = new GasPlanet(randomInt(24000,70000),orbiting,distance);
		}else{
			world = new TelluricPlanet(randomInt(2000,9000),orbiting,distance);
		}
		worlds.push_back(world);
	}
	
	// Satellites
	for(size_t i = 0;i < 10;i++){
		size_t nbSatellites;
		if(worlds[i]->isGasPlanet()){
			nbSatellites = randomInt(1,91);
		}else{
			nbSatellites = randomInt(4);
		}
		for(size_t j = 0;j < nbSatellites;j++){
			size_t distance = randomInt(6000000,20000000);
			TelluricPlanet* satellite = new TelluricPlanet(randomInt(1000,worlds[i]->getRadius()/2),worlds[i],distance);
			worlds.push_back(satellite);
		}
	}
}

StarSystem::StarSystem() : StarSystem(generateName(10)){}

StarSystem::~StarSystem(){
	for(size_t i = 0;i < stars.size();i++){
		delete stars[i];
	}
	for(size_t i = 0;i < worlds.size();i++){
		delete worlds[i];
	}
}

std::vector<World*> StarSystem::getHabitableWorlds(){
	std::vector<World*> res;
	for(size_t i = 0;i < worlds.size();i++){
		World* world = worlds[i];
		if(world->isGasPlanet()){
			continue;
		}
		TelluricPlanet* planet = (TelluricPlanet*)world;
		double albedo = 0.3;
		size_t atmosphereDensity = planet->getAtmosphereDensity();
		double planetMultiplier = std::pow(1-albedo,1.0/4)*std::pow(1.0+atmosphereDensity,1.0/4);
		size_t hottest;
		// nullptr means circumbinary
		AstralObject* orbiting = planet->getOrbiting();
		if(orbiting == nullptr || (orbiting->isWorld() && ((World*)orbiting)->getOrbiting() == nullptr)){
			// Hottest star is the closest to circumbinary planet: hottest case
			hottest = 0;
			// We assume circumbinary planets have the same distance between them and all the stars
			size_t distance;
			if(orbiting == nullptr){
				distance = planet->getDistance();
			}else{
				distance = ((World*)orbiting)->getDistance();
			}
			for(size_t j = 0;j < stars.size();j++){
				size_t starTemp = stars[j]->getTemperature();
				size_t starRadius = stars[j]->getRadius();
				size_t temperature = starTemp*std::sqrt(starRadius/(2.0*distance));
				if(temperature > hottest){
					hottest = temperature;
				}
			}
		}else{
			// Non-circumbinary planet is between its orbiting star and its hottest companion: hottest case
			Star* sun;
			size_t distanceSun;
			if(orbiting->isStar()){
				sun = (Star*)orbiting;
				distanceSun = planet->getDistance();
			}else{
				sun = (Star*)(((World*)orbiting)->getOrbiting());
				distanceSun = ((World*)orbiting)->getDistance() - planet->getDistance();
			}
			hottest = 0;
			std::vector<std::pair<Star*,size_t>> companions = sun->getCompanions();
			for(size_t j = 0;j < companions.size();j++){
				Star* companion = companions[j].first;
				size_t starTemp = companion->getTemperature();
				size_t starRadius = companion->getRadius();
				size_t distanceCompanion = companions[j].second - distanceSun;
				size_t temperature = starTemp*std::sqrt(starRadius/(2.0*distanceCompanion));
				if(temperature > hottest){
					hottest = temperature;
				}
			}
			size_t starTemp = sun->getTemperature();
			size_t starRadius = sun->getRadius();
			hottest += starTemp*std::sqrt(starRadius/(2.0*distanceSun));
		}
		hottest *= planetMultiplier;
		planet->setHottestTemperature(hottest);
		/*if(!(hottest > 175 && hottest < 371)){
			// The planet is either too hot or already too cold. Abandon.
			//continue;
		}*/
		
		size_t coldest;
		if(orbiting != nullptr && !orbiting->isStar()){
			World* o = (World*)orbiting;
			size_t orbitDensity;
			if(o->isGasPlanet()){
				orbitDensity = 200;
			}else{
				orbitDensity = ((TelluricPlanet*)o)->getAtmosphereDensity();
			}
			// Orbiting planet is eclipsing the star(s) of satellite: coldest case
			// First step: get planet temperature
			size_t planetTemp;
			size_t orbitingMultiplier = std::pow(1-0.3,1.0/4)*std::pow(1.0+orbitDensity,1.0/4);
			if(o->getOrbiting() == nullptr){
				// Orbiting planet is circumbinary: get the coldest star
				size_t coldestStar = -1;
				size_t distance = o->getDistance();
				for(size_t j = 0;j < stars.size();j++){
					Star* star = stars[j];
					size_t starTemp = star->getTemperature();
					size_t starRadius = star->getRadius();
					size_t temperature = starTemp*std::sqrt(starRadius/(2.0*distance));
					if(temperature < coldestStar){
						coldestStar = temperature;
					}
				}
				planetTemp = coldestStar*orbitingMultiplier;
			}else{
				Star* sun = (Star*)o->getOrbiting();
				size_t starTemp = sun->getTemperature();
				size_t starRadius = sun->getRadius();
				size_t distance = o->getDistance();
				planetTemp = starTemp*std::sqrt(starRadius/(2.0*distance))*orbitingMultiplier;
			}
			coldest = planetTemp*std::sqrt(o->getRadius()/(2.0*planet->getDistance()));
		}else if(orbiting == nullptr){
			// Coldest star is the closest to circumbinary planet: coldest case
			coldest = -1;
			size_t distance = planet->getDistance();
			for(size_t j = 0;j < stars.size();j++){
				size_t starTemp = stars[j]->getTemperature();
				size_t starRadius = stars[j]->getRadius();
				size_t temperature = starTemp*std::sqrt(starRadius/(2.0*distance));
				if(temperature < coldest){
					coldest = temperature;
				}
			}
		}else{
			// Non-circumbinary non-satellite is not between two stars: coldest case
			Star* sun = (Star*)orbiting;
			size_t starTemp = sun->getTemperature();
			size_t starRadius = sun->getRadius();
			size_t distance = planet->getDistance();
			coldest = starTemp*std::sqrt(starRadius/(2.0*distance));
		}
		coldest *= planetMultiplier;
		planet->setColdestTemperature(coldest);
		if(hottest > 175 && hottest < 371 && coldest > 175 && coldest < 371){
			res.push_back(world);
		}
	}
	return res;
}

std::string StarSystem::getName() const{
	return name;
}

const std::vector<Star*> StarSystem::getStars() const{
	return stars;
}

const std::vector<World*> StarSystem::getWorlds() const{
	return worlds;
}
