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
		/// A structure that contains audio data conversion information.
		/// </summary>
        [StructLayout(LayoutKind::Sequential)]
		public value struct AudioCVT
		{
        public:
            [StructLayout(LayoutKind::Sequential, Size = sizeof(SDL_AudioFilter) * (SDL_AUDIOCVT_MAX_FILTERS + 1))]
            [CompilerGenerated]
            [UnsafeValueType]
            value struct e__FixedBuffer
            {
                SDL_AudioFilter FixedElementField;
            };

        public:
            /// <summary>
            /// Set to 1 if conversion possible.
            /// </summary>
            int Needed;

            /// <summary>
            /// Source audio format.
            /// </summary>
            AudioFormat SrcFormat;

            /// <summary>
            /// Target audio format.
            /// </summary>
            AudioFormat DstFormat;

            /// <summary>
            /// Rate conversion increment.
            /// </summary>
            double RateIncr;

            /// <summary>
            /// The buffer to hold entire audio data.
            /// </summary>
            Uint8* Buf;

            /// <summary>
            /// Length of original audio buffer.
            /// </summary>
            int Len;

            /// <summary>
            /// Length of converted audio buffer.
            /// </summary>
            int LenCvt;

            /// <summary>
            /// Buf must be Len*LenMult big.
            /// </summary>
            int LenMult;

            /// <summary>
            /// Given len, final size is Len*LenRatio.
            /// </summary>
            double LenRatio;

        private:
            [FixedBuffer(SDL_AudioFilter::typeid, SDL_AUDIOCVT_MAX_FILTERS + 1)]
            e__FixedBuffer filters;
            int filter_index;
		};
	}
}