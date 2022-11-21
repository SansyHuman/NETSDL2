#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "Finger.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

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

			/// <summary>
			/// Get the number of registered touch devices.
			/// </summary>
			static property int NumTouchDevices
			{
				int get();
			}

			/// <summary>
			/// Get the number of active fingers for a
			/// given touch device.
			/// </summary>
			/// <param name="touchID">The ID of a touch
			/// device.</param>
			/// <returns>The number of active fingers for a
			/// given touch device on success or None on
			/// failure.</returns>
			static Result<int, None^> GetNumTouchFingers(SDL_TouchID touchID);

			/// <summary>
			/// Get the touch ID with the given index.
			/// </summary>
			/// <param name="index">The touch device
			/// index.</param>
			/// <returns>The touch ID with the given index
			/// on success or None if the index is
			/// invalid.</returns>
			static Result<SDL_TouchID, None^> GetTouchDevice(int index);

			/// <summary>
			/// Get the touch device name as reported from
			/// the driver.
			/// </summary>
			/// <param name="index">The touch device
			/// index.</param>
			/// <returns>The name on success or None if
			/// the index is invalid.</returns>
			static Result<System::String^, None^> GetTouchName(int index);

			/// <summary>
			/// Get the type of the given touch device.
			/// </summary>
			/// <param name="touchID">The ID of the
			/// requested touch device.</param>
			/// <returns>The type of the touch device.
			/// </returns>
			static TouchDeviceType GetTouchDeviceType(SDL_TouchID touchID);

			/// <summary>
			/// Get the finger object for specified touch
			/// device ID and finger index.
			/// </summary>
			/// <param name="touchID">The ID of the
			/// requested touch device.</param>
			/// <param name="index">The index of the
			/// requested finger.</param>
			/// <returns>A Finger object or None if no
			/// object at the given ID and index could be
			/// found.</returns>
			static Result<Finger, None^> GetTouchFinger(SDL_TouchID touchID, int index);
		};
	}
}