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
		/// Functions that don't fit elsewhere.
		/// </summary>
		public ref struct Misc abstract sealed
		{
		public:
			/// <summary>
			/// Open a URL/URI in the browser or other appropriate external
			/// application.
			/// </summary>
			/// <param name="url">A valid URL/URI to open. Use
			/// `file:///full/path/to/file` for local files, if supported.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> OpenURL(System::String^ url);
		};
	}
}