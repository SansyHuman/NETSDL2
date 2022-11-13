#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// The scaling mode for a texture.
		/// </summary>
		public enum class ScaleMode
		{
			/// <summary>
			/// Nearest pixel sampling.
			/// </summary>
			Nearest = SDL_ScaleModeNearest,

			/// <summary>
			/// Linear filtering.
			/// </summary>
			Linear = SDL_ScaleModeLinear,

			/// <summary>
			/// Anisotropic filtering.
			/// </summary>
			Best = SDL_ScaleModeBest,
		};
	}
}