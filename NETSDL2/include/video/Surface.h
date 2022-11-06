#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "PixelFormat.h"

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

		internal:
			Surface(SDL_Surface* surface, bool releaseOnDestroy);
			property SDL_Surface* NativeSurface
			{
				SDL_Surface* get();
			}

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
		};
	}
}