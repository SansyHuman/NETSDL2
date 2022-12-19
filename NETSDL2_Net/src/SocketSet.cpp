#include "../include/SocketSet.h"

using namespace NETSDL2::Net;

NETSDL2::Net::SocketSet::SocketSet(int maxsockets)
{
	set = SDLNet_AllocSocketSet(maxsockets);
	if(set == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Net::SocketSet::~SocketSet()
{
	this->!SocketSet();
}

NETSDL2::Net::SocketSet::!SocketSet()
{
	SDLNet_FreeSocketSet(set);
	set = __nullptr;
}

Result<int, None^> NETSDL2::Net::SocketSet::AddSocket(IGenericSocket^ sock)
{
	int result = SDLNet_AddSocket(set, sock == nullptr ? __nullptr : sock->NativeSocket);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Net::SocketSet::DelSocket(IGenericSocket^ sock)
{
	int result = SDLNet_DelSocket(set, sock == nullptr ? __nullptr : sock->NativeSocket);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Net::SocketSet::CheckSockets(Uint32 timeout)
{
	int result = SDLNet_CheckSockets(set, timeout);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}
