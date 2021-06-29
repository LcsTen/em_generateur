#ifndef general_h
#define general_h

#include <string>
#include <vector>
#include <algorithm>

int randomInt(int min,int max);

int randomInt(int max);

double randouble();

void genererGentile(std::string nom,std::string* ms,std::string* mp,std::string* fs,std::string* fp);

std::string generateName(int syllablesMax);

std::string format(int a);

std::string operator+(std::string a,int b);

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
