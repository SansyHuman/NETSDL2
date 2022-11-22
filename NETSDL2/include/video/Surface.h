#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"
#include "Rect.h"
#include "Blend.h"
#include "Palette.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Surface.
		/// </summary>
		public ref class Surface
		{
		private:
			SDL_Surface* surface;
			bool releaseOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Surface^>^ nativeSurfaceConnections;

			static Surface()
			{
				nativeSurfaceConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Surface^>();
			}

		internal:
			Surface(SDL_Surface* surface, bool releaseOnDestroy);
			property SDL_Surface* NativeSurface
			{
				SDL_Surface* get();
			}

			// Gets surface from native surface, or null if not exists.
			static Surface^ GetSurfaceFromNative(SDL_Surface* surface);

		private:
			void InitSurface(SDL_Surface* surface);

		public:
			/// <summary>
			/// Allocate a new RGB surface.
			/// </summary>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="rmask">The red mask for the pixels.</param>
			/// <param name="gmask">The green mask for the pixels.</param>
			/// <param name="bmask">The blue mask for the pixels.</param>
			/// <param name="amask">The alpha mask for the pixels.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(int width, int height, int depth, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

			/// <summary>
			/// Allocate a new RGB surface with existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="rmask">The red mask for the pixels.</param>
			/// <param name="gmask">The green mask for the pixels.</param>
			/// <param name="bmask">The blue mask for the pixels.</param>
			/// <param name="amask">The alpha mask for the pixels.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

			/// <summary>
			/// Allocate a new RGB surface with existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="rmask">The red mask for the pixels.</param>
			/// <param name="gmask">The green mask for the pixels.</param>
			/// <param name="bmask">The blue mask for the pixels.</param>
			/// <param name="amask">The alpha mask for the pixels.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

			/// <summary>
			/// Allocate a new RGB surface with existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="rmask">The red mask for the pixels.</param>
			/// <param name="gmask">The green mask for the pixels.</param>
			/// <param name="bmask">The blue mask for the pixels.</param>
			/// <param name="amask">The alpha mask for the pixels.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

			/// <summary>
			/// Allocate a new RGB surface with a specific pixel format.
			/// </summary>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="format">The new surface's pixel format.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(int width, int height, int depth, PixelFormatEnum format);

			/// <summary>
			/// Allocate a new RGB surface with with a specific pixel format
			/// and existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="format">The new surface's pixel format.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, PixelFormatEnum format);

			/// <summary>
			/// Allocate a new RGB surface with with a specific pixel format
			/// and existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="format">The new surface's pixel format.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(void* pixels, int width, int height, int depth, int pitch, PixelFormatEnum format);

			/// <summary>
			/// Allocate a new RGB surface with with a specific pixel format
			/// and existing pixel data.
			/// </summary>
			/// <param name="pixels">A pointer to existing pixel data.</param>
			/// <param name="width">The width of the surface.</param>
			/// <param name="height">The height of the surface.</param>
			/// <param name="depth">The depth of the surface in bits.</param>
			/// <param name="pitch">The pitch of the surface in bits.</param>
			/// <param name="format">The new surface's pixel format.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, PixelFormatEnum format);

			/// <summary>
			/// Creates a new surface identical to the existing surface.
			/// </summary>
			/// <param name="surface">The surface to duplicate.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Surface(Surface^ surface);

			/// <summary>
			/// Load a BMP image from a file path.
			/// </summary>
			/// <param name="file">The file containing a BMP image.</param>
			Surface(System::String^ file);

			// TODO: LoadBMP_RW

			~Surface();
			!Surface();

			/// <summary>
			/// The format of the pixels stored in the surface.
			/// </summary>
			property PixelFormat% Format
			{
				PixelFormat% get();
			}

			/// <summary>
			/// The width in pixels.
			/// </summary>
			property int Width
			{
				int get();
			}

			/// <summary>
			/// The height in pixels.
			/// </summary>
			property int Height
			{
				int get();
			}

			/// <summary>
			/// The length of a row of pixels in bytes.
			/// </summary>
			property int Pitch
			{
				int get();
			}

			/// <summary>
			/// The pointer to the actual pixel data.
			/// </summary>
			property System::IntPtr Pixels
			{
				System::IntPtr get();
			}

			/// <summary>
			/// An arbitrary pointer you can set.
			/// </summary>
			property System::IntPtr Userdata
			{
				System::IntPtr get();
				void set(System::IntPtr value);
			}

			/// <summary>
			/// A <see cref="NETSDL2::Video::Rect"/> structure used to clip
			/// blits to the surface.
			/// </summary>
			property Rect ClipRect
			{
				Rect get();
			}

			/// <summary>
			/// Use this function to perform a scaled surface copy to a destination
			/// surface.
			/// </summary>
			/// <param name="src">The surface to be copied from.</param>
			/// <param name="srcrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle to be copied, or null to copy
			/// the entire surface.</param>
			/// <param name="dst">The surface that is the blit target.</param>
			/// <param name="dstrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle that is copied into, or null to
			/// copy into the entire surface.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> BlitScaled(Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect,
				Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect);

			/// <summary>
			/// Use this function to perform a fast surface copy to a destination
			/// surface.
			/// </summary>
			/// <param name="src">The surface to be copied from.</param>
			/// <param name="srcrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle to be copied, or null to copy
			/// the entire surface.</param>
			/// <param name="dst">The surface that is the blit target.</param>
			/// <param name="dstrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle that is copied into, or null to
			/// copy into the entire surface.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> BlitSurface(
				Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect,
				Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect);

			/// <summary>
			/// Perform bilinear scaling between two surfaces of the same format, 32BPP.
			/// </summary>
			/// <param name="src">The surface to be copied from.</param>
			/// <param name="srcrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle to be copied, or null to copy
			/// the entire surface.</param>
			/// <param name="dst">The surface that is the blit target.</param>
			/// <param name="dstrect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the rectangle that is copied into, or null to
			/// copy into the entire surface.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> SoftStretchLinear(
				Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect,
				Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect);

			/// <summary>
			/// Copy the surface to a new surface of the specified format.
			/// </summary>
			/// <param name="fmt">The <see cref="PixelFormat"/> structure that
			/// the new surface is optimized for.</param>
			/// <returns>New surface that is created or None on failure.</returns>
			Result<Surface^, None^> ConvertSurface([In][IsReadOnly]PixelFormat% fmt);

			/// <summary>
			/// Copy the surface to a new surface of the specified format enum.
			/// </summary>
			/// <param name="fmt">The <see cref="PixelFormatEnum"/> that
			/// the new surface is optimized for.</param>
			/// <returns>New surface that is created or None on failure.</returns>
			Result<Surface^, None^> ConvertSurfaceFormat(PixelFormatEnum pixelFormat);

			/// <summary>
			/// Perform a fast fill of a rectangle with a specific color.
			/// </summary>
			/// <param name="rect">The <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the rectangle to fill, or NULL to fill the entire
			/// surface.</param>
			/// <param name="color">The color to fill with.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRect(System::Nullable<NETSDL2::Video::Rect> rect, Uint32 color);

			/// <summary>
			/// Perform a fast fill of a set of rectangles with a specific color.
			/// </summary>
			/// <param name="rects">An array of <see cref="NETSDL2::Video::Rect"/>
			/// representing the rectangles to fill.</param>
			/// <param name="color">The color to fill with.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRects(array<NETSDL2::Video::Rect>^ rects, Uint32 color);

			/// <summary>
			/// Get the color key (transparent pixel) for a surface.
			/// </summary>
			/// <returns>Color key on success or error code on failure.</returns>
			Result<Uint32, int> GetColorKey();

			/// <summary>
			/// Get the additional alpha value used in blit operations.
			/// </summary>
			/// <returns>Alpha mod on success or error code on failure.</returns>
			Result<Uint8, int> GetSurfaceAlphaMod();

			/// <summary>
			/// Get the blend mode used for blit operations.
			/// </summary>
			/// <returns>Blend mode on success or error code on failure.</returns>
			Result<BlendMode, int> GetSurfaceBlendMode();

			/// <summary>
			/// Get the additional color value multiplied into blit operations.
			/// </summary>
			/// <param name="r">The current red color value.</param>
			/// <param name="g">The current green color value.</param>
			/// <param name="b">The current blue color value.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetSurfaceColorMod([Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b);

			/// <summary>
			/// Set up a surface for directly accessing the pixels.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> LockSurface();

			/// <summary>
			/// Whether a surface must be locked for access.
			/// </summary>
			property bool MustLock
			{
				bool get();
			}

			/// <summary>
			/// Save a surface to a BMP file.
			/// </summary>
			/// <param name="file">The file to be saved to.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SaveBMP(System::String^ file);

			// TODO: SaveBMP_RW

			/// <summary>
			/// Set the clipping rectangle for a surface.
			/// </summary>
			/// <param name="rect">The <see cref="NETSDL2::Video::Rect"/>
			/// structure representing the clipping rectangle, or null to disable
			/// clipping.</param>
			/// <returns>true if the rectangle intersects the surface, otherwise
			/// false and blits will be completely clipped.</returns>
			bool SetClipRect(System::Nullable<NETSDL2::Video::Rect> rect);

			/// <summary>
			/// Set the color key (transparent pixel) in a surface.
			/// </summary>
			/// <param name="flag">true to enable color key, false to disable
			/// color key.</param>
			/// <param name="key">The transparent pixel.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetColorKey(bool flag, Uint32 key);

			/// <summary>
			/// Returns whether the surface has a color key
			/// </summary>
			property bool HasColorKey
			{
				bool get();
			}

			/// <summary>
			/// Set an additional alpha value used in blit operations.
			/// </summary>
			/// <param name="alpha">The alpha value multiplied into blit
			/// operations.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetSurfaceAlphaMod(Uint8 alpha);

			/// <summary>
			/// Set the blend mode used for blit operations.
			/// </summary>
			/// <param name="blendMode">The <see cref="BlendMode"/> to use for
			/// blit blending.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetSurfaceBlendMode(BlendMode blendMode);

			/// <summary>
			/// Set an additional color value multiplied into blit operations.
			/// </summary>
			/// <param name="r">The red color value multiplied into blit
			/// operations.</param>
			/// <param name="g">The green color value multiplied into blit
			/// operations.</param>
			/// <param name="b">The blue color value multiplied into blit
			/// operations.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetSurfaceColorMod(Uint8 r, Uint8 g, Uint8 b);

			/// <summary>
			/// Set the palette used by a surface.
			/// </summary>
			/// <param name="palette">The <see cref="Palette"/> structure to use.
			/// </param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetSurfacePalette(Palette* palette);

			/// <summary>
			/// Set the RLE acceleration hint for a surface.
			/// </summary>
			/// <param name="flag">false to disable, true to enable RLE
			/// acceleration.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetSurfaceRLE(bool flag);

			/// <summary>
			/// Returns whether the surface is RLE enabled.
			/// </summary>
			property bool HasSurfaceRLE
			{
				bool get();
			}

			/// <summary>
			/// Release a surface after directly accessing the pixels.
			/// </summary>
			void UnlockSurface();
		};
	}
}