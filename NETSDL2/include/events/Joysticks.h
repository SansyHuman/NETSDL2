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

		/// <summary>
		/// Type of joystick.
		/// </summary>
		public enum class JoystickType : Uint16
		{
			Unknown = SDL_JOYSTICK_TYPE_UNKNOWN,
			GameController = SDL_JOYSTICK_TYPE_GAMECONTROLLER,
			Wheel = SDL_JOYSTICK_TYPE_WHEEL,
			ArcadeStick = SDL_JOYSTICK_TYPE_ARCADE_STICK,
			FlightStick = SDL_JOYSTICK_TYPE_FLIGHT_STICK,
			DancePad = SDL_JOYSTICK_TYPE_DANCE_PAD,
			Guitar = SDL_JOYSTICK_TYPE_GUITAR,
			DrumKit = SDL_JOYSTICK_TYPE_DRUM_KIT,
			ArcadePad = SDL_JOYSTICK_TYPE_ARCADE_PAD,
			Throttle = SDL_JOYSTICK_TYPE_THROTTLE,
		};

		/// <summary>
		/// Joystick hat positions.
		/// </summary>
		[System::Flags]
		public enum class HatPosition : Uint8
		{
			Centered = SDL_HAT_CENTERED,
			Up = SDL_HAT_UP,
			Right = SDL_HAT_RIGHT,
			Down = SDL_HAT_DOWN,
			Left = SDL_HAT_LEFT,
			RightUp = SDL_HAT_RIGHTUP,
			RightDown = SDL_HAT_RIGHTDOWN,
			LeftUp = SDL_HAT_LEFTUP,
			LeftDown = SDL_HAT_LEFTDOWN,
		};

		using JoystickUpdate = void (SDLCALL*)(void* userdata);
		using JoystickSetPlayerIndex = void (SDLCALL*)(void* userdata, int player_index);
		using JoystickRumble = int (SDLCALL*)(void* userdata, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble);
		using JoystickRumbleTriggers = int (SDLCALL*)(void* userdata, Uint16 left_rumble, Uint16 right_rumble);
		using JoystickSetLED = int (SDLCALL*)(void* userdata, Uint8 red, Uint8 green, Uint8 blue);
		using JoystickSendEffect = int (SDLCALL*)(void* userdata, const void* data, int size);

		/// <summary>
		/// The structure that defines an extended virtual joystick description
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct VirtualJoystickDesc
		{
			/// <summary>
			/// <see cref="VirtualJoystickDesc::VirtualJoystickDescVersion"/>.
			/// </summary>
			Uint16 Version;

			/// <summary>
			/// Type of the joystick.
			/// </summary>
			JoystickType Type;
			
			/// <summary>
			/// The number of axes on this joystick.
			/// </summary>
			Uint16 NAxes;

			/// <summary>
			/// The number of buttons on this joystick.
			/// </summary>
			Uint16 NButtons;

			/// <summary>
			/// The number of hats on this joystick.
			/// </summary>
			Uint16 NHats;

			/// <summary>
			/// The USB vendor ID of this joystick.
			/// </summary>
			Uint16 VendorID;

			/// <summary>
			/// The USB product ID of this joystick.
			/// </summary>
			Uint16 ProductID;

			/// <summary>
			/// Unused.
			/// </summary>
			Uint16 Padding;

			/// <summary>
			/// A mask of which buttons are valid for this controller.
			/// </summary>
			Uint32 ButtonMask;

			/// <summary>
			/// A mask of which axes are valid for this controller.
			/// </summary>
			Uint32 AxisMask;

			/// <summary>
			/// The name of the joystick.
			/// </summary>
			char* Name;

			/// <summary>
			/// User data pointer passed to callbacks.
			/// </summary>
			System::IntPtr userdata;

			/// <summary>
			/// Called when the joystick state should be updated.
			/// </summary>
			JoystickUpdate Update;

			/// <summary>
			/// Called when the player index is set.
			/// </summary>
			JoystickSetPlayerIndex SetPlayerIndex;

			/// <summary>
			/// Implements <see cref="Joystick::Rumble"/>.
			/// </summary>
			JoystickRumble Rumble;

			/// <summary>
			/// Implements <see cref="Joystick::RumbleTriggers"/>.
			/// </summary>
			JoystickRumbleTriggers RumbleTriggers; 

			/// <summary>
			/// Implements <see cref="Joystick::SetLED"/>.
			/// </summary>
			JoystickSetLED SetLED;

			/// <summary>
			/// Implements <see cref="Joystick::SendEffect"/>.
			/// </summary>
			JoystickSendEffect SendEffect;

			/// <summary>
			/// Virtual joystick description struct version.
			/// </summary>
			literal Uint16 VirtualJoystickDescVersion = SDL_VIRTUAL_JOYSTICK_DESC_VERSION;
		};
	}
}