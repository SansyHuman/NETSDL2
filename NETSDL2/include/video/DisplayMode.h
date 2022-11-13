#pragma once

#include <SDL.h>
#include "../../include/video/PixelFormat.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// Display orientation
		/// </summary>
		public enum class DisplayOrientation
		{
			/// <summary>
			/// The display orientation can't be determined.
			/// </summary>
			Unknown = SDL_ORIENTATION_UNKNOWN,

			/// <summary>
			/// The display is in landscape mode, with the right side up, relative to portrait mode.
			/// </summary>
			Landscape = SDL_ORIENTATION_LANDSCAPE,

			/// <summary>
			/// The display is in landscape mode, with the left side up, relative to portrait mode.
			/// </summary>
			LandscapeFlipped = SDL_ORIENTATION_LANDSCAPE_FLIPPED,

			/// <summary>
			/// The display is in portrait mode.
			/// </summary>
			Portrait = SDL_ORIENTATION_PORTRAIT,

			/// <summary>
			/// The display is in portrait mode, upside down.
			/// </summary>
			PortraitFlipped = SDL_ORIENTATION_PORTRAIT_FLIPPED,
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// A structure that contains the description of a display mode.
		/// </summary>
		public value struct DisplayMode
		{
			/// <summary>
			/// Pixel format.
			/// </summary>
			PixelFormatEnum Format;

			/// <summary>
			/// Width, in screen coordinates.
			/// </summary>
			int W;

			/// <summary>
			/// Height, in screen coordinates.
			/// </summary>
			int H;

			/// <summary>
			/// Refresh rate (in Hz), or 0 for unspecified.
			/// </summary>
			int RefreshRate;

			/// <summary>
			/// Driver-specific data.
			/// </summary>
			System::IntPtr Driverdata;

			virtual System::String^ ToString() override;
		};
	}
}
