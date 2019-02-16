/******************************************************************
* Titre:		Dossier de clients (8INF259\TP1)				  *
*                                                                 *
* Auteur(e)s:   Dominique Boivin (BOID31609701),				  *
*				Jason Gilbert (GILJ05069703)				      *
* Date:         2019-02-18										  *
*                                                                 *
* Description:  Gestion de messagerie électronique.				  *
*																  *
******************************************************************/

#include "pch.h"
#include <iostream>
#include <fstream>
#include "DossierClient.h"
#include "LinkedList.h"

using namespace std;

int main()
{
	DossierClient dossierClient;
	char pathClient[] = "../Resource Files/Data/CLIENT.txt";
	char pathHistorique[] = "../Resource Files/Data/HISTORIQUE.txt";
	dossierClient.Ouvrir(pathClient, pathHistorique);

	dossierClient.Debug_DisplayClients();

	system("pause");
	return 0;
}

