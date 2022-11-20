#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
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