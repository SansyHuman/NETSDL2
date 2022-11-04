#include "../../include/video/Pixels.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

PixelFormat* NETSDL2::Video::Pixels::AllocFormat(PixelFormatEnum pixelFormat)
{
	return (PixelFormat*)SDL_AllocFormat((Uint32)pixelFormat);
}

Palette* NETSDL2::Video::Pixels::AllocPalette(int nColors)
{
	return (Palette*)SDL_AllocPalette(nColors);
}

Result<None^, None^> NETSDL2::Video::Pixels::CalculateGammaRamp(float gamma, array<Uint16>^ ramp)
{
	if(ramp->Length < 256)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	pin_ptr<Uint16> pRamp = &ramp[0];
	SDL_CalculateGammaRamp(gamma, (Uint16*)pRamp);
	pRamp = nullptr;

	return None::Value;
}

void NETSDL2::Video::Pixels::FreeFormat(PixelFormat* format)
{
	SDL_FreeFormat((SDL_PixelFormat*)format);
}

void NETSDL2::Video::Pixels::FreePalette(Palette* palette)
{
	SDL_FreePalette((SDL_Palette*)palette);
}

void NETSDL2::Video::Pixels::GetRGB(Uint32 pixel, PixelFormat* format, Uint8% r, Uint8% g, Uint8% b)
{
	Uint8 R, G, B;

	SDL_GetRGB(pixel, (const SDL_PixelFormat*)format, &R, &G, &B);

	r = R;
	g = G;
	b = B;
}

void NETSDL2::Video::Pixels::GetRGBA(Uint32 pixel, PixelFormat* format, Uint8% r, Uint8% g, Uint8% b, Uint8% a)
{
	Uint8 R, G, B, A;

	SDL_GetRGBA(pixel, (const SDL_PixelFormat*)format, &R, &G, &B, &A);

	r = R;
	g = G;
	b = B;
	a = A;
}

Uint32 NETSDL2::Video::Pixels::MapRGB(PixelFormat* format, Uint8 r, Uint8 g, Uint8 b)
{
	return SDL_MapRGB((const SDL_PixelFormat*)format, r, g, b);
}

Uint32 NETSDL2::Video::Pixels::MapRGBA(PixelFormat* format, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	return SDL_MapRGBA((const SDL_PixelFormat*)format, r, g, b, a);
}

PixelFormatEnum NETSDL2::Video::Pixels::MasksToPixelFormatEnum(int bpp, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask)
{
	return (PixelFormatEnum)SDL_MasksToPixelFormatEnum(bpp, rmask, gmask, bmask, amask);
}

bool NETSDL2::Video::Pixels::PixelFormatEnumToMasks(PixelFormatEnum format, int% bpp, Uint32% rmask, Uint32% gmask, Uint32% bmask, Uint32% amask)
{
	int BPP;
	Uint32 Rmask, Gmask, Bmask, Amask;

	SDL_bool result = SDL_PixelFormatEnumToMasks((Uint32)format, &BPP, &Rmask, &Gmask, &Bmask, &Amask);
	if(result == SDL_FALSE)
		return false;

	bpp = BPP;
	rmask = Rmask;
	gmask = Gmask;
	bmask = Bmask;
	amask = Amask;
	return true;
}

Result<None^, int> NETSDL2::Video::Pixels::SetPaletteColors(Palette* palette, int firstColor, ...array<NETSDL2::Video::Color>^ colors)
{
	pin_ptr<NETSDL2::Video::Color> pColors = &colors[0];

	int result = SDL_SetPaletteColors((SDL_Palette*)palette, (const SDL_Color*)pColors, firstColor, colors->Length);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	pColors = nullptr;

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Pixels::SetPixelFormatPalette(PixelFormat* format, Palette* palette)
{
	SDL_PixelFormat* pFormat = (SDL_PixelFormat*)format;
	SDL_Palette* pPalette = (SDL_Palette*)palette;

	int result = SDL_SetPixelFormatPalette(pFormat, pPalette);

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

NETSDL2::Video::PixelFormatWrapper::PixelFormatWrapper(PixelFormat* format)
	: format(format)
{
	
}

NETSDL2::Video::PixelFormatWrapper::~PixelFormatWrapper()
{
	this->!PixelFormatWrapper();
}

NETSDL2::Video::PixelFormatWrapper::!PixelFormatWrapper()
{
	Pixels::FreeFormat(format);
}

NETSDL2::Video::PixelFormatWrapper::operator PixelFormat* (PixelFormatWrapper^ wrapper)
{
	return wrapper->format;
}

PixelFormat* PixelFormatWrapper::Format::get()
{
	return format;
}

NETSDL2::Video::PaletteWrapper::PaletteWrapper(NETSDL2::Video::Palette* palette)
	: palette(palette)
{
	
}

NETSDL2::Video::PaletteWrapper::~PaletteWrapper()
{
	this->!PaletteWrapper();
}

NETSDL2::Video::PaletteWrapper::!PaletteWrapper()
{
	Pixels::FreePalette(palette);
}

NETSDL2::Video::PaletteWrapper::operator NETSDL2::Video::Palette* (PaletteWrapper^ wrapper)
{
	return wrapper->palette;
}

NETSDL2::Video::Palette* PaletteWrapper::Palette::get()
{
	return palette;
}