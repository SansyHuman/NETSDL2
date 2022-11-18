#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// An enumeration of axes available from a
		/// controller.
		/// </summary>
		public enum class GameControllerAxis : Uint8
		{
			Invalid = SDL_CONTROLLER_AXIS_INVALID,
			LeftX = SDL_CONTROLLER_AXIS_LEFTX,
			LeftY = SDL_CONTROLLER_AXIS_LEFTY,
			RightX = SDL_CONTROLLER_AXIS_RIGHTX,
			RightY = SDL_CONTROLLER_AXIS_RIGHTY,
			TriggerLeft = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
			TriggerRight = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
			Max = SDL_CONTROLLER_AXIS_MAX,
		};

		/// <summary>
		/// An enumeration of buttons available from a
		/// controller.
		/// </summary>
		public enum class GameControllerButton : Uint8
		{
			Invalid = SDL_CONTROLLER_BUTTON_INVALID,
			A = SDL_CONTROLLER_BUTTON_A,
			B = SDL_CONTROLLER_BUTTON_B,
			X = SDL_CONTROLLER_BUTTON_X,
			Y = SDL_CONTROLLER_BUTTON_Y,
			Back = SDL_CONTROLLER_BUTTON_BACK,
			Guide = SDL_CONTROLLER_BUTTON_GUIDE,
			Start = SDL_CONTROLLER_BUTTON_START,
			LeftStick = SDL_CONTROLLER_BUTTON_LEFTSTICK,
			RightStick = SDL_CONTROLLER_BUTTON_RIGHTSTICK,
			LeftShoulder = SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
			RightShoulder = SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
			DpadUp = SDL_CONTROLLER_BUTTON_DPAD_UP,
			DpadDown = SDL_CONTROLLER_BUTTON_DPAD_DOWN,
			DpadLeft = SDL_CONTROLLER_BUTTON_DPAD_LEFT,
			DpadRight = SDL_CONTROLLER_BUTTON_DPAD_RIGHT,

			/// <summary>
			/// Xbox Series X share button, PS5 microphone
			/// button, Nintendo Switch Pro capture button,
			/// Amazon Luna microphone button.
			/// </summary>
			Misc1 = SDL_CONTROLLER_BUTTON_MISC1,

			/// <summary>
			/// Xbox Elite paddle P1.
			/// </summary>
			Paddle1 = SDL_CONTROLLER_BUTTON_PADDLE1,

			/// <summary>
			/// Xbox Elite paddle P3.
			/// </summary>
			Paddle2 = SDL_CONTROLLER_BUTTON_PADDLE2,

			/// <summary>
			/// Xbox Elite paddle P2.
			/// </summary>
			Paddle3 = SDL_CONTROLLER_BUTTON_PADDLE3,

			/// <summary>
			/// Xbox Elite paddle P4.
			/// </summary>
			Paddle4 = SDL_CONTROLLER_BUTTON_PADDLE4,

			/// <summary>
			/// PS4/PS5 touchpad button.
			/// </summary>
			Touchpad = SDL_CONTROLLER_BUTTON_TOUCHPAD,
			Max = SDL_CONTROLLER_BUTTON_MAX,
		};
	}
}