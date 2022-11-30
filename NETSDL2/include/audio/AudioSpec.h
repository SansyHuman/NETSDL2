#pragma once

#include <SDL.h>

#include "AudioFormat.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		/// <summary>
		/// A structure that contains the audio output format. It also contains a callback
		/// that is called when the audio device needs more data.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct AudioSpec
		{
			/// <summary>
			/// DSP frequency (samples per second).
			/// </summary>
			int Freq;

			/// <summary>
			/// Audio data format.
			/// </summary>
			AudioFormat Format;

			/// <summary>
			/// Number of separate sound channels.
			/// </summary>
			Uint8 Channels;

			/// <summary>
			/// Audio buffer silence value (calculated).
			/// </summary>
			Uint8 Silence;

			/// <summary>
			/// Audio buffer size in samples (power of 2).
			/// </summary>
			Uint16 Samples; 
			Uint16 padding;

			/// <summary>
			/// Audio buffer size in bytes (calculated).
			/// </summary>
			Uint32 Size;

			/// <summary>
			/// The function to call when the audio device needs more data.
			/// </summary>
			SDL_AudioCallback Callback;

			/// <summary>
			/// A pointer that is passed to callback.
			/// </summary>
			System::IntPtr Userdata;

			virtual System::String^ ToString() override;
		};
	}
}