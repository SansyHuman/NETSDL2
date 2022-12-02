#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Systems
	{
		using namespace NETSDL2::Core;

#pragma unmanaged
		Uint16 swap16(Uint16 x)
		{
			return SDL_Swap16(x);
		}

		Uint32 swap32(Uint32 x)
		{
			return SDL_Swap32(x);
		}

		Uint64 swap64(Uint64 x)
		{
			return SDL_Swap64(x);
		}

		Uint16 swapBE16(Uint16 x)
		{
			return SDL_SwapBE16(x);
		}

		Uint32 swapBE32(Uint32 x)
		{
			return SDL_SwapBE32(x);
		}

		Uint64 swapBE64(Uint64 x)
		{
			return SDL_SwapBE64(x);
		}

		float swapFloat(float x)
		{
			return SDL_SwapFloat(x);
		}

		float swapFloatBE(float x)
		{
			return SDL_SwapFloatBE(x);
		}

		float swapFloatLE(float x)
		{
			return SDL_SwapFloatLE(x);
		}

		Uint16 swapLE16(Uint16 x)
		{
			return SDL_SwapLE16(x);
		}

		Uint32 swapLE32(Uint32 x)
		{
			return SDL_SwapLE32(x);
		}

		Uint64 swapLE64(Uint64 x)
		{
			return SDL_SwapLE64(x);
		}

#pragma managed

		/// <summary>
		/// Functions for handling endian-specific values.
		/// </summary>
		public ref struct Endian abstract sealed
		{
		public:
			/// <summary>
			/// Use this function to swap the byte order of a 16-bit value.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The swapped value.</returns>
			static Uint16 Swap16(Uint16 x);

			/// <summary>
			/// Use this function to swap the byte order of a 32-bit value.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The swapped value.</returns>
			static Uint32 Swap32(Uint32 x);

			/// <summary>
			/// Use this function to swap the byte order of a 64-bit value.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The swapped value.</returns>
			static Uint64 Swap64(Uint64 x);

			/// <summary>
			/// Use this function to swap the byte order of a 16-bit big-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 16-bit value.</returns>
			static Uint16 SwapBE16(Uint16 x);

			/// <summary>
			/// Use this function to swap the byte order of a 32-bit big-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 32-bit value.</returns>
			static Uint32 SwapBE32(Uint32 x);

			/// <summary>
			/// Use this function to swap the byte order of a 64-bit big-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 64-bit value.</returns>
			static Uint64 SwapBE64(Uint64 x);

			/// <summary>
			/// Use this function to swap the byte order of a floating point value.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The swapped value.</returns>
			static float SwapFloat(float x);

			/// <summary>
			/// Use this function to swap the byte order of a big-endian floating
			/// point value to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native floating point value.</returns>
			static float SwapFloatBE(float x);

			/// <summary>
			/// Use this function to swap the byte order of a little-endian floating
			/// point value to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native floating point value.</returns>
			static float SwapFloatLE(float x);

			/// <summary>
			/// Use this function to swap the byte order of a 16-bit little-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 16-bit value.</returns>
			static Uint16 SwapLE16(Uint16 x);

			/// <summary>
			/// Use this function to swap the byte order of a 32-bit little-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 32-bit value.</returns>
			static Uint32 SwapLE32(Uint32 x);

			/// <summary>
			/// Use this function to swap the byte order of a 64-bit little-endian value
			/// to native ordering.
			/// </summary>
			/// <param name="x">The value to be swapped.</param>
			/// <returns>The native 64-bit value.</returns>
			static Uint64 SwapLE64(Uint64 x);
		};
	}
}