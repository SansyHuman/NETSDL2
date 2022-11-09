#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of texture access patterns.
		/// </summary>
		public enum class TextureAccess
		{
			/// <summary>
			/// Changes rarely, not lockable.
			/// </summary>
			Static = SDL_TEXTUREACCESS_STATIC,

			/// <summary>
			/// Changes frequently, lockable.
			/// </summary>
			Streaming = SDL_TEXTUREACCESS_STREAMING,

			/// <summary>
			/// Can be used as a render target.
			/// </summary>
			Target = SDL_TEXTUREACCESS_TARGET,
		};
	}
}