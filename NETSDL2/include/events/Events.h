#pragma once

#include <SDL.h>

#include "Event.h"
#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for event handling.
		/// </summary>
		public ref struct Events abstract sealed
		{
		public:
			/// <summary>
			/// Poll for currently pending events.
			/// </summary>
			/// <param name="event">The <see cref="Event"/> structure to be
			/// filled with the next event from the queue.</param>
			/// <returns>Success if there is a pending event or Failure if
			/// there are none available.</returns>
			static Result<None^, None^> PollEvent([Out]Event% event);

			/// <summary>
			/// Check whether there is an event in the queue.
			/// </summary>
			static property bool EventExist
			{
				bool get();
			}
		};
	}
}