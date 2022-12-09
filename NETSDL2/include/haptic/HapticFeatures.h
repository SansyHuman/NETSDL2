#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Haptic
	{
		/// <summary>
		/// Flags of supported haptic features.
		/// </summary>
		[System::Flags]
		public enum class HapticFeatures : unsigned int
		{
			None = 0,

			/// <summary>
			/// Constant effect supported.
			/// </summary>
			Constant = SDL_HAPTIC_CONSTANT,

			/// <summary>
			/// Sine wave effect supported.
			/// </summary>
			Sine = SDL_HAPTIC_SINE,

			/// <summary>
			/// Left/Right effect supported.
			/// </summary>
			LeftRight = SDL_HAPTIC_LEFTRIGHT,

			/// <summary>
			/// Triangle wave effect supported.
			/// </summary>
			Triangle = SDL_HAPTIC_TRIANGLE,

			/// <summary>
			/// Sawtoothup wave effect supported.
			/// </summary>
			SawToothUp = SDL_HAPTIC_SAWTOOTHUP,

			/// <summary>
			/// Sawtoothdown wave effect supported.
			/// </summary>
			SawToothDown = SDL_HAPTIC_SAWTOOTHDOWN,

			/// <summary>
			/// Ramp effect supported.
			/// </summary>
			Ramp = SDL_HAPTIC_RAMP,

			/// <summary>
			/// Spring effect supported - uses axes position.
			/// </summary>
			Spring = SDL_HAPTIC_SPRING,

			/// <summary>
			/// Damper effect supported - uses axes velocity.
			/// </summary>
			Damper = SDL_HAPTIC_DAMPER,

			/// <summary>
			/// Inertia effect supported - uses axes acceleration.
			/// </summary>
			Inertia = SDL_HAPTIC_INERTIA,

			/// <summary>
			/// Friction effect supported - uses axes movement.
			/// </summary>
			Friction = SDL_HAPTIC_FRICTION,

			/// <summary>
			/// Custom effect is supported.
			/// </summary>
			Custom = SDL_HAPTIC_CUSTOM,

			/// <summary>
			/// Device can set global gain.
			/// </summary>
			Gain = SDL_HAPTIC_GAIN,

			/// <summary>
			/// Device can set autocenter.
			/// </summary>
			Autocenter = SDL_HAPTIC_AUTOCENTER,

			/// <summary>
			/// Device can be queried for effect status.
			/// </summary>
			Status = SDL_HAPTIC_STATUS,

			/// <summary>
			/// Device can be paused.
			/// </summary>
			Pause = SDL_HAPTIC_PAUSE,
		};
	}
}