#include <iostream>
#include "Personne.hpp"
#include "Entite.hpp"
#include "Monde.hpp"

int main(){
	Personne p("Jean","Martin",99);
	std::cout << p << std::endl;
	std::cout << p.sePresente() << std::endl;
	
	Monde m;
	std::cout << m << std::endl;
	return 0;
}