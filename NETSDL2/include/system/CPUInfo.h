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

		/// <summary>
		/// Functions for gathering information about the processor's features.
		/// </summary>
		public ref struct CPUInfo abstract sealed
		{
		public:
			/// <summary>
			/// Determine the L1 cache line size of the CPU in bytes.
			/// </summary>
			static property int CPUCacheLineSize
			{
				int get();
			}

			/// <summary>
			/// Get the number of CPU cores available.
			/// </summary>
			static property int CPUCount
			{
				int get();
			}

			/// <summary>
			/// Get the amount of RAM configured in the system in MiB.
			/// </summary>
			static property int SystemRAM
			{
				int get();
			}

			/// <summary>
			/// Report the alignment this system needs for SIMD allocations.
			/// </summary>
			static property size_t SIMDAlignment
			{
				size_t get();
			}

			/// <summary>
			/// Allocate memory in a SIMD-friendly way.
			/// </summary>
			/// <param name="len">The length, in bytes, of the block to allocate. The actual allocated block
			/// might be larger due to padding, etc.</param>
			/// <returns>A pointer to the newly-allocated block, None if out of memory.</returns>
			static Result<System::IntPtr, None^> SIMDAlloc(size_t len);

			/// <summary>
			/// Reallocate memory obtained from <see cref="SIMDAlloc"/>.
			/// </summary>
			/// <param name="mem">The pointer obtained from <see cref="SIMDAlloc"/>.</param>
			/// <param name="len">The length, in bytes, of the block to allocated.</param>
			/// <returns>A pointer to the newly-reallocated block, None if out of memory.</returns>
			static Result<System::IntPtr, None^> SIMDRealloc(System::IntPtr mem, size_t len);

			/// <summary>
			/// Deallocate memory obtained from <see cref="SIMDAlloc"/>.
			/// </summary>
			/// <param name="ptr">The pointer, returned from <see cref="SIMDAlloc"/> or
			/// <see cref="SIMDRealloc"/>, to deallocate.</param>
			static void SIMDFree(System::IntPtr ptr);

			/// <summary>
			/// Determine whether the CPU has 3DNow! features.
			/// </summary>
			static property bool Has3DNow
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has AltiVec features.
			/// </summary>
			static property bool HasAltiVec
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has AVX features.
			/// </summary>
			static property bool HasAVX
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has AVX2 features.
			/// </summary>
			static property bool HasAVX2
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has AVX-512F features.
			/// </summary>
			static property bool HasAVX512F
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has ARM SIMD (ARMv6) features.
			/// </summary>
			static property bool HasARMSIMD
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has NEON (ARM SIMD) features.
			/// </summary>
			static property bool HasNEON
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has LSX (LOONGARCH SIMD) features.
			/// </summary>
			static property bool HasLSX
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has LASX (LOONGARCH SIMD) features.
			/// </summary>
			static property bool HasLASX
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has MMX features.
			/// </summary>
			static property bool HasMMX
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has the RDTSC instruction.
			/// </summary>
			static property bool HasRDTSC
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has SSE features.
			/// </summary>
			static property bool HasSSE
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has SSE2 features.
			/// </summary>
			static property bool HasSSE2
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has SSE3 features.
			/// </summary>
			static property bool HasSSE3
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has SSE4.1 features.
			/// </summary>
			static property bool HasSSE41
			{
				bool get();
			}

			/// <summary>
			/// Determine whether the CPU has SSE4.2 features.
			/// </summary>
			static property bool HasSSE42
			{
				bool get();
			}
		};
	}
}
