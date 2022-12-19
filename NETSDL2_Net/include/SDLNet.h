#pragma once

#include <SDL_net.h>

#include "IGenericSocket.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Net
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions of SDL_net.
		/// </summary>
		public ref struct SDLNet abstract sealed
		{
		public:
			/// <summary>
			/// Query the version of SDL_net that the program is compiled against.
			/// </summary>
			static property SDLVersion Version
			{
				SDLVersion get();
			}

			/// <summary>
			/// Query the version of SDL_net that the program is linked against.
			/// </summary>
			static property SDLVersion LinkedVersion
			{
				SDLVersion get();
			}

			/// <summary>
			/// Initialize SDL_net.
			/// </summary>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> Init();

			/// <summary>
			/// Deinitialize SDL_net.
			/// </summary>
			static void Quit();

			/// <summary>
			/// See if a specific socket has data available after checking it in a set.
			/// </summary>
			/// <param name="sock">The socket to check.</param>
			/// <returns>true if socket has new data available, false otherwise.</returns>
			static bool SocketReady(IGenericSocket^ sock);

			/// <summary>
			/// Write a 16-bit value to network packet buffer.
			/// </summary>
			/// <param name="value">Value to write.</param>
			/// <param name="areap">Buffer pointer to write.</param>
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void Write16(Uint16 value, System::IntPtr areap);

			/// <summary>
			/// Write a 32-bit value to network packet buffer.
			/// </summary>
			/// <param name="value">Value to write.</param>
			/// <param name="areap">Buffer pointer to write.</param>
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void Write32(Uint32 value, System::IntPtr areap);

			/// <summary>
			/// Read a 16-bit value from network packet buffer.
			/// </summary>
			/// <param name="areap">Buffer pointer to read.</param>
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static Uint16 Read16(System::IntPtr areap);

			/// <summary>
			/// Read a 32-bit value from network packet buffer.
			/// </summary>
			/// <param name="areap">Buffer pointer to read.</param>
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static Uint32 Read32(System::IntPtr areap);
		};
	}
}