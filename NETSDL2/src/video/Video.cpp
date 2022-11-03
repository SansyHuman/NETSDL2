#include "../../include/video/Video.h"
#include <msclr/marshal.h>

#include "../../include/internal/StringMarshal.h"

#include <vector>

using namespace NETSDL2::Internal;

using namespace msclr::interop;

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

Result<None^, int> NETSDL2::Video::Video::Init(System::String^ driverName)
{
	StringMarshal context;
	int result = SDL_VideoInit(context.ManagedToUTF8Native(driverName));
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Video::Quit()
{
	SDL_VideoQuit();
}
