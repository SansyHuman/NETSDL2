#include "../include/TCPSocket.h"

using namespace NETSDL2::Net;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

NETSDL2::Net::TCPSocket::TCPSocket(TCPsocket socket)
	: socket(socket)
{
	
}

SDLNet_GenericSocket TCPSocket::NativeSocket::get()
{
	return (SDLNet_GenericSocket)socket;
}

NETSDL2::Net::TCPSocket::TCPSocket(IPAddress ip)
{
	socket = SDLNet_TCP_Open((IPaddress*)&ip);
	if(socket == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Net::TCPSocket::~TCPSocket()
{
	this->!TCPSocket();
}

NETSDL2::Net::TCPSocket::!TCPSocket()
{
	Close();
}

Result<TCPSocket^, None^> NETSDL2::Net::TCPSocket::Accept()
{
	TCPsocket result = SDLNet_TCP_Accept(socket);
	if(result == __nullptr)
	{
		return Result<TCPSocket^, None^>::MakeFailure(None::Value);
	}

	return gcnew TCPSocket(result);
}

Result<IPAddress, None^> NETSDL2::Net::TCPSocket::GetPeerAddress()
{
	IPaddress* addr = SDLNet_TCP_GetPeerAddress(socket);
	if(addr == __nullptr)
	{
		return Result<IPAddress, None^>::MakeFailure(None::Value);
	}

	return *((IPAddress*)addr);
}

Result<int, None^> NETSDL2::Net::TCPSocket::Send(System::IntPtr data, int len)
{
	int result = SDLNet_TCP_Send(socket, data.ToPointer(), len);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Net::TCPSocket::Recv(System::IntPtr data, int maxlen)
{
	int result = SDLNet_TCP_Recv(socket, data.ToPointer(), maxlen);
	if(result <= 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Net::TCPSocket::Close()
{
	SDLNet_TCP_Close(socket);
	socket = __nullptr;
}
