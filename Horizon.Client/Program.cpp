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


class ClientPacket {
public:
	string id;
	string ping;
	string ip;
	string compName;
	string userName;
	string privilege;
	string os;
	string activity;
	string usage;

	ClientPacket(string pid, string pping, string pip, string pcompName, string puserName, string pprivilege, string pos, string pactivity, string pusage)
		: id(pid), ping(pping), ip(pip), compName(pcompName), userName(puserName), privilege(pprivilege), os(pos), activity(pactivity), usage(pusage) { }

	MSGPACK_DEFINE(id, ping, ip, compName, userName, privilege, os, activity, usage);

	size_t Size() const {
		return id.size() + ping.size() + ip.size() + compName.size() + userName.size() + privilege.size() + os.size() + activity.size() + usage.size();
	}

	void PrintSize() const
	{
		/*cout << id.size() << endl;
		cout << ping.size() << endl;
		cout << ip.size() << endl;
		cout << compName.size() << endl;
		cout << userName.size() << endl;
		cout << privilege.size() << endl;
		cout << os.size() << endl;
		cout << activity.size() << endl;
		cout << usage.size() << endl;*/
		cout << "----Total----" << endl;
		cout << id.size() + ping.size() + ip.size() + compName.size() + userName.size() + privilege.size() + os.size() + activity.size() + usage.size() << endl;
	}
};


char* Ser(const string& packetName, const char* packet, const size_t packetSize)
{
	const auto packetNameSize = packetName.size();

	vector<char> buffer;
	auto bytesWritten = 0;
	buffer.resize((2 * sizeof(int)) + packetNameSize + packetSize);
	std::memcpy(buffer.data() + bytesWritten, &packetNameSize, sizeof(int));
	bytesWritten += sizeof(int);
	std::memcpy(buffer.data() + bytesWritten, &packetSize, sizeof(int));
	bytesWritten += sizeof(int);
	std::memcpy(buffer.data() + bytesWritten, packetName.c_str(), packetNameSize);
	bytesWritten += packetNameSize;
	std::memcpy(buffer.data() + bytesWritten, packet, packetSize);
	return buffer.data();
}


class Serializer
{
	int packetNameSize_;
	vector<char> buffer_;
	size_t bytesWritten_ = 0;
public:
	Serializer(const string& packetName, const char* packet, const size_t packetSize)
	{
		this->packetNameSize_ = packetName.size();
		buffer_.resize((2 * sizeof(int)) + packetNameSize_ + packetSize);
		std::memcpy(buffer_.data() + bytesWritten_, &packetNameSize_, sizeof(int));
		bytesWritten_ += sizeof(int);
		std::memcpy(buffer_.data() + bytesWritten_, &packetSize, sizeof(int));
		bytesWritten_ += sizeof(int);
		std::memcpy(buffer_.data() + bytesWritten_, packetName.c_str(), packetNameSize_);
		bytesWritten_ += packetNameSize_;
		std::memcpy(buffer_.data() + bytesWritten_, packet, packetSize);
		bytesWritten_ += packetSize;
	}

	char* Data()
	{
		return buffer_.data();
	}

	[[nodiscard]] size_t Size() const
	{
		return bytesWritten_;
	}
};


void Serialize() {
	const string packetName = "ClientPacket";
	const ClientPacket packet("guid", "24ms", "127.0.0.1", "DELL-PC", "rkh4c", "Admin", "Windows 10 Pro", "Google Chrome", "84%");
	msgpack::sbuffer buf, out;
	pack(buf, packet);
	const auto serialized = new Serializer("ClientPacket", buf.data(), buf.size());
	ofstream file("C:\\ProgramData\\Ser.bin", ofstream::binary);
	file.write(serialized->Data(), serialized->Size());
	file.close();
	delete(serialized);
}
void Initialize() {

	SocketClientImpl<HorizonClient> client;
	//HorizonClient handler;
	if (client.StartClient(nullptr, "127.0.0.1", "1997", AF_INET, SOCK_STREAM)) {
		cout << "Connected\n";
		const string packetName = "ClientPacket";
		const ClientPacket packet("guid", "24ms", "127.0.0.1", "DELL-PC", "rkh4c", "Admin", "Windows 10 Pro", "Google Chrome", "84%");
		//const ChatPacket packet(18, "Raj", "Hello MessagePack", "Programmer");
		msgpack::sbuffer buf, out;
		pack(buf, packet);
		const auto serialized = new Serializer(packetName, buf.data(), buf.size());
		client.Write(reinterpret_cast<const LPBYTE>(serialized->Data()), serialized->Size());
		delete(serialized);
		while (true)
		{

		}
	}
	else
		cout << "Connection Failed\n";
}

int main()
{
	LoadApis();
	try
	{
		Sleep(1000);
		//Initialize();
		//Serialize();
		while (true) {
			cout << "Trying to connect\n";
			Initialize();
			Sleep(100);
		}
	}
	catch (...)
	{

	}
}