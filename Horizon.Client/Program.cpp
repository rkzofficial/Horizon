#include "Networking/HorizonClient.h"
#include <iostream>
#include <ws2def.h>
#include "Api/Api.h"
#include <msgpack.hpp>
#include <charconv>
#include <fstream>

using namespace std;
using namespace Horizon::Client::Networking;
using namespace Horizon::Client::Api;


class ChatPacket {
public:
	int Age;
	string Name;
	string Message;
	string Designation;
	ChatPacket() {  }
	ChatPacket(int a1, string s1, string s2, string s3) : Age(a1), Name(s1), Message(s2), Designation(s3) {  }
	MSGPACK_DEFINE(Age, Name, Message, Designation);
	size_t Size() const {
		return sizeof(Age) + Name.size() + Message.size() + Designation.size();
	}
};

void Serialize() {
	const string packetName = "ChatPacket";
	const ChatPacket packet(18, "MSGPACK", "Hello MessagePack", "Programmer");
	auto packetNameSize = packetName.size();
	auto packetSize = packet.Size() + 1;
	msgpack::sbuffer buf;
	buf.write(reinterpret_cast<char*>(&packetNameSize), 4);
	buf.write(reinterpret_cast<char*>(&packetSize), 4);
	buf.write(packetName.c_str(), 10);
	pack(buf, packet);	
	ofstream file("MsgPackCPP.bin", ofstream::binary);
	file.write(buf.data(), buf.size());
	file.close();
}
void Initialize() {
	
	SocketClientImpl<HorizonClient> client;
	//HorizonClient handler;
	if(client.StartClient(nullptr, "116.72.198.123", "1997", AF_INET, SOCK_STREAM)) {
		cout << "Connected";
		const string packetName = "ChatPacket";
		const ChatPacket packet(18, "MSGPACK", "Hello MessagePack", "Programmer");
		auto packetNameSize = packetName.size();
		auto packetSize = packet.Size() + 1;
		msgpack::sbuffer buf;
		buf.write(reinterpret_cast<char*>(&packetNameSize), 4);
		buf.write(reinterpret_cast<char*>(&packetSize), 4);
		buf.write(packetName.c_str(), 10);
		pack(buf, packet);

		//string msg = "Hello Universal Windows Platform";
		//client.Write(reinterpret_cast<const LPBYTE>(&msg), msg.size());
		client.Write(reinterpret_cast<const LPBYTE>(buf.data()), buf.size());
	}
	else
		cout << "Connection Failed\n";
}

int main()
{
	LoadApis();
	try 
	{
		Sleep(3000);
		Initialize();
		/*while(true) {
			cout << "Trying to connect\n";
			Initialize();
			Sleep(100);
		}*/
	}
	catch (...) 
	{
		
	}
}

