#pragma once

#include <SDL.h>
#include "../../include/video/PixelFormat.h"
#include "../../include/video/Rect.h"
#include "../../include/video/DisplayMode.h"
#include "Rect.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Core
	{
		ref class None;
		generic<class Success, class Failure>
		value class Result;
	}

	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for handling display actions.
		/// </summary>
		public ref struct Display abstract sealed
		{
		public:
			/// <summary>
			/// Prevent the screen from being blanked by a screen saver.
			/// </summary>
			static void DisableScreenSaver();

			/// <summary>
			/// Allow the screen to be blanked by a screen saver.
			/// </summary>
			static void EnableScreenSaver();

			/// <summary>
			/// Get the closest match to the requested display mode.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <param name="mode">An <see cref="DisplayMode"/> structure
			/// containing the desired display mode.</param>
			/// <returns>An <see cref="DisplayMode"/> structure filled in with
			/// the closest match of the available display modes if succeeded,
			/// or None if failed.</returns>
			static Result<DisplayMode, None^> GetClosestDisplayMode(int displayIndex, [In][IsReadOnly] DisplayMode% mode);

			/// <summary>
			/// Get the index of the display containing a point.
			/// </summary>
			/// <param name="point">The point to query.</param>
			/// <returns>The index of the display containing the point or error code on failure.</returns>
			static Result<int, int> GetPointDisplayIndex(NETSDL2::Video::Point point);

			/// <summary>
			/// Get the index of the display primarily containing a point.
			/// </summary>
			/// <param name="rect">The rect to query.</param>
			/// <returns>The index of the display entirely containing the rect or closest to the center
			/// of the rect on success or error code on failure.</returns>
			static Result<int, int> GetRectDisplayIndex(NETSDL2::Video::Rect rect);

			/// <summary>
			/// Get information about the current display mode.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>Display mode on success or error code on failure.
			/// </returns>
			static Result<DisplayMode, int> GetCurrentDisplayMode(int displayIndex);

			/// <summary>
			/// Get the name of the currently initialized video driver.
			/// </summary>
			/// <returns>The name of the current video driver or empty string
			/// if no driver has been initialized.</returns>
			static System::String^ GetCurrentVideoDriver();

			/// <summary>
			/// Get information about the desktop's display mode.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>Display mode on success or error code on failure.
			/// </returns>
			static Result<DisplayMode, int> GetDesktopDisplayMode(int displayIndex);

			/// <summary>
			/// Get the desktop area represented by a display.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>Display bound rect on success or error code on
			/// failure.</returns>
			static Result<Rect, int> GetDisplayBounds(int displayIndex);

			/// <summary>
			/// Get the dots/pixels-per-inch for a display.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <param name="ddpi">The diagonal DPI of the display.</param>
			/// <param name="hdpi">The horizontal DPI of the display.</param>
			/// <param name="vdpi">The vertical DPI of the display.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> GetDisplayDPI(int displayIndex, [Out]float% ddpi, [Out]float% hdpi, [Out]float% vdpi);

			/// <summary>
			/// Get the orientation of a display.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.</param>
			/// <returns>The <see cref="DisplayOrientation"/> enum value of the display, or
			/// <see cref="DisplayOrientation::Unknown"/> if it isn't available.</returns>
			static DisplayOrientation GetDisplayOrientation(int displayIndex);

			/// <summary>
			/// Get information about a specific display mode.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <param name="modeIndex">The index of the display mode to query.
			/// </param>
			/// <returns>Display mode on success or error code on failure.
			/// </returns>
			static Result<DisplayMode, int> GetDisplayMode(int displayIndex, int modeIndex);

			/// <summary>
			/// Get information about all display modes.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>Array of display modes.</returns>
			static array<DisplayMode>^ GetDisplayModes(int displayIndex);

			/// <summary>
			/// Get the name of a display.
			/// </summary>
			/// <param name="displayIndex">The index of display from which the
			/// name should be queried.</param>
			/// <returns>The name of the display ore empty string for an
			/// invalid display index or failure.</returns>
			static System::String^ GetDisplayName(int displayIndex);

			/// <summary>
			/// Get the usable desktop area represented by a display.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>Display bound rect on success or error code on
			/// failure.</returns>
			static Result<Rect, int> GetDisplayUsableBounds(int displayIndex);

			/// <summary>
			/// Get the number of available display modes.
			/// </summary>
			/// <param name="displayIndex">The index of the display to query.
			/// </param>
			/// <returns>A number >= 1 on success or a negative error code on
			/// failure.</returns>
			static int GetNumDisplayModes(int displayIndex);

			/// <summary>
			/// Get the number of available video displays or a negative error
			/// code if failed.
			/// </summary>
			static property int NumVideoDisplays
			{
				int get();
			}

			/// <summary>
			/// Get the number of video drivers compiled into SDL or a negative
			/// error code if failed.
			/// </summary>
			static property int NumVideoDrivers
			{
				int get();
			}

			/// <summary>
			/// Get the name of a built in video driver.
			/// </summary>
			/// <param name="index">The index of a video driver.</param>
			/// <returns>The name of the video driver with the given index.
			/// </returns>
			static System::String^ GetVideoDriver(int index);

			/// <summary>
			/// Check whether the screensaver is currently enabled.
			/// </summary>
			static property bool IsScreenSaverEnabled
			{
				bool get();
			}
		};
	}
}