#include "../../include/video/Surface.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Surface::Surface(SDL_Surface* surface, bool releaseOnDestroy)
	: releaseOnDestroy(releaseOnDestroy)
{
	InitSurface(surface);
}

Surface^ NETSDL2::Video::Surface::GetSurfaceFromNative(SDL_Surface* surface)
{
	Surface^ surf = nullptr;
	bool found = nativeSurfaceConnections->TryGetValue(System::IntPtr(surface), surf);
	if(found)
		return surf;
	else
		return nullptr;
}

void NETSDL2::Video::Surface::InitSurface(SDL_Surface* surface)
{
	this->surface = surface;
	nativeSurfaceConnections[System::IntPtr(surface)] = this;
}

SDL_Surface* Surface::NativeSurface::get()
{
	return surface;
}

NETSDL2::Video::Surface::Surface(int width, int height, int depth, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurface(0, width, height, depth, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels.ToPointer(), width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	pin_ptr<unsigned char> pPixels = &pixels[0];
	SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)pPixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(int width, int height, int depth, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.ToPointer(), width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(void* pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	pin_ptr<unsigned char> pPixels = &pixels[0];
	SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)pPixels, width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surface);
}

NETSDL2::Video::Surface::~Surface()
{
	Surface^ dummy = nullptr;
	nativeSurfaceConnections->TryRemove(System::IntPtr(surface), dummy);
	this->!Surface();
}

NETSDL2::Video::Surface::!Surface()
{
	if(releaseOnDestroy)
		SDL_FreeSurface(surface);

	surface = __nullptr;
}

PixelFormat% Surface::Format::get()
{
	return *((PixelFormat*)surface->format);
}

int Surface::Width::get()
{
	return surface->w;
}

int Surface::Height::get()
{
	return surface->h;
}

int Surface::Pitch::get()
{
	return surface->pitch;
}

System::IntPtr Surface::Pixels::get()
{
	return System::IntPtr(surface->pixels);
}

System::IntPtr Surface::Userdata::get()
{
	return System::IntPtr(surface->userdata);
}

void Surface::Userdata::set(System::IntPtr value)
{
	surface->userdata = value.ToPointer();
}

Rect Surface::ClipRect::get()
{
	return *((Rect*)&surface->clip_rect);
}
