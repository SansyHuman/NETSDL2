#include "../../include/video/GL.h"
#include <msclr/marshal.h>

#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"
#include "../../include/video/Window.h"
#include "../../include/video/GLContext.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace msclr::interop;

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

Result<GLContext^, None^> NETSDL2::Video::GL::CreateContext(Window^ window)
{
	return window->CreateGLContext();
}

bool NETSDL2::Video::GL::ExtensionSupported(System::String^ extension)
{
	StringMarshal context;
	return SDL_GL_ExtensionSupported(context.ManagedToUTF8Native(extension)) == SDL_TRUE;
}

Result<int, int> NETSDL2::Video::GL::GetAttribute(GLAttr attr)
{
	int value;
	int result = SDL_GL_GetAttribute((SDL_GLattr)attr, &value);

	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return value;
}

Result<GLContext^, None^> NETSDL2::Video::GL::GetCurrentContext()
{
	return GLContext::GetCurrentContext();
}

Result<Window^, None^> NETSDL2::Video::GL::GetCurrentWindow()
{
	return Window::GetGLCurrentWindow();
}

void NETSDL2::Video::GL::GetDrawableSize(Window^ window, int% w, int% h)
{
	return window->GetGLDrawableSize(w, h);
}

System::IntPtr NETSDL2::Video::GL::GetProcAddress(System::String^ proc)
{
	StringMarshal context;
	return System::IntPtr(SDL_GL_GetProcAddress(context.ManagedToUTF8Native(proc)));
}

int NETSDL2::Video::GL::GetSwapInterval()
{
	return SDL_GL_GetSwapInterval();
}

#ifdef LoadLibrary
#undef LoadLibrary
#endif

Result<None^, int> NETSDL2::Video::GL::LoadLibrary(System::String^ path)
{
	StringMarshal context;
	int result = 0;
	if(path == nullptr)
		result = SDL_GL_LoadLibrary(__nullptr);
	else
		result = SDL_GL_LoadLibrary(context.ManagedToUTF8Native(path));

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

#ifndef LoadLibrary
#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#else
#define LoadLibrary  LoadLibraryA
#endif
#endif

Result<None^, int> NETSDL2::Video::GL::MakeCurrent(Window^ window, GLContext^ context)
{
	return window->MakeCurrent(context);
}

void NETSDL2::Video::GL::ResetAttributes()
{
	SDL_GL_ResetAttributes();
}

Result<None^, int> NETSDL2::Video::GL::SetAttribute(GLAttr attr, int value)
{
	int result = SDL_GL_SetAttribute((SDL_GLattr)attr, value);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::GL::SetSwapInterval(int interval)
{
	int result = SDL_GL_SetSwapInterval(interval);

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::GL::SwapWindow(Window^ window)
{
	window->SwapWindow();
}

void NETSDL2::Video::GL::UnloadLibrary()
{
	SDL_GL_UnloadLibrary();
}
