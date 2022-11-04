#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		ref class Window;

		/// <summary>
		/// An enumeration of flags for <see cref="MessageBoxButtonData"/>.
		/// </summary>
		[System::Flags]
		public enum class MessageBoxButtonFlags : Uint32
		{
			None = 0U,

			/// <summary>
			/// Marks the default button when return is hit.
			/// </summary>
			ReturnkeyDefault = SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,

			/// <summary>
			/// Marks the default button when escape is hit.
			/// </summary>
			EscapekeyDefault = SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
		};

		/// <summary>
		/// A structure that contains individual button data for a message box.
		/// </summary>
		public value struct MessageBoxButtonData
		{
			/// <summary>
			/// One of the values from <see cref="MessageBoxButtonFlags"/>.
			/// </summary>
			MessageBoxButtonFlags Flags;

			/// <summary>
			/// User defined button id.
			/// </summary>
			int ButtonID;

			/// <summary>
			/// The button text.
			/// </summary>
			System::String^ Text;

			MessageBoxButtonData(MessageBoxButtonFlags flags, int id, System::String^ text);

			virtual System::String^ ToString() override;
		};

		/// <summary>
		/// A structure that contains RGB value used in an
		/// <see cref="MessageBoxColorScheme"/>.
		/// </summary>
		public value struct MessageBoxColor
		{
			/// <summary>
			/// The red component in the range 0-255.
			/// </summary>
			Uint8 R;

			/// <summary>
			/// The green component in the range 0-255.
			/// </summary>
			Uint8 G;

			/// <summary>
			/// The blue component in the range 0-255.
			/// </summary>
			Uint8 B;

			MessageBoxColor(Uint8 r, Uint8 g, Uint8 b);

			virtual System::String^ ToString() override;
		};

		/// <summary>
		/// An enumeration of positions inside the colors array of
		/// <see cref="MessageBoxColorScheme"/>.
		/// </summary>
		public enum class MessageBoxColorType : int
		{
			Background = SDL_MESSAGEBOX_COLOR_BACKGROUND,
			Text = SDL_MESSAGEBOX_COLOR_TEXT,
			ButtonBorder = SDL_MESSAGEBOX_COLOR_BUTTON_BORDER,
			ButtonBackground = SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND,
			ButtonSelected = SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED,
		};

		/// <summary>
		/// A class that contains a set of colors to use for message box
		/// dialogs.
		/// </summary>
		public ref class MessageBoxColorScheme
		{
		private:
			array<MessageBoxColor>^ colors;

		public:
			MessageBoxColorScheme();

			property MessageBoxColor default[MessageBoxColorType]
			{
				MessageBoxColor get(MessageBoxColorType index);
				void set(MessageBoxColorType index, MessageBoxColor value);
			}
		};

		/// <summary>
		/// An enumeration of message box flags (e.g. if supported message box
		/// will display warning icon).
		/// </summary>
		[System::Flags]
		public enum class MessageBoxFlags : Uint32
		{
			/// <summary>
			/// Error dialog.
			/// </summary>
			Error = SDL_MESSAGEBOX_ERROR,

			/// <summary>
			/// Warning dialog.
			/// </summary>
			Warning = SDL_MESSAGEBOX_WARNING,

			/// <summary>
			/// Informational dialog.
			/// </summary>
			Information = SDL_MESSAGEBOX_INFORMATION,

			/// <summary>
			/// Buttons placed left to right.
			/// </summary>
			ButtonsLeftToRight = SDL_MESSAGEBOX_BUTTONS_LEFT_TO_RIGHT,

			/// <summary>
			/// Buttons placed right to left.
			/// </summary>
			ButtonsRightToLeft = SDL_MESSAGEBOX_BUTTONS_RIGHT_TO_LEFT,
		};

		/// <summary>
		/// A structure that contains title, text, window and other data for
		/// a message box.
		/// </summary>
		public value struct MessageBoxData
		{
			/// <summary>
			/// An <see cref="MessageBoxFlags"/>.
			/// </summary>
			MessageBoxFlags Flags;
			
			/// <summary>
			/// Parent window, can be null.
			/// </summary>
			Window^ Window;

			/// <summary>
			/// Title.
			/// </summary>
			System::String^ Title;

			/// <summary>
			/// Message text.
			/// </summary>
			System::String^ Message;

			/// <summary>
			/// An array of <see cref="MessageBoxButtonData"/>.
			/// </summary>
			array<MessageBoxButtonData>^ Buttons;

			/// <summary>
			/// An <see cref="MessageBoxColorScheme"/>, can be null to use
			/// system settings.
			/// </summary>
			MessageBoxColorScheme^ ColorScheme;

			MessageBoxData(
				MessageBoxFlags flags, NETSDL2::Video::Window^ window, System::String^ title,
				System::String^ message, MessageBoxColorScheme^ colorScheme,
				...array<MessageBoxButtonData>^ buttons);
		};
	}
}