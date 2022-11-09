#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"
#include "Rect.h"

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
		};
	}
}