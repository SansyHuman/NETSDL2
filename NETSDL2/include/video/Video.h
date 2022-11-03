#pragma once

#include <SDL.h>
#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Video subsystem.
		/// </summary>
		public ref struct Video abstract sealed
		{
		public:
			/// <summary>
			/// Initialize the video subsystem, optionally specifying a video
			/// driver.
			/// </summary>
			/// <param name="driverName">The name of a video driver to
			/// initialize, or null for the default driver.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> Init(System::String^ driverName);

			/// <summary>
			/// Shut down the video subsystem, if initialized with
			/// <see cref="Video::Init"/>.
			/// </summary>
			static void Quit();
		};
	}
}