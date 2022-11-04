#pragma once

#include <SDL.h>
#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for clipboard handling.
		/// </summary>
		public ref struct Clipboard abstract sealed
		{
		public:
			/// <summary>
			/// Get a text from the clipboard.
			/// </summary>
			/// <returns>The clipboard text on success or an empty string on
			/// failure.</returns>
			static System::String^ GetClipboardText();

			/// <summary>
			/// Query whether the clipboard exists and contains a non-empty
			/// text string.
			/// </summary>
			static property bool HasClipboardText
			{
				bool get();
			}

			/// <summary>
			/// Put a text into the clipboard.
			/// </summary>
			/// <param name="text">The text to store in the clipboard.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> SetClipboardText(System::String^ text);
		};
	}
}