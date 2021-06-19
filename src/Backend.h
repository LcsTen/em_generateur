#ifndef backend_h
#define backend_h

#include <functional>

#if QT == 0
	#define STRING_TYPE std::string
	#define Q_OBJECT
	#define Q_INVOKABLE
	#define signals private
	#define emit
#else
	#include <QObject>
	#define STRING_TYPE QString
#endif

#include "Personne.h"
#include "Entite.h"
#include "Monde.h"
#include "Pays.h"
#include "Ville.h"
#include "Groupe.h"
#include "StarSystem.h"
#include "GasPlanet.h"
#include "TelluricPlanet.h"
#include "general.h"

class Backend
#if QT != 0
	: public QObject
#endif
{
	Q_OBJECT

	public:
		Backend();

		Q_INVOKABLE STRING_TYPE politicsToString(int index_country = -1, int index_city = -1);
		Q_INVOKABLE STRING_TYPE spaceToString();
		std::string mapToString();
		Q_INVOKABLE void generateWorld();
		void onWorldChanged(std::function<void()> f);
		void onLogPrinted(std::function<void(std::string)> f);

	signals:
		void worldChanged();
		void logPrinted(STRING_TYPE s);

	private:
		std::string entiteToString(Ville* ville, int depth = 0);
		std::string entiteToString(Pays* pays, int depth = 0);
		std::string entiteToString(Monde* m, int depth = 0);
		std::string spaceToString(GasPlanet* g);
		std::string spaceToString(TelluricPlanet* t);
		std::string spaceToString(World* w);
		std::string spaceToString(StarSystem* s);

		Monde* monde = nullptr;
		StarSystem* space = nullptr;
		std::vector<std::function<void()>> worldChangedCallbacks;
		std::vector<std::function<void(std::string)>> logPrintedCallbacks;
};

#endif // backend_h
