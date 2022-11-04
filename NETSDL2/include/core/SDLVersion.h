#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Core
	{

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// A structure that contains information about the version of SDL in
		/// use.
		/// </summary>
		public value struct SDLVersion
		{
			/// <summary>
			/// Major version.
			/// </summary>
			Uint8 Major;

			/// <summary>
			/// Minor version.
			/// </summary>
			Uint8 Minor;

			/// <summary>
			/// Update version (patchlevel).
			/// </summary>
			Uint8 Patch;

			SDLVersion(Uint8 major, Uint8 minor, Uint8 patch);

			virtual System::String^ ToString() override;
		};
	}
}