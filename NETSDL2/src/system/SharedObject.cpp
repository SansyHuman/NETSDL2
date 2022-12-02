#include "../../include/system/SharedObject.h"

#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;

NETSDL2::Systems::SharedObject::SharedObject(System::String^ sofile)
{
	StringMarshal context;

	object = SDL_LoadObject(context.ManagedToUTF8Native(sofile));
	if(object == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Systems::SharedObject::~SharedObject()
{
	this->!SharedObject();
}

NETSDL2::Systems::SharedObject::!SharedObject()
{
	SDL_UnloadObject(object);
	object = __nullptr;
}

Result<System::IntPtr, None^> NETSDL2::Systems::SharedObject::LoadFunction(System::String^ name)
{
	StringMarshal context;

	void* result = SDL_LoadFunction(object, context.ManagedToUTF8Native(name));
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}
