#include "../include/Font.h"

using namespace NETSDL2::Text;
using namespace NETSDL2::Internal;

NETSDL2::Text::Font::Font(System::String^ file, int ptsize)
{
	StringMarshal context;

	font = TTF_OpenFont(context.ManagedToUTF8Native(file), ptsize);
	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(System::String^ file, int ptsize, unsigned int hdpi, unsigned int vdpi)
{
	StringMarshal context;

	font = TTF_OpenFontDPI(context.ManagedToUTF8Native(file), ptsize, hdpi, vdpi);
	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(RWops^ src, bool freesrc, int ptsize, unsigned int hdpi, unsigned int vdpi)
{
	font = TTF_OpenFontDPIRW(src->NativeOps, freesrc ? 1 : 0, ptsize, hdpi, vdpi);
	if(freesrc)
	{
		delete src;
	}

	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(RWops^ src, bool freesrc, int ptsize, long index, unsigned int hdpi, unsigned int vdpi)
{
	font = TTF_OpenFontIndexDPIRW(src->NativeOps, freesrc ? 1 : 0, ptsize, index, hdpi, vdpi);
	if(freesrc)
	{
		delete src;
	}

	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(RWops^ src, bool freesrc, int ptsize, long index)
{
	font = TTF_OpenFontIndexRW(src->NativeOps, freesrc ? 1 : 0, ptsize, index);
	if(freesrc)
	{
		delete src;
	}

	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(System::String^ file, int ptsize, long index)
{
	StringMarshal context;

	font = TTF_OpenFontIndex(context.ManagedToUTF8Native(file), ptsize, index);
	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(System::String^ file, int ptsize, long index, unsigned int hdpi, unsigned int vdpi)
{
	StringMarshal context;

	font = TTF_OpenFontIndexDPI(context.ManagedToUTF8Native(file), ptsize, index, hdpi, vdpi);
	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::Font(RWops^ src, bool freesrc, int ptsize)
{
	font = TTF_OpenFontRW(src->NativeOps, freesrc ? 1 : 0, ptsize);
	if(freesrc)
	{
		delete src;
	}

	if(font == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Text::Font::~Font()
{
	this->!Font();
}

NETSDL2::Text::Font::!Font()
{
	TTF_CloseFont(font);
	font = __nullptr;
}

int Font::FontAscent::get()
{
	return TTF_FontAscent(font);
}

int Font::FontDescent::get()
{
	return TTF_FontDescent(font);
}

System::String^ Font::FamilyName::get()
{
	return StringMarshal::UTF8NativeToManaged(TTF_FontFaceFamilyName(font));
}

bool Font::IsFixedWidth::get()
{
	return TTF_FontFaceIsFixedWidth(font) != 0;
}

long Font::FontFaces::get()
{
	return TTF_FontFaces(font);
}

System::String^ Font::StyleName::get()
{
	return StringMarshal::UTF8NativeToManaged(TTF_FontFaceStyleName(font));
}

int Font::Height::get()
{
	return TTF_FontHeight(font);
}

int Font::LineSkip::get()
{
	return TTF_FontLineSkip(font);
}

TTFHinting Font::Hinting::get()
{
	return (TTFHinting)TTF_GetFontHinting(font);
}

void Font::Hinting::set(TTFHinting value)
{
	TTF_SetFontHinting(font, (int)value);
}

bool Font::Kerning::get()
{
	return TTF_GetFontKerning(font) != 0;
}

void Font::Kerning::set(bool value)
{
	TTF_SetFontKerning(font, value ? 1 : 0);
}

int Font::Outline::get()
{
	return TTF_GetFontOutline(font);
}

void Font::Outline::set(int value)
{
	TTF_SetFontOutline(font, value);
}

TTFStyle Font::Style::get()
{
	return (TTFStyle)TTF_GetFontStyle(font);
}

void Font::Style::set(TTFStyle value)
{
	TTF_SetFontStyle(font, (int)value);
}

TTFWrapped Font::WrappedAlign::get()
{
	return (TTFWrapped)TTF_GetFontWrappedAlign(font);
}

void Font::WrappedAlign::set(TTFWrapped value)
{
	TTF_SetFontWrappedAlign(font, (int)value);
}

Result<int, None^> NETSDL2::Text::Font::GetFontKerningSizeGlyphs(Uint16 previousCh, Uint16 ch)
{
	int result = TTF_GetFontKerningSizeGlyphs(font, previousCh, ch);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Text::Font::GetFontKerningSizeGlyphs32(Uint32 previousCh, Uint32 ch)
{
	int result = TTF_GetFontKerningSizeGlyphs32(font, previousCh, ch);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

bool NETSDL2::Text::Font::GlyphIsProvided(Uint16 ch)
{
	return TTF_GlyphIsProvided(font, ch) != 0;
}

bool NETSDL2::Text::Font::GlyphIsProvided32(Uint32 ch)
{
	return TTF_GlyphIsProvided32(font, ch) != 0;
}

void NETSDL2::Text::Font::GlyphMetrics(Uint16 ch, int% minx, int% maxx, int% miny, int% maxy, int% advance)
{
	int minX = 0, maxX = 0, minY = 0, maxY = 0, adv = 0;
	int result = TTF_GlyphMetrics(font, ch, &minX, &maxX, &minY, &maxY, &adv);

	minx = minX;
	maxx = maxX;
	miny = minY;
	maxy = maxY;
	advance = adv;
}

void NETSDL2::Text::Font::GlyphMetrics32(Uint32 ch, int% minx, int% maxx, int% miny, int% maxy, int% advance)
{
	int minX = 0, maxX = 0, minY = 0, maxY = 0, adv = 0;
	int result = TTF_GlyphMetrics32(font, ch, &minX, &maxX, &minY, &maxY, &adv);

	minx = minX;
	maxx = maxX;
	miny = minY;
	maxy = maxY;
	advance = adv;
}

Result<None^, None^> NETSDL2::Text::Font::Measure(System::String^ text, int measureWidth, int% extent, int% count)
{
	int ex = 0, cnt = 0;
	StringMarshal context;
	int result = TTF_MeasureUTF8(font, context.ManagedToUTF8Native(text), measureWidth, &ex, &cnt);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	extent = ex;
	count = cnt;
	return None::Value;
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyph32Blended(Uint32 ch, NETSDL2::Video::Color fg)
{
	SDL_Surface* surface = TTF_RenderGlyph32_Blended(font, ch, *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyph32LCD(Uint32 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	SDL_Surface* surface = TTF_RenderGlyph32_LCD(font, ch, *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyph32Shaded(Uint32 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	SDL_Surface* surface = TTF_RenderGlyph32_Shaded(font, ch, *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyph32Solid(Uint32 ch, NETSDL2::Video::Color fg)
{
	SDL_Surface* surface = TTF_RenderGlyph32_Solid(font, ch, *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyphBlended(Uint16 ch, NETSDL2::Video::Color fg)
{
	SDL_Surface* surface = TTF_RenderGlyph_Blended(font, ch, *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyphLCD(Uint16 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	SDL_Surface* surface = TTF_RenderGlyph_LCD(font, ch, *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyphShaded(Uint16 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	SDL_Surface* surface = TTF_RenderGlyph_Shaded(font, ch, *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderGlyphSolid(Uint16 ch, NETSDL2::Video::Color fg)
{
	SDL_Surface* surface = TTF_RenderGlyph_Solid(font, ch, *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextBlended(System::String^ text, NETSDL2::Video::Color fg)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Blended(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextBlendedWrapped(System::String^ text, NETSDL2::Video::Color fg, Uint32 wrapLength)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Blended_Wrapped(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), wrapLength);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextLCD(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_LCD(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextLCDWrapped(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg, Uint32 wrapLength)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_LCD_Wrapped(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), *((SDL_Color*)&bg), wrapLength);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextShaded(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Shaded(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), *((SDL_Color*)&bg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextShadedWrapped(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg, Uint32 wrapLength)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Shaded_Wrapped(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), *((SDL_Color*)&bg), wrapLength);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextSolid(System::String^ text, NETSDL2::Video::Color fg)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Solid(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Text::Font::RenderTextSolidWrapped(System::String^ text, NETSDL2::Video::Color fg, Uint32 wrapLength)
{
	StringMarshal context;

	SDL_Surface* surface = TTF_RenderUTF8_Solid_Wrapped(font, context.ManagedToUTF8Native(text), *((SDL_Color*)&fg), wrapLength);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<None^, None^> NETSDL2::Text::Font::SetFontDirection(TTFDirection direction)
{
	int result = TTF_SetFontDirection(font, (TTF_Direction)direction);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Text::Font::SetFontScriptName(System::String^ script)
{
	StringMarshal context;
	int result = TTF_SetFontScriptName(font, context.ManagedToUTF8Native(script));
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool NETSDL2::Text::Font::GetFontSDF()
{
	return TTF_GetFontSDF(font) == SDL_TRUE;
}

Result<None^, None^> NETSDL2::Text::Font::SetFontSDF(bool onOff)
{
	int result = TTF_SetFontSDF(font, onOff ? SDL_TRUE : SDL_FALSE);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Text::Font::SetFontSize(int ptsize)
{
	int result = TTF_SetFontSize(font, ptsize);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Text::Font::SetFontSizeDPI(int ptsize, unsigned int hdpi, unsigned int vdpi)
{
	int result = TTF_SetFontSizeDPI(font, ptsize, hdpi, vdpi);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Text::Font::Size(System::String^ text, int% w, int% h)
{
	StringMarshal context;

	int width = 0, height = 0;
	int result = TTF_SizeUTF8(font, context.ManagedToUTF8Native(text), &width, &height);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	w = width;
	h = height;
	return None::Value;
}
