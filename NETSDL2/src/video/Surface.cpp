#include "../../include/video/Surface.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Surface::Surface(SDL_Surface* surface, bool releaseOnDestroy)
	: surface(surface), releaseOnDestroy(releaseOnDestroy)
{
	
}

SDL_Surface* Surface::NativeSurface::get()
{
	return surface;
}

NETSDL2::Video::Surface::Surface(int width, int height, int depth, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurface(0, width, height, depth, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurfaceFrom(pixels.ToPointer(), width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(void* pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurfaceFrom(pixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
	: releaseOnDestroy(true)
{
	pin_ptr<unsigned char> pPixels = &pixels[0];
	surface = SDL_CreateRGBSurfaceFrom((void*)pPixels, width, height, depth, pitch, rmask, gmask, bmask, amask);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(int width, int height, int depth, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, depth, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(System::IntPtr pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels.ToPointer(), width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(void* pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::Surface(array<unsigned char>^ pixels, int width, int height, int depth, int pitch, PixelFormatEnum format)
	: releaseOnDestroy(true)
{
	pin_ptr<unsigned char> pPixels = &pixels[0];
	surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)pPixels, width, height, depth, pitch, (Uint32)format);
	if(surface == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Surface::~Surface()
{
	this->!Surface();
}

NETSDL2::Video::Surface::!Surface()
{
	if(releaseOnDestroy)
		SDL_FreeSurface(surface);

	surface = __nullptr;
}
