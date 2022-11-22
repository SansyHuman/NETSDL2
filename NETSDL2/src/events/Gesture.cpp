#include "../../include/events/Gesture.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Core;

Result<None^, None^> NETSDL2::Events::Gesture::RecordGesture(SDL_TouchID touchId)
{
	int result = SDL_RecordGesture(touchId);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
