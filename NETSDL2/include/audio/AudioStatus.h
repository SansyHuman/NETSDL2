#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		/// <summary>
		/// An enumeration of audio device states.
		/// </summary>
		public enum class AudioStatus
		{
			/// <summary>
			/// Audio device is stopped.
			/// </summary>
			Stopped = SDL_AUDIO_STOPPED,

			/// <summary>
			/// Audio device is playing.
			/// </summary>
			Playing = SDL_AUDIO_PLAYING,

			/// <summary>
			/// Audio device is paused.
			/// </summary>
			Paused = SDL_AUDIO_PAUSED,
		};
	}
}