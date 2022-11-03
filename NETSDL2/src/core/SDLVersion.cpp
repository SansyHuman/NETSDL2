#include "../../include/core/SDLVersion.h"

using namespace NETSDL2::Core;

System::String^ NETSDL2::Core::SDLVersion::ToString()
{
	return System::String::Format("{0}.{1}.{2}", Major, Minor, Patch);
}
