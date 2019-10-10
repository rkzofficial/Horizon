#include "Networking/HorizonClient.h"
#include <iostream>
#include <fstream>
#include <ws2def.h>
#include "Api/Api.h"
#include "Networking/Chat.pb.h"

using namespace std;
using namespace Horizon::Client::Networking;
using namespace Horizon::Client::Api;


void Serialize() {

	ChatPacket object;
	object.set_message("Hello Google Protobuf");
	const auto size = object.ByteSizeLong();
	const auto buffer = new char[size];
	object.SerializeToArray(buffer, size);
	cout << buffer;
	ofstream myfile;
	myfile.open("example.bin");
	myfile << buffer;
	myfile.close();
	delete[] buffer;
}
void Initialize() {
	
	SocketClientImpl<HorizonClient> client;
	if(client.StartClient(nullptr, "127.0.0.1", "1997", AF_INET, SOCK_STREAM)) {
		
		ChatPacket object;
		object.set_message("Hello Google Protobuf");
		const auto size = object.ByteSizeLong();
		const auto buffer = new char[size];
		object.SerializeToArray(buffer, size);

		string msg = "Hello Google Protobuf";
		client.Write((const LPBYTE)msg.c_str(), msg.size());
		
		delete[] buffer;
		
		while(true) {
			Sleep(1000);
		}
	}
	else
		cout << "Connection Failed\n";
}

int main()
{
	LoadApis();
	Serialize();
	try 
	{
		while(true) {
			cout << "Trying to connect\n";
			Initialize();
			Sleep(1000);
		}
	}
	catch (...) 
	{
		
	}
}

