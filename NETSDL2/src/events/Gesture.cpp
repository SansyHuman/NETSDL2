#include "../../include/events/Gesture.h"
#include "../../include/io/RWops.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Core;

Result<int, int> NETSDL2::Events::Gesture::LoadDollarTemplates(SDL_TouchID touchId, RWops^ src)
{
	int result = SDL_LoadDollarTemplates(touchId, src->NativeOps);
	if(result <= 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<None^, None^> NETSDL2::Events::Gesture::RecordGesture(SDL_TouchID touchId)
{
	int result = SDL_RecordGesture(touchId);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<int, None^> NETSDL2::Events::Gesture::SaveAllDollarTemplates(RWops^ dst)
{
	int result = SDL_SaveAllDollarTemplates(dst->NativeOps);
	if(result == 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Events::Gesture::SaveDollarTemplate(SDL_GestureID gestureId, RWops^ dst)
{
	int result = SDL_SaveDollarTemplate(gestureId, dst->NativeOps);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
