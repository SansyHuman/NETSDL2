#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Systems
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for handling information about the current platform.
		/// </summary>
		public ref struct Platform abstract sealed
		{
		public:
			/// <summary>
			/// Get the name of the platform.
			/// </summary>
			/// <returns>The name of the platform. If the correct platform name is
			/// not available, returns a string beginning with the text "Unknown".
			/// </returns>
			static System::String^ GetPlatform();
		};
	}
}