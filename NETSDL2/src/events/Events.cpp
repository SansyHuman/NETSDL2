#include "../../include/events/Events.h"

using namespace NETSDL2::Events;

void NETSDL2::Events::Events::AddEventWatch(FunctionPointer<EventFilter^>^ filter, System::IntPtr userdata)
{
	SDL_AddEventWatch((SDL_EventFilter)filter->Pointer.ToPointer(), userdata.ToPointer());
}

void NETSDL2::Events::Events::DelEventWatch(FunctionPointer<EventFilter^>^ filter, System::IntPtr userdata)
{
	SDL_DelEventWatch((SDL_EventFilter)filter->Pointer.ToPointer(), userdata.ToPointer());
}

EventState NETSDL2::Events::Events::SetEventState(EventType type, EventState state)
{
	return (EventState)SDL_EventState((Uint32)type, (int)state);
}

void NETSDL2::Events::Events::FilterEvents(EventFilter^ filter, System::IntPtr userdata)
{
	GCHandle handle = GCHandle::Alloc(filter);
	System::IntPtr fp = Marshal::GetFunctionPointerForDelegate(filter);

	SDL_FilterEvents((SDL_EventFilter)fp.ToPointer(), userdata.ToPointer());

	handle.Free();
}

void NETSDL2::Events::Events::FlushEvent(EventType type)
{
	SDL_FlushEvent((Uint32)type);
}

void NETSDL2::Events::Events::FlushEvents(EventType minType, EventType maxType)
{
	SDL_FlushEvents((Uint32)minType, (Uint32)maxType);
}

bool NETSDL2::Events::Events::GetEventFilter(System::IntPtr% filter, System::IntPtr% userdata)
{
	SDL_EventFilter fp = __nullptr;
	void* ud = __nullptr;
	SDL_bool result = SDL_GetEventFilter(&fp, &ud);
	if(result == SDL_TRUE)
	{
		filter = System::IntPtr(fp);
		userdata = System::IntPtr(ud);
	}
	else
	{
		filter = System::IntPtr::Zero;
		userdata = System::IntPtr::Zero;
	}

	return result == SDL_TRUE;
}

EventState NETSDL2::Events::Events::GetEventState(EventType type)
{
	return (EventState)SDL_GetEventState((Uint32)type);
}

bool NETSDL2::Events::Events::HasEvent(EventType type)
{
	return SDL_HasEvent((Uint32)type) == SDL_TRUE;
}

bool NETSDL2::Events::Events::HasEvents(EventType minType, EventType maxType)
{
	return SDL_HasEvents((Uint32)minType, (Uint32)maxType) == SDL_TRUE;
}

Result<int, int> NETSDL2::Events::Events::PeepEvents(array<Event>^ events, EventAction action, EventType minType, EventType maxType)
{
	if(events->Length == 0)
	{
		int result = SDL_PeepEvents(__nullptr, 0, (SDL_eventaction)action, (Uint32)minType, (Uint32)maxType);
		if(result < 0)
		{
			return Result<int, int>::MakeFailure(result);
		}

		return result;
	}

	pin_ptr<Event> pEvents = &events[0];
	int result = SDL_PeepEvents((SDL_Event*)pEvents, events->Length, (SDL_eventaction)action, (Uint32)minType, (Uint32)maxType);
	pEvents = nullptr;

	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

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

void NETSDL2::Events::Events::PumpEvents()
{
	SDL_PumpEvents();
}

Result<int, int> NETSDL2::Events::Events::PushEvent(Event% event)
{
	pin_ptr<Event> pEvent = &event;
	int result = SDL_PushEvent((SDL_Event*)pEvent);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

bool Events::QuitRequested::get()
{
	return SDL_QuitRequested() == SDL_TRUE;
}

bool Events::EventExist::get()
{
	return SDL_PollEvent(__nullptr) == 1;
}

Result<EventType, None^> NETSDL2::Events::Events::RegisterEvents(int numevents)
{
	Uint32 result = SDL_RegisterEvents(numevents);
	if(result == ((Uint32)-1))
	{
		return Result<EventType, None^>::MakeFailure(None::Value);
	}

	return (EventType)result;
}

void NETSDL2::Events::Events::SetEventFilter(FunctionPointer<EventFilter^>^ filter, System::IntPtr userdata)
{
	SDL_SetEventFilter((SDL_EventFilter)filter->Pointer.ToPointer(), userdata.ToPointer());
}

Result<None^, None^> NETSDL2::Events::Events::WaitEvent(Event% event)
{
	pin_ptr<Event> pEvent = &event;
	int result = SDL_WaitEvent((SDL_Event*)pEvent);
	pEvent = nullptr;
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Events::WaitEvent()
{
	int result = SDL_WaitEvent(__nullptr);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Events::WaitEventTimeout(Event% event, int timeout)
{
	pin_ptr<Event> pEvent = &event;
	int result = SDL_WaitEventTimeout((SDL_Event*)pEvent, timeout);
	pEvent = nullptr;
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Events::WaitEventTimeout(int timeout)
{
	int result = SDL_WaitEventTimeout(__nullptr, timeout);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
