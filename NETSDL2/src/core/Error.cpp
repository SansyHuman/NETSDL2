#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;

void NETSDL2::Core::Error::ClearError()
{
	SDL_ClearError();
}

System::String^ NETSDL2::Core::Error::GetError()
{
	const char* message = SDL_GetError();
	return StringMarshal::UTF8NativeToManaged(message);
}

char* NETSDL2::Core::Error::GetErrorMsg(char* errstr, int maxlen)
{
	return SDL_GetErrorMsg(errstr, maxlen);
}

void NETSDL2::Core::Error::SetError(System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_SetError(context.ManagedToUTF8Native(message));
}
