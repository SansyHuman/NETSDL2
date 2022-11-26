#pragma once

#include <SDL.h>

#include "Scancode.h"
#include "Keycode.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// The SDL keysym structure, used in key events.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Keysym
		{
			/// <summary>
			/// SDL physical key code.
			/// </summary>
			NETSDL2::Events::Scancode Scancode;

			/// <summary>
			/// SDL virtual key code.
			/// </summary>
			Keycode Sym;

			/// <summary>
			/// Current key modifiers.
			/// </summary>
			Keymod Mod;
			Uint32 Unused;

			virtual System::String^ ToString() override;
		};
	}
}