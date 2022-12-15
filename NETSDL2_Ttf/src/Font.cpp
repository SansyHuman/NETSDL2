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

bool Font::Kerning::get()
{
	return TTF_GetFontKerning(font) != 0;
}

int Font::Outline::get()
{
	return TTF_GetFontOutline(font);
}

TTFStyle Font::Style::get()
{
	return (TTFStyle)TTF_GetFontStyle(font);
}

TTFWrapped Font::WrappedAlign::get()
{
	return (TTFWrapped)TTF_GetFontWrappedAlign(font);
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
