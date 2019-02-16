#include "pch.h"
#include "DossierClient.h"
#include <string>
#include <fstream>
#include <iostream>
#include "List.h"
#include "Node.h"

using namespace std;

DossierClient::DossierClient()
{

	//TODO

}

DossierClient::~DossierClient()
{

	//TODO

}

void DossierClient::Ouvrir(char * fichierClient, char * fichierHistorique)
{
	string village;

	//historique
	string sender, receiver, message, next, tmp; //Variables temporaires pour la lecture ?

	// Pour les ajouts dans la listes; seront réutilisés pour chacun
	Client cunt;
	Message message;

	List<Client>* client_list = new List<Client>();
	List<Message>* messag_list = new List<Message>();

	// Ajuster pour utiliser pointeurs chars JASON CHANGE THIS
	string tmpfichierClient = ("../Resource Files/Data/CLIENT.txt");
	string tmpfichierHistorique = ("../Resource Files/Data/HISTORIQUE.txt");

	// Input filesteams
	ifstream ifs_client(tmpfichierClient.c_str(), ios::in);
	ifstream ifs_historique(tmpfichierHistorique.c_str(), ios::in);

	// Open successful
	if (ifs_client && ifs_historique)
	{
		int cpt = 0;

		// while not at end of file
		while (!ifs_client.eof())
		{
			//Check if start of file
			if (cpt == 0) {
				ifs_client >> village;
			}

			/* if premiere ligne only, village name*/
			ifs_client >> cunt.rue;
			ifs_client >> cunt.numero;
			ifs_client >> cunt.nom;

			client_list->Add(cunt);
		}

		while (!ifs_historique.eof())
		{
			/* Trouver logique pour l'ajout */
			ifs_historique >> tmp;

			if (tmp != "&") {

			}

			//messag_list->Add(message) //temp
		}

		// Fermer
		ifs_client.close();
		ifs_historique.close();
	}
	else //open not successful
	{
		cout << "NOPE";
	}
	   

}

void DossierClient::Sauvegarder(char * fichierClient, char * fichierHistorique)
{
	//TODO
}

void DossierClient::AjouterClient(char * nom, char * rue, int numero)
{
	//TODO
}

void DossierClient::SupprimerClient(char * nom)
{
	//TODO
}

void DossierClient::AjouterMessage(char * nomClient, char * nomDestination, char * message)
{
	//TODO
}

int DossierClient::NombreEchange(char * X, char * Y)
{
	//TODO
	return 0;
}

char * DossierClient::MeilleurClient() const
{
	//TODO
	return nullptr;
}

char * DossierClient::RuePayante() const
{
	//TODO
	return nullptr;
}
