#pragma once

#include <SDL.h>
#include <SDL_bits.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Systems
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for bit-level operations ("bit-twiddling").
		/// </summary>
		public ref struct Bits abstract sealed
		{
		public:
			/// <summary>
			/// Use this function to get the index of the most significant (set) bit
			/// in a 32-bit number. This is also the same as the base 2 logarithm of
			/// the number.
			/// </summary>
			/// <param name="x">The number to find the MSB of</param>
			/// <returns>The index of the most significant bit of x, or -1 if x is 0.
			/// </returns>
			static int MostSignificantBitIndex32(Uint32 x);

			static bool HasExactlyOneBitSet32(Uint32 x);
		};
	}
}