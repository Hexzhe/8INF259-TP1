#pragma once
#include "Models.h"

class DossierClient
{
private:
	Client * tete;
public:
	DossierClient();
	~DossierClient();

	void Ouvrir(char * fichierClient, char * fichierHistorique);
	void Sauvegarder(char * fichierClient, char * fichierHistorique); 

	void AjouterClient(char * nom, char * rue, int numero);
	void SupprimerClient(char * nom);
	void AjouterMessage(char * nomClient, char * nomDestination, char * message);

	int NombreEchange(char * X, char * Y);
	char* MeilleurClient() const;
	char* RuePayante() const;
};

