#include "../../include/system/Platform.h"

#include "../../include/internal/StringMarshal.h"
#include "../../include/core/Error.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;

System::String^ NETSDL2::Systems::Platform::GetPlatform()
{
	return StringMarshal::UTF8NativeToManaged(SDL_GetPlatform());
}
