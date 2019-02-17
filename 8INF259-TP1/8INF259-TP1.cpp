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
#include <regex>

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
		if (line.length() == 0)
		{
			std::cout << "Empty line skipped" << std::endl;
			continue;
		}

		std::cout << "    Processing \"" << line << "\"..." << std::flush;

		//Split the line on space
		std::regex regex{ R"([\s]+)" };
		std::sregex_token_iterator it{ line.begin(), line.end(), regex, -1 };
		std::vector<std::string> transaction{ it, {} }; //TODO: Use our LinkedList instead of a vector maybe

		switch (transaction[0].c_str()[0])
		{
		case '-':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->SupprimerClient(transaction[1].c_str());
			break;
		case '+':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->AjouterClient(transaction[1].c_str(), transaction[2].c_str(), atoi(transaction[3].c_str()));
			break;
		case '=':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->AjouterMessage(transaction[1].c_str(), transaction[2].c_str(), transaction[3].c_str());
			break;
		case '&':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->NombreEchange(transaction[1].c_str(), transaction[2].c_str());
			break;
		case '!':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->MeilleurClient();
			break;
		case '$':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->RuePayante();
			break;
		case 'O':
			dossierClient->Ouvrir(transaction[1].c_str(), transaction[2].c_str());
			break;
		case 'S':
			std::cout << std::endl << "        Debug: Comment this line to enable this instruction. Skip." << std::endl; continue;
			dossierClient->Sauvegarder(transaction[1].c_str(), transaction[2].c_str());
			break;
		default:
			std::cout << std::endl << "        Nothing implemented for instruction \"" << transaction[0].c_str()[0] << "\". Skip." << std::endl;
			continue;
		}

		std::cout << "Done!" << std::endl;
	}

	ifs_transaction.close();
	std::cout << "Done!" << std::endl;

	system("pause");
	delete dossierClient;
	return 0;
}

