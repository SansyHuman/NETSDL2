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
