#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Audio
	{
		/// <summary>
		/// An enumeration of audio formats.
		/// </summary>
		public enum class AudioFormat : Uint16
		{
			/// <summary>
			/// Unsigned 8-bit samples.
			/// </summary>
			U8 = AUDIO_U8,

			/// <summary>
			/// Signed 8-bit samples.
			/// </summary>
			S8 = AUDIO_S8,

			/// <summary>
			/// Unsigned 16-bit samples in little-endian byte order.
			/// </summary>
			U16LSB = AUDIO_U16LSB,

			/// <summary>
			/// Signed 16-bit samples in little-endian byte order.
			/// </summary>
			S16LSB = AUDIO_S16LSB,

			/// <summary>
			/// Unsigned 16-bit samples in big-endian byte order.
			/// </summary>
			U16MSB = AUDIO_U16MSB,
			
			/// <summary>
			/// Signed 16-bit samples in big-endian byte order.
			/// </summary>
			S16MSB = AUDIO_S16MSB,

			/// <summary>
			/// U16LSB.
			/// </summary>
			U16 = AUDIO_U16,

			/// <summary>
			/// S16LSB
			/// </summary>
			S16 = AUDIO_S16,

			/// <summary>
			/// 32-bit integer samples in little-endian byte order.
			/// </summary>
			S32LSB = AUDIO_S32LSB,

			/// <summary>
			/// 32-bit integer samples in big-endian byte order.
			/// </summary>
			S32MSB = AUDIO_S32MSB,

			/// <summary>
			/// S32LSB.
			/// </summary>
			S32 = AUDIO_S32,

			/// <summary>
			/// 32-bit floating point samples in little-endian byte order.
			/// </summary>
			F32LSB = AUDIO_F32LSB,

			/// <summary>
			/// 32-bit floating point samples in big-endian byte order.
			/// </summary>
			F32MSB = AUDIO_F32MSB,

			/// <summary>
			/// F32LSB.
			/// </summary>
			F32 = AUDIO_F32,

			/// <summary>
			/// Unsigned 16-bit samples in native byte order.
			/// </summary>
			U16Sys = AUDIO_U16SYS,

			/// <summary>
			/// Signed 16-bit samples in native byte order.
			/// </summary>
			S16Sys = AUDIO_S16SYS,

			/// <summary>
			/// 32-bit integer samples in native byte order.
			/// </summary>
			S32Sys = AUDIO_S32SYS,

			/// <summary>
			/// 32-bit floating point samples in native byte order.
			/// </summary>
			F32Sys = AUDIO_F32SYS,
		};

		/// <summary>
		/// Functions that queries the audio format data.
		/// </summary>
		public ref struct AudioFormatHelper abstract sealed
		{
		public:
			/// <summary>
			/// Get the sample bit size of the audio format.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>Sample bit size of the format.</returns>
			static Uint16 Bitsize(AudioFormat format);

			/// <summary>
			/// Get whether the sample is float.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is float, else false.</returns>
			static bool IsFloat(AudioFormat format);

			/// <summary>
			/// Get whether the sample is big endian.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is big endian, else false.</returns>
			static bool IsBigEndian(AudioFormat format);

			/// <summary>
			/// Get whether the sample is signed.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is signed, else false.</returns>
			static bool IsSigned(AudioFormat format);

			/// <summary>
			/// Get whether the sample is integer.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is integer, else false.</returns>
			static bool IsInt(AudioFormat format);

			/// <summary>
			/// Get whether the sample is little endian.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is little endian, else false.</returns>
			static bool IsLittleEndian(AudioFormat format);

			/// <summary>
			/// Get whether the sample is unsigned.
			/// </summary>
			/// <param name="format">Audio format.</param>
			/// <returns>true if sample is unsigned, else false.</returns>
			static bool IsUnsigned(AudioFormat format);
		};
	}
}