#ifndef general_h
#define general_h

#include <string>
#include <vector>
#include <algorithm>

int randomInt(int min,int max);

int randomInt(int max);

void genererGentile(std::string nom,std::string* ms,std::string* mp,std::string* fs,std::string* fp);

std::string genererNom(int longMax);

template<typename T>
typename std::vector<T>::const_iterator find(const std::vector<T>& vector,const T& needle){
	return std::find(vector.begin(),vector.end(),needle);
}

#endif // general_h
