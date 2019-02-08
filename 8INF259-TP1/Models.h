#pragma once

struct Message
{
	char destinataire[50];
	char message[80];
	Message * suivant;
};

struct Client
{
	char rue[50];
	int numero;
	char nom[50];
	Message * listeMessage;
	Client * suivant;
};