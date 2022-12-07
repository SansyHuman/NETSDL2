#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// Mouse buttons.
		/// </summary>
		public enum class Button : Uint8
		{
			/// <summary>
			/// Left mouse button.
			/// </summary>
			Left = SDL_BUTTON_LEFT,

			/// <summary>
			/// Middle mouse button.
			/// </summary>
			Middle = SDL_BUTTON_MIDDLE,

			/// <summary>
			/// Right mouse button.
			/// </summary>
			Right = SDL_BUTTON_RIGHT,

			/// <summary>
			/// X1 mouse button.
			/// </summary>
			X1 = SDL_BUTTON_X1,

			/// <summary>
			/// X2 mouse button.
			/// </summary>
			X2 = SDL_BUTTON_X2,
		};

		/// <summary>
		/// Current mouse button states.
		/// </summary>
		[System::Flags]
		public enum class ButtonState : Uint32
		{
			/// <summary>
			/// No button pressed.
			/// </summary>
			None = 0,
			
			/// <summary>
			/// Left mouse button pressed.
			/// </summary>
			Lmask = SDL_BUTTON_LMASK,

			/// <summary>
			/// Middle mouse button pressed.
			/// </summary>
			Mmask = SDL_BUTTON_MMASK,

			/// <summary>
			/// Right mouse button pressed.
			/// </summary>
			Rmask = SDL_BUTTON_RMASK,

			/// <summary>
			/// X1 mouse button pressed.
			/// </summary>
			X1mask = SDL_BUTTON_X1MASK,

			/// <summary>
			/// X2 mouse button pressed.
			/// </summary>
			X2mask = SDL_BUTTON_X2MASK,
		};

		/// <summary>
		/// General keyboard/mouse button states.
		/// </summary>
		public enum class ButtonPress : Uint8
		{
			/// <summary>
			/// The button is pressed.
			/// </summary>
			Pressed = SDL_PRESSED,

			/// <summary>
			/// The button is released.
			/// </summary>
			Released = SDL_RELEASED,
		};

		/// <summary>
		/// Scroll direction types for the Scroll event.
		/// </summary>
		public enum class MousewheelDirection : Uint32
		{
			/// <summary>
			/// The scroll direction is normal.
			/// </summary>
			Normal = SDL_MOUSEWHEEL_NORMAL,

			/// <summary>
			/// The scroll direction is flipped.
			/// </summary>
			Flipped = SDL_MOUSEWHEEL_FLIPPED,
		};
	}
}