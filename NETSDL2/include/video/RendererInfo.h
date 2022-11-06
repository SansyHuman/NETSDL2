#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of flags used when creating a rendering context.
		/// </summary>
		[System::Flags]
		public enum class RendererFlags : Uint32
		{
			None = 0,

			/// <summary>
			/// The renderer is a software fallback.
			/// </summary>
			Software = SDL_RENDERER_SOFTWARE,

			/// <summary>
			/// The renderer uses hardware acceleration.
			/// </summary>
			Accelerated = SDL_RENDERER_ACCELERATED,

			/// <summary>
			/// Present is synchronized with the refresh rate.
			/// </summary>
			PresentVsync = SDL_RENDERER_PRESENTVSYNC,

			/// <summary>
			/// The renderer supports rendering to texture.
			/// </summary>
			TargetTexture = SDL_RENDERER_TARGETTEXTURE,
		};
	}
}