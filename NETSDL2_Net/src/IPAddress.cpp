#include "../include/IPAddress.h"

using namespace NETSDL2::Net;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Systems;

NETSDL2::Net::IPAddress::IPAddress(Uint32 host, Uint16 port)
{
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	Host = Endian::Swap32(host);
	Port = Endian::Swap16(port);
#else
	Host = host;
	Port = port;
#endif
}

NETSDL2::Net::IPAddress::IPAddress(Uint8 h1, Uint8 h2, Uint8 h3, Uint8 h4, Uint16 port)
{
	Host = h1 | (h2 << 8) | (h3 << 16) | (h4 << 24);
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	Port = Endian::Swap16(port);
#else
	Port = port;
#endif
}

NETSDL2::Net::IPAddress::IPAddress(System::String^ host, Uint16 port)
{
	StringMarshal context;

	IPaddress addr = {};
	int result = SDLNet_ResolveHost(&addr, host == nullptr ? __nullptr : context.ManagedToUTF8Native(host), port);
	if(result < 0)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	Host = addr.host;
	Port = addr.port;
}

System::String^ NETSDL2::Net::IPAddress::ToString()
{
	Uint8 h1 = 0xFFU & Host;
	Uint8 h2 = 0xFFU & (Host >> 8);
	Uint8 h3 = 0xFFU & (Host >> 16);
	Uint8 h4 = 0xFFU & (Host >> 24);

	Uint16 port = Port;
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
	port = Endian::Swap16(port);
#endif

	return System::String::Format("{0}.{1}.{2}.{3}:{4}", h1, h2, h3, h4, port);
}

Result<System::String^, NETSDL2::Core::None^> NETSDL2::Net::IPAddress::ResolveIP()
{
	IPaddress addr = {};
	addr.host = Host;
	addr.port = Port;
	const char* result = SDLNet_ResolveIP(&addr);
	if(result == __nullptr)
	{
		return Result<System::String^, NETSDL2::Core::None^>::MakeFailure(NETSDL2::Core::None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

int NETSDL2::Net::IPAddress::GetLocalAddresses(array<IPAddress>^ addresses, int offset)
{
	if(addresses->Length == 0)
	{
		return 0;
	}

	if(offset < 0 || offset >= addresses->Length)
	{
		return 0;
	}

	int maxcount = addresses->Length - offset;
	pin_ptr<IPAddress> pAddr = &addresses[offset];
	IPaddress* pAddrN = (IPaddress*)pAddr;
	int result = SDLNet_GetLocalAddresses((IPaddress*)pAddr, maxcount);
	pAddr = nullptr;

	return result;
}
