#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "RendererInfo.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions related to rendering.
		/// </summary>
		public ref struct Render abstract sealed
		{
		public:
			/// <summary>
			/// Get the number of 2D rendering drivers available for the current
			/// display.
			/// </summary>
			/// <returns>A number >= 0 on success or a negative error code on
			/// failure.</returns>
			static Result<int, int> GetNumRenderDrivers();

			/// <summary>
			/// Get info about a specific 2D rendering driver for the current
			/// display.
			/// </summary>
			/// <param name="index">The index of the driver to query information
			/// about.</param>
			/// <returns>Renderer info on success or error code on failure.
			/// </returns>
			static Result<RendererInfo, int> GetRenderDriverInfo(int index);

			/// <summary>
			/// Get info about all 2D rendering drivers for the current
			/// display.
			/// </summary>
			/// <returns>Array of renderer infos.</returns>
			static array<RendererInfo>^ GetRenderDriverInfos();
		};
	}
}