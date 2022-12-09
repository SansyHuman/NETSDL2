#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "Joysticks.h"
#include "Event.h"
#include "Button.h"
#include "../core/GUID.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Joystick class.
		/// </summary>
		public ref class Joystick
		{
		private:
			SDL_Joystick* joystick;
			bool closeOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Joystick^>^ nativeJoystickConnections;

			static Joystick()
			{
				nativeJoystickConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Joystick^>();
			}

			void InitJoystick(SDL_Joystick* joystick);

		internal:
			// Used by game controller.
			Joystick(SDL_Joystick* joystick, bool closeOnDestroy);
			
			static Joystick^ GetJoystickFromNative(SDL_Joystick* joystick);
			property SDL_Joystick* NativeJoystick
			{
				SDL_Joystick* get();
			}

		public:
			/// <summary>
			/// Open a joystick for use.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Joystick(int deviceIndex);

			~Joystick();
			!Joystick();

			/// <summary>
			/// Locking for multi-threaded access to the joystick API.
			/// </summary>
			static void Lock();

			/// <summary>
			/// Unlocking for multi-threaded access to the joystick API.
			/// </summary>
			static void Unlock();

			/// <summary>
			/// Get the battery level of a joystick.
			/// </summary>
			property JoystickPowerLevel CurrentPowerLevel
			{
				JoystickPowerLevel get();
			}

			/// <summary>
			/// Enable/disable joystick event polling.
			/// </summary>
			/// <param name="state">Can be one of <see cref="EventState::Query"/>,
			/// <see cref="EventState::Ignore"/>, or <see cref="EventState::Enable"/>.
			/// </param>
			/// <returns>true if enabled, false if disabled, or a negative error code on
			/// failure.</returns>
			static Result<bool, int> EventState(NETSDL2::Events::EventState state);

			/// <summary>
			/// Get the joystick associated with an instance id.
			/// </summary>
			/// <param name="instanceID">The instance id to get the joystick for.</param>
			/// <returns>A joystick on success or None on failure.</returns>
			static Result<Joystick^, None^> JoystickFromInstanceID(SDL_JoystickID instanceID);

			/// <summary>
			/// Get the joystick associated with a player index.
			/// </summary>
			/// <param name="instanceID">The player index to get the joystick for.</param>
			/// <returns>A joystick on success or None on failure.</returns>
			static Result<Joystick^, None^> JoystickFromPlayerIndex(int playerIndex);

			/// <summary>
			/// Attach a new virtual joystick.
			/// </summary>
			/// <param name="type">Type of the joystick.</param>
			/// <param name="naxes">The number of axes.</param>
			/// <param name="nbuttons">The number of buttons.</param>
			/// <param name="nhats">The number of hats.</param>
			/// <returns>The joystick's device index, or None if an error occurred.</returns>
			static Result<int, None^> AttachVirtual(JoystickType type, int naxes, int nbuttons, int nhats);

			/// <summary>
			/// Attach a new virtual joystick with extended properties.
			/// </summary>
			/// <param name="desc">The joystick description.</param>
			/// <returns>The joystick's device index, or None if an error occurred.</returns>
			static Result<int, None^> AttachVirtualEx([In][IsReadOnly]VirtualJoystickDesc% desc);

			/// <summary>
			/// Detach a virtual joystick.
			/// </summary>
			/// <param name="deviceIndex">A value previously returned from <see cref="AttachVirtual"/>.</param>
			/// <returns>Success or Failure.</returns>
			static Result<None^, None^> DetachVirtual(int deviceIndex);

			/// <summary>
			/// Query whether or not the joystick at a given device index is virtual.
			/// </summary>
			/// <param name="deviceIndex">A joystick device index.</param>
			/// <returns>true if the joystick is virtual, false otherwise.</returns>
			static bool IsVirtual(int deviceIndex);

			/// <summary>
			/// Set values on an opened, virtual-joystick's axis.
			/// </summary>
			/// <param name="axis">The specific axis on the virtual joystick to set.</param>
			/// <param name="value">The new value for the specified axis.</param>
			/// <returns>Success or Failure.</returns>
			Result<None^, None^> SetVirtualAxis(int axis, Sint16 value);

			/// <summary>
			/// Set values on an opened, virtual-joystick's button.
			/// </summary>
			/// <param name="button">The specific button on the virtual joystick to set.</param>
			/// <param name="value">The new value for the specified button.</param>
			/// <returns>Success or Failure.</returns>
			Result<None^, None^> SetVirtualButton(int button, bool value);

			/// <summary>
			/// Set values on an opened, virtual-joystick's hat.
			/// </summary>
			/// <param name="hat">The specific hat on the virtual joystick to set.</param>
			/// <param name="value">The new value for the specified hat.</param>
			/// <returns>Success or Failure.</returns>
			Result<None^, None^> SetVirtualHat(int hat, HatPosition value);

			/// <summary>
			/// Get whether the joystick has been opened.
			/// </summary>
			property bool Attached
			{
				bool get();
			}

			/// <summary>
			/// Get the current state of an axis control on a joystick.
			/// </summary>
			/// <param name="axis">The axis to query; the axis indices start at index 0.
			/// </param>
			/// <returns>A 16-bit signed integer representing the current position of the
			/// axis.</returns>
			Sint16 GetAxis(int axis);

			/// <summary>
			/// Get the initial state of an axis control on a joystick.
			/// </summary>
			/// <param name="axis">The axis to query; the axis indices start at index 0.</param>
			/// <returns>Initial value if this axis has any initial value, or None if not.</returns>
			Result<Sint16, None^> GetAxisInitialState(int axis);

			/// <summary>
			/// Get the ball axis change since the last poll.
			/// </summary>
			/// <param name="ball">The ball index to query; ball indices start at index
			/// 0.</param>
			/// <param name="dx">Stores the difference in the x axis position since the
			/// last poll.</param>
			/// <param name="dy">Stores the difference in the y axis position since the
			/// last poll.</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> GetBall(int ball, [Out]int% dx, [Out]int% dy);

			/// <summary>
			/// Get the current state of a button on a joystick.
			/// </summary>
			/// <param name="button">The button index to get the state from; indices
			/// start at index 0.</param>
			/// <returns>true if the specified button is pressed, false otherwise.
			/// </returns>
			bool GetButton(int button);

			/// <summary>
			/// Start a rumble effect.
			/// </summary>
			/// <param name="lowFrequencyRumble">The intensity of the low frequency (left) rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="highFrequencyRumble">The intensity of the high frequency (right) rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="duration">The duration of the rumble effect, in milliseconds.</param>
			/// <returns>Success or Failure if rumble isn't supported on this joystick.</returns>
			Result<None^, None^> Rumble(Uint16 lowFrequencyRumble, Uint16 highFrequencyRumble, Uint32 duration);

			/// <summary>
			/// Start a rumble effect in the joystick's triggers
			/// </summary>
			/// <param name="leftRumble">The intensity of the left trigger rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="rightRumble">The intensity of the right trigger rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="duration">The duration of the rumble effect, in milliseconds.</param>
			/// <returns>Success or Failure if trigger rumble isn't supported on this joystick.</returns>
			Result<None^, None^> RumbleTriggers(Uint16 leftRumble, Uint16 rightRumble, Uint32 duration);

			/// <summary>
			/// Query whether a joystick has an LED.
			/// </summary>
			property bool HasLED
			{
				bool get();
			}

			/// <summary>
			/// Query whether a joystick has rumble support.
			/// </summary>
			property bool HasRumble
			{
				bool get();
			}

			/// <summary>
			/// Query whether a joystick has rumble support on triggers.
			/// </summary>
			property bool HasRumbleTriggers
			{
				bool get();
			}

			/// <summary>
			/// Update a joystick's LED color.
			/// </summary>
			/// <param name="red">The intensity of the red LED.</param>
			/// <param name="green">The intensity of the green LED.</param>
			/// <param name="blue">The intensity of the blue LED.</param>
			/// <returns>Success or Failure if this joystick does not have a modifiable LED.</returns>
			Result<None^, None^> SetLED(Uint8 red, Uint8 green, Uint8 blue);

			/// <summary>
			/// Send a joystick specific effect packet.
			/// </summary>
			/// <param name="data">The data to send to the joystick.</param>
			/// <param name="size">The size of the data to send to the joystick.</param>
			/// <returns>Success or Failure if this joystick or driver doesn't support effect packets.
			/// </returns>
			Result<None^, None^> SendEffect(System::IntPtr data, int size);

			/// <summary>
			/// Get the implementation-dependent GUID for the joystick at a given
			/// device index.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The GUID of the selected joystick. If called on an invalid
			/// index, this function returns a zero GUID.</returns>
			static NETSDL2::Core::GUID GetDeviceGUID(int deviceIndex);

			/// <summary>
			/// Get the USB vendor ID of a joystick, if available.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The USB vendor ID of the selected joystick. If called on an invalid index, this
			/// function returns None.</returns>
			static Result<Uint16, None^> GetDeviceVendor(int deviceIndex);

			/// <summary>
			/// Get the USB product ID of a joystick, if available.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The USB product ID of the selected joystick. If called on an invalid index, this
			/// function returns None.</returns>
			static Result<Uint16, None^> GetDeviceProduct(int deviceIndex);

			/// <summary>
			/// Get the product version of a joystick, if available.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The product version of the selected joystick. If called on an invalid index, this
			/// function returns None.</returns>
			static Result<Uint16, None^> GetDeviceProductVersion(int deviceIndex);

			/// <summary>
			/// Get the type of a joystick, if available.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The type of the selected joystick.</returns>
			static JoystickType GetDeviceType(int deviceIndex);

			/// <summary>
			/// Get the instance ID of a joystick.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The instance id of the selected joystick. If called on an invalid index, this
			/// function returns None.</returns>
			static Result<SDL_JoystickID, None^> GetDeviceInstanceID(int deviceIndex);

			/// <summary>
			/// Get the implementation-dependent GUID for the joystick.
			/// </summary>
			property NETSDL2::Core::GUID Guid
			{
				NETSDL2::Core::GUID get();
			}

			/// <summary>
			/// Get the USB vendor ID of an opened joystick, if available.
			/// </summary>
			/// <returns>The USB vendor ID of the selected joystick, or None if unavailable.</returns>
			Result<Uint16, None^> GetVendor();

			/// <summary>
			/// Get the USB product ID of an opened joystick, if available.
			/// </summary>
			/// <returns>The USB product ID of the selected joystick, or None if unavailable.</returns>
			Result<Uint16, None^> GetProduct();

			/// <summary>
			/// Get the product version of an opened joystick, if available.
			/// </summary>
			/// <returns>The product version of the selected joystick, or None if unavailable.</returns>
			Result<Uint16, None^> GetProductVersion();

			/// <summary>
			/// Get the firmware version of an opened joystick, if available.
			/// </summary>
			/// <returns>The firmware version of the selected joystick, or None if unavailable.</returns>
			Result<Uint16, None^> GetFirmwareVersion();

			/// <summary>
			/// Get the serial number of an opened joystick, if available.
			/// </summary>
			/// <returns>The serial number of the selected joystick, or None if unavailable.</returns>
			Result<System::String^, None^> GetSerial();

			/// <summary>
			/// Get the type of an opened joystick.
			/// </summary>
			property JoystickType Type
			{
				JoystickType get();
			}

			/// <summary>
			/// Get the current state of a POV hat on a joystick.
			/// </summary>
			/// <param name="hat">The hat index to get the state from.</param>
			/// <returns>The current hat position.</returns>
			HatPosition GetHat(int hat);

			/// <summary>
			/// Get the instance ID of an opened joystick.
			/// </summary>
			/// <returns>The instance ID of the specified joystick on success or a
			/// negative error code on failure.</returns>
			Result<SDL_JoystickID, int> InstanceID();

			/// <summary>
			/// Get the implementation dependent name of a joystick.
			/// </summary>
			/// <returns>The name of the selected joystick. If no name can be found,
			/// this function returns None.</returns>
			Result<System::String^, None^> Name();

			/// <summary>
			/// Get the implementation dependent path of a joystick.
			/// </summary>
			/// <returns>The path of the selected joystick. If no path can be found,
			/// this function returns None.</returns>
			Result<System::String^, None^> Path();

			/// <summary>
			/// Get the player index of an opened joystick.
			/// </summary>
			/// <returns>The player index, or None if it's not available.</returns>
			Result<int, None^> GetPlayerIndex();

			/// <summary>
			/// Set the player index of an opened joystick.
			/// </summary>
			/// <param name="playerIndex">Player index to assign to this joystick, or -1 to clear the player
			/// indexand turn off player LEDs.</param>
			void SetPlayerIndex(int playerIndex);

			/// <summary>
			/// Get the implementation dependent name of a joystick.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The name of the selected joystick. If no name can be found,
			/// this function returns None.</returns>
			static Result<System::String^, None^> NameForIndex(int deviceIndex);

			/// <summary>
			/// Get the implementation dependent path of a joystick.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The path of the selected joystick. If no path can be found,
			/// this function returns None.</returns>
			static Result<System::String^, None^> PathForIndex(int deviceIndex);

			/// <summary>
			/// Get the player index of a joystick.
			/// </summary>
			/// <param name="deviceIndex">The index of the joystick to query.</param>
			/// <returns>The player index of a joystick, or None if it's not available.</returns>
			static Result<int, None^> GetDevicePlayerIndex(int deviceIndex);

			/// <summary>
			/// Get the number of general axis controls on a joystick.
			/// </summary>
			/// <returns>The number of axis controls/number of axes on success or a
			/// negative error code on failure.</returns>
			Result<int, int> NumAxes();

			/// <summary>
			/// Get the number of trackballs on a joystick.
			/// </summary>
			/// <returns>The number of trackballs on success or a negative error code
			/// on failure.</returns>
			Result<int, int> NumBalls();

			/// <summary>
			/// Get the number of POV hats on a joystick.
			/// </summary>
			/// <returns>The number of POV hats on success or a negative error code
			/// on failure.</returns>
			Result<int, int> NumHats();

			/// <summary>
			/// Get the number of buttons on a joystick.
			/// </summary>
			/// <returns>The number of buttons on success or a negative error code on failure.</returns>
			Result<int, int> NumButtons();

			/// <summary>
			/// Update the current state of the open joysticks.
			/// </summary>
			static void Update();

			/// <summary>
			/// Count the number of joysticks attached to the system.
			/// </summary>
			/// <returns>The number of attached joysticks on success or a negative
			/// error code on failure.</returns>
			static Result<int, int> NumJoysticks();

			/// <summary>
			/// Query if a joystick has haptic features.
			/// </summary>
			/// <returns>true if the joystick is haptic, false if it isn't, or a
			/// negative error code on failure.</returns>
			Result<bool, int> IsHaptic();
		};
	}
}