#pragma once

#include <SDL_ttf.h>

#include "TTFHinting.h"
#include "TTFStyle.h"
#include "TTFWrapped.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Text
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// TTF font information
		/// </summary>
		public ref class Font
		{
		private:
			TTF_Font* font;

		public:
			/// <summary>
			/// Create a font from a file, using a specified point size.
			/// </summary>
			/// <param name="file">Path to font file.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(System::String^ file, int ptsize);

			~Font();
			!Font();

			/// <summary>
			/// Query the offset from the baseline to the top of a font.
			/// </summary>
			property int FontAscent
			{
				int get();
			}

			/// <summary>
			/// Query the offset from the baseline to the bottom of a font.
			/// </summary>
			property int FontDescent
			{
				int get();
			}

			/// <summary>
			/// Query a font's family name.
			/// </summary>
			property System::String^ FamilyName
			{
				System::String^ get();
			}

			/// <summary>
			/// Query whether a font is fixed-width.
			/// </summary>
			property bool IsFixedWidth
			{
				bool get();
			}

			/// <summary>
			/// Query the number of faces of a font.
			/// </summary>
			property long FontFaces
			{
				long get();
			}

			/// <summary>
			/// Query a font's style name.
			/// </summary>
			property System::String^ StyleName
			{
				System::String^ get();
			}

			/// <summary>
			/// Query the total height of a font.
			/// </summary>
			property int Height
			{
				int get();
			}

			/// <summary>
			/// Query the recommended spacing between lines of text for a font.
			/// </summary>
			property int LineSkip
			{
				int get();
			}

			/// <summary>
			/// Query a font's current FreeType hinter setting.
			/// </summary>
			property TTFHinting Hinting
			{
				TTFHinting get();
			}

			/// <summary>
			/// Query whether or not kerning is allowed for a font.
			/// </summary>
			property bool Kerning
			{
				bool get();
			}

			/// <summary>
			/// Query a font's current outline.
			/// </summary>
			property int Outline
			{
				int get();
			}

			/// <summary>
			/// Query a font's current style.
			/// </summary>
			property TTFStyle Style
			{
				TTFStyle get();
			}

			/// <summary>
			/// Query a font's current wrap alignment option.
			/// </summary>
			property TTFWrapped WrappedAlign
			{
				TTFWrapped get();
			}

			/// <summary>
			/// Check whether a glyph is provided by the font for a 16-bit codepoint.
			/// </summary>
			/// <param name="ch">The character code to check.</param>
			/// <returns>true if font provides a glyph for this character, false if
			/// not.</returns>
			bool GlyphIsProvided(Uint16 ch);

			/// <summary>
			/// Check whether a glyph is provided by the font for a 32-bit codepoint.
			/// </summary>
			/// <param name="ch">The character code to check.</param>
			/// <returns>true if font provides a glyph for this character, false if
			/// not.</returns>
			bool GlyphIsProvided32(Uint32 ch);

			/// <summary>
			/// Query the metrics (dimensions) of a font's 16-bit glyph.
			/// </summary>
			/// <param name="ch">The character code to check.</param>
			/// <param name="minx"></param>
			/// <param name="maxx"></param>
			/// <param name="miny"></param>
			/// <param name="maxy"></param>
			/// <param name="advance"></param>
			void GlyphMetrics(Uint16 ch, [Out]int% minx, [Out]int% maxx, [Out]int% miny, [Out]int% maxy, [Out]int% advance);

			/// <summary>
			/// Query the metrics (dimensions) of a font's 32-bit glyph.
			/// </summary>
			/// <param name="ch">The character code to check.</param>
			/// <param name="minx"></param>
			/// <param name="maxx"></param>
			/// <param name="miny"></param>
			/// <param name="maxy"></param>
			/// <param name="advance"></param>
			void GlyphMetrics32(Uint32 ch, [Out]int% minx, [Out]int% maxx, [Out]int% miny, [Out]int% maxy, [Out]int% advance);

			/// <summary>
			/// Calculate how much of a string will fit in a given width.
			/// </summary>
			/// <param name="text">Text to calculate.</param>
			/// <param name="measureWidth">Maximum width, in pixels, available for
			/// the string.</param>
			/// <param name="extent">On return, filled with latest calculated width.
			/// </param>
			/// <param name="count">On return, filled with number of characters that
			/// can be rendered.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> Measure(System::String^ text, int measureWidth, [Out]int% extent, [Out]int% count);
		};
	}
}