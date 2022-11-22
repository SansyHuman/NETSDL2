#include "../../include/video/Surface.h"

#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

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

NETSDL2::Video::Surface::Surface(Surface^ surface)
	: releaseOnDestroy(true)
{
	SDL_Surface* surf = SDL_DuplicateSurface(surface->surface);
	if(surf == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSurface(surf);
}

NETSDL2::Video::Surface::Surface(System::String^ file)
	: releaseOnDestroy(true)
{
	StringMarshal context;
	SDL_Surface* surface = SDL_LoadBMP(context.ManagedToUTF8Native(file));
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

Result<None^, int> NETSDL2::Video::Surface::BlitScaled(Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect, Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect)
{
	int result = SDL_BlitScaled(src->surface, srcrect.HasValue ? (const SDL_Rect*)&srcrect.Value : __nullptr, dst->surface, dstrect.HasValue ? (SDL_Rect*)&dstrect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::BlitSurface(Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect, Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect)
{
	int result = SDL_BlitSurface(src->surface, srcrect.HasValue ? (const SDL_Rect*)&srcrect.Value : __nullptr, dst->surface, dstrect.HasValue ? (SDL_Rect*)&dstrect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::SoftStretchLinear(Surface^ src, System::Nullable<NETSDL2::Video::Rect> srcrect, Surface^ dst, System::Nullable<NETSDL2::Video::Rect> dstrect)
{
	int result = SDL_SoftStretchLinear(src->surface, srcrect.HasValue ? (const SDL_Rect*)&srcrect.Value : __nullptr, dst->surface, dstrect.HasValue ? (SDL_Rect*)&dstrect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<Surface^, None^> NETSDL2::Video::Surface::ConvertSurface(PixelFormat% fmt)
{
	pin_ptr<PixelFormat> pFmt = &fmt;
	SDL_Surface* newSurf = SDL_ConvertSurface(surface, (const SDL_PixelFormat*)pFmt, 0);
	pFmt = nullptr;

	if(newSurf == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(newSurf, true);
}

Result<Surface^, None^> NETSDL2::Video::Surface::ConvertSurfaceFormat(PixelFormatEnum pixelFormat)
{
	SDL_Surface* newSurf = SDL_ConvertSurfaceFormat(surface, (Uint32)pixelFormat, 0);
	if(newSurf == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(newSurf, true);
}

Result<None^, int> NETSDL2::Video::Surface::FillRect(System::Nullable<NETSDL2::Video::Rect> rect, Uint32 color)
{
	int result = SDL_FillRect(surface, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr, color);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::FillRects(array<NETSDL2::Video::Rect>^ rects, Uint32 color)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Rect> pRects = &rects[0];
	int result = SDL_FillRects(surface, (const SDL_Rect*)pRects, rects->Length, color);
	pRects = nullptr;

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<Uint32, int> NETSDL2::Video::Surface::GetColorKey()
{
	Uint32 key;
	int result = SDL_GetColorKey(surface, &key);
	if(result < 0)
	{
		return Result<Uint32, int>::MakeFailure(result);
	}

	return key;
}

Result<Uint8, int> NETSDL2::Video::Surface::GetSurfaceAlphaMod()
{
	Uint8 alpha;
	int result = SDL_GetSurfaceAlphaMod(surface, &alpha);
	if(result < 0)
	{
		return Result<Uint8, int>::MakeFailure(result);
	}

	return alpha;
}

Result<BlendMode, int> NETSDL2::Video::Surface::GetSurfaceBlendMode()
{
	SDL_BlendMode mode;
	int result = SDL_GetSurfaceBlendMode(surface, &mode);
	if(result < 0)
	{
		return Result<BlendMode, int>::MakeFailure(result);
	}

	return (BlendMode)mode;
}

Result<None^, int> NETSDL2::Video::Surface::GetSurfaceColorMod(Uint8% r, Uint8% g, Uint8% b)
{
	Uint8 red, green, blue;
	int result = SDL_GetSurfaceColorMod(surface, &red, &green, &blue);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	r = red;
	g = green;
	b = blue;

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::LockSurface()
{
	int result = SDL_LockSurface(surface);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

bool Surface::MustLock::get()
{
	return SDL_MUSTLOCK(surface) == SDL_TRUE;
}

Result<None^, int> NETSDL2::Video::Surface::SaveBMP(System::String^ file)
{
	StringMarshal context;
	int result = SDL_SaveBMP(surface, context.ManagedToUTF8Native(file));
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

bool NETSDL2::Video::Surface::SetClipRect(System::Nullable<NETSDL2::Video::Rect> rect)
{
	return SDL_SetClipRect(surface, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr) == SDL_TRUE;
}

Result<None^, int> NETSDL2::Video::Surface::SetColorKey(bool flag, Uint32 key)
{
	int result = SDL_SetColorKey(surface, flag ? SDL_TRUE : SDL_FALSE, key);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

bool Surface::HasColorKey::get()
{
	return SDL_HasColorKey(surface) == SDL_TRUE;
}

Result<None^, int> NETSDL2::Video::Surface::SetSurfaceAlphaMod(Uint8 alpha)
{
	int result = SDL_SetSurfaceAlphaMod(surface, alpha);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::SetSurfaceBlendMode(BlendMode blendMode)
{
	int result = SDL_SetSurfaceBlendMode(surface, (SDL_BlendMode)blendMode);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::SetSurfaceColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	int result = SDL_SetSurfaceColorMod(surface, r, g, b);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::SetSurfacePalette(Palette* palette)
{
	int result = SDL_SetSurfacePalette(surface, (SDL_Palette*)palette);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Surface::SetSurfaceRLE(bool flag)
{
	int result = SDL_SetSurfaceRLE(surface, flag ? 1 : 0);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

bool Surface::HasSurfaceRLE::get()
{
	return SDL_HasSurfaceRLE(surface) == SDL_TRUE;
}

void NETSDL2::Video::Surface::UnlockSurface()
{
	SDL_UnlockSurface(surface);
}
