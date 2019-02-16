#pragma once

#include "LinkedList.h"

struct Message
{
	string destinataire; //[50]; TODO: The PDF suggest that we must(?) use char[]. I used strings to get something functional ASAP. Add some .c_str() or I dunno
	string message; //[80];
};

struct Client
{
	string rue; //[50];
	int numero;
	string nom; //[50];
	LinkedList<Message> * messages;
};