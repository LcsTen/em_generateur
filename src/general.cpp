#include "general.h"

#include <random>
#include <cstring>

int randomInt(int min,int max){
	int res;
	if(min == max){
		res = min;
	}else{
		res = ((rand()%(max-min))+min);
	}
	return res;
}

int randomInt(int max){
	return randomInt(0,max);
}

double randouble(){
	return rand()/(double)RAND_MAX;
}

bool endsWith(std::string a,std::string b){
	return (a.size() >= b.size() && a.substr(a.size()-b.size(),b.size()) == b);
}

bool endsWith(std::string a,char b){
	return (a.back() == b);
}

void genererGentile(std::string nom,std::string* ms,std::string* mp,std::string* fs,std::string* fp){
	if(endsWith(nom,"ie") || endsWith(nom,"ye")){
		if(randomInt(2) == 0){
			*ms = nom + 'n';
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else{
			*ms = nom.substr(0,nom.size()-2) + 'e';
			*mp = *ms + 's';
			*fs = *ms;
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"ia") || endsWith(nom,"ya")){
		if(randomInt(2) == 0){
			*ms = nom + 'n';
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else{
			*ms = nom.substr(0,nom.size()-1) + "en";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"io") || endsWith(nom,"iu") || endsWith(nom,"yo") || endsWith(nom,"yu")){
		*ms = nom.substr(0,nom.size()-1) + "en";
		*mp = *ms + 's';
	      *fs = *ms + "ne";
	      *fp = *fs + 's';
	}else if(endsWith(nom,"in")){
	      *ms = nom;
	      *mp = *ms + 's';
	      *fs = *ms + 'e';
	      *fp = *fs + 's';
	}else if(endsWith(nom,"ine")){
	      *ms = nom.substr(0,nom.size()-1);
	      *mp = *ms + 's';
	      *fs = nom;
	      *fp = *fs + 's';
	}else if(endsWith(nom,"ae") || endsWith(nom,"oe") || endsWith(nom,"ue")){
	      *ms = nom.substr(0,nom.size()-1) + "éen";
	      *mp = *ms + 's';
	      *fs = *ms + "ne";
	      *fp = *fs + 's';
	}else if(endsWith(nom,"au")){
	      *ms = nom.substr(0,nom.size()-1) + "vien";
	      *mp = *ms + 's';
	      *fs = *ms + "ne";
	      *fp = *fs + 's';
	}else if(endsWith(nom,"ou")){
		int alea = randomInt(3);
		if(alea == 0){
			*ms = nom.substr(0,nom.size()-1) + "is";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = nom + "nais";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else{
			*ms = nom.substr(0,nom.size()-1) + "vite";
			*mp = *ms + 's';
			*fs = *ms;
			*fp = *mp;
		}
	}else if(endsWith(nom,"li")){
		if(randomInt(2) == 0){
			*ms = nom + "nais";
			*mp = *ms;
			*fs = *ms + "e";
			*fp = *fs + "s";
		}else{
			*ms = nom.substr(0,nom.size()-1) + "ois";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"a")){
		int alea = randomInt(3);
		if(alea == 0){
			*ms = nom + "in";
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = nom + "is";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 2){
			*ms = nom.substr(0,nom.size()-1) + "ien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else if(alea == 3){
			*ms = nom + 'n';
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else{
			*ms = nom.substr(0,nom.size()-1) + "énien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"i")){
		int alea = randomInt(4);
		if(alea == 0){
			*ms = nom + "en";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = nom.substr(0,nom.size()-1) + "ais";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 2){
			*ms = nom.substr(0,nom.size()-1) + "ois";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else{
			*ms = nom + "te";
			*mp = *ms + 's';
			*fs = *ms;
			*fp = *mp;
		}
	}else if(endsWith(nom,"o")){
		int alea = randomInt(4);
		if(alea == 0){
			*ms = nom + "is";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = nom.substr(0,nom.size()-1) + "in";
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 2){
			*ms = nom.substr(0,nom.size()-1) + "ien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else{
			*ms = nom.substr(0,nom.size()-1) + "énien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"u")){
		int alea = randomInt(5);
		if(alea == 0){
			*ms = nom + "nien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = nom.substr(0,nom.size()-1) + "ien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else if(alea == 2){
			*ms = nom.substr(0,nom.size()-1) + "ois";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 3){
			*ms = nom + "an";
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 4){
			*ms = nom + "nais";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}
	}else if(endsWith(nom,"y")){
	      *ms = nom + "en";
	      *mp = *ms + 's';
	      *fs = *ms + "ne";
	      *fp = *fs + 's';
	}else{
		std::string tmpNom = nom;
		if(endsWith(tmpNom,"e")){
			tmpNom = tmpNom.substr(0,tmpNom.size()-1);
		}
		int alea = randomInt(4);
		if(alea == 0){
			*ms = tmpNom + "ien";
			*mp = *ms + 's';
			*fs = *ms + "ne";
			*fp = *fs + 's';
		}else if(alea == 1){
			*ms = tmpNom + "ais";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 2){
			*ms = tmpNom + "ain";
			*mp = *ms + 's';
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}else if(alea == 3){
			*ms = tmpNom + "ois";
			*mp = *ms;
			*fs = *ms + 'e';
			*fp = *fs + 's';
		}
	}
}
	
std::string generateName(int syllablesMax){
	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	static const std::string consonants = "bcdfghjklmnpqrstvwxz";
	static const std::vector<std::string> allVowels = {"a", "e", "i", "o",
		"u", "y", "ai", "au", "ei", "eu", "oi", "ou"};
	static const std::vector<std::string> allConsonants = {"b", "c", "d",
		"f", "g", "h", "j", "k", "l", "m", "n", "p", "q", "r", "s", "t",
		"v", "w", "x", "z", "bl", "br", "ch", "cl", "cr", "dr", "fl",
		"fr", "gl", "gn", "gr", "kl", "kr", "ph", "pl", "pr", "qr",
		"ql", "tr", "vl", "vr", "wl", "wr"};
	std::string res = "";
	int nbSyllabes = randomInt(1, syllablesMax+1);
	for(int i = 0;i < nbSyllabes;i++){
		if(randomInt(2) == 0){
			res += randomElement(allConsonants);
		}
		res += randomElement(allVowels);
		if(randomInt(2) == 0){
			res += randomElement(consonants);
		}
	}
	res[0] = alphabet[alphabet.find(res[0])+alphabet.size()/2];
	return res;
}

std::string format(int a){
	char buf[1024];
	sprintf(buf,"%d",a);
	std::string res = "";
	int length = strlen(buf);
	for(int i = 0;i < length;i++){
		if(i % 3 == 0 && i != 0){
			res = ' '+res;
		}
		res = buf[length-i-1]+res;
	}
	return res;
}

std::string operator+(std::string a,int b){
	return a+format(b);
}

std::string operator+(gnu::autosprintf a, std::string b){
	return a.operator std::string()+b;
}

std::string operator+(std::string a, gnu::autosprintf b){
	return a+b.operator std::string();
}

#if QT != 0
QString operator+(QString a, std::string b){
	return a+QString::fromStdString(b);
}
#endif
