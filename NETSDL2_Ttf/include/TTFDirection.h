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
		/// Direction flags.
		/// </summary>
		public enum class TTFDirection
		{
			LTR = TTF_DIRECTION_LTR,
			RTL = TTF_DIRECTION_RTL,
			TTB = TTF_DIRECTION_TTB,
			BTT = TTF_DIRECTION_BTT,
		};
	}
}