#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// Functions related to touch events.
		/// </summary>
		public ref struct Touch abstract sealed
		{
		public:
			/// <summary>
			/// Used as the device ID for mouse events
			/// simulated with touch input.
			/// </summary>
			literal Uint32 TOUCH_MOUSEID = SDL_TOUCH_MOUSEID;

			/// <summary>
			/// Used as the TouchID for touch events
			/// simulated with mouse input.
			/// </summary>
			literal Sint64 MOUSE_TOUCHID = SDL_MOUSE_TOUCHID;
		};
	}
}