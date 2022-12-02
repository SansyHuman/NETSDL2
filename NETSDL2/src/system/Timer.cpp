#include "../../include/system/Timer.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Core;

NETSDL2::Systems::Timer::Timer(Uint32 interval, TimerCallback^ callback, System::IntPtr param)
{
	handle = GCHandle::Alloc(callback);
	SDL_TimerCallback cb = (SDL_TimerCallback)Marshal::GetFunctionPointerForDelegate(callback).ToPointer();

	id = SDL_AddTimer(interval, cb, param.ToPointer());
	if(id == 0)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Systems::Timer::~Timer()
{
	this->!Timer();
}

NETSDL2::Systems::Timer::!Timer()
{
	handle.Free();
	SDL_RemoveTimer(id);
	id = 0;
}

void NETSDL2::Systems::Timer::Delay(Uint32 ms)
{
	SDL_Delay(ms);
}

Uint64 Timer::PerformanceCounter::get()
{
	return SDL_GetPerformanceCounter();
}

Uint64 Timer::PerformanceFrequency::get()
{
	return SDL_GetPerformanceFrequency();
}

Uint32 Timer::Ticks::get()
{
	return SDL_GetTicks();
}

Uint64 Timer::Ticks64::get()
{
	return SDL_GetTicks64();
}
