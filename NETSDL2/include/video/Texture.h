#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"
#include "TextureAccess.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Renderer;
		ref class Surface;

		/// <summary>
		/// Texture.
		/// </summary>
		public ref class Texture
		{
		private:
			SDL_Texture* texture;

		internal:
			Texture(SDL_Texture* texture);

		public:
			/// <summary>
			/// Create a texture for a rendering context.
			/// </summary>
			/// <param name="renderer">The rendering context.</param>
			/// <param name="format">One of the enumerated values in
			/// <see cref="PixelFormatEnum"/>.</param>
			/// <param name="access">One of the enumerated values in
			/// <see cref="TextureAccess"/></param>
			/// <param name="w">The width of the texture in pixels.</param>
			/// <param name="h">The height of the texture in pixels.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Texture(Renderer^ renderer, PixelFormatEnum format, TextureAccess access, int w, int h);

			/// <summary>
			/// Create a texture from an existing surface.
			/// </summary>
			/// <param name="renderer">The rendering context.</param>
			/// <param name="surface">The surface containing pixel data used
			/// to fill the texture.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Texture(Renderer^ renderer, Surface^ surface);

			~Texture();
			!Texture();
		};
	}
}