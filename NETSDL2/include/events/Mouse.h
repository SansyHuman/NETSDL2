#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "Button.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		ref class Window;
	}

	namespace Events
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::Video;

		ref class Cursor;

		/// <summary>
		/// Enum of cursor state.
		/// </summary>
		public enum class CursorState
		{
			/// <summary>
			/// Show the cursor.
			/// </summary>
			Enable = SDL_ENABLE,

			/// <summary>
			/// Hide the cursor.
			/// </summary>
			Disable = SDL_DISABLE,

			/// <summary>
			/// Query the current state.
			/// </summary>
			Query = SDL_QUERY,
		};

		/// <summary>
		/// Functions for handling inputs from mice and other similar pointing devices,
		/// as well as some cursor management tasks.
		/// </summary>
		public ref struct Mouse abstract sealed
		{
		public:
			/// <summary>
			/// Capture the mouse and to track input outside an SDL window.
			/// </summary>
			/// <param name="enabled">true to enable capturing, false to disable.</param>
			/// <returns>Success or Failure if not supported.</returns>
			static Result<None^, None^> CaptureMouse(bool enabled);

			/// <summary>
			/// Get the active cursor.
			/// </summary>
			/// <returns>The active cursor or None if there is no mouse.</returns>
			static Result<Cursor^, None^> GetCursor();

			/// <summary>
			/// Get the default cursor.
			/// </summary>
			/// <returns>The default cursor on success or None on failure.</returns>
			static Result<Cursor^, None^> GetDefaultCursor();

			/// <summary>
			/// Get the current state of the mouse in relation to the desktop.
			/// </summary>
			/// <param name="x">Filled in with the current X coord relative to the
			/// desktop.</param>
			/// <param name="y">Filled in with the current Y coord relative to the
			/// desktop.</param>
			/// <returns>The current button state as a bitmask.</returns>
			static ButtonState GetGlobalMouseState([Out]int% x, [Out]int% y);

			/// <summary>
			/// Get the window which currently has mouse focus.
			/// </summary>
			/// <returns>The window with mouse focus if success or None on failure.
			/// </returns>
			static Result<Window^, None^> GetMouseFocus();

			/// <summary>
			/// Retrieve the current state of the mouse.
			/// </summary>
			/// <param name="x">The x coordinate of the mouse cursor position relative to
			/// the focus window.</param>
			/// <param name="y">The y coordinate of the mouse cursor position relative to
			/// the focus window.</param>
			/// <returns>The current button state as a bitmask.</returns>
			static ButtonState GetMouseState([Out]int% x, [Out]int% y);

			/// <summary>
			/// Query whether relative mouse mode is enabled.
			/// </summary>
			static property bool RelativeMouseMode
			{
				bool get();
			}

			/// <summary>
			/// Retrieve the relative state of the mouse.
			/// </summary>
			/// <param name="x">The last recorded x coordinate of the mouse.</param>
			/// <param name="y">The last recorded y coordinate of the mouse.</param>
			/// <returns>The current button state as a bitmask.</returns>
			static ButtonState GetRelativeMouseState([Out]int% x, [Out]int% y);

			/// <summary>
			/// Set the active cursor.
			/// </summary>
			/// <param name="cursor">A cursor to make active.</param>
			static void SetCursor(Cursor^ cursor);

			/// <summary>
			/// Set relative mouse mode.
			/// </summary>
			/// <param name="enabled">true to enable relative mode, false to disable.
			/// </param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> SetRelativeMouseMode(bool enabled);

			/// <summary>
			/// Toggle whether or not the cursor is shown.
			/// </summary>
			/// <param name="toggle"><see cref="CursorState::Enable"/> to show the
			/// cursor, <see cref="CursorState::Disable"/> to hide it,
			/// <see cref="CursorState::Query"/> to query the current state without
			/// changing it.</param>
			/// <returns>Current cursor state on success or error code on failure.
			/// </returns>
			static Result<CursorState, int> ShowCursor(CursorState toggle);

			/// <summary>
			/// Move the mouse to the given position in global screen space.
			/// </summary>
			/// <param name="x">The x coordinate.</param>
			/// <param name="y">The y coordinate.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> WarpMouseGlobal(int x, int y);

			/// <summary>
			/// Move the mouse cursor to the given position within the window.
			/// </summary>
			/// <param name="window">The window to move the mouse into, or null for the
			/// current mouse focus.</param>
			/// <param name="x">The x coordinate within the window.</param>
			/// <param name="y">The y coordinate within the window.</param>
			static void WarpMouseInWindow(Window^ window, int x, int y);
		};
	}
}