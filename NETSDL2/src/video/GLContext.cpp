#include "../../include/video/GLContext.h"
#include <msclr/marshal.h>

#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"

using namespace msclr::interop;

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::GLContext::GLContext(SDL_GLContext context)
	: context(context)
{
	nativeContextConnections[System::IntPtr(context)] = this;
}

NETSDL2::Video::GLContext::~GLContext()
{
	GLContext^ dummy;
	nativeContextConnections->TryRemove(System::IntPtr(context), dummy);
	this->!GLContext();
}

NETSDL2::Video::GLContext::!GLContext()
{
	SDL_GL_DeleteContext(context);
	context = __nullptr;
}

void NETSDL2::Video::GLContext::DeleteContext(GLContext^ context)
{
	delete context;
}

Result<GLContext^, None^> NETSDL2::Video::GLContext::GetCurrentContext()
{
	SDL_GLContext c = SDL_GL_GetCurrentContext();
	if(c == __nullptr)
	{
		return Result<GLContext^, None^>::MakeFailure(None::Value);
	}

	GLContext^ res = nullptr;
	nativeContextConnections->TryGetValue(System::IntPtr(c), res);
	if(res == nullptr)
	{
		return Result<GLContext^, None^>::MakeFailure(None::Value);
	}

	return res;
}

SDL_GLContext GLContext::NativeContext::get()
{
	return context;
}
