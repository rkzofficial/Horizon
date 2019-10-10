#pragma once
#include "SocketClientImpl.h"

namespace Horizon::Client::Networking
{
	class HorizonClient : public ISocketClientHandler
	{
	public:
		void OnConnectionDropped(CSocketHandle*) override;
		void OnDataReceived(CSocketHandle*, const BYTE*, DWORD, const SockAddrIn&) override;
		

	};
}
