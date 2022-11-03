#include "../../include/core/Version.h"

#include <msclr/marshal.h>
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace msclr::interop;

using namespace NETSDL2::Core;

System::String^ Version::Revision::get()
{
	const char* rev = SDL_GetRevision();

	return StringMarshal::UTF8NativeToManaged(rev);
}

SDLVersion Version::LibraryVersion::get()
{
	SDLVersion version = {};
	SDL_GetVersion((SDL_version*)&version);
	return version;
}

SDLVersion Version::CompiledVersion::get()
{
	SDLVersion version = {};
	SDL_VERSION((SDL_version*)&version);

	return version;
}
