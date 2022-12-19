#include "../include/UDPSocket.h"

using namespace NETSDL2::Net;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

NETSDL2::Net::UDPSocket::UDPSocket(UDPsocket socket)
	: socket(socket)
{
	
}

SDLNet_GenericSocket UDPSocket::NativeSocket::get()
{
	return (SDLNet_GenericSocket)socket;
}

NETSDL2::Net::UDPSocket::UDPSocket(Uint16 port)
{
	socket = SDLNet_UDP_Open(port);
	if(socket == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Net::UDPSocket::~UDPSocket()
{
	this->!UDPSocket();
}

NETSDL2::Net::UDPSocket::!UDPSocket()
{
	Close();
}

void UDPSocket::PacketLoss::set(int value)
{
	SDLNet_UDP_SetPacketLoss(socket, value);
}

Result<int, None^> NETSDL2::Net::UDPSocket::Bind(int channel, IPAddress address)
{
	int result = SDLNet_UDP_Bind(socket, channel, (IPaddress*)&address);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Net::UDPSocket::Unbind(int channel)
{
	SDLNet_UDP_Unbind(socket, channel);
}

Result<IPAddress, None^> NETSDL2::Net::UDPSocket::GetPeerAddress(int channel)
{
	IPaddress* result = SDLNet_UDP_GetPeerAddress(socket, channel);
	if(result == __nullptr)
	{
		return Result<IPAddress, None^>::MakeFailure(None::Value);
	}

	return *((IPAddress*)result);
}

int NETSDL2::Net::UDPSocket::SendV(UDPPacket** packets, int npackets)
{
	return SDLNet_UDP_SendV(socket, (UDPpacket**)packets, npackets);
}

Result<None^, None^> NETSDL2::Net::UDPSocket::Send(int channel, UDPPacket* packet)
{
	int result = SDLNet_UDP_Send(socket, channel, (UDPpacket*)packet);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<int, None^> NETSDL2::Net::UDPSocket::RecvV(UDPPacket** packets)
{
	int result = SDLNet_UDP_RecvV(socket, (UDPpacket**)packets);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Net::UDPSocket::Recv(UDPPacket* packet)
{
	int result = SDLNet_UDP_Recv(socket, (UDPpacket*)packet);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Net::UDPSocket::Close()
{
	SDLNet_UDP_Close(socket);
	socket = __nullptr;
}
