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
		/// Initialization flags.
		/// </summary>
		[System::Flags]
		public enum class MixerInitFlags : int
		{
			None = 0,
			Flac = MIX_INIT_FLAC,
			Mod = MIX_INIT_MOD,
			Mp3 = MIX_INIT_MP3,
			Ogg = MIX_INIT_OGG,
			Mid = MIX_INIT_MID,
			Opus = MIX_INIT_OPUS,
		};
	}
}
