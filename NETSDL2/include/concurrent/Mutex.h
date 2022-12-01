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
		/// SDL mutex.
		/// </summary>
		public ref class Mutex
		{
		private:
			SDL_mutex* mutex;

		internal:
			property SDL_mutex* NativeMutex
			{
				SDL_mutex* get();
			}

		public:
			/// <summary>
			/// The timeout value which corresponds to never time out.
			/// </summary>
			literal Uint32 MaxWait = SDL_MUTEX_MAXWAIT;

			/// <summary>
			/// Synchronization functions which can time out return this value if they
			/// time out.
			/// </summary>
			literal int TimedOut = SDL_MUTEX_TIMEDOUT;

			/// <summary>
			/// Create a new mutex.
			/// </summary>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Mutex();

			~Mutex();
			!Mutex();

			/// <summary>
			/// Lock the mutex.
			/// </summary>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> Lock();

			/// <summary>
			/// Try to lock a mutex without blocking.
			/// </summary>
			/// <returns>0, <see cref="Mutex::TimedOut"/>, or None on error.</returns>
			Result<int, None^> TryLock();

			/// <summary>
			/// Unlock the mutex.
			/// </summary>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> Unlock();
		};
	}
}
