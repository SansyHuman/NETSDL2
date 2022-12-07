#include "../../include/core/GUID.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

NETSDL2::Core::GUID::GUID(System::String^ guid)
{
	StringMarshal context;
	SDL_GUID id = SDL_GUIDFromString(context.ManagedToASCIINative(guid));

	pin_ptr<GUID> pGuid = &*this;
	*((SDL_GUID*)pGuid) = id;
	pGuid = nullptr;
}

System::String^ NETSDL2::Core::GUID::ToString()
{
	char psz[40] = { 0 };
	pin_ptr<GUID> pGuid = &*this;

	SDL_GUIDToString(*((SDL_GUID*)pGuid), psz, 40);
	pGuid = nullptr;

	return StringMarshal::ASCIINativeToManaged(psz);
}
