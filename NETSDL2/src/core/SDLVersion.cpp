#include "../../include/core/SDLVersion.h"

using namespace NETSDL2::Core;

NETSDL2::Core::SDLVersion::SDLVersion(Uint8 major, Uint8 minor, Uint8 patch)
	: Major(major), Minor(minor), Patch(patch)
{
	
}

System::String^ NETSDL2::Core::SDLVersion::ToString()
{
	return System::String::Format("{0}.{1}.{2}", Major, Minor, Patch);
}
