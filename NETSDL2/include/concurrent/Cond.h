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

		ref class Mutex;

		/// <summary>
		/// SDL conditional variable.
		/// </summary>
		public ref class Cond
		{
		private:
			SDL_cond* cond;

		public:
			/// <summary>
			/// Create a condition variable.
			/// </summary>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Cond();

			~Cond();
			!Cond();

			/// <summary>
			/// Restart all threads that are waiting on the condition variable.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Broadcast();

			/// <summary>
			/// Restart one of the threads that are waiting on the condition variable.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Signal();

			/// <summary>
			/// Wait until a condition variable is signaled.
			/// </summary>
			/// <param name="mutex">The mutex used to coordinate thread access.</param>
			/// <returns>None when it is signaled or error code on failure.</returns>
			Result<None^, int> Wait(Mutex^ mutex);

			/// <summary>
			/// Wait until a condition variable is signaled or a certain time has passed.
			/// </summary>
			/// <param name="mutex">The mutex used to coordinate thread access.</param>
			/// <param name="ms">The maximum time to wait, in milliseconds, or
			/// <see cref="Mutex::MaxWait"/> to wait indefinitely</param>
			/// <returns>0 if the condition variable is signaled,
			/// <see cref="Mutex::TimedOut"/> if the condition is not signaled in the
			/// allotted time, or a negative error code on failure.</returns>
			Result<int, int> WaitTimeout(Mutex^ mutex, Uint32 ms);
		};
	}
}
