#include "HorizonClient.h"
#include <iostream>

using namespace Horizon::Client::Networking;

int main()
{

	SocketClientImpl<HorizonClient> client;
	try 
	{
		if (client.StartClient(nullptr, "10.0.48.101", "2000", AF_INET, SOCK_STREAM))
			std::cout << "Connected";
	}
	catch (...) 
	{
		
	}
	system("pause");
	return 0;
}