#include "../../include/events/Events.h"

using namespace NETSDL2::Events;

Result<None^, None^> NETSDL2::Events::Events::PollEvent(Event% event)
{
	pin_ptr<Event> pEvent = &event;
	int result = SDL_PollEvent((SDL_Event*)pEvent);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	pEvent = nullptr;
	return None::Value;
}

bool Events::EventExist::get()
{
	return SDL_PollEvent(__nullptr) == 1;
}
