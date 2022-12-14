#include "../../include/system/Misc.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Internal;

Result<None^, None^> NETSDL2::Systems::Misc::OpenURL(System::String^ url)
{
	StringMarshal context;
	int result = SDL_OpenURL(context.ManagedToUTF8Native(url));
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
