#pragma once

#include <SDL_ttf.h>

#include "TTFHinting.h"
#include "TTFStyle.h"
#include "TTFWrapped.h"
#include "TTFDirection.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Text
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::IO;
		using namespace NETSDL2::Video;

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

			/// <summary>
			/// Create a font from a file, using target resolutions (in DPI).
			/// </summary>
			/// <param name="file">Path to font file.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="hdpi">The target horizontal DPI.</param>
			/// <param name="vdpi">The target vertical DPI.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(System::String^ file, int ptsize, unsigned int hdpi, unsigned int vdpi);

			/// <summary>
			/// Opens a font from an RWops with target resolutions (in DPI).
			/// </summary>
			/// <param name="src">A RWops to provide a font file's data.</param>
			/// <param name="freesrc">true to close the RWops before returning, false to
			/// leave it open.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="hdpi">The target horizontal DPI.</param>
			/// <param name="vdpi">The target vertical DPI.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(RWops^ src, bool freesrc, int ptsize, unsigned int hdpi, unsigned int vdpi);

			/// <summary>
			/// Opens a font from an RWops with target resolutions (in DPI).
			/// </summary>
			/// <param name="src">A RWops to provide a font file's data.</param>
			/// <param name="freesrc">true to close the RWops before returning, false to
			/// leave it open.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="index">Index of the face in the font file.</param>
			/// <param name="hdpi">The target horizontal DPI.</param>
			/// <param name="vdpi">The target vertical DPI.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(RWops^ src, bool freesrc, int ptsize, long index, unsigned int hdpi, unsigned int vdpi);

			/// <summary>
			/// Create a font from an RWops, using a specified face index.
			/// </summary>
			/// <param name="src">A RWops to provide a font file's data.</param>
			/// <param name="freesrc">true to close the RWops before returning, false to
			/// leave it open.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="index">Index of the face in the font file.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(RWops^ src, bool freesrc, int ptsize, long index);

			/// <summary>
			/// Create a font from a file, using a specified face index.
			/// </summary>
			/// <param name="file">File path to font file.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="index">Index of the face in the font file.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(System::String^ file, int ptsize, long index);

			/// <summary>
			/// Create a font from a file, using target resolutions (in DPI).
			/// </summary>
			/// <param name="file">File path to font file.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <param name="index">Index of the face in the font file.</param>
			/// <param name="hdpi">The target horizontal DPI.</param>
			/// <param name="vdpi">The target vertical DPI.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(System::String^ file, int ptsize, long index, unsigned int hdpi, unsigned int vdpi);

			/// <summary>
			/// Create a font from an RWops, using a specified point size.
			/// </summary>
			/// <param name="src">A RWops to provide a font file's data.</param>
			/// <param name="freesrc">true to close the RWops before returning, false to
			/// leave it open.</param>
			/// <param name="ptsize">Point size to use for the newly-opened font.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Font(RWops^ src, bool freesrc, int ptsize);

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
			/// Get or set a font's current FreeType hinter setting.
			/// </summary>
			property TTFHinting Hinting
			{
				TTFHinting get();
				void set(TTFHinting value);
			}

			/// <summary>
			/// Get or set whether or not kerning is allowed for a font.
			/// </summary>
			property bool Kerning
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Query the kerning size of two 16-bit glyphs.
			/// </summary>
			/// <param name="previousCh">The previous character's code, 16 bits.</param>
			/// <param name="ch">The current character's code, 16 bits.</param>
			/// <returns>The kerning size between the two specified characters, in pixels, or None on
			/// error.</returns>
			Result<int, None^> GetFontKerningSizeGlyphs(Uint16 previousCh, Uint16 ch);

			/// <summary>
			/// Query the kerning size of two 32-bit glyphs.
			/// </summary>
			/// <param name="previousCh">The previous character's code, 32 bits.</param>
			/// <param name="ch">The current character's code, 32 bits.</param>
			/// <returns>The kerning size between the two specified characters, in pixels, or None on
			/// error.</returns>
			Result<int, None^> GetFontKerningSizeGlyphs32(Uint32 previousCh, Uint32 ch);

			/// <summary>
			/// Get or set a font's current outline.
			/// </summary>
			property int Outline
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Get or set a font's current style.
			/// </summary>
			property TTFStyle Style
			{
				TTFStyle get();
				void set(TTFStyle value);
			}

			/// <summary>
			/// Get or set a font's current wrap alignment option.
			/// </summary>
			property TTFWrapped WrappedAlign
			{
				TTFWrapped get();
				void set(TTFWrapped value);
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

			/// <summary>
			/// Render a single 32-bit glyph at high quality to a new ARGB surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderGlyph32Blended(Uint32 ch, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render a single 32-bit glyph at LCD subpixel quality to a new ARGB
			/// surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderGlyph32LCD(Uint32 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render a single 32-bit glyph at high quality to a new 8-bit surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderGlyph32Shaded(Uint32 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render a single 32-bit glyph at fast quality to a new 8-bit surface.
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderGlyph32Solid(Uint32 ch, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render a single 16-bit glyph at high quality to a new ARGB surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderGlyphBlended(Uint16 ch, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render a single 16-bit glyph at LCD subpixel quality to a new ARGB
			/// surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderGlyphLCD(Uint16 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render a single 16-bit glyph at high quality to a new 8-bit surface.
			/// </summary>
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderGlyphShaded(Uint16 ch, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render a single 16-bit glyph at fast quality to a new 8-bit surface.
			/// <param name="ch">The character to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderGlyphSolid(Uint16 ch, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render a text at high quality to a new ARGB surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderTextBlended(System::String^ text, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render word-wrapped text at high quality to a new ARGB surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="wrapLength">Maximum length of one line in pixels.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderTextBlendedWrapped(System::String^ text, NETSDL2::Video::Color fg, Uint32 wrapLength);

			/// <summary>
			/// Render a text at LCD subpixel quality to a new ARGB
			/// surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderTextLCD(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render word-wrapped text at LCD subpixel quality to a new ARGB
			/// surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <param name="wrapLength">Maximum length of one line in pixels.</param>
			/// <returns>A new 32-bit, ARGB surface, or None if there was an error.
			/// </returns>
			Result<Surface^, None^> RenderTextLCDWrapped(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg, Uint32 wrapLength);

			/// <summary>
			/// Render a text at high quality to a new 8-bit surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderTextShaded(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg);

			/// <summary>
			/// Render word-wrapped text at high quality to a new 8-bit surface.
			/// </summary>
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="bg">The background color for the text.</param>
			/// <param name="wrapLength">Maximum length of one line in pixels.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderTextShadedWrapped(System::String^ text, NETSDL2::Video::Color fg, NETSDL2::Video::Color bg, Uint32 wrapLength);

			/// <summary>
			/// Render a text at fast quality to a new 8-bit surface.
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderTextSolid(System::String^ text, NETSDL2::Video::Color fg);

			/// <summary>
			/// Render word-wrapped text at fast quality to a new 8-bit surface.
			/// <param name="text">Text to render.</param>
			/// <param name="fg">The foreground color for the text.</param>
			/// <param name="wrapLength">Maximum length of one line in pixels.</param>
			/// <returns>A new 8-bit, palettized surface, or None if there was an
			/// error.</returns>
			Result<Surface^, None^> RenderTextSolidWrapped(System::String^ text, NETSDL2::Video::Color fg, Uint32 wrapLength);

			/// <summary>
			/// Set direction to be used for text shaping by a font.
			/// </summary>
			/// <param name="direction">Direction the new direction for text to flow.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetFontDirection(TTFDirection direction);

			/// <summary>
			/// Set script to be used for text shaping by a font.
			/// </summary>
			/// <param name="script">String of exactly 4 characters.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetFontScriptName(System::String^ script);

			/// <summary>
			/// Query whether Signed Distance Field rendering is enabled for a font.
			/// </summary>
			/// <returns>true if enabled, false otherwise.</returns>
			bool GetFontSDF();

			/// <summary>
			/// Enable Signed Distance Field rendering for a font.
			/// </summary>
			/// <param name="onOff">true to enable SDF, false to disable.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetFontSDF(bool onOff);

			/// <summary>
			/// Set a font's size dynamically.
			/// </summary>
			/// <param name="ptsize">The new point size.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetFontSize(int ptsize);

			/// <summary>
			/// Set font size dynamically with target resolutions (in DPI).
			/// </summary>
			/// <param name="ptsize">The new point size.</param>
			/// <param name="hdpi">The target horizontal DPI.</param>
			/// <param name="vdpi">The target vertical DPI.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetFontSizeDPI(int ptsize, unsigned int hdpi, unsigned int vdpi);

			/// <summary>
			/// Calculate the dimensions of a rendered text.
			/// </summary>
			/// <param name="text">Text to calculate.</param>
			/// <param name="w">Will be filled with width, in pixels, on return.</param>
			/// <param name="h">Will be filled with height, in pixels, on return.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> Size(System::String^ text, [Out]int% w, [Out]int% h);
		};
	}
}