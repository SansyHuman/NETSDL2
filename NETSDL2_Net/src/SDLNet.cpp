#include "../include/SDLNet.h"

using namespace NETSDL2::Net;
using namespace NETSDL2::Systems;

SDLVersion SDLNet::Version::get()
{
	SDL_version version;
	SDL_NET_VERSION(&version);
	return *((SDLVersion*)&version);
}

SDLVersion SDLNet::LinkedVersion::get()
{
	const SDL_version* version = SDLNet_Linked_Version();
	return *((const SDLVersion*)version);
}

Result<None^, None^> NETSDL2::Net::SDLNet::Init()
{
	int result = SDLNet_Init();
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

void NETSDL2::Net::SDLNet::Quit()
{
	SDLNet_Quit();
}

bool NETSDL2::Net::SDLNet::SocketReady(IGenericSocket^ sock)
{
	return SDLNet_SocketReady(sock->NativeSocket) != 0;
}

void NETSDL2::Net::SDLNet::Write16(Uint16 value, System::IntPtr areap)
{
	*(Uint16*)areap.ToPointer() = Endian::SwapBE16(value);
}

void NETSDL2::Net::SDLNet::Write32(Uint32 value, System::IntPtr areap)
{
	*(Uint32*)areap.ToPointer() = Endian::SwapBE32(value);
}

Uint16 NETSDL2::Net::SDLNet::Read16(System::IntPtr areap)
{
	return Endian::SwapBE16(*(Uint16*)areap.ToPointer());
}

Uint32 NETSDL2::Net::SDLNet::Read32(System::IntPtr areap)
{
	return Endian::SwapBE32(*(Uint32*)areap.ToPointer());
}
