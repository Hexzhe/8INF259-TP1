#include "pch.h"
#include "DossierClient.h"
#include <string>
#include <fstream>
#include <iostream>
#include "LinkedList.cpp" //TODO: We should be able to include the .h instead, but we get an "unresolved externals" error

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
	clients = new LinkedList<Client>();

	//Input streams
	ifstream ifs_client(fichierClient, ios::in);
	ifstream ifs_historique(fichierHistorique, ios::in);

	//Open validations
	if (!ifs_client.is_open())
	{
		cout << "Erreur lors de l'ouverture du fichier client." << endl;
		return;
	}

	if (!ifs_historique.is_open())
	{
		cout << "Erreur lors de l'ouverture du fichier historique." << endl;
		return;
	}

	//First row = village
	string village;
	ifs_client >> village; //TODO: Do something with this?

	//Load clients
	Client client;
	while (!ifs_client.eof())
	{
		ifs_client >> client.rue;
		ifs_client >> client.numero;
		ifs_client >> client.nom;

		clients->Add(client);
	}

	//Load messages
	string line;
	Message * message = new Message();
	bool skip = false;
	for (int i = 0; getline(ifs_historique, line); i++)
	{
		if (line == "&") //end of record, start new
		{
			i = 0;
			skip = false;
			continue;
		}

		if (skip) continue; //Mean we didn't find a client to associate those messages with. Continue until the next & or EOF

		if (i == 0) //Sender
		{
			//TODO
			//We could:
			//	move this->clients to this specific sender (clients->Move(FindClient(clients, line)))
			//		If found, we can already set the list position (clients->Move())
			//		If not found (-1), we can ignore those messages and move to the next record, we can't associate them to anyone anyway. Set skip to true
			continue;
		}

		if (i % 2 != 0) //Recipient
		{
			message = new Message();
			strncpy_s(message->destinataire, line.c_str(), 50);
			continue;
		}

		//Message
		strncpy_s(message->message, line.c_str(), 80);

		//TODO: Attach message to its client
		//	Depending on what we chose to do in (i == 0), we may already be at the right position
		//	Get the current value and attach the message (.Add())
	}

	//Close streams
	ifs_client.close();
	ifs_historique.close();
}

int DossierClient::FindClient(LinkedList<Client> * clients, char * name)
{
	//TODO
	//Iterate through clients (.MoveNext()) and return the index if we find it (.GetValue())
	//Similar the the .Find() function of LinkedList, but to search on a specific field of the node's value

	return -1;
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

void DossierClient::Debug_DisplayClients()
{

}