#pragma once

#include <SDL_mixer.h>

#include "InitFlags.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		/// <summary>
		/// NETSDL2_Mmage global functions.
		/// </summary>
		public ref struct Mixer abstract sealed
		{
		public:
			/// <summary>
			/// Initialize SDL_mixer.
			/// </summary>
			/// <param name="flags">Initialization flags, OR'd together.</param>
			/// <returns>All currently initialized flags.</returns>
			static MixerInitFlags Init(MixerInitFlags flags);

			/// <summary>
			/// Dynamically change the number of channels managed by the mixer.
			/// </summary>
			/// <param name="numchans">The new number of channels, or less than 0 to
			/// query current channel count.</param>
			/// <returns>The new number of allocated channels.</returns>
			static int AllocateChannels(int numchans);

			/// <summary>
			/// Set a callback that runs when a channel has finished playing.
			/// </summary>
			/// <param name="channelFinished">The callback function to become the new
			/// notification mechanism.</param>
			static void ChannelFinished(void (SDLCALL* channelFinished)(int channel));

			/// <summary>
			/// Close the mixer, halting all playing audio.
			/// </summary>
			static void CloseAudio();
		};
	}
}