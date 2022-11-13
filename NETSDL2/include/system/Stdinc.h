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
		/// Provides functions of standard C library.
		/// </summary>
		public ref struct Stdinc abstract sealed
		{
		public:
			literal size_t SIZE_MAX = SDL_SIZE_MAX;
			literal Sint8 MAX_SINT8 = SDL_MAX_SINT8;
			literal Sint8 MIN_SINT8 = SDL_MIN_SINT8;
			literal Uint8 MAX_UINT8 = SDL_MAX_UINT8;
			literal Uint8 MIN_UINT8 = SDL_MIN_UINT8;
			literal Sint16 MAX_SINT16 = SDL_MAX_SINT16;
			literal Sint16 MIN_SINT16 = SDL_MIN_SINT16;
			literal Uint16 MAX_UINT16 = SDL_MAX_UINT16;
			literal Uint16 MIN_UINT16 = SDL_MIN_UINT16;
			literal Sint32 MAX_SINT32 = SDL_MAX_SINT32;
			literal Sint32 MIN_SINT32 = SDL_MIN_SINT32;
			literal Uint32 MAX_UINT32 = SDL_MAX_UINT32;
			literal Uint32 MIN_UINT32 = SDL_MIN_UINT32;
			literal Sint64 MAX_SINT64 = SDL_MAX_SINT64;
			literal Sint64 MIN_SINT64 = SDL_MIN_SINT64;
			literal Uint64 MAX_UINT64 = SDL_MAX_UINT64;
			literal Uint64 MIN_UINT64 = SDL_MIN_UINT64;

			literal float FLT_EPSILON = SDL_FLT_EPSILON;

			literal double PI = M_PI;

			/// <summary>
			/// Define a four character code as a Uint32.
			/// </summary>
			/// <param name="a">First character.</param>
			/// <param name="b">Second character.</param>
			/// <param name="c">Third character.</param>
			/// <param name="d">Fourth caracter.</param>
			/// <returns>Uint32 code of four character.</returns>
			static Uint32 FourCC(Uint8 a, Uint8 b, Uint8 c, Uint8 d);

			/// <summary>
			/// Allocate the memory.
			/// </summary>
			/// <param name="size">Size of the memory to allocate in bytes.</param>
			/// <returns>Allocated memory on success or None on failure.</returns>
			static Result<System::IntPtr, None^> Malloc(size_t size);

			/// <summary>
			/// Allocate the memory.
			/// </summary>
			/// <param name="nmemb">The number of objects.</param>
			/// <param name="size">Size of each object.</param>
			/// <returns>Allocated memory on success or None on failure.</returns>
			static Result<System::IntPtr, None^> Calloc(size_t nmemb, size_t size);

			/// <summary>
			/// Reallocate the given area of memory.
			/// </summary>
			/// <param name="mem">Pointer to the memory area to be reallocated.</param>
			/// <param name="size">New size of the memory in bytes.</param>
			/// <returns>Allocated memory on success or None on failure.</returns>
			static Result<System::IntPtr, None^> Realloc(System::IntPtr mem, size_t size);

			/// <summary>
			/// Free the memory.
			/// </summary>
			/// <param name="mem">Pointer to the memory area to be freed.</param>
			static void Free(System::IntPtr mem);

			/// <summary>
			/// Get the original set of SDL memory functions.
			/// </summary>
			/// <param name="mallocFunc"></param>
			/// <param name="callocFunc"></param>
			/// <param name="reallocFunc"></param>
			/// <param name="freeFunc"></param>
			static void GetOriginalMemoryFunctions(
				[Out]SDL_malloc_func% mallocFunc,
				[Out]SDL_calloc_func% callocFunc,
				[Out]SDL_realloc_func% reallocFunc,
				[Out]SDL_free_func% freeFunc
			);

			/// <summary>
			/// Get the current set of SDL memory functions.
			/// </summary>
			/// <param name="mallocFunc"></param>
			/// <param name="callocFunc"></param>
			/// <param name="reallocFunc"></param>
			/// <param name="freeFunc"></param>
			static void GetMemoryFunctions(
				[Out]SDL_malloc_func% mallocFunc,
				[Out]SDL_calloc_func% callocFunc,
				[Out]SDL_realloc_func% reallocFunc,
				[Out]SDL_free_func% freeFunc
			);

			/// <summary>
			/// Replace SDL's memory allocation functions with a custom set.
			/// </summary>
			/// <param name="mallocFunc"></param>
			/// <param name="callocFunc"></param>
			/// <param name="reallocFunc"></param>
			/// <param name="freeFunc"></param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> SetMemoryFunctions(
				SDL_malloc_func mallocFunc,
				SDL_calloc_func callocFunc,
				SDL_realloc_func reallocFunc,
				SDL_free_func freeFunc
			);

			/// <summary>
			/// Get the number of outstanding (unfreed) allocations.
			/// </summary>
			static property int NumAllocations
			{
				int get();
			}

			/// <summary>
			/// Get the CRC16 checksum of the data.
			/// </summary>
			/// <param name="crc">16-bit CRC value.</param>
			/// <param name="data">Data to check.</param>
			/// <param name="len">Byte length of the data.</param>
			/// <returns>CRC16 checksum.</returns>
			static Uint16 CRC16(Uint16 crc, System::IntPtr data, size_t len);

			/// <summary>
			/// Get the CRC32 checksum of the data.
			/// </summary>
			/// <param name="crc">32-bit CRC value.</param>
			/// <param name="data">Data to check.</param>
			/// <param name="len">Byte length of the data.</param>
			/// <returns>CRC16 checksum.</returns>
			static Uint32 CRC32(Uint32 crc, System::IntPtr data, size_t len);

			/// <summary>
			/// Sets a buffer to a specified character.
			/// </summary>
			/// <param name="dst">Pointer to destination.</param>
			/// <param name="c">Character to set.</param>
			/// <param name="len">Number of characters.</param>
			/// <returns>dst pointer on success or None on failure.</returns>
			static Result<System::IntPtr, None^> Memset(System::IntPtr dst, unsigned char c, size_t len);

			/// <summary>
			/// Sets a buffer to a specified 32-bit value.
			/// </summary>
			/// <param name="dst">Pointer to destination.</param>
			/// <param name="val">32-bit value to set.</param>
			/// <param name="dwords">The number of 32-bit values.</param>
			static void Memset4(System::IntPtr dst, Uint32 val, size_t dwords);

			/// <summary>
			/// Copies count bytes from the object pointed to by src to the object pointed to by dst.
			/// </summary>
			/// <param name="dst">Pointer to destination.</param>
			/// <param name="src">Pointer to source.</param>
			/// <param name="len">Byte length to copy.</param>
			static void Memcpy(System::IntPtr dst, System::IntPtr src, size_t len);

			/// <summary>
			/// Copies count bytes from the object pointed to by src to the object pointed to by dst.
			/// </summary>
			/// <param name="dst">Pointer to destination.</param>
			/// <param name="src">Pointer to source.</param>
			/// <param name="len">Byte length to copy.</param>
			static void Memmove(System::IntPtr dst, System::IntPtr src, size_t len);

			/// <summary>
			/// Copies count bytes from the object pointed to by src to the object pointed to by dst.
			/// </summary>
			/// <param name="dst">Pointer to destination.</param>
			/// <param name="src">Pointer to source.</param>
			/// <param name="dwords">Length to copy in DWORD(32-bit) count.</param>
			static void Memcpy4(System::IntPtr dst, System::IntPtr src, size_t dwords);
		};
	}
}