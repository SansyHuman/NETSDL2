#include "../../include/concurrent/Cond.h"

#include "../../include/concurrent/Mutex.h"
#include "../../include/core/Error.h"

using namespace NETSDL2::Concurrent;
using namespace NETSDL2::Core;

NETSDL2::Concurrent::Cond::Cond()
{
	cond = SDL_CreateCond();
	if(cond == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Concurrent::Cond::~Cond()
{
	this->!Cond();
}

NETSDL2::Concurrent::Cond::!Cond()
{
	SDL_DestroyCond(cond);
	cond = __nullptr;
}

Result<None^, int> NETSDL2::Concurrent::Cond::Broadcast()
{
	int result = SDL_CondBroadcast(cond);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Concurrent::Cond::Signal()
{
	int result = SDL_CondSignal(cond);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Concurrent::Cond::Wait(Mutex^ mutex)
{
	int result = SDL_CondWait(cond, mutex->NativeMutex);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<int, int> NETSDL2::Concurrent::Cond::WaitTimeout(Mutex^ mutex, Uint32 ms)
{
	int result = SDL_CondWaitTimeout(cond, mutex->NativeMutex, ms);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}
