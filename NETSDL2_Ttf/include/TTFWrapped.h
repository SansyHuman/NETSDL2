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
		/// Special layout option for rendering wrapped text.
		/// </summary>
		public enum class TTFWrapped
		{
			AlignLeft = TTF_WRAPPED_ALIGN_LEFT,
			AlignCenter = TTF_WRAPPED_ALIGN_CENTER,
			AlignRight = TTF_WRAPPED_ALIGN_RIGHT,
		};
	}
}