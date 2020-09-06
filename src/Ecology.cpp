#include "Ecology.h"

Ecology::Ecology(Map pMap) : map(pMap){
	
}

Ecology::Ecology(size_t lin,size_t col) : Ecology(Map(lin,col)) {}

Ecology::Ecology() : Ecology(100,100) {}

