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

		/// <summary>
		/// An enumeration of the different kinds of Joystick controls a
		/// GameControllerButtonBind can map to.
		/// </summary>
		public enum class GameControllerBindType
		{
			/// <summary>
			/// Not mapped to anything on this Joystick.
			/// </summary>
			None = SDL_CONTROLLER_BINDTYPE_NONE,

			/// <summary>
			/// Maps to a button.
			/// </summary>
			Button = SDL_CONTROLLER_BINDTYPE_BUTTON,

			/// <summary>
			/// Maps to an axis.
			/// </summary>
			Axis = SDL_CONTROLLER_BINDTYPE_AXIS,

			/// <summary>
			/// Maps to (a direction of) a hat.
			/// </summary>
			Hat = SDL_CONTROLLER_BINDTYPE_HAT
		};

		/// <summary>
		/// A structure that contains info on how a logical GameController button or axis
		/// is mapped to the underlying Joystick's button/axis/hat.
		/// </summary>
		[StructLayout(LayoutKind::Explicit, Size = 12)]
		public value struct GameControllerButtonBind
		{
			/// <summary>
			/// What kind of control this maps to (button/axis/hat/not mapped)
			/// </summary>
			[FieldOffset(0)] GameControllerBindType BindType;

			/// <summary>
			/// The Joystick button this maps to.
			/// </summary>
			[FieldOffset(4)] int Button;

			/// <summary>
			/// The Joystick axis this maps to.
			/// </summary>
			[FieldOffset(4)] int Axis;

			/// <summary>
			/// The Joystick hat this maps to.
			/// </summary>
			[FieldOffset(4)] int Hat;

			/// <summary>
			/// The mask you need to binary-& with the hat's value with.
			/// </summary>
			[FieldOffset(8)] int HatMask;
		};

		/// <summary>
		/// Type of the controller.
		/// </summary>
		public enum class GameControllerType
		{
			Unknown = SDL_CONTROLLER_TYPE_UNKNOWN,
			Xbox360 = SDL_CONTROLLER_TYPE_XBOX360,
			XboxOne = SDL_CONTROLLER_TYPE_XBOXONE,
			PS3 = SDL_CONTROLLER_TYPE_PS3,
			PS4 = SDL_CONTROLLER_TYPE_PS4,
			NintendoSwitchPro = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO,
			Virtual = SDL_CONTROLLER_TYPE_VIRTUAL,
			PS5 = SDL_CONTROLLER_TYPE_PS5,
			AmazonLuna = SDL_CONTROLLER_TYPE_AMAZON_LUNA,
			GoogleStadia = SDL_CONTROLLER_TYPE_GOOGLE_STADIA,
			NvidiaShield = SDL_CONTROLLER_TYPE_NVIDIA_SHIELD,
			NintendoSwitchJoyconLeft = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_LEFT,
			NintendoSwitchJoyconRight = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_RIGHT,
			NintendoSwitchJoyconPair = SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_JOYCON_PAIR,
		};
	}
}