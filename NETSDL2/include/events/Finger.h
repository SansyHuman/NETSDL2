#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// Types of touch device.
		/// </summary>
		public enum class TouchDeviceType
		{
			Invalid = SDL_TOUCH_DEVICE_INVALID,

			/// <summary>
			/// Touch screen with window-relative
			/// coordinates.
			/// </summary>
			Direct = SDL_TOUCH_DEVICE_DIRECT,

			/// <summary>
			/// Trackpad with absolute device coordinates.
			/// </summary>
			IndirectAbsolute = SDL_TOUCH_DEVICE_INDIRECT_ABSOLUTE,

			/// <summary>
			/// Trackpad with screen cursor-relative
			/// coordinates.
			/// </summary>
			IndirectRelative = SDL_TOUCH_DEVICE_INDIRECT_RELATIVE,
		};

		/// <summary>
		/// A structure that contains touch information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Finger
		{
			/// <summary>
			/// The finger id.
			/// </summary>
			SDL_FingerID ID;

			/// <summary>
			/// The x-axis location of the touch event,
			/// normalized (0...1).
			/// </summary>
			float X;

			/// <summary>
			/// The y-axis location of the touch event,
			/// normalized (0...1).
			/// </summary>
			float Y;

			/// <summary>
			/// The quantity of pressure applied,
			/// normalized (0...1).
			/// </summary>
			float Pressure;

			virtual System::String^ ToString() override;
		};
	}
}