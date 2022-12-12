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
		/// These are types of music files (not libraries used to load them).
		/// </summary>
		public enum class MusicType
		{
			None = MUS_NONE,
			Cmd = MUS_CMD,
			Wav = MUS_WAV,
			Mod = MUS_MOD,
			Mid = MUS_MID,
			Ogg = MUS_OGG,
			Mp3 = MUS_MP3,
			Mp3MadUnused = MUS_MP3_MAD_UNUSED,
			Flac = MUS_FLAC,
			ModplugUnused = MUS_MODPLUG_UNUSED,
			Opus = MUS_OPUS,
		};
	}
}