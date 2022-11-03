#include "../../include/core/Log.h"

#include <msclr/marshal.h>
#include <vcclr.h>

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace msclr::interop;

using namespace System::Threading;
using namespace NETSDL2::Core;

void NETSDL2::Core::Logging::LogOutputNative(void* userdata, int category, SDL_LogPriority priority, const char* message)
{
	callback(System::IntPtr(userdata), (LogCategory)category, (LogPriority)priority, StringMarshal::UTF8NativeToManaged(message));
}

void NETSDL2::Core::Logging::DefaultLogOutputFunction(System::IntPtr userData, LogCategory category, LogPriority priority, System::String^ message)
{
	System::Console::Error->WriteLine(message);
}

void NETSDL2::Core::Logging::Init()
{
	if(logInit)
		return;

	callback = gcnew LogOutputFunction(&Logging::DefaultLogOutputFunction);
	NativeLogOutputFunction^ native = gcnew NativeLogOutputFunction(&Logging::LogOutputNative);

	callbackHandle = GCHandle::Alloc(native);
	nativeCallback = reinterpret_cast<SDL_LogOutputFunction>(Marshal::GetFunctionPointerForDelegate(native).ToPointer());

	SDL_LogSetOutputFunction(nativeCallback, __nullptr);

	logOutputSetLock = gcnew Object();

	logInit = true;
}

void NETSDL2::Core::Logging::Quit()
{
	if(!logInit)
		return;

	nativeCallback = __nullptr;
	logOutputSetLock = nullptr;
	callbackHandle.Free();

	logInit = false;
}

void NETSDL2::Core::Logging::Log(System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_Log(context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogCritical(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogCritical((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogDebug(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogDebug((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogError(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogError((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogInfo(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogInfo((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogVerbose(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogVerbose((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogWarn(LogCategory category, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogWarn((int)category, context.ManagedToUTF8Native(message));
}

void NETSDL2::Core::Logging::LogMessage(LogCategory category, LogPriority priority, System::String^ format, ...array<Object^>^ args)
{
	System::String^ message = System::String::Format(format, args);

	StringMarshal context;
	SDL_LogMessage((int)category, (SDL_LogPriority)priority, context.ManagedToUTF8Native(message));
}

LogOutputFunction^ NETSDL2::Core::Logging::GetOutputFunction(System::IntPtr% userdata)
{
	SDL_LogOutputFunction func = __nullptr;
	void* userData = __nullptr;

	SDL_LogGetOutputFunction(&func, &userData);

	userdata = System::IntPtr(userData);

	return callback;
}

LogOutputFunction^ NETSDL2::Core::Logging::GetOutputFunction(void** userdata)
{
	SDL_LogOutputFunction func = __nullptr;

	SDL_LogGetOutputFunction(&func, userdata);

	return callback;
}

void NETSDL2::Core::Logging::SetOutputFunction(LogOutputFunction^ callback, System::IntPtr userdata)
{
	try
	{
		Monitor::Enter(logOutputSetLock);

		Logging::callback = callback;
		SDL_LogSetOutputFunction(nativeCallback, userdata.ToPointer());
	}
	finally
	{
		Monitor::Exit(logOutputSetLock);
	}
}

void NETSDL2::Core::Logging::SetOutputFunction(LogOutputFunction^ callback, void* userdata)
{
	try
	{
		Monitor::Enter(logOutputSetLock);

		Logging::callback = callback;
		SDL_LogSetOutputFunction(nativeCallback, userdata);
	}
	finally
	{
		Monitor::Exit(logOutputSetLock);
	}
}

LogPriority NETSDL2::Core::Logging::GetPriority(LogCategory category)
{
	return (LogPriority)SDL_LogGetPriority((int)category);
}

void NETSDL2::Core::Logging::SetPriority(LogCategory category, LogPriority priority)
{
	SDL_LogSetPriority((int)category, (SDL_LogPriority)priority);
}

void NETSDL2::Core::Logging::SetAllPriority(LogPriority priority)
{
	SDL_LogSetAllPriority((SDL_LogPriority)priority);
}

void NETSDL2::Core::Logging::ResetPriorities()
{
	SDL_LogResetPriorities();
}
