#pragma once

#include <SDL.h>

#include "Event.h"
#include "../core/Result.h"
#include "../core/None.h"
#include "Scancode.h"
#include "Keycode.h"
#include "../video/Rect.h"

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

		/// <summary>
		/// Functions for handling keyboard inputs.
		/// </summary>
		public ref struct Keyboard abstract sealed
		{
		public:
			/// <summary>
			/// Wrapper of keyboard state array.
			/// </summary>
			value struct KeyboardState
			{
			private:
				Uint8* states;
				int numkeys;

			internal:
				KeyboardState(Uint8* states, int numkeys);

			public:
				/// <summary>
				/// Gets the key state of the scancode.
				/// </summary>
				property Uint8 default[Scancode]
				{
					Uint8 get(Scancode index);
				}

				/// <summary>
				/// Gets the number of states in the array.
				/// </summary>
				property int NumKeys
				{
					int get();
				}
			};

			/// <summary>
			/// Query the window which currently has keyboard focus.
			/// </summary>
			/// <returns>The window with keyboard focus if success or None on failure.
			/// </returns>
			static Result<Window^, None^> GetKeyboardFocus();

			/// <summary>
			/// Get a snapshot of the current state of the keyboard.
			/// </summary>
			/// <param name="numkeys">Receives the length of the returned array.</param>
			/// <returns>A pointer to an array of key states.</returns>
			static Uint8* GetKeyboardState([Out]int% numkeys);

			/// <summary>
			/// Get a snapshot of the current state of the keyboard.
			/// </summary>
			/// <returns>An array of key states.</returns>
			static KeyboardState GetKeyboardState();

			/// <summary>
			/// Clear the state of the keyboard.
			/// </summary>
			static void ResetKeyboard();

			/// <summary>
			/// Get a key code from a human-readable name.
			/// </summary>
			/// <param name="name">The human-readable key name.</param>
			/// <returns>Key code, or <see cref="Keycode::Unknown"/> if the name wasn't
			/// recognized.</returns>
			static Keycode GetKeyFromName(System::String^ name);

			/// <summary>
			/// Get the key code corresponding to the given scancode according to the
			/// current keyboard layout.
			/// </summary>
			/// <param name="scancode">The desired scancode to query.</param>
			/// <returns>The <see cref="Keycode"/> that corresponds to the given
			/// <see cref="Scancode"/>.</returns>
			static Keycode GetKeyFromScancode(Scancode scancode);

			/// <summary>
			/// Get a human-readable name for a key.
			/// </summary>
			/// <param name="key">The desired keycode to query</param>
			/// <returns>The name for a key.</returns>
			static System::String^ GetKeyName(Keycode key);

			/// <summary>
			/// Get the current key modifier state for the keyboard.
			/// </summary>
			/// <returns>An OR'd combination of the modifier keys for the keyboard.
			/// </returns>
			static Keymod GetModState();

			/// <summary>
			/// Get the scancode corresponding to the given key code according to the
			/// current keyboard layout.
			/// </summary>
			/// <param name="key">The desired keycode to query.</param>
			/// <returns>The <see cref="Scancode"/> that corresponds to the given
			/// <see cref="Keycode"/>.</returns>
			static Scancode GetScancodeFromKey(Keycode key);

			/// <summary>
			/// Get a scancode from a human-readable name.
			/// </summary>
			/// <param name="name">The human-readable scancode name.</param>
			/// <returns>Key code, or <see cref="Scancode::Unknown"/> if the name wasn't
			/// recognized.</returns>
			static Scancode GetScancodeFromName(System::String^ name);

			/// <summary>
			/// Get a human-readable name for a scancode.
			/// </summary>
			/// <param name="scancode">The desired scancode to query.</param>
			/// <returns>The name for the scancode.</returns>
			static System::String^ GetScancodeName(Scancode scancode);

			/// <summary>
			/// Check whether the platform has screen keyboard support.
			/// </summary>
			static property bool HasScreenKeyboardSupport
			{
				bool get();
			}

			/// <summary>
			/// Check whether the screen keyboard is shown for given window.
			/// </summary>
			/// <param name="window">The window for which screen keyboard should be
			/// queried.</param>
			/// <returns>true if screen keyboard is shown or false if not.</returns>
			static bool IsScreenKeyboardShown(Window^ window);

			/// <summary>
			/// Check whether or not Unicode text input events are enabled.
			/// </summary>
			static property bool IsTextInputActive
			{
				bool get();
			}

			/// <summary>
			/// Set the current key modifier state for the keyboard.
			/// </summary>
			/// <param name="modstate">The desired <see cref="Keymod"/> for the
			/// keyboard.</param>
			static void SetModState(Keymod modstate);

			/// <summary>
			/// Set the rectangle used to type Unicode text inputs.
			/// </summary>
			/// <param name="rect">The <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the rectangle to receive text.</param>
			static void SetTextInputRect(NETSDL2::Video::Rect rect);

			/// <summary>
			/// Start accepting Unicode text input events.
			/// </summary>
			static void StartTextInput();
			
			/// <summary>
			/// Stop receiving any text input events.
			/// </summary>
			static void StopTextInput();

			/// <summary>
			/// Dismiss the composition window/IME without disabling the subsystem.
			/// </summary>
			static void ClearComposition();

			/// <summary>
			/// Returns if an IME Composite or Candidate window is currently shown.
			/// </summary>
			static property bool IsTextInputShown
			{
				bool get();
			}
		};
	}
}