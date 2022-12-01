#include "../../include/concurrent/Thread.h"
#include "../../include/internal/StringMarshal.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Concurrent;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;

NETSDL2::Concurrent::Thread::Thread(ThreadFunction^ fn, System::String^ name, System::IntPtr data)
{
	StringMarshal context;

	fnHandle = GCHandle::Alloc(fn);
	SDL_ThreadFunction func = (SDL_ThreadFunction)Marshal::GetFunctionPointerForDelegate(fn).ToPointer();

	thread = SDL_CreateThread(func, context.ManagedToUTF8Native(name), data.ToPointer());
	if(thread == __nullptr)
	{
		fnHandle.Free();
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Concurrent::Thread::~Thread()
{
	this->!Thread();
}

NETSDL2::Concurrent::Thread::!Thread()
{
	fnHandle.Free();
	thread = __nullptr;
}

void NETSDL2::Concurrent::Thread::Detach()
{
	SDL_DetachThread(thread);
}

SDL_threadID Thread::ThreadID::get()
{
	return SDL_GetThreadID(thread);
}

System::String^ Thread::ThreadName::get()
{
	const char* name = SDL_GetThreadName(thread);
	return StringMarshal::UTF8NativeToManaged(name);
}

Result<None^, int> NETSDL2::Concurrent::Thread::SetThreadPriority(ThreadPriority priority)
{
	int result = SDL_SetThreadPriority((SDL_ThreadPriority)priority);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

SDL_threadID Thread::CurrentThreadID::get()
{
	return SDL_ThreadID();
}

int NETSDL2::Concurrent::Thread::Wait()
{
	int status = 0;
	SDL_WaitThread(thread, &status);

	return status;
}
