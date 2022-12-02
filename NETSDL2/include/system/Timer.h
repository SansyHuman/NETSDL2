#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Systems
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Function prototype for the timer callback function.
		/// 
		/// The callback function is passed the current timer interval and returns
		/// the next timer interval. If the returned value is the same as the one
		/// passed in, the periodic alarm continues, otherwise a new alarm is
		/// scheduled. If the callback returns 0, the periodic alarm is cancelled.
		/// </summary>
		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		public delegate Uint32 TimerCallback(Uint32 interval, System::IntPtr param);

		/// <summary>
		/// Timer object.
		/// </summary>
		public ref class Timer
		{
		private:
			SDL_TimerID id;
			GCHandle handle;

		public:
			/// <summary>
			/// Call a callback function at a future time.
			/// </summary>
			/// <param name="interval">The timer delay, in milliseconds, passed to
			/// callback.</param>
			/// <param name="callback">The callback function to call when the
			/// specified interval elapses.</param>
			/// <param name="param">A pointer that is passed to callback.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Timer(Uint32 interval, TimerCallback^ callback, System::IntPtr param);

			~Timer();
			!Timer();

			/// <summary>
			/// Wait a specified number of milliseconds before returning.
			/// </summary>
			/// <param name="ms">The number of milliseconds to delay.</param>
			static void Delay(Uint32 ms);

			/// <summary>
			/// Get the current value of the high resolution counter.
			/// </summary>
			static property Uint64 PerformanceCounter
			{
				Uint64 get();
			}

			/// <summary>
			/// Get the count per second of the high resolution counter.
			/// </summary>
			static property Uint64 PerformanceFrequency
			{
				Uint64 get();
			}

			/// <summary>
			/// Get the number of milliseconds since SDL library initialization.
			/// </summary>
			static property Uint32 Ticks
			{
				Uint32 get();
			}

			/// <summary>
			/// Get the number of milliseconds since SDL library initialization.
			/// </summary>
			static property Uint64 Ticks64
			{
				Uint64 get();
			}
		};
	}
}