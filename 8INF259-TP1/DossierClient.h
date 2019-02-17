#pragma once
#include "pch.h"
#include "Models.h"
#include <string>
#include <fstream>
#include <iostream>
#include "LinkedList.cpp"

class DossierClient
{
public:
	DossierClient();
	~DossierClient();

	void Ouvrir(const char * fichierClient, const char * fichierHistorique);
	void Sauvegarder(char * fichierClient, char * fichierHistorique); 

	void AjouterClient(char * nom, char * rue, int numero);
	void SupprimerClient(char * nom);
	void AjouterMessage(char * nomClient, char * nomDestination, char * message);

	int NombreEchange(char * X, char * Y);
	char* MeilleurClient() const;
	char* RuePayante() const;

	int FindClient(std::string name);

	void Debug_DisplayClients();
private:
	LinkedList<Client> * clients;
};

