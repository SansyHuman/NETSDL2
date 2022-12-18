#pragma once

#include <SDL_net.h>

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
			Result<None^, None^> Init();

			/// <summary>
			/// Deinitialize SDL_net.
			/// </summary>
			void Quit();
		};
	}
}