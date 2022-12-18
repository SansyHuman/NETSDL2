#pragma once

#include <SDL_ttf.h>

#include "TTFDirection.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Text
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// SDL_ttf functions.
		/// </summary>
		public ref struct TTF abstract sealed
		{
		public:
			/// <summary>
			/// Tell SDL_ttf whether UNICODE text is generally byteswapped.
			/// </summary>
			/// <param name="swapped">Boolean to indicate whether text is
			/// byteswapped.</param>
			static void ByteSwappedUnicode(bool swapped);

			/// <summary>
			/// Query the version of the FreeType library in use.
			/// </summary>
			/// <param name="major">The major version number.</param>
			/// <param name="minor">The minor version number.</param>
			/// <param name="patch">The param version number.</param>
			static void GetFreeTypeVersion([Out]int% major, [Out]int% minor, [Out]int% patch);

			/// <summary>
			/// Query the version of the HarfBuzz library in use.
			/// </summary>
			/// <param name="major">The major version number.</param>
			/// <param name="minor">The minor version number.</param>
			/// <param name="patch">The param version number.</param>
			static void GetHarfBuzzVersion([Out]int% major, [Out]int% minor, [Out]int% patch);

			/// <summary>
			/// Initialize SDL_ttf.
			/// </summary>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> Init();

			/// <summary>
			/// Query the version of SDL_ttf that the program is linked against.
			/// </summary>
			static property SDLVersion LinkedVersion
			{
				SDLVersion get();
			}

			/// <summary>
			/// Query the version of SDL_ttf that the program is compiled against.
			/// </summary>
			static property SDLVersion Version
			{
				SDLVersion get();
			}

			/// <summary>
			/// Deinitialize SDL_ttf.
			/// </summary>
			static void Quit();

			/// <summary>
			/// Set a global direction to be used for text shaping.
			/// </summary>
			/// <param name="direction">A direction value.</param>
			/// <returns>Success or Failure if SDL_ttf is not compiled with HarfBuzz
			/// support.</returns>
			static Result<None^, None^> SetDirection(TTFDirection direction);

			/// <summary>
			/// Set a global script to be used for text shaping.
			/// </summary>
			/// <param name="script"></param>
			/// <returns>Success or Failure if SDL_ttf is not compiled with HarfBuzz
			/// support.</returns>
			static Result<None^, None^> SetScript(int script);

			/// <summary>
			/// Get the current number of initialization calls
			/// </summary>
			static property int WasInit
			{
				int get();
			}
		};
	}
}