#include "pch.h"
#include "DossierClient.h"

DossierClient::DossierClient()
{
	clients = new LinkedList<Client>();
}

DossierClient::~DossierClient()
{
	delete clients;
}

///O CLIENT HITORIQUE: ouvre les fichiers client "CLIENT" et historique "HISTORIQUE".
void DossierClient::Ouvrir(const char * fichierClient, const char * fichierHistorique)
{
	//Paths formating
	char pathClient[260];
	sprintf_s(pathClient, "Resource Files/Data/%s", fichierClient);
	char pathHistorique[260];
	sprintf_s(pathHistorique, "Resource Files/Data/%s", fichierHistorique);

	//Input streams
	std::ifstream ifs_client(pathClient, std::ios::in);
	std::ifstream ifs_historique(pathHistorique, std::ios::in);

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
			village = line;
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
			if (FindClient(line) == -1)
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

///S CLIENT HITORIQUE: enregistre les fichiers client "CLIENT" et historique "HISTORIQUE"
void DossierClient::Sauvegarder(const char * fichierClient, const char * fichierHistorique)
{
	//Paths formating
	char pathClient[260];
	sprintf_s(pathClient, "Resource Files/Data/%s", fichierClient);
	char pathHistorique[260];
	sprintf_s(pathHistorique, "Resource Files/Data/%s", fichierHistorique);

	//Input streams
	std::ofstream ofs_client(pathClient, std::ios::trunc);
	std::ofstream ofs_historique(pathHistorique, std::ios::trunc);

	//Open validations
	if (!ofs_client.is_open())
	{
		std::cout << "Erreur lors de l'ouverture du fichier client." << std::endl;
		return;
	}

	if (!ofs_historique.is_open())
	{
		std::cout << "Erreur lors de l'ouverture du fichier historique." << std::endl;
		return;
	}

	//First row = village
	ofs_client << village << std::endl;

	if (clients->Count() < 1) return;

	for (clients->Move(0); clients->IsInRange(); clients->MoveNext()) //Iterate through clients
	{
		ofs_client << clients->GetValue().rue << std::endl;
		ofs_client << clients->GetValue().numero << std::endl;
		ofs_client << clients->GetValue().nom << std::flush;

		if (clients->GetValue().messages->Count() > 0)
		{
			clients->GetValue().messages->Move(0);

			//First row = sender name
			ofs_historique << clients->GetValue().nom << std::endl;

			for (clients->GetValue().messages->Move(0); clients->GetValue().messages->IsInRange(); clients->GetValue().messages->MoveNext()) //Iterate through clients' messages
			{
				ofs_historique << clients->GetValue().messages->GetValue().destinataire << std::endl;
				ofs_historique << clients->GetValue().messages->GetValue().message << std::flush;

				//Fix std::endl at the end of the file
				clients->GetValue().messages->MoveNext(); //Peak next value
				if (clients->GetValue().messages->IsInRange()) //Only add a "std::endl" if we aren't at the last index
					ofs_historique << std::endl;
				clients->GetValue().messages->MovePrevious(); //Move back
			}

			clients->GetValue().messages->Move(0);
		}

		//Fix std::endl at the end of the files
		clients->MoveNext(); //Peak next value
		if (clients->IsInRange()) //Only add a "&" if we aren't at the last index
		{
			ofs_client << std::endl;
			if (clients->GetValue().messages->Count() > 0) //Do not add anything to historique file if the client didn't have messages
				ofs_historique << std::endl << "&" << std::endl;
		}
		clients->MovePrevious(); //Move back
	}

	clients->Move(0);

	//Close streams
	ofs_client.close();
	ofs_historique.close();
}

///+ X A N : ajouter un client X habitant à l'adresse A et au numéro N à la liste chaînée.
void DossierClient::AjouterClient(const char * nom, const char * rue, const int numero)
{
	//Add client to the end of the list 

	// Use the filled list **************
	Client * ptr_head = 0; //TODO: USE THE OFFICIAL HEAD 888888888888888888888888888
	Client * ptr_courant = ptr_head;
	Client * ptr_precedent;

	// Tant que le suivant est pas null
	while (ptr_courant->suivant != NULL) {

		// Go to next
		ptr_precedent = ptr_courant;
		ptr_courant = ptr_courant->suivant;
	}

	//Créer le nouveau client à la fin
	ptr_courant->suivant = new Client;
	ptr_courant = ptr_courant->suivant;

	ptr_courant->nom = nom;
	ptr_courant->rue = rue;
	ptr_courant->numero = numero;

}

/// - X : supprimer un client X de la liste chaînée.
void DossierClient::SupprimerClient(const char * nom)
{
	// Use the filled list **************
	Client * ptr_head = 0; //TODO: USE THE OFFICIAL HEAD
	Client * ptr_courant = ptr_head;
	Client * ptr_precedent = ptr_head;
	int cpt = 0;
	bool found = false;

	// If first client is the one to delete
	if (ptr_courant->nom == nom) {

		ptr_head = ptr_courant->suivant; // mettre la tête au deuxième

		//supprimer tous les messages du pointeur courant
		ptr_courant->messages->Clear();

		delete ptr_courant;

	}
	else {

		// Boucler pour demander les prochaines clés
		// keep found in case it was not found
		while (ptr_courant->suivant != NULL && found == false) {


			if (ptr_courant->nom == nom) {
				found = true;
			}
			else {
				// Go to next
				ptr_courant = ptr_courant->suivant;
			}
		}

		if (!found) {
			//TODO: Client was not found
		}
	}
}

///= X Y M : ajouter un message M envoyé du client X au client Y.
void DossierClient::AjouterMessage(const char * nomClient, const char * nomDestination, const char * message)
{
	// Use the filled list **************
	Client * ptr_head = 0; //TODO: USE THE OFFICIAL HEAD 888888888888888888888888888
	Client * ptr_courant = ptr_head;
	bool found = false;

	// Tant que le suivant est pas null
	while (ptr_courant->suivant != NULL) {

		// Client trouvé
		if (ptr_courant->nom == nomClient) {

			found = true;
			Message newMessage;
			newMessage.destinataire = nomDestination;
			newMessage.message = message;

			// Add new message
			ptr_courant->messages->Add(newMessage);
		}
		else {
			// Go to next
			ptr_courant = ptr_courant->suivant;
		}

	}

	if (!found) {
		//TODO: do something if the client wasn't found
	}

}

///& X Y : afficher le nombre de messages échanger entre le client X et Y.
int DossierClient::NombreEchange(const char * X, const char * Y)
{
	//TODO
	return 0;
}

///! : Afficher le client qui envoie le plus de messages.
char * DossierClient::MeilleurClient() const
{
	//TODO
	return nullptr;
}

///$ : Afficher le nom de la rue la plus payante.
char * DossierClient::RuePayante() const
{
	// Use the filled list **************
	Client * ptr_head = 0; //TODO: USE THE OFFICIAL HEAD 888888888888888888888888888
	Client * ptr_courant = ptr_head;
	Message msg;
	int cpt = 0, cptTmp = 0;
	char * ruePayante;
	bool found = false;

	struct Rues{
		char * nomRue;
		int cptClients;
		Rues * suivante;
	};
	
	// Tant que le suivant est pas null
	while (ptr_courant->suivant != NULL) {

		bool fin = false;

		while (fin == false) {
			//ptr_courant->messages->Head
			//TODO: CONTINUE HERE
		}


	}

	if (!found) {
		//TODO: do something if the client wasn't found
	}


	//TODO
	return nullptr;
}

int DossierClient::FindClient(std::string name)
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
	//Delete this before prod
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