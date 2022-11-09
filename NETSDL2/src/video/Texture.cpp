#include "../../include/video/Texture.h"

#include "../../include/core/Error.h"
#include "../../include/video/Renderer.h"
#include "../../include/video/Surface.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Texture::Texture(SDL_Texture* texture)
	: texture(texture)
{
	
}

NETSDL2::Video::Texture::Texture(Renderer^ renderer, PixelFormatEnum format, TextureAccess access, int w, int h)
{
	texture = renderer->CreateTexture(format, access, w, h);
	if(texture == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Texture::Texture(Renderer^ renderer, Surface^ surface)
{
	texture = renderer->CreateTextureFromSurface(surface);
	if(texture == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Video::Texture::~Texture()
{
	this->!Texture();
}

NETSDL2::Video::Texture::!Texture()
{
	SDL_DestroyTexture(texture);
	texture = __nullptr;
}
