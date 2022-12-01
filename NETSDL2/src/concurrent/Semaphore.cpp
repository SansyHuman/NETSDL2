#include "../../include/concurrent/Semaphore.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Concurrent;
using namespace NETSDL2::Core;

NETSDL2::Concurrent::Semaphore::Semaphore(Uint32 initialValue)
{
	semaphore = SDL_CreateSemaphore(initialValue);
	if(semaphore == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Concurrent::Semaphore::~Semaphore()
{
	this->!Semaphore();
}

NETSDL2::Concurrent::Semaphore::!Semaphore()
{
	SDL_DestroySemaphore(semaphore);
	semaphore = __nullptr;
}

Result<None^, int> NETSDL2::Concurrent::Semaphore::Post()
{
	int result = SDL_SemPost(semaphore);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<int, int> NETSDL2::Concurrent::Semaphore::TryWait()
{
	int result = SDL_SemTryWait(semaphore);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Uint32 Semaphore::Value::get()
{
	return SDL_SemValue(semaphore);
}

Result<None^, int> NETSDL2::Concurrent::Semaphore::Wait()
{
	int result = SDL_SemWait(semaphore);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<int, int> NETSDL2::Concurrent::Semaphore::WaitTimeout(Uint32 ms)
{
	int result = SDL_SemWaitTimeout(semaphore, ms);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}
