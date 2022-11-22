#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions related to gesture.
		/// </summary>
		public ref struct Gesture abstract sealed
		{
		public:
			// TODO: LoadDollarTemplates

			/// <summary>
			/// Begin recording a gesture on a specified
			/// touch device or all touch devices.
			/// </summary>
			/// <param name="touchId">The touch device id,
			/// or -1 for all touch devices.</param>
			/// <returns>Success or Failure if the
			/// specified device could not be found.
			/// </returns>
			static Result<None^, None^> RecordGesture(SDL_TouchID touchId);

			// TODO: SaveAllDollarTemplates
			// TODO: SaveDollarTemplate
		};
	}
}