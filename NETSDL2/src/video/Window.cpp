#include "../../include/video/Window.h"
#include <msclr/marshal.h>

#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"
#include "../../include/video/Display.h"
#include "../../include/video/GLContext.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace msclr::interop;

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

void NETSDL2::Video::Window::InitCallbacks()
{
	hitTestCallback = gcnew HitTest(&Window::DefaultHitTest);
	NativeHitTest^ native = gcnew NativeHitTest(&Window::HitTestNative);

	hitTestCallbackHandle = GCHandle::Alloc(native);
	nativeHitTestCallback = reinterpret_cast<SDL_HitTest>(Marshal::GetFunctionPointerForDelegate(native).ToPointer());

	if(SDL_SetWindowHitTest(window, nativeHitTestCallback, __nullptr) < 0)
		throw gcnew System::Exception("Failed to initialize hit test callback.");
}

void NETSDL2::Video::Window::ClearCallbacks()
{
	nativeHitTestCallback = __nullptr;
	hitTestCallbackHandle.Free();
}

NETSDL2::Video::Window::Window(System::String^ title, int x, int y, int w, int h, WindowFlags flags)
{
	StringMarshal context;
	window = SDL_CreateWindow(context.ManagedToUTF8Native(title), x, y, w, h, (Uint32)flags);

	if(window == __nullptr)
		throw gcnew System::Exception(Error::GetError());

	nativeWindowConnections[System::IntPtr(window)] = this;

	InitCallbacks();
}

NETSDL2::Video::Window::Window(void* data)
{
	window = SDL_CreateWindowFrom(data);

	if(window == __nullptr)
		throw gcnew System::Exception(Error::GetError());

	nativeWindowConnections[System::IntPtr(window)] = this;

	InitCallbacks();
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
