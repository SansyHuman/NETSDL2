#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		ref class Surface;
	}

	namespace Events
	{
		using namespace NETSDL2::Video;

		/// <summary>
		/// An enumeration of system cursors.
		/// </summary>
		public enum class SystemCursor
		{
			/// <summary>
			/// Arrow (typically the default cursor).
			/// </summary>
			Arrow = SDL_SYSTEM_CURSOR_ARROW,

			/// <summary>
			/// I-beam.
			/// </summary>
			Ibeam = SDL_SYSTEM_CURSOR_IBEAM,

			/// <summary>
			/// Wait.
			/// </summary>
			Wait = SDL_SYSTEM_CURSOR_WAIT,

			/// <summary>
			/// Crosshair.
			/// </summary>
			Crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,

			/// <summary>
			/// Small wait cursor (or Wait if not available).
			/// </summary>
			WaitArrow = SDL_SYSTEM_CURSOR_WAITARROW,

			/// <summary>
			/// Double arrow pointing northwest and southeast.
			/// </summary>
			SizeNWSE = SDL_SYSTEM_CURSOR_SIZENWSE,

			/// <summary>
			/// Double arrow pointing northeast and southwest.
			/// </summary>
			SizeNESW = SDL_SYSTEM_CURSOR_SIZENESW,

			/// <summary>
			/// Double arrow pointing west and east.
			/// </summary>
			SizeWE = SDL_SYSTEM_CURSOR_SIZEWE,

			/// <summary>
			/// Double arrow pointing north and south.
			/// </summary>
			SizeNS = SDL_SYSTEM_CURSOR_SIZENS,

			/// <summary>
			/// Four pointed arrow pointing north, south, east and west.
			/// </summary>
			SizeAll = SDL_SYSTEM_CURSOR_SIZEALL,

			/// <summary>
			/// Slashed circle or crossbones.
			/// </summary>
			No = SDL_SYSTEM_CURSOR_NO,

			/// <summary>
			/// Hand.
			/// </summary>
			Hand = SDL_SYSTEM_CURSOR_HAND,
		};

		/// <summary>
		/// Cursor object.
		/// </summary>
		public ref class Cursor
		{
		private:
			SDL_Cursor* cursor;
			bool releaseOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Cursor^>^ nativeCursorConnections;

			static Cursor()
			{
				nativeCursorConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Cursor^>();
			}

		internal:
			property SDL_Cursor* NativeCursor
			{
				SDL_Cursor* get();
			}

			// Returns the managed cursor from native cursor, or null if not exists.
			static Cursor^ GetCursorFromNative(SDL_Cursor* cursor);

		private:
			void InitCursor(SDL_Cursor* cursor);

		internal:
			Cursor(SDL_Cursor* cursor, bool releaseOnDestroy);

		public:
			/// <summary>
			/// Create a color cursor.
			/// </summary>
			/// <param name="surface">A surface representing the cursor image.</param>
			/// <param name="hotX">The x position of the cursor hot spot.</param>
			/// <param name="hotY">The y position of the cursor hot spot.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Cursor(Surface^ surface, int hotX, int hotY);

			/// <summary>
			/// Create a cursor using the specified bitmap data and mask (in MSB format).
			/// </summary>
			/// <param name="data">The color value for each pixel of the cursor.</param>
			/// <param name="mask">The mask value for each pixel of the cursor.</param>
			/// <param name="w">The width of the cursor.</param>
			/// <param name="h">The height of the cursor.</param>
			/// <param name="hotX">The X-axis location of the upper left corner of the
			/// cursor relative to the actual mouse position.</param>
			/// <param name="hotY">The Y-axis location of the upper left corner of the
			/// cursor relative to the actual mouse position.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Cursor(Uint8* data, Uint8* mask, int w, int h, int hotX, int hotY);

			/// <summary>
			/// Create a system cursor.
			/// </summary>
			/// <param name="id">A <see cref="SystemCursor"/> enum value.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Cursor(SystemCursor id);

			~Cursor();
			!Cursor();
		};
	}
}