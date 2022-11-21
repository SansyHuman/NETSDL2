#include "../../include/events/Touch.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Internal;

int Touch::NumTouchDevices::get()
{
	return SDL_GetNumTouchDevices();
}

Result<int, None^> NETSDL2::Events::Touch::GetNumTouchFingers(SDL_TouchID touchID)
{
	int result = SDL_GetNumTouchFingers(touchID);
	if(result == 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<SDL_TouchID, None^> NETSDL2::Events::Touch::GetTouchDevice(int index)
{
	SDL_TouchID result = SDL_GetTouchDevice(index);
	if(result == 0)
	{
		return Result<SDL_TouchID, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<System::String^, None^> NETSDL2::Events::Touch::GetTouchName(int index)
{
	const char* name = SDL_GetTouchName(index);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

TouchDeviceType NETSDL2::Events::Touch::GetTouchDeviceType(SDL_TouchID touchID)
{
	return (TouchDeviceType)SDL_GetTouchDeviceType(touchID);
}

Result<Finger, None^> NETSDL2::Events::Touch::GetTouchFinger(SDL_TouchID touchID, int index)
{
	SDL_Finger* result = SDL_GetTouchFinger(touchID, index);
	if(result == __nullptr)
	{
		return Result<Finger, None^>::MakeFailure(None::Value);
	}

	return *((Finger*)result);
}
