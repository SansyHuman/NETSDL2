#include "../../include/video/Renderer.h"

#include "../../include/video/Window.h"
#include "../../include/video/Surface.h"
#include "../../include/video/Texture.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Renderer::Renderer(SDL_Renderer* renderer, bool releaseOnDestroy)
	: releaseOnDestroy(releaseOnDestroy)
{
	InitRenderer(renderer);
}

Renderer^ NETSDL2::Video::Renderer::GetRendererFromNative(SDL_Renderer* renderer)
{
	Renderer^ rend = nullptr;
	bool found = nativeRendererConnections->TryGetValue(System::IntPtr(renderer), rend);
	if(found)
		return rend;
	else
		return nullptr;
}

void NETSDL2::Video::Renderer::InitRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	nativeRendererConnections[System::IntPtr(renderer)] = this;
}

NETSDL2::Video::Renderer::Renderer(Window^ window, int index, RendererFlags flags)
	: releaseOnDestroy(true)
{
	SDL_Renderer* renderer = window->CreateRenderer(index, (Uint32)flags);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitRenderer(renderer);
}

NETSDL2::Video::Renderer::Renderer(Surface^ surface)
	: releaseOnDestroy(true)
{
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface->NativeSurface);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitRenderer(renderer);
}

NETSDL2::Video::Renderer::~Renderer()
{
	Renderer^ dummy = nullptr;
	nativeRendererConnections->TryRemove(System::IntPtr(renderer), dummy);
	this->!Renderer();
}

NETSDL2::Video::Renderer::!Renderer()
{
	if(releaseOnDestroy)
		SDL_DestroyRenderer(renderer);
	renderer = __nullptr;
}

Result<BlendMode, int> NETSDL2::Video::Renderer::GetRenderDrawBlendMode()
{
	SDL_BlendMode mode;
	int result = SDL_GetRenderDrawBlendMode(renderer, &mode);
	if(result < 0)
	{
		return Result<BlendMode, int>::MakeFailure(result);
	}

	return (BlendMode)mode;
}

Result<None^, int> NETSDL2::Video::Renderer::GetRenderDrawColor(Uint8% r, Uint8% g, Uint8% b, Uint8% a)
{
	Uint8 red, green, blue, alpha;

	int result = SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	r = red;
	g = green;
	b = blue;
	a = alpha;

	return None::Value;
}

Result<RendererInfo, int> NETSDL2::Video::Renderer::GetRendererInfo()
{
	RendererInfo info;

	int result = SDL_GetRendererInfo(renderer, (SDL_RendererInfo*)&info);
	if(result < 0)
	{
		return Result<RendererInfo, int>::MakeFailure(result);
	}

	return info;
}

Result<None^, int> NETSDL2::Video::Renderer::GetRendererOutputSize(int% w, int% h)
{
	int width, height;

	int result = SDL_GetRendererOutputSize(renderer, &width, &height);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	w = width;
	h = height;
	return None::Value;
}

Texture^ NETSDL2::Video::Renderer::GetRenderTarget()
{
	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	if(target == __nullptr)
		return nullptr;

	Texture^ managedTarget = Texture::GetTextureFromNative(target);
	if(managedTarget == nullptr)
	{
		managedTarget = gcnew Texture(target, false);
	}

	return managedTarget;
}

Result<None^, int> NETSDL2::Video::Renderer::SetRenderTarget(Texture^ texture)
{
	int result = SDL_SetRenderTarget(renderer, texture->NativeTexture);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

SDL_Texture* NETSDL2::Video::Renderer::CreateTexture(PixelFormatEnum format, TextureAccess access, int w, int h)
{
	return SDL_CreateTexture(renderer, (Uint32)format, (int)access, w, h);
}

SDL_Texture* NETSDL2::Video::Renderer::CreateTextureFromSurface(Surface^ surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface->NativeSurface);
}
