#pragma once

#include <SDL.h>

#include "AudioFormat.h"

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// An class that buffers, converts, resamples, and generally streams audio
		/// data.
		/// </summary>
		public ref class AudioStream
		{
		private:
			SDL_AudioStream* stream;

		public:
			/// <summary>
			/// Create a new audio stream.
			/// </summary>
			/// <param name="srcFormat">The format of the source audio.</param>
			/// <param name="srcChannels">The number of channels of the source audio.
			/// </param>
			/// <param name="srcRate">The sampling rate of the source audio.</param>
			/// <param name="dstFormat">The format of the desired audio output.</param>
			/// <param name="dstChannels">The number of channels of the desired audio
			/// output.</param>
			/// <param name="dstRate">The sampling rate of the desired audio output.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			AudioStream(
				AudioFormat srcFormat, Uint8 srcChannels, int srcRate,
				AudioFormat dstFormat, Uint8 dstChannels, int dstRate
			);

			~AudioStream();
			!AudioStream();

			/// <summary>
			/// Add data to be converted/resampled to the stream.
			/// </summary>
			/// <param name="buf">A pointer to the audio data to add.</param>
			/// <param name="len">The number of bytes to write to the stream.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> Put(System::IntPtr buf, int len);

			/// <summary>
			/// Get the number of converted/resampled bytes available.
			/// </summary>
			property int Available
			{
				int get();
			}

			/// <summary>
			/// A buffer to fill with audio data.
			/// </summary>
			/// <param name="buf">A buffer to fill with audio data.</param>
			/// <param name="len">The maximum number of bytes to fill.</param>
			/// <returns>The number of bytes read from the stream, or None on error.
			/// </returns>
			Result<int, None^> Get(System::IntPtr buf, int len);

			/// <summary>
			/// Tell the stream that you're done sending data, and anything being
			/// buffered should be converted/resampled and made available immediately.
			/// </summary>
			void Flush();

			/// <summary>
			/// Clear any pending data in the stream without converting it.
			/// </summary>
			void Clear();
		};
	}
}