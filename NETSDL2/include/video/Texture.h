#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"
#include "TextureAccess.h"
#include "Blend.h"
#include "Rect.h"
#include "ScaleMode.h"

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
			Texture(void* texture, bool releaseOnDestroy);

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
			/// Get the scale mode used for texture scale operations.
			/// </summary>
			/// <returns>Scale mode on success or error code on failure.</returns>
			Result<ScaleMode, int> GetTextureScaleMode();

			/// <summary>
			/// Get the user-specified pointer associated with a texture
			/// </summary>
			/// <returns>The pointer associated with the texture or None if the texture is not valid.
			/// </returns>
			Result<System::IntPtr, None^> GetTextureUserData();

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
			/// Lock a portion of the texture for write-only pixel access, and expose it as a SDL
			/// surface.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to lock for access; null to lock the entire
			/// texture.</param>
			/// <param name="surface">SDL surface representing the locked area.</param>
			/// <returns>None on success or error code if the texture is not
			/// valid or was not created with
			/// <see cref="TextureAccess::Streaming"/></returns>
			Result<None^, int> LockTextureToSurface(System::Nullable<Rect> rect, [Out]Surface^% surface);

			/// <summary>
			/// Query the attributes of a texture.
			/// </summary>
			/// <param name="format">The raw format of the texture.</param>
			/// <param name="access">The actual access to the texture.</param>
			/// <param name="w">The width of the texture in pixels.</param>
			/// <param name="h">The height of the texture in pixels.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> QueryTexture([Out]PixelFormatEnum% format, [Out]TextureAccess% access, [Out]int% w, [Out]int% h);

			/// <summary>
			/// Set an additional alpha value multiplied into render copy
			/// operations.
			/// </summary>
			/// <param name="alpha">The source alpha value multiplied into copy
			/// operations.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetTextureAlphaMod(Uint8 alpha);

			/// <summary>
			/// Set the blend mode used for texture copy operations.
			/// </summary>
			/// <param name="blendMode">The <see cref="BlendMode"/> to use for
			/// texture blending.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetTextureBlendMode(BlendMode blendMode);

			/// <summary>
			/// Set an additional color value multiplied into render copy
			/// operations.
			/// </summary>
			/// <param name="r">The red color value multiplied into copy
			/// operations.</param>
			/// <param name="g">The green color value multiplied into copy
			/// operations.</param>
			/// <param name="b">The blue color value multiplied into copy
			/// operations.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetTextureColorMod(Uint8 r, Uint8 g, Uint8 b);

			/// <summary>
			/// Set the scale mode used for texture scale operations.
			/// </summary>
			/// <param name="scaleMode">the <see cref="ScaleMode"/> to use for texture scaling.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetTextureScaleMode(ScaleMode scaleMode);

			/// <summary>
			/// Associate a user-specified pointer with a texture.
			/// </summary>
			/// <param name="userdata">The pointer to associate with the texture.</param>
			/// <returns>None on success, or -1 if the texture is not valid.</returns>
			Result<None^, int> SetTextureUserData(System::IntPtr userdata);

			/// <summary>
			/// Unlock a texture, uploading the changes to video memory, if needed.
			/// </summary>
			void UnlockTexture();

			/// <summary>
			/// Update the given texture rectangle with new pixel data.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to update, or null to update the entire
			/// texture.</param>
			/// <param name="pixels">The raw pixel data in the format of the
			/// texture.</param>
			/// <param name="pitch">The number of bytes in a row of pixel data,
			/// including padding between lines.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> UpdateTexture(System::Nullable<NETSDL2::Video::Rect> rect, System::IntPtr pixels, int pitch);

			/// <summary>
			/// Update a rectangle within a planar YV12 or IYUV texture with new
			/// pixel data.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to update, or null to update the entire
			/// texture.</param>
			/// <param name="yplane">The raw pixel data for the Y plane.</param>
			/// <param name="ypitch">The number of bytes between rows of pixel
			/// data for the Y plane.</param>
			/// <param name="uplane">The raw pixel data for the U plane.</param>
			/// <param name="upitch">The number of bytes between rows of pixel
			/// data for the U plane.</param>
			/// <param name="vplane">The raw pixel data for the V plane.</param>
			/// <param name="vpitch">The number of bytes between rows of pixel
			/// data for the V plane.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> UpdateYUVTexture(
				System::Nullable<NETSDL2::Video::Rect> rect,
				Uint8* yplane, int ypitch, Uint8* uplane, int upitch,
				Uint8* vplane, int vpitch);

			/// <summary>
			/// Update a rectangle within a planar NV12 or NV21 texture with new pixels.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to update, or null to update the entire
			/// texture.</param>
			/// <param name="yplane">The raw pixel data for the Y plane.</param>
			/// <param name="ypitch">The number of bytes between rows of pixel
			/// data for the Y plane.</param>
			/// <param name="uvplane">The raw pixel data for the UV plane.</param>
			/// <param name="uvpitch">The number of bytes between rows of pixel
			/// data for the UV plane.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> UpdateNVTexture(
				System::Nullable<NETSDL2::Video::Rect> rect,
				Uint8* yplane, int ypitch, Uint8* uvplane, int uvpitch);
		};
	}
}