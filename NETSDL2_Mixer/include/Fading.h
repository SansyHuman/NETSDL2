#pragma once

#include <SDL_mixer.h>

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		/// <summary>
		/// The different fading types supported.
		/// </summary>
		public enum class Fading
		{
			NoFading = MIX_NO_FADING,
			FadingOut = MIX_FADING_OUT,
			FadingIn = MIX_FADING_IN,
		};
	}
}