#include "../../include/video/Window.h"
#include <msclr/marshal.h>

#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"
#include "../../include/video/Display.h"
#include "../../include/video/GLContext.h"
#include "../../include/video/Renderer.h"
#include "../../include/video/Surface.h"

#include "../../include/internal/StringMarshal.h"

#include <SDL_vulkan.h>
#include <vector>

using namespace NETSDL2::Internal;

using namespace msclr::interop;
using namespace System::Threading;

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

SDL_HitTestResult NETSDL2::Video::Window::HitTestNative(SDL_Window* win, const SDL_Point* area, void* data)
{
	Window^ window = nullptr;
	if(!nativeWindowConnections->TryGetValue(System::IntPtr(win), window))
		return SDL_HITTEST_NORMAL;

	return (SDL_HitTestResult)window->hitTestCallback(window, *((NETSDL2::Video::Point*)area), System::IntPtr(data));
}

HitTestResult NETSDL2::Video::Window::DefaultHitTest(Window^ win, NETSDL2::Video::Point area, System::IntPtr data)
{
	return HitTestResult::Normal;
}

int NETSDL2::Video::Window::WindowEventCheckNative(void* userdata, SDL_Event* event)
{
	if(event->type == SDL_WINDOWEVENT)
	{
		SDL_WindowEvent* winEvent = &event->window;
		if(winEvent->windowID != this->ID)
			return 0;

		switch(winEvent->event)
		{
		case SDL_WINDOWEVENT_NONE:
			break;
		case SDL_WINDOWEVENT_SHOWN:
			OnShown(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			OnHidden(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_EXPOSED:
			OnExposed(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_MOVED:
			OnMoved(this, winEvent->timestamp, winEvent->data1, winEvent->data2);
			break;
		case SDL_WINDOWEVENT_RESIZED:
			OnResized(this, winEvent->timestamp, winEvent->data1, winEvent->data2);
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			OnSizeChanged(this, winEvent->timestamp, winEvent->data1, winEvent->data2);
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			OnMinimized(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			OnMaximized(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_RESTORED:
			OnRestored(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_ENTER:
			OnEnter(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_LEAVE:
			OnLeave(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			OnFocusGained(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
			OnFocusLost(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_CLOSE:
			OnClose(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_TAKE_FOCUS:
			OnTakeFocus(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_HIT_TEST:
			OnHitTest(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_ICCPROF_CHANGED:
			OnICCProfileChanged(this, winEvent->timestamp);
			break;
		case SDL_WINDOWEVENT_DISPLAY_CHANGED:
			OnDisplayChanged(this, winEvent->timestamp, winEvent->data1);
			break;
		default:
			break;
		}
	}

	if(event->type == SDL_KEYDOWN)
	{
		SDL_KeyboardEvent* keyEvent = &event->key;
		if(keyEvent->windowID != this->ID)
			return 0;

		if(keyEvent->repeat == 0)
		{
			OnKeyPressed(this, keyEvent->timestamp, (Scancode)keyEvent->keysym.scancode, (Keycode)keyEvent->keysym.sym, (Keymode)keyEvent->keysym.mod);
		}
		else
		{
			OnKeyPressing(this, keyEvent->timestamp, (Scancode)keyEvent->keysym.scancode, (Keycode)keyEvent->keysym.sym, (Keymode)keyEvent->keysym.mod);
		}
	}

	if(event->type == SDL_KEYUP)
	{
		SDL_KeyboardEvent* keyEvent = &event->key;
		if(keyEvent->windowID != this->ID)
			return 0;

		OnKeyReleased(this, keyEvent->timestamp, (Scancode)keyEvent->keysym.scancode, (Keycode)keyEvent->keysym.sym, (Keymode)keyEvent->keysym.mod);
	}

	return 0;
}

void NETSDL2::Video::Window::InitCallbacks()
{
	hitTestCallback = gcnew HitTest(&Window::DefaultHitTest);
	NativeHitTest^ native = gcnew NativeHitTest(&Window::HitTestNative);

	hitTestCallbackHandle = GCHandle::Alloc(native);
	nativeHitTestCallback = reinterpret_cast<SDL_HitTest>(Marshal::GetFunctionPointerForDelegate(native).ToPointer());

	if(SDL_SetWindowHitTest(window, nativeHitTestCallback, __nullptr) < 0)
		throw gcnew System::Exception("Failed to initialize hit test callback.");

	OnShown += gcnew WindowShownEvent(Window::WindowEventNoData);
	OnHidden += gcnew NETSDL2::Video::WindowHiddenEvent(NETSDL2::Video::Window::WindowEventNoData);
	OnExposed += gcnew NETSDL2::Video::WindowExposedEvent(NETSDL2::Video::Window::WindowEventNoData);
	OnMoved += gcnew NETSDL2::Video::WindowMovedEvent(NETSDL2::Video::Window::WindowEventTwoData);
	OnResized += gcnew NETSDL2::Video::WindowResizedEvent(NETSDL2::Video::Window::WindowEventTwoData);
	OnSizeChanged += gcnew NETSDL2::Video::WindowSizeChangedEvent(NETSDL2::Video::Window::WindowEventTwoData);
	OnMinimized += gcnew NETSDL2::Video::WindowMinimizedEvent(Window::WindowEventNoData);
	OnMaximized += gcnew NETSDL2::Video::WindowMaximizedEvent(Window::WindowEventNoData);
	OnRestored += gcnew NETSDL2::Video::WindowRestoredEvent(Window::WindowEventNoData);
	OnEnter += gcnew NETSDL2::Video::WindowEnterEvent(Window::WindowEventNoData);
	OnLeave += gcnew NETSDL2::Video::WindowLeaveEvent(Window::WindowEventNoData);
	OnFocusGained += gcnew NETSDL2::Video::WindowFocusGainedEvent(Window::WindowEventNoData);
	OnFocusLost += gcnew NETSDL2::Video::WindowFocusLostEvent(Window::WindowEventNoData);
	OnClose += gcnew NETSDL2::Video::WindowCloseEvent(Window::WindowEventNoData);
	OnTakeFocus += gcnew NETSDL2::Video::WindowTakeFocusEvent(Window::WindowEventNoData);
	OnHitTest += gcnew NETSDL2::Video::WindowHitTestEvent(Window::WindowEventNoData);
	OnICCProfileChanged += gcnew NETSDL2::Video::WindowICCProfileChangedEvent(Window::WindowEventNoData);
	OnDisplayChanged += gcnew NETSDL2::Video::WindowDisplayChangedEvent(Window::WindowEventOneData);
	OnKeyPressed += gcnew NETSDL2::Video::WindowKeyboardInputEvent(Window::WindowEventKeyboardInput);
	OnKeyPressing += gcnew NETSDL2::Video::WindowKeyboardInputEvent(Window::WindowEventKeyboardInput);
	OnKeyReleased += gcnew NETSDL2::Video::WindowKeyboardInputEvent(Window::WindowEventKeyboardInput);

	NativeWindowEventFilter^ nativeWindow = gcnew NativeWindowEventFilter(this, &Window::WindowEventCheckNative);

	windowEventCallbackHandle = GCHandle::Alloc(nativeWindow);
	nativeWindowEventCallback = reinterpret_cast<SDL_EventFilter>(Marshal::GetFunctionPointerForDelegate(nativeWindow).ToPointer());

	SDL_AddEventWatch(nativeWindowEventCallback, window);
}

void NETSDL2::Video::Window::ClearCallbacks()
{
	nativeHitTestCallback = __nullptr;
	hitTestCallbackHandle.Free();

	SDL_DelEventWatch(nativeWindowEventCallback, window);
	nativeWindowEventCallback = __nullptr;
	windowEventCallbackHandle.Free();
}

void NETSDL2::Video::Window::InitWindow(SDL_Window* window)
{
	this->window = window;
	windowSurface = nullptr;
	nativeWindowConnections[System::IntPtr(window)] = this;

	InitCallbacks();
}

NETSDL2::Video::Window::Window(System::String^ title, int x, int y, int w, int h, WindowFlags flags)
{
	StringMarshal context;
	SDL_Window* window = SDL_CreateWindow(context.ManagedToUTF8Native(title), x, y, w, h, (Uint32)flags);

	if(window == __nullptr)
		throw gcnew System::Exception(Error::GetError());

	InitWindow(window);
}

NETSDL2::Video::Window::Window(int width, int height, WindowFlags flags, Renderer^% renderer)
{
	SDL_Window* win = __nullptr;
	SDL_Renderer* ren = __nullptr;

	int result = SDL_CreateWindowAndRenderer(width, height, (Uint32)flags, &win, &ren);
	if(result < 0)
		throw gcnew System::Exception(Error::GetError());

	InitWindow(win);
	renderer = gcnew Renderer(ren);
}

NETSDL2::Video::Window::Window(void* data)
{
	SDL_Window* window = SDL_CreateWindowFrom(data);

	if(window == __nullptr)
		throw gcnew System::Exception(Error::GetError());

	InitWindow(window);
}

NETSDL2::Video::Window::~Window()
{
	Window^ dummy = nullptr;
	nativeWindowConnections->TryRemove(System::IntPtr(window), dummy);
	this->!Window();
}

NETSDL2::Video::Window::!Window()
{
	ClearCallbacks();

	SDL_DestroyWindow(window);
	window = __nullptr;
}

System::String^ NETSDL2::Video::Window::ToString()
{
	return System::String::Format("Window \"{0}\" [ID: {1}]", Title, ID);
}

Result<None^, int> NETSDL2::Video::Window::FlashWindow(FlashOperation operation)
{
	int result = SDL_FlashWindow(window, (SDL_FlashOperation)operation);
	if(result < 0)
		return Result<None^, int>::MakeFailure(result);

	return None::Value;
}

Window^ Window::GrabbedWindow::get()
{
	SDL_Window* grabbed = SDL_GetGrabbedWindow();
	if(grabbed == __nullptr)
		return nullptr;

	Window^ grabbedWindow = nullptr;
	if(!nativeWindowConnections->TryGetValue(System::IntPtr(grabbed), grabbedWindow))
		return nullptr;

	return grabbedWindow;
}

Result<None^, int> NETSDL2::Video::Window::GetWindowBordersSize(int% top, int% left, int% bottom, int% right)
{
	int t, l, b, r;
	int result = SDL_GetWindowBordersSize(window, &t, &l, &b, &r);
	if(result < 0)
		return Result<None^, int>::MakeFailure(result);

	top = t;
	left = l;
	bottom = b;
	right = r;

	return None::Value;
}

float Window::WindowBrightness::get()
{
	return SDL_GetWindowBrightness(window);
}

System::IntPtr NETSDL2::Video::Window::GetWindowData(System::String^ name)
{
	StringMarshal context;
	return System::IntPtr(SDL_GetWindowData(window, context.ManagedToUTF8Native(name)));
}

int Window::WindowDisplayIndex::get()
{
	return SDL_GetWindowDisplayIndex(window);
}

Result<DisplayMode, int> NETSDL2::Video::Window::GetWindowDisplayMode()
{
	DisplayMode mode;
	int result = SDL_GetWindowDisplayMode(window, (SDL_DisplayMode*)&mode);
	if(result < 0)
		return Result<DisplayMode, int>::MakeFailure(result);

	return mode;
}

WindowFlags Window::Flags::get()
{
	return (WindowFlags)SDL_GetWindowFlags(window);
}

Result<Window^, None^> NETSDL2::Video::Window::GetWindowFromID(Uint32 id)
{
	SDL_Window* win = SDL_GetWindowFromID(id);
	if(win == __nullptr)
		return Result<Window^, None^>::MakeFailure(None::Value);

	Window^ window = nullptr;
	if(!nativeWindowConnections->TryGetValue(System::IntPtr(win), window))
		return Result<Window^, None^>::MakeFailure(None::Value);

	return window;
}

Result<None^, int> NETSDL2::Video::Window::GetWindowGammaRamp(array<Uint16>^ red, array<Uint16>^ green, array<Uint16>^ blue)
{
	if(red != nullptr && red->Length < 256)
	{
		SDL_InvalidParamError(red);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	if(green != nullptr && green->Length < 256)
	{
		SDL_InvalidParamError(green);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	if(blue != nullptr && blue->Length < 256)
	{
		SDL_InvalidParamError(blue);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	pin_ptr<Uint16> pRed = red == nullptr ? nullptr : &red[0];
	pin_ptr<Uint16> pGreen = green == nullptr ? nullptr : &green[0];
	pin_ptr<Uint16> pBlue = blue == nullptr ? nullptr : &blue[0];

	int result = SDL_GetWindowGammaRamp(window, (Uint16*)pRed, (Uint16*)pGreen, (Uint16*)pBlue);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	pRed = nullptr;
	pGreen = nullptr;
	pBlue = nullptr;

	return None::Value;
}

bool Window::IsGrabbed::get()
{
	return SDL_GetWindowGrab(window) == SDL_TRUE;
}

void Window::IsGrabbed::set(bool value)
{
	SDL_SetWindowGrab(window, value ? SDL_TRUE : SDL_FALSE);
}

Uint32 Window::ID::get()
{
	return SDL_GetWindowID(window);
}

void NETSDL2::Video::Window::GetWindowMaximumSize(int% w, int% h)
{
	int width, height;
	SDL_GetWindowMaximumSize(window, &width, &height);
	w = width;
	h = height;
}

void NETSDL2::Video::Window::GetWindowMinimumSize(int% w, int% h)
{
	int width, height;
	SDL_GetWindowMinimumSize(window, &width, &height);
	w = width;
	h = height;
}

Result<float, int> NETSDL2::Video::Window::GetWindowOpacity()
{
	float opacity;
	int result = SDL_GetWindowOpacity(window, &opacity);
	if(result < 0)
	{
		return Result<float, int>::MakeFailure(result);
	}

	return opacity;
}

PixelFormatEnum Window::WindowPixelFormat::get()
{
	return (PixelFormatEnum)SDL_GetWindowPixelFormat(window);
}

void NETSDL2::Video::Window::GetWindowPosition(int% x, int% y)
{
	int px, py;
	SDL_GetWindowPosition(window, &px, &py);
	x = px;
	y = py;
}

void NETSDL2::Video::Window::GetWindowSize(int% w, int% h)
{
	int width, height;
	SDL_GetWindowSize(window, &width, &height);
	w = width;
	h = height;
}

#ifdef MemoryBarrier
#undef MemoryBarrier
#endif

Result<Surface^, None^> NETSDL2::Video::Window::GetWindowSurface()
{
	// Thread-safe non-blocking implementation.

	while(true)
	{
		SDL_Surface* surface = SDL_GetWindowSurface(window);
		if(surface == __nullptr)
		{
			return Result<Surface^, None^>::MakeFailure(None::Value);
		}

		Surface^ current = windowSurface;
		Interlocked::MemoryBarrier();

		if(current == nullptr || current->NativeSurface != surface)
		{
			Surface^ newCurr = gcnew Surface(surface, false);

			Interlocked::MemoryBarrier();
			if(Interlocked::CompareExchange(windowSurface, newCurr, current) != current)
			{
				// The windowSurface has changed. Retry.
				delete newCurr;
				continue;
			}

			return newCurr;
		}
		else
		{
			return current;
		}
	}
}

#ifndef MemoryBarrier
#define MemoryBarrier __faststorefence
#endif

System::String^ Window::Title::get()
{
	const char* title = SDL_GetWindowTitle(window);
	return StringMarshal::UTF8NativeToManaged(title);
}

void Window::Title::set(System::String^ title)
{
	StringMarshal context;
	SDL_SetWindowTitle(window, context.ManagedToUTF8Native(title));
}

bool NETSDL2::Video::Window::GetWindowWMInfo(SysWMInfo% info)
{
	pin_ptr<SysWMInfo> pInfo = &info;

	SDL_bool result = SDL_GetWindowWMInfo(window, (SDL_SysWMinfo*)pInfo);
	pInfo = nullptr;

	return result == SDL_TRUE;
}

void NETSDL2::Video::Window::HideWindow()
{
	SDL_HideWindow(window);
}

void NETSDL2::Video::Window::MaximizeWindow()
{
	SDL_MaximizeWindow(window);
}

void NETSDL2::Video::Window::MinimizeWindow()
{
	SDL_MinimizeWindow(window);
}

void NETSDL2::Video::Window::RaiseWindow()
{
	SDL_RaiseWindow(window);
}

void NETSDL2::Video::Window::RestoreWindow()
{
	SDL_RestoreWindow(window);
}

void NETSDL2::Video::Window::SetWindowBordered(bool bordered)
{
	SDL_SetWindowBordered(window, bordered ? SDL_TRUE : SDL_FALSE);
}

Result<None^, int> NETSDL2::Video::Window::SetWindowBrightness(float brightness)
{
	int result = SDL_SetWindowBrightness(window, brightness);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

System::IntPtr NETSDL2::Video::Window::SetWindowData(System::String^ name, System::IntPtr userdata)
{
	StringMarshal context;
	return System::IntPtr(SDL_SetWindowData(window, context.ManagedToUTF8Native(name), userdata.ToPointer()));
}

Result<None^, int> NETSDL2::Video::Window::SetWindowDisplayMode(System::Nullable<DisplayMode> mode)
{
	int result;
	if(mode.HasValue)
	{
		SDL_DisplayMode m = *((SDL_DisplayMode*)&mode.Value);
		result = SDL_SetWindowDisplayMode(window, &m);
	}
	else
	{
		result = SDL_SetWindowDisplayMode(window, __nullptr);
	}

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Window::SetWindowFullscreen(WindowFlags flags)
{
	int result = SDL_SetWindowFullscreen(window, (Uint32)flags);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Window::SetWindowGammaRamp(array<Uint16>^ red, array<Uint16>^ green, array<Uint16>^ blue)
{
	if(red != nullptr && red->Length < 256)
	{
		SDL_InvalidParamError(red);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	if(green != nullptr && green->Length < 256)
	{
		SDL_InvalidParamError(green);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	if(blue != nullptr && blue->Length < 256)
	{
		SDL_InvalidParamError(blue);
		return Result<None^, int>::MakeFailure(SDL_Error(SDL_LASTERROR));
	}

	pin_ptr<Uint16> pRed = red == nullptr ? nullptr : &red[0];
	pin_ptr<Uint16> pGreen = green == nullptr ? nullptr : &green[0];
	pin_ptr<Uint16> pBlue = blue == nullptr ? nullptr : &blue[0];

	int result = SDL_SetWindowGammaRamp(window, (Uint16*)pRed, (Uint16*)pGreen, (Uint16*)pBlue);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	pRed = nullptr;
	pGreen = nullptr;
	pBlue = nullptr;

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Window::SetWindowHitTest(HitTest^ callback, System::IntPtr callbackData)
{
	int result = SDL_SetWindowHitTest(window, nativeHitTestCallback, callbackData.ToPointer());
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	hitTestCallback = callback;

	return None::Value;
}

void NETSDL2::Video::Window::SetWindowIcon(Surface^ icon)
{
	SDL_SetWindowIcon(window, icon->NativeSurface);
}

Result<None^, int> NETSDL2::Video::Window::SetWindowInputFocus()
{
	int result = SDL_SetWindowInputFocus(window);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Window::SetWindowMaximumSize(int maxW, int maxH)
{
	SDL_SetWindowMaximumSize(window, maxW, maxH);
}

void NETSDL2::Video::Window::SetWindowMinimumSize(int minW, int minH)
{
	SDL_SetWindowMinimumSize(window, minW, minH);
}

Result<None^, int> NETSDL2::Video::Window::SetWindowModalFor(Window^ parentWindow)
{
	int result = SDL_SetWindowModalFor(window, parentWindow->window);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Window::SetWindowOpacity(float opacity)
{
	int result = SDL_SetWindowOpacity(window, opacity);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Window::SetWindowPosition(int x, int y)
{
	SDL_SetWindowPosition(window, x, y);
}

void NETSDL2::Video::Window::SetWindowResizable(bool resizable)
{
	SDL_SetWindowResizable(window, resizable ? SDL_TRUE : SDL_FALSE);
}

void NETSDL2::Video::Window::SetWindowSize(int w, int h)
{
	SDL_SetWindowSize(window, w, h);
}

Result<int, int> NETSDL2::Video::Window::ShowMessageBox(MessageBoxData% messageBoxData)
{
	StringMarshal context;

	int buttonid;

	SDL_MessageBoxData data = {};
	data.flags = (Uint32)messageBoxData.Flags;
	data.window = messageBoxData.Window == nullptr ? __nullptr : messageBoxData.Window->window;
	data.title = context.ManagedToUTF8Native(messageBoxData.Title);
	data.message = context.ManagedToUTF8Native(messageBoxData.Message);
	data.numbuttons = messageBoxData.Buttons->Length;

	std::vector<SDL_MessageBoxButtonData> buttons(data.numbuttons);
	for(int i = 0; i < data.numbuttons; i++)
	{
		buttons[i].flags = (Uint32)messageBoxData.Buttons[i].Flags;
		buttons[i].buttonid = messageBoxData.Buttons[i].ButtonID;
		buttons[i].text = context.ManagedToUTF8Native(messageBoxData.Buttons[i].Text);
	}
	data.buttons = buttons.data();

	SDL_MessageBoxColorScheme colorScheme = {};

	if(messageBoxData.ColorScheme == nullptr)
	{
		data.colorScheme = __nullptr;
	}
	else
	{
		for(int i = 0; i < (int)SDL_MESSAGEBOX_COLOR_MAX; i++)
		{
			MessageBoxColor color = messageBoxData.ColorScheme[(MessageBoxColorType)i];
			colorScheme.colors[i].r = color.R;
			colorScheme.colors[i].g = color.G;
			colorScheme.colors[i].b = color.B;
		}
		data.colorScheme = &colorScheme;
	}

	int result = SDL_ShowMessageBox(&data, &buttonid);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return buttonid;
}

Result<None^, int> NETSDL2::Video::Window::ShowSimpleMessageBox(MessageBoxFlags flags, System::String^ title, System::String^ message, Window^ window)
{
	StringMarshal context;

	int result = SDL_ShowSimpleMessageBox((Uint32)flags, context.ManagedToUTF8Native(title), context.ManagedToUTF8Native(message), window == nullptr ? __nullptr : window->window);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Window::ShowWindow()
{
	SDL_ShowWindow(window);
}

Result<None^, int> NETSDL2::Video::Window::UpdateWindowSurface()
{
	int result = SDL_UpdateWindowSurface(window);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Window::UpdateWindowSurfaceRects(...array<NETSDL2::Video::Rect>^ rects)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Rect> pRects = &rects[0];
	int result = SDL_UpdateWindowSurfaceRects(window, (const SDL_Rect*)pRects, rects->Length);
	pRects = nullptr;

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<GLContext^, None^> NETSDL2::Video::Window::CreateGLContext()
{
	SDL_GLContext context = SDL_GL_CreateContext(window);
	if(context == __nullptr)
	{
		return Result<GLContext^, None^>::MakeFailure(None::Value);
	}

	return gcnew GLContext(context);
}

void NETSDL2::Video::Window::GetGLDrawableSize(int% w, int% h)
{
	int width, height;
	SDL_GL_GetDrawableSize(window, &width, &height);
	w = width;
	h = height;
}

Result<Window^, None^> NETSDL2::Video::Window::GetGLCurrentWindow()
{
	SDL_Window* win = SDL_GL_GetCurrentWindow();
	if(win == __nullptr)
	{
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	Window^ window = nullptr;
	nativeWindowConnections->TryGetValue(System::IntPtr(win), window);

	if(window == nullptr)
	{
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	return window;
}

Result<None^, int> NETSDL2::Video::Window::MakeCurrent(GLContext^ context)
{
	int result = SDL_GL_MakeCurrent(window, context->NativeContext);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Window::SwapWindow()
{
	SDL_GL_SwapWindow(window);
}

bool NETSDL2::Video::Window::CreateVulkanSurface(void* instance, void** surface)
{
	return SDL_Vulkan_CreateSurface(window, (VkInstance)instance, (VkSurfaceKHR*)surface) == SDL_TRUE;
}

void NETSDL2::Video::Window::GetVulkanDrawableSize(int% w, int% h)
{
	int width, height;
	SDL_Vulkan_GetDrawableSize(window, &width, &height);
	w = width;
	h = height;
}

Result<array<System::String^>^, None^> NETSDL2::Video::Window::GetVulkanInstanceExtensions()
{
	unsigned int count = 0;
	SDL_bool result = SDL_Vulkan_GetInstanceExtensions(window, &count, __nullptr);
	if(result == SDL_FALSE)
	{
		return Result<array<System::String^>^, None^>::MakeFailure(None::Value);
	}

	std::vector<const char*> extensions(count);
	result = SDL_Vulkan_GetInstanceExtensions(window, &count, extensions.data());
	if(result == SDL_FALSE)
	{
		return Result<array<System::String^>^, None^>::MakeFailure(None::Value);
	}

	array<System::String^>^ ret = gcnew array<System::String^>(count);
	for(unsigned int i = 0; i < count; i++)
	{
		ret[i] = StringMarshal::UTF8NativeToManaged(extensions[i]);
	}

	return ret;
}

SDL_Renderer* NETSDL2::Video::Window::CreateRenderer(int index, Uint32 flags)
{
	return SDL_CreateRenderer(window, index, flags);
}
