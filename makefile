all: main


main: main.cpp Personne.o Monde.o Pays.o Ville.o Groupe.o Entite.o general.o
	g++ -Wall -o main main.cpp Personne.o Monde.o Pays.o Ville.o Groupe.o Entite.o general.o

Personne.o: Personne.cpp
	g++ -Wall -c Personne.cpp
	
Monde.o: Monde.cpp
	g++ -Wall -c Monde.cpp
	
Pays.o: Pays.cpp
	g++ -Wall -c Pays.cpp
	
Ville.o: Ville.cpp
	g++ -Wall -c Ville.cpp
	
Groupe.o: Groupe.cpp
	g++ -Wall -c Groupe.cpp

Entite.o: Entite.cpp
	g++ -Wall -c Entite.cpp
	
general.o: general.cpp
	g++ -Wall -c general.cpp
	
run: main
	./main



main.html: main.cpp emPersonne.o emMonde.o emPays.o emVille.o emGroupe.o emEntite.o em_general.o
	em++ -s DISABLE_DEPRECATED_FIND_EVENT_TARGET_BEHAVIOR -std=c++11 --emrun --bind -Wall -o main.html em_main.cpp emPersonne.o emMonde.o emPays.o emVille.o emGroupe.o emEntite.o em_general.o

emPersonne.o: Personne.cpp
	em++ -std=c++11 -Wall -c -o emPersonne.o Personne.cpp

emMonde.o: Monde.cpp
	em++ -std=c++11 -Wall -c -o emMonde.o Monde.cpp
	
emPays.o: Pays.cpp
	em++ -std=c++11 -Wall -c -o emPays.o Pays.cpp
	
emVille.o: Ville.cpp
	em++ -std=c++11 -Wall -c -o emVille.o Ville.cpp
	
emGroupe.o: Groupe.cpp
	em++ -std=c++11 -Wall -c -o emGroupe.o Groupe.cpp

emEntite.o: Entite.cpp
	em++ -std=c++11 -Wall -c -o emEntite.o Entite.cpp

em_general.o: general.cpp
	em++ -std=c++11 -Wall -c -o em_general.o general.cpp

run_web: main.html
	emrun main.html
	

clean:
	rm *.exe *.o *.html *.js *.wasm