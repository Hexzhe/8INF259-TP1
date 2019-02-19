/******************************************************************
* Titre:		Dossier de clients (8INF259\TP1)				  *
*                                                                 *
* Auteur(e)s:   Dominique Boivin (BOID31609701),				  *
*				Jason Gilbert (GILJ05069703)				      *
* Date:         2019-02-18										  *
*                                                                 *
* Description:  Gestion de messagerie électronique.	La page		  *
*				actuelle contient le main et les appels de		  *
				classes.										  *
*																  *
* Instructions: Les fichiers de données (clients, historique et   *
*               transaction se trouvent dans                      *
*               8INF259-TP1/8INF259-TP1/Resource Files/Data/	  *
******************************************************************/

#include "pch.h"
#include "DossierClient.h"
#include <sstream>

int main()
{
	//Initialization
	std::cout << "Initializing..." << std::flush;
	DossierClient * dossierClient = new DossierClient();
	std::cout << "Done!" << std::endl;

	//Input stream
	std::cout << "Opening...TRANSACTION.txt..." << std::flush;
	std::ifstream ifs_transaction("Resource Files/Data/TRANSACTION.txt", std::ios::in);

	//Open validation
	if (!ifs_transaction.is_open())
	{
		std::cout << "Erreur lors de l'ouverture du fichier transaction." << std::endl;
		system("pause");
		return 1;
	}
	std::cout << "Done!" << std::endl;

	//Read row by row
	std::string line;
	std::cout << "Processing transactions..." << std::endl;
	while (getline(ifs_transaction, line))
	{
		std::cout << "    Processing \"" << line << "\"..." << std::endl;

		if (line.length() == 0)
		{
			std::cout << "        Empty line" << std::endl << "    Skipped" << std::endl;
			continue;
		}

		//Parse the transaction
		std::string transaction[4]; //max one instruction + 3 params
		std::istringstream iss(line);
		for (int i = 0; iss.good() && i < 4; i++) {

			if (i < 3) 
				iss >> transaction[i];
			else {
				//Getline -> pour accepter les espaces
				std::getline(iss, transaction[i]);
				transaction[i] = transaction[i].substr(1, transaction[i].length() - 1);
			}
		}

		switch (transaction[0].c_str()[0])
		{
		case '-':
			dossierClient->SupprimerClient(transaction[1].c_str());
			break;
		case '+':
			dossierClient->AjouterClient(transaction[1].c_str(), transaction[2].c_str(), atoi(transaction[3].c_str()));
			break;
		case '=':
			dossierClient->AjouterMessage(transaction[1].c_str(), transaction[2].c_str(), transaction[3].c_str());
			break;
		case '&':
		{
			int result = dossierClient->NombreEchange(transaction[1].c_str(), transaction[2].c_str());
			std::cout << "        Nombre d'echanges: " << result << std::endl;
			break;
		}
		case '!':
		{
			std::string result = dossierClient->MeilleurClient();
			std::cout << "        Meilleur client: " << result << std::endl;
			break;
		}
		case '$':
		{
			std::string result = dossierClient->RuePayante();
			std::cout << "        Rue payante: " << result << std::endl;
			break;
		}
		case 'O':
			dossierClient->Ouvrir(transaction[1].c_str(), transaction[2].c_str());
			break;
		case 'S':
			dossierClient->Sauvegarder(transaction[1].c_str(), transaction[2].c_str());
			break;
		default:
			std::cout << "        Nothing implemented for instruction \"" << transaction[0].c_str()[0] << "\"" << std::endl << "    Skipped" << std::endl;
			continue;
		}

		std::cout << "    Done!" << std::endl;
	}

	ifs_transaction.close();
	std::cout << "Done!" << std::endl;

	system("pause");
	delete dossierClient;
	return 0;
}

