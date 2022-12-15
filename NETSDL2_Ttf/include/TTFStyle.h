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
		/// Font style flags
		/// </summary>
		[System::Flags]
		public enum class TTFStyle
		{
			Normal = TTF_STYLE_NORMAL,
			Bold = TTF_STYLE_BOLD,
			Italic = TTF_STYLE_ITALIC,
			Underline = TTF_STYLE_UNDERLINE,
			StrikeThrough = TTF_STYLE_STRIKETHROUGH,
		};
	}
}