#include "Networking/HorizonClient.h"
#include <iostream>
#include <ws2def.h>
#include "Api/Api.h"

using namespace Horizon::Client::Networking;
using namespace Horizon::Client::Api;

int main()
{
	LoadApis();
	
	SocketClientImpl<HorizonClient> client;
	try 
	{
		if (client.StartClient(nullptr, "127.0.0.1", "1997", AF_INET, SOCK_STREAM)) {
			std::cout << "Connected";
			const std::string str = "Hello";
			const auto pByte = new BYTE[str.size() + 1];
			// ReSharper disable once CppCStyleCast
			memcpy(pByte, (void*)(str.c_str()), str.size());
			client.Write(pByte, 5);
		}
		else {
			std::cout << "Connection Failed";
		}
	}
	catch (...) 
	{
		
	}
	system("pause");
	return 0;
}