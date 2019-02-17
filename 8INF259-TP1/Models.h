#pragma once
#include <string>
#include "LinkedList.cpp"

struct Message
{
	std::string destinataire;
	std::string message;
};

struct Client
{
	std::string rue;
	int numero;
	std::string nom;
	LinkedList<Message> * messages;
	Client *suivant;

	Client()
	{
		messages = new LinkedList<Message>();
	}
	~Client()
	{
		//delete messages; //Tought that it would be a good idea, but it looks like the destructor is called when we attach the message to the client (around the end of Ouvrir()). Commenting this line may cause memory leak, but at least it work 
	}
};
