#pragma once

#include <SDL.h>

#include "Keysym.h"
#include "Button.h"
#include "Touch.h"
#include "Joysticks.h"
#include "Controllers.h"
#include "Sensors.h"
#include "../video/SysWMInfo.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;
using namespace NETSDL2::Video;

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
		/// Keyboard button event structure.
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
		/// A structure that contains keyboard text
		/// editing event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct TextEditingEvent
		{
			[StructLayout(LayoutKind::Sequential, Size = SDL_TEXTEDITINGEVENT_TEXT_SIZE)]
			[CompilerGenerated]
			[UnsafeValueType]
			value struct e__FixedBuffer
			{
				char FixedElementField;

				property char default[int]
				{
					char get(int index);
				}
			};

			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with keyboard focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The null-terminated editing text in
			/// UTF-8 encoding.
			/// </summary>
			[FixedBuffer(char::typeid, SDL_TEXTEDITINGEVENT_TEXT_SIZE)]
			e__FixedBuffer Text;

			/// <summary>
			/// The location to begin editing from.
			/// </summary>
			Sint32 Start;

			/// <summary>
			/// The number of characters to edit from
			/// the start point.
			/// </summary>
			Sint32 Length;

			/// <summary>
			/// Get the .NET string of the Text field.
			/// </summary>
			property System::String^ ManagedText
			{
				System::String^ get();
			}
		};

		/// <summary>
		/// Extended keyboard text editing event structure
		/// when text would be truncated if stored in the
		/// text buffer TextEditingEvent.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct TextEditingExtEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with keyboard focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The editing text, which should be freed
			/// with SDL_free(), and will not be null.
			/// </summary>
			char* Text;

			/// <summary>
			/// The location to begin editing from.
			/// </summary>
			Sint32 Start;

			/// <summary>
			/// The number of characters to edit from
			/// the start point.
			/// </summary>
			Sint32 Length;

			/// <summary>
			/// Get the .NET string of the Text field.
			/// </summary>
			property System::String^ ManagedText
			{
				System::String^ get();
			}
		};

		/// <summary>
		/// A structure that contains keyboard text input
		/// event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct TextInputEvent
		{
			[StructLayout(LayoutKind::Sequential, Size = SDL_TEXTINPUTEVENT_TEXT_SIZE)]
			[CompilerGenerated]
			[UnsafeValueType]
			value struct e__FixedBuffer
			{
				char FixedElementField;

				property char default[int]
				{
					char get(int index);
				}
			};

			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with keyboard focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The null-terminated input text in
			/// UTF-8 encoding.
			/// </summary>
			[FixedBuffer(char::typeid, SDL_TEXTINPUTEVENT_TEXT_SIZE)]
			e__FixedBuffer Text;

			/// <summary>
			/// Get the .NET string of the Text field.
			/// </summary>
			property System::String^ ManagedText
			{
				System::String^ get();
			}
		};

		/// <summary>
		/// A structure that contains mouse motion event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct MouseMotionEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with mouse focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The mouse instance id, or
			/// <see cref="Touch::TOUCH_MOUSEID"/>.
			/// </summary>
			Uint32 Which;

			/// <summary>
			/// The state of the button.
			/// </summary>
			ButtonState State;

			/// <summary>
			/// X coordinate, relative to window.
			/// </summary>
			Sint32 X;

			/// <summary>
			/// Y coordinate, relative to window.
			/// </summary>
			Sint32 Y;

			/// <summary>
			/// Relative motion in the X direction.
			/// </summary>
			Sint32 Xrel;

			/// <summary>
			/// Relative motion in the Y direction.
			/// </summary>
			Sint32 Yrel;
		};

		/// <summary>
		/// A structure that contains mouse button event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct MouseButtonEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with mouse focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The mouse instance id, or
			/// <see cref="Touch::TOUCH_MOUSEID"/>.
			/// </summary>
			Uint32 Which;

			/// <summary>
			/// The button that changed.
			/// </summary>
			Button Button;

			/// <summary>
			/// The state of the button.
			/// </summary>
			ButtonPress State;

			/// <summary>
			/// 1 for single-click, 2 for double-click, etc.
			/// </summary>
			Uint8 Clicks;
			Uint8 padding1;

			/// <summary>
			/// X coordinate, relative to window.
			/// </summary>
			Sint32 X;

			/// <summary>
			/// Y coordinate, relative to window.
			/// </summary>
			Sint32 Y;
		};

		/// <summary>
		/// A structure that contains mouse wheel event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct MouseWheelEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The window with mouse focus, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// The mouse instance id, or
			/// <see cref="Touch::TOUCH_MOUSEID"/>.
			/// </summary>
			Uint32 Which;

			/// <summary>
			/// The amount scrolled horizontally, positive
			/// to the right and negative to the left.
			/// </summary>
			Sint32 X;

			/// <summary>
			/// The amount scrolled vertically, positive
			/// away from the user and negative towards the
			/// user.
			/// </summary>
			Sint32 Y;

			/// <summary>
			/// If direction is Flipped the values in x
			/// and y will be opposite. Multiply by -1 to
			/// change them back.
			/// </summary>
			MousewheelDirection Direction;

			/// <summary>
			/// The amount scrolled horizontally, positive
			/// to the right and negative to the left, with
			/// float precision.
			/// </summary>
			float PreciseX;

			/// <summary>
			/// The amount scrolled vertically, positive
			/// away from the user and negative toward the
			/// user, with float precision.
			/// </summary>
			float PreciseY;
		};

		/// <summary>
		/// A structure that contains joystick axis motion
		/// event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyAxisEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The index of the axis that changed.
			/// </summary>
			Uint8 Axis;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;

			/// <summary>
			/// The current position of the axis
			/// (range: -32768 to 32767).
			/// </summary>
			Sint16 Value;
			Uint16 padding4;
		};

		/// <summary>
		/// A structure that contains joystick trackball
		/// motion event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyBallEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The index of the trackball that changed.
			/// </summary>
			Uint8 Ball;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;

			/// <summary>
			/// The relative motion in the X direction.
			/// </summary>
			Sint16 Xrel;

			/// <summary>
			/// The relative motion in the Y direction.
			/// </summary>
			Sint16 Yrel;
		};

		/// <summary>
		/// A structure that contains joystick hat position
		/// change event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyHatEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The index of the hat that changed.
			/// </summary>
			Uint8 Hat;

			/// <summary>
			/// The new position of the hat.
			/// </summary>
			HatPosition Value;
			Uint8 padding1;
			Uint8 padding2;
		};

		/// <summary>
		/// A structure that contains joystick button event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyButtonEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The index of the button that changed.
			/// </summary>
			Uint8 Button;

			/// <summary>
			/// The state of the button.
			/// </summary>
			ButtonPress State;
			Uint8 padding1;
			Uint8 padding2;
		};

		/// <summary>
		/// A structure that contains joystick device event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyDeviceEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The joystick device index for the
			/// SDL_JOYDEVICEADDED event or the instance
			/// id for the SDL_JOYDEVICEREMOVED event.
			/// </summary>
			Sint32 Which;
		};

		/// <summary>
		/// Joysick battery level change event structure.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct JoyBatteryEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The joystick battery level.
			/// </summary>
			JoystickPowerLevel Level;
		};

		/// <summary>
		/// A structure that contains game controller axis
		/// motion event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct ControllerAxisEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The controller axis.
			/// </summary>
			GameControllerAxis Axis;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;

			/// <summary>
			/// The axis value
			/// (range: -32768 to 32767).
			/// </summary>
			Sint16 Value;
			Uint16 padding4;
		};

		/// <summary>
		/// A structure that contains game controller
		/// button event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct ControllerButtonEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The controller button.
			/// </summary>
			GameControllerButton Button;

			/// <summary>
			/// The state of the button.
			/// </summary>
			ButtonPress State;
			Uint8 padding1;
			Uint8 padding2;
		};

		/// <summary>
		/// A structure that contains controller device
		/// event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct ControllerDeviceEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The joystick device index for the
			/// SDL_CONTROLLERDEVICEADDED event or instance
			/// id for the SDL_CONTROLLERDEVICEREMOVED or
			/// SDL_CONTROLLERDEVICEREMAPPED event.
			/// </summary>
			Sint32 Which;
		};

		/// <summary>
		/// Game controller touchpad event structure.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct ControllerTouchpadEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The index of the touchpad.
			/// </summary>
			Sint32 Touchpad;

			/// <summary>
			/// The index of the finger on the touchpad.
			/// </summary>
			Sint32 Finger;

			/// <summary>
			/// Normalized in the range 0...1 with 0 being
			/// on the left.
			/// </summary>
			float X;

			/// <summary>
			/// Normalized in the range 0...1 with 0 being
			/// at the top.
			/// </summary>
			float Y;

			/// <summary>
			/// Normalized in the range 0...1.
			/// </summary>
			float Pressure;
		};

		/// <summary>
		/// Game controller sensor event structure.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct ControllerSensorEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance id of the joystick that
			/// reported the event.
			/// </summary>
			SDL_JoystickID Which;

			/// <summary>
			/// The type of the sensor
			/// </summary>
			SensorType Sensor;

			/// <summary>
			/// Up to 3 values from the sensor.
			/// </summary>
			float Data1;

			/// <summary>
			/// Up to 3 values from the sensor.
			/// </summary>
			float Data2;

			/// <summary>
			/// Up to 3 values from the sensor.
			/// </summary>
			float Data3;
		};

		/// <summary>
		/// A structure that contains Audio device event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct AudioDeviceEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The audio device index for the
			/// SDL_AUDIODEVICEADDED event,
			/// SDL_AudioDeviceID for the
			/// SDL_AUDIODEVICEREMOVED event
			/// </summary>
			Uint32 Which;

			/// <summary>
			/// Zero if an audio output device, non-zero
			/// if an audio capture device.
			/// </summary>
			Uint8 IsCapture;
			Uint8 padding1;
			Uint8 padding2;
			Uint8 padding3;
		};

		/// <summary>
		/// A structure that contains sensor updates.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct SensorEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The instance ID of the sensor.
			/// </summary>
			Sint32 Which;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data1;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data2;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data3;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data4;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data5;

			/// <summary>
			/// Up to 6 values from the sensor.
			/// </summary>
			float Data6;
		};

		/// <summary>
		/// A structure that contains the "quit requested"
		/// event.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct QuitEvent
		{
			EventType Type;
			Uint32 Timestamp;
		};

		/// <summary>
		/// A structure that contains an application-defined
		/// event type.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct UserEvent
		{
			/// <summary>
			/// Value obtained from RegisterEvents
			/// </summary>
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The associated window, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// User defined event code.
			/// </summary>
			Sint32 Code;

			/// <summary>
			/// User defined data pointer.
			/// </summary>
			System::IntPtr Data1;

			/// <summary>
			/// User defined data pointer.
			/// </summary>
			System::IntPtr Data2;
		};

		/// <summary>
		/// A structure that contains a video driver
		/// dependent system event.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct SysWMEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// Driver dependent data.
			/// </summary>
			SysWMMsg* Msg;
		};

		/// <summary>
		/// A structure that contains a video driver
		/// dependent system event.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct TouchFingerEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The touch device id.
			/// </summary>
			SDL_TouchID TouchId;

			/// <summary>
			/// The finger id.
			/// </summary>
			SDL_FingerID FingerId;

			/// <summary>
			/// The x-axis location of the touch event,
			/// normalized (0...1).
			/// </summary>
			float X;

			/// <summary>
			/// The y-axis location of the touch event,
			/// normalized (0...1).
			/// </summary>
			float Y;

			/// <summary>
			/// The distance moved in the x-axis,
			/// normalized (-1...1).
			/// </summary>
			float Dx;

			/// <summary>
			/// The distance moved in the y-axis,
			/// normalized (-1...1).
			/// </summary>
			float Dy;

			/// <summary>
			/// The quantity of pressure applied,
			/// normalized (0...1).
			/// </summary>
			float Pressure;

			/// <summary>
			/// The window underneath the finger, if any.
			/// </summary>
			Uint32 WindowID;
		};

		/// <summary>
		/// A structure that contains multiple finger
		/// gesture event information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct MultiGestureEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The touch device id.
			/// </summary>
			SDL_TouchID TouchId;

			/// <summary>
			/// The amount that the fingers rotated
			/// during this motion, in radians.
			/// </summary>
			float DTheta;

			/// <summary>
			/// The amount that the fingers pinched during
			/// this motion.
			/// </summary>
			float DDist;

			/// <summary>
			/// The normalized center of gesture.
			/// </summary>
			float X;

			/// <summary>
			/// The normalized center of gesture.
			/// </summary>
			float Y;

			/// <summary>
			/// The number of fingers used in the gesture.
			/// </summary>
			Uint16 NumFingers;
			Uint16 padding;
		};

		/// <summary>
		/// A structure that contains complex gesture event
		/// information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct DollarGestureEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The touch device id.
			/// </summary>
			SDL_TouchID TouchId;

			/// <summary>
			/// The unique id of the closest gesture to the
			/// performed stroke.
			/// </summary>
			SDL_GestureID GestureId;

			/// <summary>
			/// The number of fingers used to draw the
			/// stroke.
			/// </summary>
			Uint32 NumFingers;

			/// <summary>
			/// The difference between the gesture
			/// template and the actual performed gesture.
			/// </summary>
			float Error;

			/// <summary>
			/// The normalized center of gesture.
			/// </summary>
			float X;

			/// <summary>
			/// The normalized center of gesture.
			/// </summary>
			float Y;
		};

		/// <summary>
		/// A structure that contains an event used to
		/// request a file open by the system.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct DropEvent
		{
			EventType Type;
			Uint32 Timestamp;

			/// <summary>
			/// The file name, which should be freed with
			/// SDL_free(), is null on BEGIN/COMPLETE.
			/// </summary>
			char* File;

			/// <summary>
			/// The window that was dropped on, if any.
			/// </summary>
			Uint32 WindowID;

			/// <summary>
			/// Get the .NET string of the File field.
			/// </summary>
			property System::String^ ManagedFile
			{
				System::String^ get();
			}
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

			/// <summary>
			/// Text editing event data.
			/// </summary>
			[FieldOffset(0)] TextEditingEvent Edit;

			/// <summary>
			/// Extended text editing event data.
			/// </summary>
			[FieldOffset(0)] TextEditingExtEvent EditExt;

			/// <summary>
			/// Text input event data.
			/// </summary>
			[FieldOffset(0)] TextInputEvent Text;

			/// <summary>
			/// Mouse motion event data.
			/// </summary>
			[FieldOffset(0)] MouseMotionEvent Motion;

			/// <summary>
			/// Mouse button event data.
			/// </summary>
			[FieldOffset(0)] MouseButtonEvent Button;

			/// <summary>
			/// Mouse wheel event data.
			/// </summary>
			[FieldOffset(0)] MouseWheelEvent Wheel;

			/// <summary>
			/// Joystick axis event data.
			/// </summary>
			[FieldOffset(0)] JoyAxisEvent JAxis;

			/// <summary>
			/// Joystick ball event data.
			/// </summary>
			[FieldOffset(0)] JoyBallEvent JBall;

			/// <summary>
			/// Joystick hat event data.
			/// </summary>
			[FieldOffset(0)] JoyHatEvent JHat;

			/// <summary>
			/// Joystick button event data.
			/// </summary>
			[FieldOffset(0)] JoyButtonEvent JButton;

			/// <summary>
			/// Joystick device change event data.
			/// </summary>
			[FieldOffset(0)] JoyDeviceEvent JDevice;

			/// <summary>
			/// Joystick battery event data.
			/// </summary>
			[FieldOffset(0)] JoyBatteryEvent JBattery;

			/// <summary>
			/// Game controller axis event data.
			/// </summary>
			[FieldOffset(0)] ControllerAxisEvent CAxis;

			/// <summary>
			/// Game controller button event data.
			/// </summary>
			[FieldOffset(0)] ControllerButtonEvent CButton;

			/// <summary>
			/// Game controller device event data.
			/// </summary>
			[FieldOffset(0)] ControllerDeviceEvent CDevice;

			/// <summary>
			/// Game controller touchpad event data.
			/// </summary>
			[FieldOffset(0)] ControllerTouchpadEvent CTouchpad;

			/// <summary>
			/// Game controller sensor event data.
			/// </summary>
			[FieldOffset(0)] ControllerSensorEvent CSensor;

			/// <summary>
			/// Audio device event data.
			/// </summary>
			[FieldOffset(0)] AudioDeviceEvent ADevice;

			/// <summary>
			/// Sensor event data.
			/// </summary>
			[FieldOffset(0)] SensorEvent Sensor;

			/// <summary>
			/// Quit request event data.
			/// </summary>
			[FieldOffset(0)] QuitEvent Quit;

			/// <summary>
			/// Custom event data.
			/// </summary>
			[FieldOffset(0)] UserEvent User;

			/// <summary>
			/// System dependent window event data.
			/// </summary>
			[FieldOffset(0)] SysWMEvent Syswm;

			/// <summary>
			/// Touch finger event data.
			/// </summary>
			[FieldOffset(0)] TouchFingerEvent TFinger;

			/// <summary>
			/// Gesture event data.
			/// </summary>
			[FieldOffset(0)] MultiGestureEvent MGesture;

			/// <summary>
			/// Gesture event data.
			/// </summary>
			[FieldOffset(0)] DollarGestureEvent DGesture;

			/// <summary>
			/// Drag and drop event data.
			/// </summary>
			[FieldOffset(0)] DropEvent Drop;
		};
	}
}