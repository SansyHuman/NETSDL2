#include "../../include/concurrent/Mutex.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Concurrent;
using namespace NETSDL2::Core;

SDL_mutex* Mutex::NativeMutex::get()
{
	return mutex;
}

NETSDL2::Concurrent::Mutex::Mutex()
{
	mutex = SDL_CreateMutex();
	if(mutex == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Concurrent::Mutex::~Mutex()
{
	this->!Mutex();
}

NETSDL2::Concurrent::Mutex::!Mutex()
{
	SDL_DestroyMutex(mutex);
	mutex = __nullptr;
}

Result<None^, None^> NETSDL2::Concurrent::Mutex::Lock()
{
	int result = SDL_LockMutex(mutex);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<int, None^> NETSDL2::Concurrent::Mutex::TryLock()
{
	int result = SDL_TryLockMutex(mutex);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Concurrent::Mutex::Unlock()
{
	int result = SDL_UnlockMutex(mutex);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
