#pragma once

#include <SDL.h>
#include "SDLVersion.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Functions used to get information about the version of SDL.
		/// </summary>
		public ref struct Version abstract sealed
		{
		public:
			/// <summary>
			/// Get the code revision of SDL that is linked against your program.
			/// </summary>
			static property System::String^ Revision
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the version of SDL that is linked against the program.
			/// </summary>
			static property SDLVersion LibraryVersion
			{
				SDLVersion get();
			}

			/// <summary>
			/// Get the version of SDL that is compiled against the NETSDL2
			/// library.
			/// </summary>
			static property SDLVersion CompiledVersion
			{
				SDLVersion get();
			}
		};
	}
}