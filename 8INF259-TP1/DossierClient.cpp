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
void DossierClient::Ouvrir(char * fichierClient, char * fichierHistorique)
{
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
void DossierClient::Sauvegarder(char * fichierClient, char * fichierHistorique)
{
	//TODO
}

///+ X A N : ajouter un client C habitant à l'adresse A et au numéro N à la liste chaînée.
void DossierClient::AjouterClient(char * nom, char * rue, int numero)
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
void DossierClient::SupprimerClient(char * nom)
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
void DossierClient::AjouterMessage(char * nomClient, char * nomDestination, char * message)
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
int DossierClient::NombreEchange(char * X, char * Y)
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