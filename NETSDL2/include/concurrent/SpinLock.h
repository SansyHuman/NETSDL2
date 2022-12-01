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
		/// SDL spin lock.
		/// </summary>
		public ref class SpinLock
		{
		private:
			SDL_SpinLock lock;

		public:
			/// <summary>
			/// Create a spin lock.
			/// </summary>
			SpinLock();

			/// <summary>
			/// Lock a spin lock by setting it to a non-zero value.
			/// </summary>
			void Lock();

			/// <summary>
			/// Try to lock a spin lock by setting it to a non-zero value.
			/// </summary>
			/// <returns>true if the lock succeeded, false if the lock is already held.
			/// </returns>
			bool TryLock();

			/// <summary>
			/// Unlock a spin lock by setting it to 0.
			/// </summary>
			void Unlock();
		};
	}
}