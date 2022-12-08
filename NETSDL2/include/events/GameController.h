#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "Joysticks.h"
#include "Event.h"
#include "Button.h"
#include "Sensors.h"
#include "../core/GUID.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace IO
	{
		ref class RWops;
	}

	namespace Events
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::IO;

		ref class Joystick;

		/// <summary>
		/// Game controller class.
		/// </summary>
		public ref class GameController
		{
		private:
			SDL_GameController* controller;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, GameController^>^ nativeGameControllerConnections;

			static GameController()
			{
				nativeGameControllerConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, GameController^>();
			}

			void InitGameController(SDL_GameController* controller);

		public:
			/// <summary>
			/// Open a game controller for use.
			/// </summary>
			/// <param name="joystickIndex">The index of a device, up to
			/// <see cref="Joystick::NumJoysticks"/>.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			GameController(int joystickIndex);

			~GameController();
			!GameController();

			/// <summary>
			/// Add support for controllers that SDL is unaware of or to cause an
			/// existing controller to have a different binding.
			/// </summary>
			/// <param name="mappingString">The mapping string.</param>
			/// <returns>1 if a new mapping is added, 0 if an existing mapping is
			/// updated, None on error.</returns>
			static Result<int, None^> AddMapping(System::String^ mappingString);

			/// <summary>
			/// Get the number of mappings installed.
			/// </summary>
			static property int NumMappings
			{
				int get();
			}

			/// <summary>
			/// Get the mapping at a particular index.
			/// </summary>
			/// <param name="mappingIndex">Index of the mapping.</param>
			/// <returns>The mapping string or None if the index is out of range.</returns>
			static Result<System::String^, None^> MappingForIndex(int mappingIndex);

			/// <summary>
			/// Use this function to load a set of Game Controller mappings from a file.
			/// </summary>
			/// <param name="filename">The name of the database you want to load.</param>
			/// <returns>The number of mappings added or None on error.</returns>
			static Result<int, None^> AddMappingsFromFile(System::String^ filename);

			/// <summary>
			/// Load a set of Game Controller mappings from a seekable SDL data stream.
			/// </summary>
			/// <param name="rw">The data stream for the mappings to be added.</param>
			/// <param name="freerw">true to close the stream after being read.</param>
			/// <returns>The number of mappings added or None on error.</returns>
			static Result<int, None^> AddMappingsFromRW(RWops^ rw, bool freerw);

			/// <summary>
			/// Query or change current state of Game Controller events.
			/// </summary>
			/// <param name="state">Can be one of <see cref="EventState::Query"/>,
			/// <see cref="EventState::Ignore"/>, or <see cref="EventState::Enable"/>.
			/// </param>
			/// <returns>true if enabled, false if disabled, or a negative error code on
			/// failure.</returns>
			static Result<bool, int> EventState(NETSDL2::Events::EventState state);

			/// <summary>
			/// Get the game controller associated with an instance id.
			/// </summary>
			/// <param name="joyid">The instance id to get the controller for.</param>
			/// <returns>A controller on success or None on failure.</returns>
			static Result<GameController^, None^> GameControllerFromInstanceID(SDL_JoystickID joyid);

			/// <summary>
			/// Get the SDL_GameController associated with a player index.
			/// </summary>
			/// <param name="playerIndex">The player index.</param>
			/// <returns>A controller on success or None on failure.</returns>
			static Result<GameController^, None^> GameControllerFromPlayerIndex(int playerIndex);

			/// <summary>
			/// Check if a controller has been opened and is currently connected.
			/// </summary>
			property bool Attached
			{
				bool get();
			}

			/// <summary>
			/// Get the current state of an axis control on a game controller.
			/// </summary>
			/// <param name="axis">An axis index.</param>
			/// <returns>Axis state.</returns>
			Sint16 GetAxis(GameControllerAxis axis);

			/// <summary>
			/// Convert a string into <see cref="GameControllerAxis"/> enum.
			/// </summary>
			/// <param name="str">String representing a <see cref="GameControllerAxis"/>
			/// axis.</param>
			/// <returns>The <see cref="GameControllerAxis"/> enum corresponding to the
			/// input string, or <see cref="GameControllerAxis::Invalid"/> if no match
			/// was found.</returns>
			static GameControllerAxis GetAxisFromString(System::String^ str);

			/// <summary>
			/// Get the SDL joystick layer binding for a controller axis mapping.
			/// </summary>
			/// <param name="axis">An axis enum value.</param>
			/// <returns>A GameControllerButtonBind describing the bind.</returns>
			GameControllerButtonBind GetBindForAxis(GameControllerAxis axis);

			/// <summary>
			/// Query whether a game controller has a given axis.
			/// </summary>
			/// <param name="axis">An axis enum value.</param>
			/// <returns>true if the controller has this axis, false otherwise.</returns>
			bool HasAxis(GameControllerAxis axis);

			/// <summary>
			/// Get the SDL joystick layer binding for a controller button mapping.
			/// </summary>
			/// <param name="button">A button enum value.</param>
			/// <returns>A GameControllerButtonBind describing the bind.</returns>
			GameControllerButtonBind GetBindForButton(GameControllerButton button);

			/// <summary>
			/// Query whether a game controller has a given button.
			/// </summary>
			/// <param name="button">A button enum value.</param>
			/// <returns>true if the controller has this button, false otherwise.</returns>
			bool HasButton(GameControllerButton button);

			/// <summary>
			/// Get the current state of a button on a game controller.
			/// </summary>
			/// <param name="button">A button index.</param>
			/// <returns>true for pressed state or false for not pressed state or error.
			/// </returns>
			bool GetButton(GameControllerButton button);

			/// <summary>
			/// Get the number of touchpads on a game controller.
			/// </summary>
			property int NumTouchpads
			{
				int get();
			}

			/// <summary>
			/// Get the number of supported simultaneous fingers on a touchpad on a game controller.
			/// </summary>
			/// <param name="touchpad">Touchpad index.</param>
			/// <returns>The number of supported fingers.</returns>
			int GetNumTouchpadFingers(int touchpad);

			/// <summary>
			/// Get the current state of a finger on a touchpad on a game controller.
			/// </summary>
			/// <param name="touchpad">Touchpad index.</param>
			/// <param name="finger">Finger index.</param>
			/// <param name="state">State of the touchpad.</param>
			/// <param name="x">X coordinate of the finger.</param>
			/// <param name="y">Y coordinate of the finger.</param>
			/// <param name="pressure">Pressure of the finger.</param>
			/// <returns>Success or None on failure.</returns>
			Result<int, None^> GetTouchpadFinger(int touchpad, int finger, [Out]Uint8% state, [Out]float% x, [Out]float% y, [Out]float% pressure);

			/// <summary>
			/// Return whether a game controller has a particular sensor.
			/// </summary>
			/// <param name="type">The type of sensor to query.</param>
			/// <returns>true if the sensor exists, false otherwise.</returns>
			bool HasSensor(SensorType type);

			/// <summary>
			/// Set whether data reporting for a game controller sensor is enabled.
			/// </summary>
			/// <param name="type">The type of sensor to enable/disable.</param>
			/// <param name="enabled">Whether data reporting should be enabled.</param>
			/// <returns>Success or Failure if an error occured.</returns>
			Result<None^, None^> SetSensorEnabled(SensorType type, bool enabled);

			/// <summary>
			/// Query whether sensor data reporting is enabled for a game controller.
			/// </summary>
			/// <param name="type">The type of sensor to query.</param>
			/// <returns>true if the sensor is enabled, false otherwise.</returns>
			bool IsSensorEnabled(SensorType type);

			/// <summary>
			/// Get the data rate (number of events per second) of a game controller sensor.
			/// </summary>
			/// <param name="type">The type of sensor to query.</param>
			/// <returns>The data rate.</returns>
			float GetSensorDataRate(SensorType type);

			/// <summary>
			/// Get the current state of a game controller sensor.
			/// </summary>
			/// <param name="type">The type of sensor to query.</param>
			/// <param name="data">A pointer filled with the current sensor state.</param>
			/// <param name="numValues">The number of values to write to data.</param>
			/// <returns>Success or Failure if an error occured.</returns>
			Result<None^, None^> GetSensorData(SensorType type, float* data, int numValues);

			/// <summary>
			/// Get the current state of a game controller sensor.
			/// </summary>
			/// <param name="type">The type of sensor to query.</param>
			/// <param name="data">An array filled with the current sensor state.</param>
			/// <param name="offset">Offset from the start of the array.</param>
			/// <param name="numValues">The number of values to write to data.</param>
			/// <returns>Success or Failure if an error occured.</returns>
			Result<None^, None^> GetSensorData(SensorType type, array<float>^ data, int offset, int numValues);

			/// <summary>
			/// Start a rumble effect on a game controller.
			/// </summary>
			/// <param name="lowFrequencyRumble">The intensity of the low frequency (left) rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="highFrequencyRumble">The intensity of the high frequency (right) rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="duration">The duration of the rumble effect, in milliseconds.</param>
			/// <returns>Success or Failure if rumble isn't supported on this controller.</returns>
			Result<None^, None^> Rumble(Uint16 lowFrequencyRumble, Uint16 highFrequencyRumble, Uint32 duration);

			/// <summary>
			/// Start a rumble effect in the game controller's triggers.
			/// </summary>
			/// <param name="leftRumble">The intensity of the left trigger rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="rightRumble">The intensity of the right trigger rumble motor,
			/// from 0 to 0xFFFF.</param>
			/// <param name="duration">The duration of the rumble effect, in milliseconds.</param>
			/// <returns>Success or Failure if trigger rumble isn't supported on this controller.</returns>
			Result<None^, None^> RumbleTriggers(Uint16 leftRumble, Uint16 rightRumble, Uint32 duration);

			/// <summary>
			/// Query whether a game controller has an LED.
			/// </summary>
			property bool HasLED
			{
				bool get();
			}

			/// <summary>
			/// Query whether a game controller has rumble support.
			/// </summary>
			property bool HasRumble
			{
				bool get();
			}

			/// <summary>
			/// Query whether a game controller has rumble support on triggers.
			/// </summary>
			property bool HasRumbleTriggers
			{
				bool get();
			}

			/// <summary>
			/// Update a game controller's LED color.
			/// </summary>
			/// <param name="red">The intensity of the red LED.</param>
			/// <param name="green">The intensity of the green LED.</param>
			/// <param name="blue">The intensity of the blue LED.</param>
			/// <returns>Success or Failure if this controller does not have a modifiable LED.</returns>
			Result<None^, None^> SetLED(Uint8 red, Uint8 green, Uint8 blue);

			/// <summary>
			/// Send a controller specific effect packet
			/// </summary>
			/// <param name="data">The data to send to the controller.</param>
			/// <param name="size">The size of the data to send to the controller.</param>
			/// <returns>Success or Failure if this controller or driver doesn't support effect packets.
			/// </returns>
			Result<None^, None^> SendEffect(System::IntPtr data, int size);

			/// <summary>
			/// Convert a string into <see cref="GameControllerButton"/> enum.
			/// </summary>
			/// <param name="str">String representing a <see cref="GameControllerButton"/>
			/// button.</param>
			/// <returns>The <see cref="GameControllerButton"/> enum corresponding to the
			/// input string, or <see cref="GameControllerButton::Invalid"/> if no match
			/// was found.</returns>
			static GameControllerButton GetButtonFromString(System::String^ str);

			/// <summary>
			/// Get the Joystick ID from a Game Controller.
			/// </summary>
			/// <returns>A Joystick object on success or None on failure.</returns>
			Result<Joystick^, None^> GetJoystick();

			/// <summary>
			/// Convert from a <see cref="GameControllerAxis"/> enum to a string.
			/// </summary>
			/// <param name="axis">An enum value for a given
			/// <see cref="GameControllerAxis"/>.</param>
			/// <returns>A string for the given axis, or None if an invalid axis is
			/// specified.</returns>
			static Result<System::String^, None^> GetStringForAxis(GameControllerAxis axis);

			/// <summary>
			/// Convert from a <see cref="GameControllerButton"/> enum to a string.
			/// </summary>
			/// <param name="button">An enum value for a given
			/// <see cref="GameControllerButton"/>.</param>
			/// <returns>A string for the given button, or None if an invalid button is
			/// specified.</returns>
			static Result<System::String^, None^> GetStringForButton(GameControllerButton button);

			/// <summary>
			/// Get the current mapping of a Game Controller.
			/// </summary>
			/// <returns>A string that has the controller's mapping or None if no
			/// mapping is available.</returns>
			Result<System::String^, None^> Mapping();

			/// <summary>
			/// Get the game controller mapping string for a given GUID.
			/// </summary>
			/// <param name="guid">A structure containing the GUID for which a mapping is
			/// desired.</param>
			/// <returns>A mapping string or None on error.</returns>
			static Result<System::String^, None^> MappingForGUID(GUID guid);

			/// <summary>
			/// Get the implementation-dependent name for an opened game controller.
			/// </summary>
			/// <returns>The implementation dependent name for the game controller, or
			/// None if there is no name or the identifier passed is invalid.</returns>
			Result<System::String^, None^> Name();

			/// <summary>
			/// Get the implementation-dependent path for an opened game controller.
			/// </summary>
			/// <returns>The implementation dependent path for the game controller, or
			/// None if there is no path or the identifier passed is invalid.</returns>
			Result<System::String^, None^> Path();

			/// <summary>
			/// Get the type of this currently opened controller.
			/// </summary>
			property GameControllerType Type
			{
				GameControllerType get();
			}

			/// <summary>
			/// Get the player index of an opened game controller.
			/// </summary>
			/// <returns>The player index for controller, or None if it's not available.</returns>
			Result<int, None^> GetPlayerIndex();

			/// <summary>
			/// Set the player index of an opened game controller.
			/// </summary>
			/// <param name="playerIndex">Player index to assign to this controller, or -1 to clear the
			/// player index and turn off player LEDs.</param>
			void SetPlayerIndex(int playerIndex);

			/// <summary>
			/// Get the USB vendor ID of an opened controller, if available.
			/// </summary>
			/// <returns>The USB vendor ID, or None if unavailable.</returns>
			Result<Uint16, None^> GetVendor();

			/// <summary>
			/// Get the USB product ID of an opened controller, if available.
			/// </summary>
			/// <returns>The USB product ID, or None if unavailable.</returns>
			Result<Uint16, None^> GetProduct();

			/// <summary>
			/// Get the USB product version of an opened controller, if available.
			/// </summary>
			/// <returns>The USB product version, or None if unavailable.</returns>
			Result<Uint16, None^> GetProductVersion();

			/// <summary>
			/// Get the firmware version of an opened controller, if available.
			/// </summary>
			/// <returns>The firmware version, or None if unavailable.</returns>
			Result<Uint16, None^> GetFirmwareVersion();

			/// <summary>
			/// Get the serial number of an opened controller, if available.
			/// </summary>
			/// <returns>The serial number, or None if unavailable.</returns>
			Result<System::String^, None^> GetSerial();

			/// <summary>
			/// Get the implementation dependent name for the game controller.
			/// </summary>
			/// <param name="joystickIndex">The device index of a device.</param>
			/// <returns>The implementation dependent name for the game controller, or
			/// None if there is no name or the identifier passed is invalid.</returns>
			static Result<System::String^, None^> NameForIndex(int joystickIndex);

			/// <summary>
			/// Get the implementation dependent path for the game controller.
			/// </summary>
			/// <param name="joystickIndex">The device index of a device.</param>
			/// <returns>The implementation dependent path for the game controller, or
			/// None if there is no path or the identifier passed is invalid.</returns>
			static Result<System::String^, None^> PathForIndex(int joystickIndex);

			/// <summary>
			/// Get the type of a game controller.
			/// </summary>
			/// <param name="joystickIndex">The device index of a device.</param>
			/// <returns>The controller type.</returns>
			static GameControllerType TypeForIndex(int joystickIndex);

			/// <summary>
			/// Get the mapping of a game controller.
			/// </summary>
			/// <param name="joystickIndex">The device index of a device.</param>
			/// <returns>A string that has the controller's mapping or None if no
			/// mapping is available.</returns>
			static Result<System::String^, None^> MappingForDeviceIndex(int joystickIndex);

			/// <summary>
			/// Manually pump game controller updates if not using the loop.
			/// </summary>
			static void Update();

			/// <summary>
			/// Check if the given joystick is supported by the game controller interface.
			/// </summary>
			/// <param name="joystickIndex">The device index of a device.</param>
			/// <returns>true if the given joystick is supported by the game controller
			/// interface, false if it isn't or it's an invalid index.</returns>
			static bool IsGameController(int joystickIndex);

			/// <summary>
			/// Return the sfSymbolsName for a given button on a game controller on Apple platforms.
			/// </summary>
			/// <param name="button">A button on the game controller.</param>
			/// <returns>The sfSymbolsName or None if the name can't be found.</returns>
			Result<System::String^, None^> GetAppleSFSymbolsNameForButton(GameControllerButton button);

			/// <summary>
			/// Return the sfSymbolsName for a given axis on a game controller on Apple platforms.
			/// </summary>
			/// <param name="axis">A axis on the game controller.</param>
			/// <returns>The sfSymbolsName or None if the name can't be found.</returns>
			Result<System::String^, None^> GetAppleSFSymbolsNameForAxis(GameControllerAxis axis);
		};
	}
}