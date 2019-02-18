#pragma once
#include "Models.h"
#include <string>
#include <fstream>
#include <iostream>
#include "LinkedList.h"

class DossierClient
{
public:
	DossierClient();
	~DossierClient();

	void Ouvrir(const char * fichierClient, const char * fichierHistorique);
	void Sauvegarder(const char * fichierClient, const char * fichierHistorique);

	void AjouterClient(const char * nom, const char * rue, const int numero);
	void SupprimerClient(const char * nom);
	void AjouterMessage(const char * nomClient, const char * nomDestination, const char * message);

	int NombreEchange(const char * X, const char * Y);
	char* MeilleurClient() const;
	char* RuePayante() const;

	int FindClient(std::string name);

	void Debug_DisplayClients();
private:
	LinkedList<Client> * clients;
	std::string village;
};

