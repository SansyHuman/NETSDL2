#include "../../include/video/Texture.h"

#include "../../include/core/Error.h"
#include "../../include/video/Renderer.h"
#include "../../include/video/Surface.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Texture::Texture(SDL_Texture* texture, bool releaseOnDestroy)
	: releaseOnDestroy(releaseOnDestroy)
{
	InitTexture(texture);
}

Texture^ NETSDL2::Video::Texture::GetTextureFromNative(SDL_Texture* texture)
{
	Texture^ tex = nullptr;
	bool found = nativeTextureConnections->TryGetValue(System::IntPtr(texture), tex);
	if(found)
		return tex;
	else
		return nullptr;
}

SDL_Texture* Texture::NativeTexture::get()
{
	return texture;
}

void NETSDL2::Video::Texture::InitTexture(SDL_Texture* texture)
{
	this->texture = texture;
	nativeTextureConnections[System::IntPtr(texture)] = this;
}

NETSDL2::Video::Texture::Texture(Renderer^ renderer, PixelFormatEnum format, TextureAccess access, int w, int h)
	: releaseOnDestroy(true)
{
	SDL_Texture* texture = renderer->CreateTexture(format, access, w, h);
	if(texture == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitTexture(texture);
}

NETSDL2::Video::Texture::Texture(Renderer^ renderer, Surface^ surface)
	: releaseOnDestroy(true)
{
	SDL_Texture* texture = renderer->CreateTextureFromSurface(surface);
	if(texture == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitTexture(texture);
}

NETSDL2::Video::Texture::~Texture()
{
	Texture^ dummy = nullptr;
	nativeTextureConnections->TryRemove(System::IntPtr(texture), dummy);
	this->!Texture();
}

NETSDL2::Video::Texture::!Texture()
{
	if(releaseOnDestroy)
		SDL_DestroyTexture(texture);
	texture = __nullptr;
}

Result<Uint8, int> NETSDL2::Video::Texture::GetTextureAlphaMod()
{
	Uint8 alpha;
	int result = SDL_GetTextureAlphaMod(texture, &alpha);
	if(result < 0)
	{
		return Result<Uint8, int>::MakeFailure(result);
	}

	return alpha;
}

Result<BlendMode, int> NETSDL2::Video::Texture::GetTextureBlendMode()
{
	BlendMode mode;
	int result = SDL_GetTextureBlendMode(texture, (SDL_BlendMode*)&mode);
	if(result < 0)
	{
		return Result<BlendMode, int>::MakeFailure(result);
	}

	return mode;
}

Result<None^, int> NETSDL2::Video::Texture::GetTextureColorMod(Uint8% r, Uint8% g, Uint8% b)
{
	Uint8 red, green, blue;
	int result = SDL_GetTextureColorMod(texture, &red, &green, &blue);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	r = red;
	g = green;
	b = blue;
	return None::Value;
}

Result<ScaleMode, int> NETSDL2::Video::Texture::GetTextureScaleMode()
{
	SDL_ScaleMode mode;
	int result = SDL_GetTextureScaleMode(texture, &mode);
	if(result < 0)
	{
		return Result<ScaleMode, int>::MakeFailure(result);
	}

	return (ScaleMode)mode;
}

Result<System::IntPtr, None^> NETSDL2::Video::Texture::GetTextureUserData()
{
	void* result = SDL_GetTextureUserData(texture);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<None^, int> NETSDL2::Video::Texture::LockTexture(System::Nullable<Rect> rect, System::IntPtr% pixels, int% pitch)
{
	void* px;
	int pt;

	int result = SDL_LockTexture(texture, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr, &px, &pt);
	if(result < 0)
	{
		Result<None^, int>::MakeFailure(result);
	}

	pixels = System::IntPtr(px);
	pitch = pt;
	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::LockTextureToSurface(System::Nullable<Rect> rect, Surface^% surface)
{
	SDL_Surface* surf;
	int result = SDL_LockTextureToSurface(texture, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr, &surf);
	if(result < 0)
	{
		Result<None^, int>::MakeFailure(result);
	}

	surface = gcnew Surface(surf, false);
	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::QueryTexture(PixelFormatEnum% format, TextureAccess% access, int% w, int% h)
{
	Uint32 f;
	int a, width, height;

	int result = SDL_QueryTexture(texture, &f, &a, &width, &height);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	format = (PixelFormatEnum)f;
	access = (TextureAccess)a;
	w = width;
	h = height;
	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::SetTextureAlphaMod(Uint8 alpha)
{
	int result = SDL_SetTextureAlphaMod(texture, alpha);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::SetTextureBlendMode(BlendMode blendMode)
{
	int result = SDL_SetTextureBlendMode(texture, (SDL_BlendMode)blendMode);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::SetTextureColorMod(Uint8 r, Uint8 g, Uint8 b)
{
	int result = SDL_SetTextureColorMod(texture, r, g, b);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::SetTextureScaleMode(ScaleMode scaleMode)
{
	int result = SDL_SetTextureScaleMode(texture, (SDL_ScaleMode)scaleMode);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::SetTextureUserData(System::IntPtr userdata)
{
	int result = SDL_SetTextureUserData(texture, userdata.ToPointer());
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Video::Texture::UnlockTexture()
{
	SDL_UnlockTexture(texture);
}

Result<None^, int> NETSDL2::Video::Texture::UpdateTexture(System::Nullable<NETSDL2::Video::Rect> rect, System::IntPtr pixels, int pitch)
{
	int result = SDL_UpdateTexture(texture,
		rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr, pixels.ToPointer(), pitch);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::UpdateYUVTexture(System::Nullable<NETSDL2::Video::Rect> rect, Uint8* yplane, int ypitch, Uint8* uplane, int upitch, Uint8* vplane, int vpitch)
{
	int result = SDL_UpdateYUVTexture(texture,
		rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr,
		yplane, ypitch, uplane, upitch, vplane, vpitch);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Texture::UpdateNVTexture(System::Nullable<NETSDL2::Video::Rect> rect, Uint8* yplane, int ypitch, Uint8* uvplane, int uvpitch)
{
	int result = SDL_UpdateNVTexture(texture,
		rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr,
		yplane, ypitch, uvplane, uvpitch);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}