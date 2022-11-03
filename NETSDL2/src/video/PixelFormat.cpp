#include "../../include/video/PixelFormat.h"

using namespace NETSDL2::Video;

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
