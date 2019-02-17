/******************************************************************
* Titre:		Dossier de clients (8INF259\TP1)				  *
*                                                                 *
* Auteur(e)s:   Dominique Boivin (BOID31609701),				  *
*				Jason Gilbert (GILJ05069703)				      *
* Date:         2019-02-18										  *
*                                                                 *
* Description:  Gestion de messagerie électronique.				  *
*																  *
* Instructions: Les fichiers de données (clients, historique et   *
*               transaction se trouvent dans                      *
*               8INF259-TP1/8INF259-TP1/Resource Files/Data/      *
******************************************************************/

#include "pch.h"
#include "DossierClient.h"

int main()
{
	//Initialization
	std::cout << "Initializing..." << std::flush;
	DossierClient * dossierClient = new DossierClient();
	std::cout << "Done!" << std::endl;

	//TODO: Open the transaction File, for each line, parse the instruction and do the appropriate call of DossierClient()

	//DEBUG: Ouvrir()
	std::cout << "Opening..." << std::flush;
	char fileClient[] = "CLIENT.txt", fileHistorique[] = "HISTORIQUE.txt";
	std::cout << fileClient << " & " << fileHistorique << "..." << std::flush;
	dossierClient->Ouvrir(fileClient, fileHistorique);
	std::cout << "Done!" << std::endl;
	dossierClient->Debug_DisplayClients();
	//

	system("pause");
	delete dossierClient;
	return 0;
}

