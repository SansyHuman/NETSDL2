#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"
#include "TextureAccess.h"
#include "Blend.h"
#include "Rect.h"

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
			bool releaseOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Texture^>^ nativeTextureConnections;

			static Texture()
			{
				nativeTextureConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Texture^>();
			}

		internal:
			Texture(SDL_Texture* texture, bool releaseOnDestroy);

			// Gets texture from native surface, or null if not exists.
			static Texture^ GetTextureFromNative(SDL_Texture* texture);

			property SDL_Texture* NativeTexture
			{
				SDL_Texture* get();
			}

		private:
			void InitTexture(SDL_Texture* texture);

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

			/// <summary>
			/// Get the additional alpha value multiplied into render copy
			/// operations.
			/// </summary>
			/// <returns>Alpha value on success or error code on failure.</returns>
			Result<Uint8, int> GetTextureAlphaMod();

			/// <summary>
			/// Get the blend mode used for texture copy operations.
			/// </summary>
			/// <returns>Blend mode on success or error code on failure.</returns>
			Result<BlendMode, int> GetTextureBlendMode();

			/// <summary>
			/// Get the additional color value multiplied into render copy
			/// operations.
			/// </summary>
			/// <param name="r">The current red color value.</param>
			/// <param name="g">The current green color value.</param>
			/// <param name="b">The current blue color value.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetTextureColorMod([Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b);

			/// <summary>
			/// Lock a portion of the texture for write-only pixel access.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to lock for access; null to lock the entire
			/// texture.</param>
			/// <param name="pixels">This is filled in with a pointer to the
			/// locked pixels, appropriately offset by the locked area.</param>
			/// <param name="pitch">This is filled in with the pitch of the locked
			/// pixels; the pitch is the length of one row in bytes.</param>
			/// <returns>None on success or error code if the texture is not
			/// valid or was not created with
			/// <see cref="TextureAccess::Streaming"/>.</returns>
			Result<None^, int> LockTexture(System::Nullable<Rect> rect, [Out]System::IntPtr% pixels, [Out]int% pitch);

			/// <summary>
			/// Query the attributes of a texture.
			/// </summary>
			/// <param name="format">The raw format of the texture.</param>
			/// <param name="access">The actual access to the texture.</param>
			/// <param name="w">The width of the texture in pixels.</param>
			/// <param name="h">The height of the texture in pixels.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> QueryTexture([Out]PixelFormatEnum% format, [Out]TextureAccess% access, [Out]int% w, [Out]int% h);
		};
	}
}