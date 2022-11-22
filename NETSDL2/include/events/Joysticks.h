#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// Power level of the joystick.
		/// </summary>
		public enum class JoystickPowerLevel
		{
			Unknown = SDL_JOYSTICK_POWER_UNKNOWN,

			/// <summary>
			/// <= 5%.
			/// </summary>
			Empty = SDL_JOYSTICK_POWER_EMPTY,

			/// <summary>
			/// <= 20%.
			/// </summary>
			Low = SDL_JOYSTICK_POWER_LOW,

			/// <summary>
			/// <= 70%.
			/// </summary>
			Medium = SDL_JOYSTICK_POWER_MEDIUM,

			/// <summary>
			/// <= 100%.
			/// </summary>
			Full = SDL_JOYSTICK_POWER_FULL,
			Wired = SDL_JOYSTICK_POWER_FULL,
			Max = SDL_JOYSTICK_POWER_MAX,
		};
	}
}