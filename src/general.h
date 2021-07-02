#ifndef general_h
#define general_h

#include <string>
#include <vector>
#include <algorithm>
#include <autosprintf.h>

#if LOCALIZE != 0
	#include <libintl.h>
	#include <locale.h>
	#define _(string, ...) gnu::autosprintf(gettext(string), ##__VA_ARGS__)
#else
	#define _(string, ...) gnu::autosprintf(string, ##__VA_ARGS__)
#endif

int randomInt(int min,int max);

int randomInt(int max);

double randouble();

void genererGentile(std::string nom,std::string* ms,std::string* mp,std::string* fs,std::string* fp);

std::string generateName(int syllablesMax);

std::string format(int a);

std::string operator+(std::string a,int b);

std::string operator+(gnu::autosprintf a, std::string b);

std::string operator+(std::string a, gnu::autosprintf b);

#if QT != 0
#include <QString>
QString operator+(QString a, std::string b);
#endif

template<typename T>
typename std::vector<T>::const_iterator find(const std::vector<T>& vector,const T& needle){
	return std::find(vector.begin(),vector.end(),needle);
}

template<typename T>
typename T::value_type randomElement(const T& container){
	return container[randomInt(container.size())];
}

#endif // general_h
