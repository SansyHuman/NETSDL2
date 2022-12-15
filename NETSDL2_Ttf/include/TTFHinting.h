#pragma once

#include <SDL_ttf.h>

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Text
	{
		/// <summary>
		/// Font hinting flags.
		/// </summary>
		public enum class TTFHinting
		{
			Normal = TTF_HINTING_NORMAL,
			Light = TTF_HINTING_LIGHT,
			Mono = TTF_HINTING_MONO,
			None = TTF_HINTING_NONE,
			LightSubpixel = TTF_HINTING_LIGHT_SUBPIXEL,
		};
	}
}