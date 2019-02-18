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

/// Constructeur
DossierClient::DossierClient()
{
	clients = new LinkedList<Client>();
}

/// Destructeur
DossierClient::~DossierClient()
{
	delete clients;
}

/// O CLIENT HISTORIQUE: ouvre les fichiers client "CLIENT" et historique "HISTORIQUE".
void DossierClient::Ouvrir(const char * fichierClient, const char * fichierHistorique)
{
	//Paths formatting
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
		if (i == 0) // Village
		{
			village = line;
			continue;
		}

		if (i == 1) // Rue
		{
			client->rue = line;
			continue;
		}

		if (i == 2) // Numero
		{
			client->numero = atoi(line.c_str());
			continue;
		}

		// Nom
		client->nom = line;

		clients->Add(*client);
		i = 0; // Will get incremented to 1 right away so we skip the village
		client = new Client();
	}

	//Load messages
	Message * message = new Message();
	bool skip = false;
	for (int i = 0; getline(ifs_historique, line); i++)
	{
		if (line == "&") // End of record, start new
		{
			i = -1; // Will get incremented to 0 right away
			skip = false;
			continue;
		}

		if (skip) continue; // Means we didn't find a client to associate those messages with. Continue until the next & or EOF

		if (i == 0) // Sender
		{
			if (FindClient(line) == -1)
				skip = true; // Not found, we can ignore those messages and move to the next record, we can't associate them to anyone anyway. (the list position is reset to 0)

			// If the client is found, the list "current" will be on its position.
			continue;
		}

		if (i % 2 != 0) // Recipient
		{
			message->destinataire = line;
			continue;
		}

		// Check if message is longer than 80
		if (message->message.length() < 80) {
			message->message = line;
		}
		else {
			// If longer than 80 chars, truncate
			std::cout << "Le message est trop long pour pouvoir etre enregistre. Il sera tronque.";
			message->message.resize(80);
		}

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

	//Iterate through clients
	for (clients->Move(0); clients->IsInRange(); clients->MoveNext())
	{
		ofs_client << clients->GetValue().rue << std::endl;
		ofs_client << clients->GetValue().numero << std::endl;
		ofs_client << clients->GetValue().nom << std::flush;

		if (clients->GetValue().messages->Count() > 0)
		{
			clients->GetValue().messages->Move(0);

			//First row = sender name
			ofs_historique << clients->GetValue().nom << std::endl;

			//Iterate through clients' messages
			for (clients->GetValue().messages->Move(0); clients->GetValue().messages->IsInRange(); clients->GetValue().messages->MoveNext())
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

/// + X A N : ajouter un client X habitant à l'adresse A et au numéro N à la liste chaînée.
void DossierClient::AjouterClient(const char * nom, const char * rue, const int numero)
{
	Client newClient;
	newClient.nom = nom;
	newClient.rue = rue;
	newClient.numero = numero;

	clients->Add(newClient);
}

/// - X : supprimer un client X de la liste chaînée.
void DossierClient::SupprimerClient(const char * nom)
{
	if (FindClient(nom) < 0)
	{
		std::cout << "        Client not found" << std::endl;
		return;
	}

	clients->Remove();
}

///= X Y M : ajouter un message M envoyé du client X au client Y.
void DossierClient::AjouterMessage(const char * nomClient, const char * nomDestination, const char * message)
{
	Message newMessage;
	newMessage.destinataire = nomDestination;
	newMessage.message = message;

	if (FindClient(nomClient) < 0)
	{
		std::cout << "        Client not found" << std::endl;
		return;
	}

	clients->GetValue().messages->Add(newMessage);
}

///& X Y : afficher le nombre de messages échangés entre le client X et Y.
int DossierClient::NombreEchange(const char * X, const char * Y)
{
	int count = 0;

	//X -> Y
	if (FindClient(X) < 0)
	{
		std::cout << "        Client not found" << std::endl;
		return;
	}
	
	if (clients->GetValue().messages->Count() > 0)
	{
		clients->GetValue().messages->Move(0);
		while (clients->GetValue().messages->IsInRange())
		{
			if (clients->GetValue().messages->GetValue().destinataire == Y)
				count++;

			clients->GetValue().messages->MoveNext();
		}
		clients->GetValue().messages->Move(0);
	}

	//Y -> X
	if (FindClient(Y) < 0)
	{
		std::cout << "        Client not found" << std::endl;
		return;
	}
	
	if (clients->GetValue().messages->Count() > 0)
	{
		clients->GetValue().messages->Move(0);
		while (clients->GetValue().messages->IsInRange())
		{
			if (clients->GetValue().messages->GetValue().destinataire == X)
				count++;

			clients->GetValue().messages->MoveNext();
		}
		clients->GetValue().messages->Move(0);
	}

	return count;
}

///! : Afficher le client qui envoie le plus de messages.
char * DossierClient::MeilleurClient() const
{
	int cptMsg, max = 0;
	std::string bestClient;

	// Loop through clients
	while (clients->IsInRange()) {
		cptMsg = 0;

		//Loop through client's messages
		while (clients->GetValue().messages->IsInRange()) {
			cptMsg++;
			clients->GetValue().messages->MoveNext();
		}

		// If current cpt > than the current max
		if (cptMsg > max) {
			max = cptMsg;
			bestClient = clients->Current->Item.nom;
		}

		clients->MoveNext();
	}

	if (max = 0) {
		std::cout << "Aucun message n'a ete envoye dans le village.";
	}
	else {
		//return bestClient; //888888888888888888888888888888888888888888
	}
	//TODO
	return nullptr;
}

///$ : Afficher le nom de la rue la plus payante.
char * DossierClient::RuePayante() const
{
	int total = 0, max = 0;
	//char * bestStreet;
	std::string bestStreet;

	//Loop through clients
	while (clients->IsInRange()) {

		//Loop through messages
		while (clients->GetValue().messages->IsInRange()) {
			total++;
			clients->GetValue().messages->MoveNext();
		}

		if (total > max) {
			max = total;
			bestStreet = clients->GetValue().rue;
		}
		total = 0;
		clients->MoveNext();
	}

	// Si aucun message n'a été envoyé
	if (max == 0) {
		std::cout << "Aucun message n'a ete envoye.";

	}

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