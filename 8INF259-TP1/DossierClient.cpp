#include "pch.h"
#include "DossierClient.h"

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
	std::ifstream ifs_client(fichierClient, std::ios::in);
	std::ifstream ifs_historique(fichierHistorique, std::ios::in);

	//Open validations
	if (!ifs_client.is_open())
	{
		std::cout << "Erreur lors de l'ouverture du fichier client." << std::endl;
		return;
	}

	if (!ifs_historique.is_open())
	{
		std::cout << "Erreur lors de l'ouverture du fichier historique." << std::endl;
		return;
	}

	//Load clients
	std::string line;
	Client * client = new Client();
	for (int i = 0; getline(ifs_client, line); i++)
	{
		if (i == 0) //Village
		{
			//Do something
			continue;
		}

		if (i == 1) //Rue
		{
			client->rue = line;
			continue;
		}

		if (i == 2) //Numero
		{
			client->numero = atoi(line.c_str());
			continue;
		}

		//Nom
		client->nom = line;

		clients->Add(*client);
		i = 0; //Will get incremented to 1 right away so we skip the village
		client = new Client();
	}

	//Load messages
	Message * message = new Message();
	bool skip = false;
	for (int i = 0; getline(ifs_historique, line); i++)
	{
		if (line == "&") //end of record, start new
		{
			i = -1; //Will get incremented to 0 right away
			skip = false;
			continue;
		}

		if (skip) continue; //Mean we didn't find a client to associate those messages with. Continue until the next & or EOF

		if (i == 0) //Sender
		{
			if (FindClient(clients, line) == -1) 
				skip = true; //Not found, we can ignore those messages and move to the next record, we can't associate them to anyone anyway. (the list position is reset to 0)
				
			//If the client is found, the list "current" will be on its position.
			continue;
		}

		if (i % 2 != 0) //Recipient
		{
			message->destinataire = line;
			continue;
		}

		//Message
		message->message = line;

		//Attach message
		clients->GetValue().messages->Add(*message);
		message = new Message();
	}

	//Close streams
	ifs_client.close();
	ifs_historique.close();

	delete message, client;
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

int DossierClient::FindClient(LinkedList<Client> * clients, std::string name)
{
	clients->Move(0);

	for (int i = 0; clients->IsInRange(); i++)
	{
		if (clients->Current->Next->Item.nom == name)
			return i;
		else
			clients->MoveNext();
	}

	clients->Move(0);
	return -1;
}

void DossierClient::Debug_DisplayClients()
{
	if (clients->Count() < 1) return;

	clients->Move(0);

	while (clients->IsInRange())
	{
		std::cout << "nom: " << clients->GetValue().nom << std::endl;
		std::cout << "rue: " << clients->GetValue().rue << std::endl;
		std::cout << "numero: " << clients->GetValue().numero << std::endl;


		if (clients->GetValue().messages->Count() > 0)
		{
			clients->GetValue().messages->Move(0);
			while (clients->GetValue().messages->IsInRange())
			{
				std::cout << "    destinataire: " << clients->GetValue().messages->GetValue().destinataire << std::endl;
				std::cout << "    message: " << clients->GetValue().messages->GetValue().message << std::endl;

				clients->GetValue().messages->MoveNext();
			}
		}
 
		std::cout << std::endl;

		clients->MoveNext();
	}
}