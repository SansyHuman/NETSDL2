#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Concurrent
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// The function passed to create a thread.
		/// </summary>
		/// <param name="data">What was passed as `data` when creating thread.</param>
		/// <returns>A value that can be reported.</returns>
		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		public delegate int ThreadFunction(System::IntPtr data);

		/// <summary>
		/// An enumeration of the available thread priorities.
		/// </summary>
		public enum class ThreadPriority
		{
			/// <summary>
			/// For non-urgent, background processing.
			/// </summary>
			Low = SDL_THREAD_PRIORITY_LOW,

			/// <summary>
			/// For general purpose processing (default).
			/// </summary>
			Normal = SDL_THREAD_PRIORITY_NORMAL,

			/// <summary>
			/// For timing-critical processing.
			/// </summary>
			High = SDL_THREAD_PRIORITY_HIGH,
			TimeCritical = SDL_THREAD_PRIORITY_TIME_CRITICAL
		};

		/// <summary>
		/// SDL Thread class.
		/// </summary>
		public ref class Thread
		{
		private:
			SDL_Thread* thread;
			GCHandle fnHandle;

		public:
			/// <summary>
			/// Create a new thread with a default stack size.
			/// </summary>
			/// <param name="fn">The function to call in the new thread.</param>
			/// <param name="name">The name of the thread.</param>
			/// <param name="data">A pointer that is passed to fn.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Thread(ThreadFunction^ fn, System::String^ name, System::IntPtr data);

			~Thread();
			!Thread();

			/// <summary>
			/// Let a thread clean up on exit without intervention.
			/// </summary>
			void Detach();

			/// <summary>
			/// Get the thread identifier for the specified thread.
			/// </summary>
			property SDL_threadID ThreadID
			{
				SDL_threadID get();
			}

			/// <summary>
			/// Get the thread name.
			/// </summary>
			property System::String^ ThreadName
			{
				System::String^ get();
			}

			/// <summary>
			/// Set the priority for the current thread.
			/// </summary>
			/// <param name="priority">The priority to set.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetThreadPriority(ThreadPriority priority);

			/// <summary>
			/// Get the thread identifier for the current thread.
			/// </summary>
			static property SDL_threadID CurrentThreadID
			{
				SDL_threadID get();
			}

			/// <summary>
			/// Wait for a thread to finish.
			/// </summary>
			/// <returns>An integer that will receive the value returned from the thread
			/// function.</returns>
			int Wait();
		};
	}
}