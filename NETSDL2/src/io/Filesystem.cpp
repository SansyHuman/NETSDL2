#include "../../include/io/Filesystem.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::IO;
using namespace NETSDL2::Internal;

Result<System::String^, None^> NETSDL2::IO::Filesystem::GetBasePath()
{
	char* result = __nullptr;

	try
	{
		result = SDL_GetBasePath();
		if(result == __nullptr)
		{
			return Result<System::String^, None^>::MakeFailure(None::Value);
		}

		System::String^ path = StringMarshal::UTF8NativeToManaged(result);

		return path;
	}
	finally
	{
		if(result != __nullptr)
		{
			SDL_free(result);
		}
	}
}

Result<System::String^, None^> NETSDL2::IO::Filesystem::GetPrefPath(System::String^ org, System::String^ app)
{
	StringMarshal context;

	char* result = __nullptr;

	try
	{
		result = SDL_GetPrefPath(context.ManagedToUTF8Native(org), context.ManagedToUTF8Native(app));
		if(result == __nullptr)
		{
			return Result<System::String^, None^>::MakeFailure(None::Value);
		}

		System::String^ path = StringMarshal::UTF8NativeToManaged(result);

		return path;
	}
	finally
	{
		if(result != __nullptr)
		{
			SDL_free(result);
		}
	}
}
