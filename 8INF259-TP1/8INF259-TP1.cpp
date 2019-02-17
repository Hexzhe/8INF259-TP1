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
	DossierClient dossierClient;
	char fileClient[] = "CLIENT.txt", fileHistorique[] = "HISTORIQUE.txt";
	dossierClient.Ouvrir(fileClient, fileHistorique);

	dossierClient.Debug_DisplayClients();

	system("pause");
	return 0;
}

