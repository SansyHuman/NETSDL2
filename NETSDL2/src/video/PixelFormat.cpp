#include "../../include/video/PixelFormat.h"

using namespace NETSDL2::Video;

PixelFormatEnum PixelFormat::Format::get()
{
    return format;
}

NETSDL2::Video::Palette* PixelFormat::Palette::get()
{
    return palette;
}

Uint8 PixelFormat::BitsPerPixel::get()
{
    return bitsPerPixel;
}

Uint8 PixelFormat::BytesPerPixel::get()
{
    return bytesPerPixel;
}

Uint32 PixelFormat::Rmask::get()
{
    return rmask;
}

Uint32 PixelFormat::Gmask::get()
{
    return gmask;
}

Uint32 PixelFormat::Bmask::get()
{
    return bmask;
}

Uint32 PixelFormat::Amask::get()
{
    return amask;
}

Uint8 PixelFormat::Rloss::get()
{
    return rloss;
}

Uint8 PixelFormat::Gloss::get()
{
    return gloss;
}

Uint8 PixelFormat::Bloss::get()
{
    return bloss;
}

Uint8 PixelFormat::Aloss::get()
{
    return aloss;
}

Uint8 PixelFormat::Rshift::get()
{
    return rshift;
}

Uint8 PixelFormat::Gshift::get()
{
    return gshift;
}

Uint8 PixelFormat::Bshift::get()
{
    return bshift;
}

Uint8 PixelFormat::Ashift::get()
{
    return ashift;
}

PixelType NETSDL2::Video::PixelFormatInfo::GetPixelType(PixelFormatEnum format)
{
    return (PixelType)SDL_PIXELTYPE((SDL_PixelFormatEnum)format);
}

BitmapOrder NETSDL2::Video::PixelFormatInfo::GetBitmapOrder(PixelFormatEnum format)
{
    return (BitmapOrder)SDL_PIXELORDER((SDL_PixelFormatEnum)format);
}

PackedOrder NETSDL2::Video::PixelFormatInfo::GetPackedOrder(PixelFormatEnum format)
{
    return (PackedOrder)SDL_PIXELORDER((SDL_PixelFormatEnum)format);
}

ArrayOrder NETSDL2::Video::PixelFormatInfo::GetArrayOrder(PixelFormatEnum format)
{
    return (ArrayOrder)SDL_PIXELORDER((SDL_PixelFormatEnum)format);
}

PackedLayout NETSDL2::Video::PixelFormatInfo::GetPackedLayout(PixelFormatEnum format)
{
    return (PackedLayout)SDL_PIXELLAYOUT((SDL_PixelFormatEnum)format);
}

Uint32 NETSDL2::Video::PixelFormatInfo::GetBitsPerPixel(PixelFormatEnum format)
{
    return (Uint32)SDL_BITSPERPIXEL((SDL_PixelFormatEnum)format);
}

Uint32 NETSDL2::Video::PixelFormatInfo::GetBytesPerPixel(PixelFormatEnum format)
{
    return (Uint32)SDL_BYTESPERPIXEL((SDL_PixelFormatEnum)format);
}

bool NETSDL2::Video::PixelFormatInfo::IsPixelFormatIndexed(PixelFormatEnum format)
{
    return SDL_ISPIXELFORMAT_INDEXED((SDL_PixelFormatEnum)format);
}

bool NETSDL2::Video::PixelFormatInfo::IsPixelFormatAlpha(PixelFormatEnum format)
{
    return SDL_ISPIXELFORMAT_ALPHA((SDL_PixelFormatEnum)format);
}

bool NETSDL2::Video::PixelFormatInfo::IsPixelFormatFourCC(PixelFormatEnum format)
{
    return SDL_ISPIXELFORMAT_FOURCC((SDL_PixelFormatEnum)format);
}
