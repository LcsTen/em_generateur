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

		Q_INVOKABLE STRING_TYPE politicsToHtml();
		Q_INVOKABLE STRING_TYPE spaceToHtml();
		Q_INVOKABLE void generateWorld();
		void onWorldChanged(std::function<void()> f);
		void onLogPrinted(std::function<void(std::string)> f);

	signals:
		void worldChanged();
		void logPrinted(STRING_TYPE s);

	private:
		std::string entiteToHtml(Ville* ville);
		std::string entiteToHtml(Pays* pays);
		std::string entiteToHtml(Monde* m);
		std::string spaceToHtml(GasPlanet* g);
		std::string spaceToHtml(TelluricPlanet* t);
		std::string spaceToHtml(World* w);
		std::string spaceToHtml(StarSystem* s);

		Monde* monde = nullptr;
		StarSystem* space = nullptr;
		std::vector<std::function<void()>> worldChangedCallbacks;
		std::vector<std::function<void(std::string)>> logPrintedCallbacks;
};

#endif // backend_h
