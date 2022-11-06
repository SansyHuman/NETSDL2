#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "RendererInfo.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Window;
		ref class Surface;

		/// <summary>
		/// Renderer.
		/// </summary>
		public ref class Renderer
		{
		private:
			SDL_Renderer* renderer;

		internal:
			Renderer(SDL_Renderer* renderer);

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
		};
	}
}