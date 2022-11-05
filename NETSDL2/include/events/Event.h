#pragma once

#include <SDL.h>

#include "Keysym.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// An enumeration of the types of events that can be delivered.
		/// </summary>
		public enum class EventType : Uint32
		{
			/// <summary>
			/// do not remove (unused)
			/// </summary>
			FirstEvent = SDL_FIRSTEVENT,


			// Application events
			/// <summary>
			/// user-requested quit
			/// </summary>
			Quit = SDL_QUIT,


			// Android, iOS, WinRT events
			/// <summary>
			/// OS is terminating the application
			/// </summary>
			Terminating = SDL_APP_TERMINATING,

			/// <summary>
			/// OS is low on memory; free some
			/// </summary>
			LowMemory = SDL_APP_LOWMEMORY, 

			/// <summary>
			/// application is entering background
			/// </summary>
			WillEnterBackground = SDL_APP_WILLENTERBACKGROUND,

			/// <summary>
			/// application entered background
			/// </summary>
			DidEnterBackground = SDL_APP_DIDENTERBACKGROUND,

			/// <summary>
			/// application is entering foreground
			/// </summary>
			WillEnterForeground = SDL_APP_WILLENTERFOREGROUND,

			/// <summary>
			/// application entered foreground
			/// </summary>
			DidEnterForeground = SDL_APP_DIDENTERFOREGROUND,

			/// <summary>
			/// The user's locale preferences have changed
			/// </summary>
			LocaleChanged = SDL_LOCALECHANGED,


			// Display events
			/// <summary>
			/// Display state change
			/// </summary>
			DisplayEvent = SDL_DISPLAYEVENT,


			// Window events
			/// <summary>
			/// window state change
			/// </summary>
			WindowEvent = SDL_WINDOWEVENT,

			/// <summary>
			/// system specific event
			/// </summary>
			SysWMEvent = SDL_SYSWMEVENT,


			// Keyboard events
			/// <summary>
			/// key pressed
			/// </summary>
			KeyDown = SDL_KEYDOWN,

			/// <summary>
			/// key released
			/// </summary>
			KeyUp = SDL_KEYUP,

			/// <summary>
			/// keyboard text editing (composition)
			/// </summary>
			TextEditing = SDL_TEXTEDITING,

			/// <summary>
			/// keyboard text input
			/// </summary>
			TextInput = SDL_TEXTINPUT,

			/// <summary>
			/// keymap changed due to a system event such as an input language or
			/// keyboard layout change
			/// </summary>
			KeyMapChanged = SDL_KEYMAPCHANGED,

			/// <summary>
			/// Extended keyboard text editing (composition)
			/// </summary>
			TextEdittingEXT = SDL_TEXTEDITING_EXT,


			// Mouse events
			/// <summary>
			/// mouse moved
			/// </summary>
			MouseMotion = SDL_MOUSEMOTION,

			/// <summary>
			/// mouse button pressed
			/// </summary>
			MouseButtonDown = SDL_MOUSEBUTTONDOWN,

			/// <summary>
			/// mouse button released
			/// </summary>
			MouseButtonUp = SDL_MOUSEBUTTONUP,

			/// <summary>
			/// mouse wheel motion
			/// </summary>
			MouseWheel = SDL_MOUSEWHEEL,


			// Joystick events
			/// <summary>
			/// joystick axis motion
			/// </summary>
			JoyAxisMotion = SDL_JOYAXISMOTION,

			/// <summary>
			/// joystick trackball motion
			/// </summary>
			JoyBallMotion = SDL_JOYBALLMOTION,

			/// <summary>
			/// joystick hat position change
			/// </summary>
			JoyHatMotion = SDL_JOYHATMOTION,

			/// <summary>
			/// joystick button pressed
			/// </summary>
			JoyButtonDown = SDL_JOYBUTTONDOWN,

			/// <summary>
			/// joystick button released
			/// </summary>
			JoyButtonUp = SDL_JOYBUTTONUP,

			/// <summary>
			/// joystick connected
			/// </summary>
			JoyDeviceAdded = SDL_JOYDEVICEADDED,

			/// <summary>
			/// joystick disconnected
			/// </summary>
			JoyDeviceRemoved = SDL_JOYDEVICEREMOVED,

			/// <summary>
			/// Joystick battery level change
			/// </summary>
			JoyBatteryUpdated = SDL_JOYBATTERYUPDATED,


			// Controller events
			/// <summary>
			/// controller axis motion
			/// </summary>
			ControllerAxisMotion = SDL_CONTROLLERAXISMOTION,

			/// <summary>
			/// controller button pressed
			/// </summary>
			ControllerButtonDown = SDL_CONTROLLERBUTTONDOWN,

			/// <summary>
			/// controller button released
			/// </summary>
			ControllerButtonUp = SDL_CONTROLLERBUTTONUP,

			/// <summary>
			/// controller connected
			/// </summary>
			ControllerDeviceAdded = SDL_CONTROLLERDEVICEADDED,

			/// <summary>
			/// controller disconnected
			/// </summary>
			ControllerDeviceRemoved = SDL_CONTROLLERDEVICEREMOVED,

			/// <summary>
			/// controller mapping updated
			/// </summary>
			ControllerDeviceRemapped = SDL_CONTROLLERDEVICEREMAPPED,

			/// <summary>
			/// Game controller touchpad was touched
			/// </summary>
			ControllerTouchpadDown = SDL_CONTROLLERTOUCHPADDOWN,

			/// <summary>
			/// Game controller touchpad finger was moved
			/// </summary>
			ControllerTouchpadMotion = SDL_CONTROLLERTOUCHPADMOTION,

			/// <summary>
			/// Game controller touchpad finger was lifted
			/// </summary>
			ControllerTouchpadUp = SDL_CONTROLLERTOUCHPADUP,

			/// <summary>
			/// Game controller sensor was updated
			/// </summary>
			ControllerSensorUpdate = SDL_CONTROLLERSENSORUPDATE,
			

			// Touch events
			/// <summary>
			/// user has touched input device
			/// </summary>
			FingerDown = SDL_FINGERDOWN,

			/// <summary>
			/// user stopped touching input device
			/// </summary>
			FIngerUp = SDL_FINGERUP,

			/// <summary>
			/// user is dragging finger on input device
			/// </summary>
			FingerMotion = SDL_FINGERMOTION,
			

			// Gesture events

			DollarGesture = SDL_DOLLARGESTURE,
			DollarRecord = SDL_DOLLARRECORD,
			MultiGesture = SDL_MULTIGESTURE,
			

		    // Clipboard events
			/// <summary>
			/// the clipboard changed
			/// </summary>
			ClipboardUpdate = SDL_CLIPBOARDUPDATE, 


			// Drag and drop events
			/// <summary>
			/// the system requests a file open
			/// </summary>
			DropFile = SDL_DROPFILE,

			/// <summary>
			/// text/plain drag-and-drop event
			/// </summary>
			DropText = SDL_DROPTEXT,

			/// <summary>
			/// a new set of drops is beginning
			/// </summary>
			DropBegin = SDL_DROPBEGIN,

			/// <summary>
			/// current set of drops is now complete 
			/// </summary>
			DropComplete = SDL_DROPCOMPLETE,


			// Audio hotplug events
			/// <summary>
			/// a new audio device is available
			/// </summary>
			AudioDeviceAdded = SDL_AUDIODEVICEADDED,

			/// <summary>
			/// an audio device has been removed
			/// </summary>
			AudioDeviceRemoved = SDL_AUDIODEVICEREMOVED,
			

			// Sensor events
			/// <summary>
			/// A sensor was updated
			/// </summary>
			SensorUpdate = SDL_SENSORUPDATE,
			

			// Render events
			/// <summary>
			/// the render targets have been reset and their contents need to be
			/// updated
			/// </summary>
			RenderTargetsReset = SDL_RENDER_TARGETS_RESET,

			/// <summary>
			/// the device has been reset and all textures need to be recreated
			/// </summary>
			RenderDeviceReset = SDL_RENDER_DEVICE_RESET,


			// Internal events
			/// <summary>
			/// Signals the end of an event poll cycle
			/// </summary>
			PollSentinel = SDL_POLLSENTINEL, 


			/// <summary>
			/// a user-specified event
			/// </summary>
			UserEvent = SDL_USEREVENT,


			/// <summary>
			/// only for bounding internal arrays
			/// </summary>
			LastEvent = SDL_LASTEVENT,
		};

		/// <summary>
		/// Fields shared by every event.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct CommonEvent
		{
			EventType Type;

			/// <summary>
			/// Timestamp in milliseconds.
			/// </summary>
			Uint32 Timestamp;
		};

		/// <summary>
		/// Event subtype for display events.
		/// </summary>
		public enum class DisplayEventID : Uint8
		{
			/// <summary>
			/// Never used.
			/// </summary>
			None = SDL_DISPLAYEVENT_NONE,

			/// <summary>
			/// Display orientation has changed.
			/// </summary>
			Orientation = SDL_DISPLAYEVENT_ORIENTATION,

			/// <summary>
			/// Display has been added to the system.
			/// </summary>
			Connected = SDL_DISPLAYEVENT_CONNECTED,

			/// <summary>
			/// Display has been removed from the system.
			/// </summary>
			Disconnected = SDL_DISPLAYEVENT_DISCONNECTED,
		};

		/// <summary>
		/// Display state change event data.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct DisplayEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The associated display index.
			/// </summary>
			Uint32 display;

			/// <summary>
			/// Display event type.
			/// </summary>
			DisplayEventID event;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;

			/// <summary>
			/// Event dependent data.
			/// </summary>
			Sint32 data1;
		};

		/// <summary>
		/// Event subtype for window events.
		/// </summary>
		public enum class WindowEventID : Uint8
		{
			/// <summary>
			/// Never used.
			/// </summary>
			None = SDL_WINDOWEVENT_NONE,

			/// <summary>
			/// Window has been shown.
			/// </summary>
			Shown = SDL_WINDOWEVENT_SHOWN,

			/// <summary>
			/// Window has been hidden.
			/// </summary>
			Hidden = SDL_WINDOWEVENT_HIDDEN,

			/// <summary>
			/// Window has been exposed and should be redrawn.
			/// </summary>
			Exposed = SDL_WINDOWEVENT_EXPOSED,

			/// <summary>
			/// Window has been moved to data1, data2.
			/// </summary>
			Moved = SDL_WINDOWEVENT_MOVED,

			/// <summary>
			/// Window has been resized to data1xdata2.
			/// </summary>
			Resized = SDL_WINDOWEVENT_RESIZED,

			/// <summary>
			/// The window size has changed, either as a result of an API call or through the system or
			/// user changing the window size.
			/// </summary>
			SizeChanged = SDL_WINDOWEVENT_SIZE_CHANGED,

			/// <summary>
			/// Window has been minimized.
			/// </summary>
			Minimized = SDL_WINDOWEVENT_MINIMIZED,

			/// <summary>
			/// Window has been maximized.
			/// </summary>
			Maximized = SDL_WINDOWEVENT_MAXIMIZED,

			/// <summary>
			/// Window has been restored to normal size and position.
			/// </summary>
			Restored = SDL_WINDOWEVENT_RESTORED,

			/// <summary>
			/// Window has gained mouse focus.
			/// </summary>
			Enter = SDL_WINDOWEVENT_ENTER,

			/// <summary>
			/// Window has lost mouse focus.
			/// </summary>
			Leave = SDL_WINDOWEVENT_LEAVE,

			/// <summary>
			/// Window has gained keyboard focus.
			/// </summary>
			FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,

			/// <summary>
			/// Window has lost keyboard focus.
			/// </summary>
			FocusLost = SDL_WINDOWEVENT_FOCUS_LOST,

			/// <summary>
			/// The window manager requests that the window be closed.
			/// </summary>
			Close = SDL_WINDOWEVENT_CLOSE,

			/// <summary>
			/// Window is being offered a focus.
			/// </summary>
			TakeFocus = SDL_WINDOWEVENT_TAKE_FOCUS,

			/// <summary>
			/// Window had a hit test that wasn't Normal.
			/// </summary>
			HitTest = SDL_WINDOWEVENT_HIT_TEST,

			/// <summary>
			/// The ICC profile of the window's display has changed.
			/// </summary>
			CIIProfileChanged = SDL_WINDOWEVENT_ICCPROF_CHANGED,

			/// <summary>
			/// Window has been moved to display data1.
			/// </summary>
			DisplayChanged = SDL_WINDOWEVENT_DISPLAY_CHANGED
		};

		/// <summary>
		/// Window state change event data.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct WindowEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The associated window.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// Window event type.
			/// </summary>
			WindowEventID event;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;
			Sint32 data1;
			Sint32 data2;
		};

		/// <summary>
		/// State of the key.
		/// </summary>
		public enum class Keystate : Uint8
		{
			/// <summary>
			/// The key is pressed.
			/// </summary>
			Pressed = SDL_PRESSED,

			/// <summary>
			/// The key is released.
			/// </summary>
			Released = SDL_RELEASED,
		};

		/// <summary>
		/// Fields shared by every event.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct KeyboardEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with keyboard focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The state of the key.
			/// </summary>
			Keystate State;

			/// <summary>
			/// Non-zero if this is a key repeat.
			/// </summary>
			Uint8 Repeat;
			Uint8 Padding2;
			Uint8 Padding3;

			/// <summary>
			/// The key that was pressed or released
			/// </summary>
			Keysym Keysym;
		};

		/// <summary>
		/// A union that contains structures for the different event types.
		/// </summary>
		[StructLayout(LayoutKind::Explicit, Size = 56)]
		public value struct Event
		{
			/// <summary>
			/// Event type, shared with all events.
			/// </summary>
			[FieldOffset(0)] EventType Type;

			/// <summary>
			/// Common event data.
			/// </summary>
			[FieldOffset(0)] CommonEvent Common;

			/// <summary>
			/// Display event data.
			/// </summary>
			[FieldOffset(0)] DisplayEvent Display;

			/// <summary>
			/// Window event data.
			/// </summary>
			[FieldOffset(0)] WindowEvent Window;

			/// <summary>
			/// Keyboard event data.
			/// </summary>
			[FieldOffset(0)] KeyboardEvent Key;
		};
	}
}