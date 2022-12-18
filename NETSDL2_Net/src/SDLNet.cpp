#include "../include/SDLNet.h"

using namespace NETSDL2::Net;

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
