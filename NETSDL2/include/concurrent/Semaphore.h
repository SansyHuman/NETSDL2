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
		/// SDL semaphore.
		/// </summary>
		public ref class Semaphore
		{
		private:
			SDL_sem* semaphore;

		public:
			/// <summary>
			/// Create a semaphore.
			/// </summary>
			/// <param name="initialValue">The starting value of the semaphore.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Semaphore(Uint32 initialValue);

			~Semaphore();
			!Semaphore();

			/// <summary>
			/// Atomically increment a semaphore's value and wake waiting threads.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Post();

			/// <summary>
			/// See if a semaphore has a positive value and decrement it if it does.
			/// </summary>
			/// <returns>0 if the wait succeeds, <see cref="Mutex::TimedOut"/> if the
			/// wait would block, or a negative error code on failure</returns>
			Result<int, int> TryWait();

			/// <summary>
			/// Get the current value of a semaphore.
			/// </summary>
			property Uint32 Value
			{
				Uint32 get();
			}

			/// <summary>
			/// Wait until a semaphore has a positive value and then decrements it.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Wait();

			/// <summary>
			/// Wait until a semaphore has a positive value and then decrements it.
			/// </summary>
			/// <param name="ms">The length of the timeout, in milliseconds.</param>
			/// <returns>0 if the wait succeeds, <see cref="Mutex::TimedOut"/> if the
			/// wait does not succeed in the allotted time, or a negative error code on
			/// failure.</returns>
			Result<int, int> WaitTimeout(Uint32 ms);
		};
	}
}
