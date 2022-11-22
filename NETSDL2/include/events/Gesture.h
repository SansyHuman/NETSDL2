#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace IO
	{
		ref class RWops;
	}

	namespace Events
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::IO;

		/// <summary>
		/// Functions related to gesture.
		/// </summary>
		public ref struct Gesture abstract sealed
		{
		public:
			/// <summary>
			/// Load Dollar Gesture templates from a file.
			/// </summary>
			/// <param name="touchId">A touch id.</param>
			/// <param name="src">A RWops to load from.</param>
			/// <returns>The number of loaded templates on success or error code
			/// (or 0) on failure.</returns>
			static Result<int, int> LoadDollarTemplates(SDL_TouchID touchId, RWops^ src);

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

			/// <summary>
			/// Save all currently loaded Dollar Gesture templates.
			/// </summary>
			/// <param name="dst">A RWops to save to.</param>
			/// <returns>The number of saved templates on success or None on failure.
			/// </returns>
			static Result<int, None^> SaveAllDollarTemplates(RWops^ dst);

			/// <summary>
			/// Save a currently loaded Dollar Gesture template.
			/// </summary>
			/// <param name="gestureId">A gesture id.</param>
			/// <param name="dst">A RWops to save to.</param>
			/// <returns>Success or Failure.</returns>
			static Result<None^, None^> SaveDollarTemplate(SDL_GestureID gestureId, RWops^ dst);
		};
	}
}