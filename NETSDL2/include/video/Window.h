#pragma once

#include <SDL.h>
#include "../../include/video/DisplayMode.h"
#include "../../include/video/PixelFormat.h"
#include "../../include/video/SysWMInfo.h"
#include "../../include/video/Rect.h"
#include "../../include/video/MessageBoxData.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

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

		ref class GLContext;

		[System::Flags]
		/// <summary>
		/// An enumeration of window states.
		/// </summary>
		public enum class WindowFlags : Uint32
		{
			/// <summary>
			/// No flags.
			/// </summary>
			None = 0U,

			/// <summary>
			/// Fullscreen window.
			/// </summary>
			Fullscreen = SDL_WINDOW_FULLSCREEN,

			/// <summary>
			/// Fullscreen window at the current desktop resolution.
			/// </summary>
			FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP,

			/// <summary>
			/// Window usable with OpenGL context.
			/// </summary>
			OpenGL = SDL_WINDOW_OPENGL,

			/// <summary>
			/// Window usable with a Vulkan instance.
			/// </summary>
			Vulkan = SDL_WINDOW_VULKAN,

			/// <summary>
			/// Window usable for Metal view.
			/// </summary>
			Metal = SDL_WINDOW_METAL,

			/// <summary>
			/// Window is visible.
			/// </summary>
			Shown = SDL_WINDOW_SHOWN,

			/// <summary>
			/// Window is not visible.
			/// </summary>
			Hidden = SDL_WINDOW_HIDDEN,

			/// <summary>
			/// No window decoration.
			/// </summary>
			Borderless = SDL_WINDOW_BORDERLESS,

			/// <summary>
			/// Window can be resized.
			/// </summary>
			Resizable = SDL_WINDOW_RESIZABLE,

			/// <summary>
			/// Window is minimized.
			/// </summary>
			Minimized = SDL_WINDOW_MINIMIZED,

			/// <summary>
			/// Window is maximized.
			/// </summary>
			Maximized = SDL_WINDOW_MAXIMIZED,

			/// <summary>
			/// Window has grabbed input focus.
			/// </summary>
			InputGrabbed = SDL_WINDOW_INPUT_GRABBED,

			/// <summary>
			/// Window has grabbed mouse input.
			/// </summary>
			MouseGrabbed = SDL_WINDOW_MOUSE_GRABBED,

			/// <summary>
			/// Window has grabbed keyboard input.
			/// </summary>
			KeyboardGrabbed = SDL_WINDOW_KEYBOARD_GRABBED,

			/// <summary>
			/// Window has input focus.
			/// </summary>
			InputFocus = SDL_WINDOW_INPUT_FOCUS,

			/// <summary>
			/// Window has mouse focus.
			/// </summary>
			MouseFocus = SDL_WINDOW_MOUSE_FOCUS,

			/// <summary>
			/// Window not created by SDL.
			/// </summary>
			Foreign = SDL_WINDOW_FOREIGN,

			/// <summary>
			/// Window should be created in high-DPI mode if supported.
			/// </summary>
			AllowHighDPI = SDL_WINDOW_ALLOW_HIGHDPI,

			/// <summary>
			/// Window has mouse captured.
			/// </summary>
			MouseCapture = SDL_WINDOW_MOUSE_CAPTURE,

			/// <summary>
			/// Window should always be above others (X11 only).
			/// </summary>
			AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,

			/// <summary>
			/// Window should not be added to the taskbar (X11 only).
			/// </summary>
			SkipTaskbar = SDL_WINDOW_SKIP_TASKBAR,

			/// <summary>
			/// Window should be treated as a utility window (X11 only).
			/// </summary>
			Utility = SDL_WINDOW_UTILITY,

			/// <summary>
			/// Window should be treated as a tooltip (X11 only).
			/// </summary>
			Tooltip = SDL_WINDOW_TOOLTIP,

			/// <summary>
			/// Window should be treated as a popup menu (X11 only).
			/// </summary>
			PopupMenu = SDL_WINDOW_POPUP_MENU
		};

		/// <summary>
		/// Window flash operation.
		/// </summary>
		public enum class FlashOperation
		{
			/// <summary>
			/// Cancel any window flash state.
			/// </summary>
			Cancel = SDL_FLASH_CANCEL,

			/// <summary>
			/// Flash the window briefly to get attention.
			/// </summary>
			Briefly = SDL_FLASH_BRIEFLY,

			/// <summary>
			/// Flash the window until it gets focus.
			/// </summary>
			UntilFocused = SDL_FLASH_UNTIL_FOCUSED
		};

		/// <summary>
		/// An enumeration of possible return values from the
		/// <see cref="HitTest"/> callback.
		/// </summary>
		public enum class HitTestResult
		{
			/// <summary>
			/// Region is normal and has no special properties.
			/// </summary>
			Normal = SDL_HITTEST_NORMAL,

			/// <summary>
			/// Region can drag entire window.
			/// </summary>
			Draggable = SDL_HITTEST_DRAGGABLE,

			/// <summary>
			/// Region can resize top left window.
			/// </summary>
			ResizeTopleft = SDL_HITTEST_RESIZE_TOPLEFT,

			/// <summary>
			/// Region can resize top window.
			/// </summary>
			ResizeTop = SDL_HITTEST_RESIZE_TOP,

			/// <summary>
			/// Region can resize top right window.
			/// </summary>
			ResizeTopright = SDL_HITTEST_RESIZE_TOPRIGHT,

			/// <summary>
			/// Region can resize right window.
			/// </summary>
			ResizeRight = SDL_HITTEST_RESIZE_RIGHT,

			/// <summary>
			/// Region can resize bottom right window.
			/// </summary>
			ResizeBottomright = SDL_HITTEST_RESIZE_BOTTOMRIGHT,

			/// <summary>
			/// Region can resize bottom window.
			/// </summary>
			ResizeBottom = SDL_HITTEST_RESIZE_BOTTOM,

			/// <summary>
			/// Region can resize bottom left window.
			/// </summary>
			ResizeBottomleft = SDL_HITTEST_RESIZE_BOTTOMLEFT,

			/// <summary>
			/// Region can resize left window.
			/// </summary>
			ResizeLeft = SDL_HITTEST_RESIZE_LEFT
		};

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate SDL_HitTestResult NativeHitTest(SDL_Window* wind, const SDL_Point* area, void* data);

		ref class Window;

		/// <summary>
		/// Callback used for hit-testing.
		/// </summary>
		/// <param name="win">Window where hit-testing was set on.</param>
		/// <param name="area">A point which should be hit-tested.</param>
		/// <param name="data">Data what was passed as callback data to
		/// <see cref="Window::SetWindowHitTest"/>.</param>
		/// <returns>Hit test result.</returns>
		public delegate HitTestResult HitTest(Window^ win, NETSDL2::Video::Point area, System::IntPtr data);

		/// <summary>
		/// Class of SDL window.
		/// </summary>
		public ref class Window
		{
		private:
			SDL_Window* window;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Window^>^ nativeWindowConnections;

			static Window()
			{
				nativeWindowConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Window^>();
			}

			SDL_HitTest nativeHitTestCallback;
			HitTest^ hitTestCallback;

			GCHandle hitTestCallbackHandle;

			static SDL_HitTestResult HitTestNative(SDL_Window* win, const SDL_Point* area, void* data);
			static HitTestResult DefaultHitTest(Window^ win, NETSDL2::Video::Point area, System::IntPtr data);

			void InitCallbacks();
			void ClearCallbacks();

		public:
			/// <summary>
			/// Position of the window should be centered.
			/// </summary>
			literal int WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;

			/// <summary>
			/// Do not care the window position.
			/// </summary>
			literal int WINDOWPOS_UNDEFINED = SDL_WINDOWPOS_UNDEFINED;

		public:
			/// <summary>
			/// Create a window with the specified position, dimensions, and
			/// flags.
			/// </summary>
			/// <param name="title">The title of the window.</param>
			/// <param name="x">The x position of the window,
			/// <see cref="Window::WINDOWPOS_CENTERED"/> or
			/// <see cref="Window::WINDOWPOS_UNDEFINED"/>.</param>
			/// <param name="y">The y position of the window,
			/// <see cref="Window::WINDOWPOS_CENTERED"/> or
			/// <see cref="Window::WINDOWPOS_UNDEFINED"/>.</param>
			/// <param name="w">The width of the window, in screen coordinates.
			/// </param>
			/// <param name="h">The height of the window, in screen coordinates.
			/// </param>
			/// <param name="flags"><see cref="WindowFlags::None"/>, or one or
			/// more <see cref="WindowFlags"/> OR'd together</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Window(System::String^ title, int x, int y, int w, int h, WindowFlags flags);
			// TODO: CreateWindowAndRenderer

			/// <summary>
			/// Create an SDL window from an existing native window.
			/// </summary>
			/// <param name="data">A pointer to driver-dependent window
			/// creation data, typically your native window cast to a void*.
			/// </param>
			Window(void* data);
			~Window();
			!Window();

			/// <summary>
			/// Request a window to demand attention from the user.
			/// </summary>
			/// <param name="operation">The flash operation.</param>
			/// <returns>None on success or an error code.</returns>
			Result<None^, int> FlashWindow(FlashOperation operation);

			[MaybeNull]
			/// <summary>
			/// Get the window that currently has an input grab enabled or null
			/// if there is no such window.
			/// </summary>
			static property Window^ GrabbedWindow
			{
				Window^ get();
			}

			/// <summary>
			/// Get the size of a window's borders (decorations) around the
			/// client area.
			/// </summary>
			/// <param name="top">The size of the top border.</param>
			/// <param name="left">The size of the left border.</param>
			/// <param name="bottom">The size of the bottom border.</param>
			/// <param name="right">The size of the right border.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetWindowBordersSize([Out]int% top, [Out]int% left, [Out]int% bottom, [Out]int% right);

			/// <summary>
			/// Get the brightness (gamma multiplier) for a given window's
			/// display.
			/// </summary>
			property float WindowBrightness
			{
				float get();
			}

			/// <summary>
			/// Retrieve the data pointer associated with a window.
			/// </summary>
			/// <param name="name">The name of the pointer.</param>
			/// <returns>The value associated with name.</returns>
			System::IntPtr GetWindowData(System::String^ name);

			/// <summary>
			/// Get the index of the display containing the center of the
			/// window on success or a negative error code on failure.
			/// </summary>
			property int WindowDisplayIndex
			{
				int get();
			}

			/// <summary>
			/// Query the display mode to use when a window is visible at
			/// fullscreen.
			/// </summary>
			/// <returns>Display mode on success or error code on failure.
			/// </returns>
			Result<DisplayMode, int> GetWindowDisplayMode();

			/// <summary>
			/// Get the window flags.
			/// </summary>
			property WindowFlags Flags
			{
				WindowFlags get();
			}

			/// <summary>
			/// Get a window from a stored ID.
			/// </summary>
			/// <param name="id">ID of the window.</param>
			/// <returns>Window with ID or None if it does not exist.</returns>
			static Result<Window^, None^> GetWindowFromID(Uint32 id);

			/// <summary>
			/// Get the gamma ramp for a given window's display.
			/// </summary>
			/// <param name="red">256 element array of 16-bit quantities filled
			/// in with the translation table for the red channel, or null.
			/// </param>
			/// <param name="green">256 element array of 16-bit quantities filled
			/// in with the translation table for the green channel, or null.
			/// </param>
			/// <param name="blue">256 element array of 16-bit quantities filled
			/// in with the translation table for the blue channel, or null.
			/// </param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetWindowGammaRamp(array<Uint16>^ red, array<Uint16>^ green, array<Uint16>^ blue);

			/// <summary>
			/// Get and set true if input is grabbed, false otherwise.
			/// </summary>
			property bool IsGrabbed
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Get ID of the window on success or 0 on failure.
			/// </summary>
			property Uint32 ID
			{
				Uint32 get();
			}

			/// <summary>
			/// Get the maximum size of a window's client area.
			/// </summary>
			/// <param name="w">The maximum width of the window.</param>
			/// <param name="h">The maximum height of the window.</param>
			void GetWindowMaximumSize([Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the minimum size of a window's client area.
			/// </summary>
			/// <param name="w">The minimum width of the window.</param>
			/// <param name="h">The minimum height of the window.</param>
			void GetWindowMinimumSize([Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the opacity of a window.
			/// </summary>
			/// <returns>Opacity on success or error code on failure.</returns>
			Result<float, int> GetWindowOpacity();

			/// <summary>
			/// Get the pixel format of the window on success or
			/// <see cref="PixelFormatEnum::Unknown"/> on failure.
			/// </summary>
			property PixelFormatEnum WindowPixelFormat
			{
				PixelFormatEnum get();
			}

			/// <summary>
			/// Get the position of a window.
			/// </summary>
			/// <param name="x">x position of the window, in screen
			/// coordinates.</param>
			/// <param name="y">y position of the window, in screen
			/// coordinates.</param>
			void GetWindowPosition([Out]int% x, [Out]int% y);

			/// <summary>
			/// Get the size of a window's client area.
			/// </summary>
			/// <param name="w">Width of the window, in screen
			/// coordinates.</param>
			/// <param name="h">Height of the window, in screen
			/// coordinates.</param>
			void GetWindowSize([Out]int% w, [Out]int% h);

			// TODO: GetWindowSurface

			/// <summary>
			/// Get or set the title of a window.
			/// </summary>
			property System::String^ Title
			{
				System::String^ get();
				void set(System::String^ title);
			}

			/// <summary>
			/// Get driver-specific information about a window. 
			/// </summary>
			/// <param name="info"><see cref="SysWMInfo"/> Structure filled in
			/// with window information. The caller must initialize the info
			/// structure's version.</param>
			/// <returns>true if the function is implemented and the version
			/// member of the info struct is valid, or SDL_FALSE if the
			/// information could not be retrieved.</returns>
			bool GetWindowWMInfo(SysWMInfo% info);

			/// <summary>
			/// Hide a window.
			/// </summary>
			void HideWindow();

			/// <summary>
			/// Make a window as large as possible.
			/// </summary>
			void MaximizeWindow();

			/// <summary>
			/// Minimize a window to an iconic representation.
			/// </summary>
			void MinimizeWindow();

			/// <summary>
			/// Raise a window above other windows and set the input focus.
			/// </summary>
			void RaiseWindow();

			/// <summary>
			/// Restore the size and position of a minimized or maximized window.
			/// </summary>
			void RestoreWindow();

			/// <summary>
			/// Set the border state of a window.
			/// </summary>
			/// <param name="bordered">false to remove border, true to add
			/// border.</param>
			void SetWindowBordered(bool bordered);

			/// <summary>
			/// Set the brightness (gamma multiplier) for a given window's
			/// display.
			/// </summary>
			/// <param name="brightness">The brightness (gamma multiplier)
			/// value to set where 0.0 is completely dark and 1.0 is normal
			/// brightness.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowBrightness(float brightness);

			/// <summary>
			/// Associate an arbitrary named pointer with a window.
			/// </summary>
			/// <param name="name">The name of the pointer.</param>
			/// <param name="userdata">The associated pointer.</param>
			/// <returns>The previous value associated with name.</returns>
			System::IntPtr SetWindowData(System::String^ name, System::IntPtr userdata);

			/// <summary>
			/// Set the display mode to use when a window is visible at fullscreen.
			/// </summary>
			/// <param name="mode">The <see cref="DisplayMode"/> structure
			/// representing the mode to use, or null to use the window's
			/// dimensions and the desktop's format and refresh rate.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowDisplayMode(System::Nullable<DisplayMode> mode);

			/// <summary>
			/// Set a window's fullscreen state.
			/// </summary>
			/// <param name="flags"><see cref="WindowFlags::Fullscreen"/>,
			/// <see cref="WindowFlags::FullscreenDesktop"/> or
			/// <see cref="WindowFlags::None"/>.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowFullscreen(WindowFlags flags);

			/// <summary>
			/// Set the gamma ramp for the display that owns a given window.
			/// </summary>
			/// <param name="red">A 256 element array of 16-bit quantities
			/// representing the translation table for the red channel, or
			/// null.</param>
			/// <param name="green">A 256 element array of 16-bit quantities
			/// representing the translation table for the green channel, or
			/// null.</param>
			/// <param name="blue">A 256 element array of 16-bit quantities
			/// representing the translation table for the blue channel, or
			/// null.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowGammaRamp(array<Uint16>^ red, array<Uint16>^ green, array<Uint16>^ blue);

			/// <summary>
			/// Provide a callback that decides if a window region has special
			/// properties.
			/// </summary>
			/// <param name="callback">The function to call when doing a
			/// hit-test.</param>
			/// <param name="callbackData">An app-defined void pointer passed
			/// to callback.</param>
			/// <returns>None on success or -1 on failure.</returns>
			Result<None^, int> SetWindowHitTest(HitTest^ callback, System::IntPtr callbackData);

			// TODO: SetWindowIcon

			/// <summary>
			/// Explicitly set input focus to the window.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowInputFocus();

			/// <summary>
			/// Set the maximum size of a window's client area.
			/// </summary>
			/// <param name="maxW">The maximum width of the window in pixels.
			/// </param>
			/// <param name="maxH">The maximum height of the window in pixels.
			/// </param>
			void SetWindowMaximumSize(int maxW, int maxH);

			/// <summary>
			/// Set the minimum size of a window's client area.
			/// </summary>
			/// <param name="maxW">The minimum width of the window in pixels.
			/// </param>
			/// <param name="maxH">The minimum height of the window in pixels.
			/// </param>
			void SetWindowMinimumSize(int minW, int minH);

			/// <summary>
			/// Set the window as a modal for another window.
			/// </summary>
			/// <param name="parentWindow">The parent window for the modal
			/// window.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowModalFor(Window^ parentWindow);

			/// <summary>
			/// Set the opacity for a window.
			/// </summary>
			/// <param name="opacity">The opacity value (0.0f - transparent,
			/// 1.0f - opaque).</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetWindowOpacity(float opacity);

			/// <summary>
			/// Set the position of a window.
			/// </summary>
			/// <param name="x">The x position of the window in screen
			/// coordinates, or <see cref="Window::WINDOWPOS_CENTERED"/> or
			/// <see cref="Window::WINDOWPOS_UNDEFINED"/>.</param>
			/// <param name="y">The y position of the window in screen
			/// coordinates, or <see cref="Window::WINDOWPOS_CENTERED"/> or
			/// <see cref="Window::WINDOWPOS_UNDEFINED"/>.</param>
			void SetWindowPosition(int x, int y);

			/// <summary>
			/// Set the user-resizable state of a window.
			/// </summary>
			/// <param name="resizable">true to allow resizing, false to
			/// disallow.</param>
			void SetWindowResizable(bool resizable);

			/// <summary>
			/// Set the size of a window's client area.
			/// </summary>
			/// <param name="w">The width of the window in pixels,
			/// in screen coordinates.</param>
			/// <param name="h">The height of the window in pixels,
			/// in screen coordinates.</param>
			void SetWindowSize(int w, int h);

			/// <summary>
			/// Create a modal message box.
			/// </summary>
			/// <param name="messageBoxData">The
			/// <see cref="Window::MessageBoxData"/> structure with title,
			/// text and other options.</param>
			/// <returns>ID of hit button on success or error code on failure.
			/// </returns>
			static Result<int, int> ShowMessageBox([In][IsReadOnly]MessageBoxData% messageBoxData);

			/// <summary>
			/// Display a simple modal message box.
			/// </summary>
			/// <param name="flags">An <see cref="MessageBoxFlags"/> value.
			/// </param>
			/// <param name="title">Title text.</param>
			/// <param name="message">Message text.</param>
			/// <param name="window">The parent window, or null for no parent.
			/// </param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> ShowSimpleMessageBox(MessageBoxFlags flags, System::String^ title, System::String^ message, Window^ window);

			/// <summary>
			/// Show a window.
			/// </summary>
			void ShowWindow();

			/// <summary>
			/// Copy the window surface to the screen.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> UpdateWindowSurface();

			/// <summary>
			/// Copy areas of the window surface to the screen.
			/// </summary>
			/// <param name="rects">An array of
			/// <see cref="NETSDL2::Video::Rect"/> structures representing
			/// areas of the surface to copy.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> UpdateWindowSurfaceRects(...array<NETSDL2::Video::Rect>^ rects);

		internal:
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static Result<Window^, None^> NETSDL2::Video::Window::GetGLCurrentWindow();

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			Result<GLContext^, None^> CreateGLContext();

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			void GetGLDrawableSize([Out]int% w, [Out]int% h);

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			Result<None^, int> MakeCurrent(GLContext^ context);

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			void SwapWindow();
		};
	}
}