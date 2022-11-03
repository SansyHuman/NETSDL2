#pragma once

#include <SDL.h>
#include "../../include/video/PixelFormat.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
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
