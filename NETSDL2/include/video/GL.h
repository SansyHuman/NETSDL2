#pragma once

#include <SDL.h>
#include "GLAttr.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Core
	{
		ref class None;
	}

	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Window;
		ref class GLContext;
		ref class Texture;

		/// <summary>
		/// Functions related to OpenGL.
		/// </summary>
		public ref struct GL abstract sealed
		{
		public:
			/// <summary>
			/// Bind an OpenGL/ES/ES2 texture to the current context.
			/// </summary>
			/// <param name="texture">The texture to bind to the current
			/// OpenGL/ES/ES2 context.</param>
			/// <param name="texw">The texture width.</param>
			/// <param name="texh">The texture height.</param>
			/// <returns>None on success or -1 if the operation is not supported.
			/// </returns>
			static Result<None^, int> BindTexture(Texture^ texture, [Out]float% texw, [Out]float% texh);

			/// <summary>
			/// Unbind an OpenGL/ES/ES2 texture from the current context.
			/// </summary>
			/// <param name="texture">The texture to unbind from the current
			/// OpenGL/ES/ES2 context.</param>
			/// <returns>None on success or -1 if the operation is not supported.
			/// </returns>
			static Result<None^, int> UnbindTexture(Texture^ texture);

			/// <summary>
			/// Create an OpenGL context for an OpenGL window, and make it
			/// current.
			/// </summary>
			/// <param name="window">The window to associate with the context.
			/// </param>
			/// <returns>OpenGL context associated with window or None on error
			/// </returns>
			static Result<GLContext^, None^> CreateContext(Window^ window);

			/// <summary>
			/// Check if an OpenGL extension is supported for the current
			/// context.
			/// </summary>
			/// <param name="extension">Name of the extension to check.</param>
			/// <returns>true if the extension is supported, false otherwise.
			/// </returns>
			static bool ExtensionSupported(System::String^ extension);

			/// <summary>
			/// Get the actual value for an attribute from the current context.
			/// </summary>
			/// <param name="attr"><see cref="GLAttr"/> enum value specifying
			/// the OpenGL attribute to get.</param>
			/// <returns>The current value of attribute or error code if
			/// failed.</returns>
			static Result<int, int> GetAttribute(GLAttr attr);

			/// <summary>
			/// Get the currently active OpenGL context.
			/// </summary>
			/// <returns>Currently active OpenGL context or None on failure.
			/// </returns>
			static Result<GLContext^, None^> GetCurrentContext();

			/// <summary>
			/// Get the currently active OpenGL window.
			/// </summary>
			/// <returns></returns>
			static Result<Window^, None^> GetCurrentWindow();

			/// <summary>
			/// Get the size of a window's underlying drawable in pixels.
			/// </summary>
			/// <param name="window">The window from which the drawable size
			/// should be queried.</param>
			/// <param name="w">The width in pixels.</param>
			/// <param name="h">The height in pixels/</param>
			static void GetDrawableSize(Window^ window, [Out]int% w, [Out]int% h);

			/// <summary>
			/// Get an OpenGL function by name.
			/// </summary>
			/// <param name="proc">The name of an OpenGL function.</param>
			/// <returns>A pointer to the named OpenGL function.</returns>
			static System::IntPtr GetProcAddress(System::String^ proc);

			/// <summary>
			/// Get the swap interval for the current OpenGL context.
			/// </summary>
			/// <returns>0 if there is no vertical retrace synchronization,
			/// 1 if the buffer swap is synchronized with the vertical retrace,
			/// and -1 if late swaps happen immediately instead of waiting for
			/// the next retrace.</returns>
			static int GetSwapInterval();

			/// <summary>
			/// Dynamically load an OpenGL library.
			/// </summary>
			/// <param name="path">The platform dependent OpenGL library name,
			/// or null to open the default OpenGL library.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> LoadLibrary(System::String^ path);

			/// <summary>
			/// Set up an OpenGL context for rendering into an OpenGL window.
			/// </summary>
			/// <param name="window">The window to associate with the context.
			/// </param>
			/// <param name="context">OpenGL context to associate with the
			/// window.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> MakeCurrent(Window^ window, GLContext^ context);

			/// <summary>
			/// Reset all previously set OpenGL context attributes to their
			/// default values.
			/// </summary>
			static void ResetAttributes();

			/// <summary>
			/// Set an OpenGL window attribute before window creation.
			/// </summary>
			/// <param name="attr"><see cref="GLAttr"/> enum value specifying
			/// the OpenGL attribute to set.</param>
			/// <param name="value">The desired value for the attribute.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> SetAttribute(GLAttr attr, int value);

			/// <summary>
			/// Set the swap interval for the current OpenGL context.
			/// </summary>
			/// <param name="interval">0 for immediate updates, 1 for updates
			/// synchronized with the vertical retrace, -1 for adaptive vsync.
			/// </param>
			/// <returns>None on success or -1 if not supported.</returns>
			static Result<None^, int> SetSwapInterval(int interval);

			/// <summary>
			/// Update a window with OpenGL rendering.
			/// </summary>
			/// <param name="window">The window to change.</param>
			static void SwapWindow(Window^ window);

			/// <summary>
			/// Unload the OpenGL library previously loaded by
			/// <see cref="LoadLibrary"/>.
			/// </summary>
			static void UnloadLibrary();
		};
	}
}