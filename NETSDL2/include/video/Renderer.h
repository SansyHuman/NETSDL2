#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "RendererInfo.h"
#include "PixelFormat.h"
#include "TextureAccess.h"
#include "Blend.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Window;
		ref class Surface;
		ref class Texture;

		/// <summary>
		/// Renderer.
		/// </summary>
		public ref class Renderer
		{
		private:
			SDL_Renderer* renderer;
			bool releaseOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Renderer^>^ nativeRendererConnections;

			static Renderer()
			{
				nativeRendererConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Renderer^>();
			}

		internal:
			Renderer(SDL_Renderer* renderer, bool releaseOnDestroy);

			// Gets renderer from native surface, or null if not exists.
			static Renderer^ GetRendererFromNative(SDL_Renderer* renderer);

		private:
			void InitRenderer(SDL_Renderer* renderer);

		public:
			/// <summary>
			/// Create a 2D rendering context for a window.
			/// </summary>
			/// <param name="window">The window where rendering is displayed.
			/// </param>
			/// <param name="index">The index of the rendering driver to
			/// initialize, or -1 to initialize the first one supporting the
			/// requested flags.</param>
			/// <param name="flags">0, or one or more <see cref="RendererFlags"/>
			/// OR'd together.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Renderer(Window^ window, int index, RendererFlags flags);

			/// <summary>
			/// Create a 2D software rendering context for a surface.
			/// </summary>
			/// <param name="surface">The surface where rendering is done.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Renderer(Surface^ surface);
			~Renderer();
			!Renderer();

			/// <summary>
			/// Get the blend mode used for drawing operations.
			/// </summary>
			/// <returns>Blend mode on success or error code on failure.</returns>
			Result<BlendMode, int> GetRenderDrawBlendMode();

			/// <summary>
			/// Get the color used for drawing operations (Rect, Line and Clear).
			/// </summary>
			/// <param name="r">The red value used to draw on the rendering
			/// target.</param>
			/// <param name="g">The green value used to draw on the rendering
			/// target.</param>
			/// <param name="b">The blue value used to draw on the rendering
			/// target.</param>
			/// <param name="a">The alpha value used to draw on the rendering
			/// target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetRenderDrawColor([Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b, [Out]Uint8% a);

			/// <summary>
			/// Get information about a rendering context.
			/// </summary>
			/// <returns>Renderer info on success or error code on failure.
			/// </returns>
			Result<RendererInfo, int> GetRendererInfo();

			/// <summary>
			/// Get the output size in pixels of a rendering context.
			/// </summary>
			/// <param name="w">The width.</param>
			/// <param name="h">The height.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetRendererOutputSize([Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the current render target.
			/// </summary>
			/// <returns>The current render target or null for the default render
			/// target.</returns>
			Texture^ GetRenderTarget();

			/// <summary>
			/// Set a texture as the current rendering target.
			/// </summary>
			/// <param name="texture">The targeted texture, which must be created
			/// with the <see cref="TextureAccess::Target"/> flag, or null to
			/// render to the window instead of a texture.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetRenderTarget(Texture^ texture);

		internal:
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			SDL_Texture* CreateTexture(PixelFormatEnum format, TextureAccess access, int w, int h);

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			SDL_Texture* CreateTextureFromSurface(Surface^ surface);
		};
	}
}