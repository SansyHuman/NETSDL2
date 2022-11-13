#include "../../include/core/Hint.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

NETSDL2::Core::SDLHint::SDLHint(System::String^ name)
	: name(name)
{
	
}

System::String^ NETSDL2::Core::SDLHint::ToString()
{
	return name;
}

void NETSDL2::Core::Hint::ClearHints()
{
	SDL_ClearHints();
}

Result<System::String^, None^> NETSDL2::Core::Hint::GetHint(SDLHint name)
{
	StringMarshal context;

	const char* value = SDL_GetHint(context.ManagedToUTF8Native(name.name));
	if(value == nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(value);
}

bool NETSDL2::Core::Hint::GetHintBoolean(SDLHint name, bool defaultValue)
{
	StringMarshal context;

	return SDL_GetHintBoolean(context.ManagedToUTF8Native(name.name), defaultValue ? SDL_TRUE : SDL_FALSE) == SDL_TRUE;
}

bool NETSDL2::Core::Hint::ResetHint(SDLHint name)
{
	StringMarshal context;

	return SDL_ResetHint(context.ManagedToUTF8Native(name.name)) == SDL_TRUE;
}

bool NETSDL2::Core::Hint::SetHint(SDLHint name, System::String^ value)
{
	StringMarshal context;

	return SDL_SetHint(context.ManagedToUTF8Native(name.name), context.ManagedToUTF8Native(value)) == SDL_TRUE;
}

bool NETSDL2::Core::Hint::SetHintWithPriority(SDLHint name, System::String^ value, HintPriority priority)
{
	StringMarshal context;

	return SDL_SetHintWithPriority(context.ManagedToUTF8Native(name.name), context.ManagedToUTF8Native(value), (SDL_HintPriority)priority) == SDL_TRUE;
}
