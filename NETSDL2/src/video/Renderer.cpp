#include "../../include/video/Renderer.h"

#include "../../include/video/Window.h"
#include "../../include/video/Surface.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Renderer::Renderer(SDL_Renderer* renderer)
	: renderer(renderer)
{
	
}

NETSDL2::Video::Renderer::Renderer(Window^ window, int index, RendererFlags flags)
{
	renderer = window->CreateRenderer(index, (Uint32)flags);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Renderer::Renderer(Surface^ surface)
{
	renderer = SDL_CreateSoftwareRenderer(surface->NativeSurface);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Renderer::~Renderer()
{
	this->!Renderer();
}

NETSDL2::Video::Renderer::!Renderer()
{
	SDL_DestroyRenderer(renderer);
	renderer = __nullptr;
}
