#pragma once

#include "LinkedList.h"

struct Message
{
	char destinataire[50];
	char message[80];
};

struct Client
{
	char rue[50];
	int numero;
	char nom[50];
	LinkedList<Message> * messages;
};