#pragma once
#include "Networking/SocketClientImpl.h"
#include <wtypes.h>

namespace Horizon::Client::Networking
{
	class HorizonClient final : public ISocketClientHandler
	{
	public:
		void OnDataReceived(CSocketHandle*, const BYTE*, DWORD, const SockAddrIn&) override;

	};
}
