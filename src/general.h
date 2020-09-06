#ifndef general_h
#define general_h

#include <string>
#include <vector>

int randomInt(int min,int max);

int randomInt(int max);

void genererGentile(std::string nom,std::string* ms,std::string* mp,std::string* fs,std::string* fp);

std::string genererNom(int longMax);

#endif // general_h