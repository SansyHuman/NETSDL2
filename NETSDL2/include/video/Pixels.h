#pragma once

#include <SDL.h>

#include "PixelFormat.h"
#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for handling pixel formats and palettes.
		/// </summary>
		public ref struct Pixels abstract sealed
		{
		public:
			/// <summary>
			/// Create an <see cref="PixelFormat"/> structure corresponding to
			/// a pixel format.
			/// </summary>
			/// <param name="pixelFormat">One of the
			/// <see cref="PixelFormatEnum"/> values.</param>
			/// <returns>New <see cref="PixelFormat"/> structure or null on
			/// failure.</returns>
			static PixelFormat* AllocFormat(PixelFormatEnum pixelFormat);

			/// <summary>
			/// Create a palette structure with the specified number of color
			/// entries.
			/// </summary>
			/// <param name="nColors">The number of color entries in the color
			/// palette.</param>
			/// <returns>New <see cref="Palette"/> structure on success or null
			/// on failure.</returns>
			static Palette* AllocPalette(int nColors);

			/// <summary>
			/// Calculate a 256 entry gamma ramp for a gamma value.
			/// </summary>
			/// <param name="gamma">A gamma value where 0.0 is black and 1.0
			/// is identity.</param>
			/// <param name="ramp">An array of 256 values filled in with the
			/// gamma ramp.</param>
			/// <returns>Failure if length of ramp is less than 256, else
			/// success.</returns>
			static Result<None^, None^> CalculateGammaRamp(float gamma, array<Uint16>^ ramp);

			/// <summary>
			/// Free an <see cref="PixelFormat"/> structure allocated by
			/// <see cref="AllocFormat"/>.
			/// </summary>
			/// <param name="format">The <see cref="PixelFormat"/> structure
			/// to free.</param>
			static void FreeFormat(PixelFormat* format);

			/// <summary>
			/// Free a palette created with <see cref="AllocPalette"/>.
			/// </summary>
			/// <param name="palette">The <see cref="Palette"/> structure to
			/// be freed.</param>
			static void FreePalette(Palette* palette);

			/// <summary>
			/// Get RGB values from a pixel in the specified format.
			/// </summary>
			/// <param name="pixel">A pixel value.</param>
			/// <param name="format">An <see cref="PixelFormat"/> structure
			/// describing the format of the pixel.</param>
			/// <param name="r">The red component.</param>
			/// <param name="g">The green component.</param>
			/// <param name="b">The blue component.</param>
			static void GetRGB(Uint32 pixel, PixelFormat* format, [Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b);

			/// <summary>
			/// Get RGBA values from a pixel in the specified format.
			/// </summary>
			/// <param name="pixel">A pixel value.</param>
			/// <param name="format">An <see cref="PixelFormat"/> structure
			/// describing the format of the pixel.</param>
			/// <param name="r">The red component.</param>
			/// <param name="g">The green component.</param>
			/// <param name="b">The blue component.</param>
			/// <param name="a">The alpha component.</param>
			static void GetRGBA(Uint32 pixel, PixelFormat* format, [Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b, [Out]Uint8% a);

			/// <summary>
			/// Map an RGB triple to an opaque pixel value for a given pixel
			/// format.
			/// </summary>
			/// <param name="format">An <see cref="PixelFormat"/> structure
			/// describing the format of the pixel.</param>
			/// <param name="r">The red component of the pixel in the range
			/// 0-255</param>
			/// <param name="g">The green component of the pixel in the range
			/// 0-255</param>
			/// <param name="b">The blue component of the pixel in the range
			/// 0-255</param>
			/// <returns>A pixel value.</returns>
			static Uint32 MapRGB(PixelFormat* format, Uint8 r, Uint8 g, Uint8 b);

			/// <summary>
			/// Map an RGBA quadruple to a pixel value for a given pixel format.
			/// </summary>
			/// <param name="format">An <see cref="PixelFormat"/> structure
			/// describing the format of the pixel.</param>
			/// <param name="r">The red component of the pixel in the range
			/// 0-255</param>
			/// <param name="g">The green component of the pixel in the range
			/// 0-255</param>
			/// <param name="b">The blue component of the pixel in the range
			/// 0-255</param>
			/// <param name="a">The alpha component of the pixel in the range
			/// 0-255</param>
			/// <returns>A pixel value.</returns>
			static Uint32 MapRGBA(PixelFormat* format, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

			/// <summary>
			/// Convert a bpp value and RGBA masks to an enumerated pixel format.
			/// </summary>
			/// <param name="bpp">A bits per pixel value.</param>
			/// <param name="rmask">The red mask for the format.</param>
			/// <param name="gmask">The green mask for the format.</param>
			/// <param name="bmask">The blue mask for the format.</param>
			/// <param name="amask">The alpha mask for the format.</param>
			/// <returns>One of the <see cref="PixelFormatEnum"/> values.
			/// </returns>
			static PixelFormatEnum MasksToPixelFormatEnum(int bpp, Uint32 rmask, Uint32 gmask, Uint32 bmask, Uint32 amask);

			/// <summary>
			/// Convert one of the enumerated pixel formats to a bpp value and
			/// RGBA masks.
			/// </summary>
			/// <param name="format">One of the <see cref="PixelFormatEnum"/>
			/// values.</param>
			/// <param name="bpp">A bits per pixel value.</param>
			/// <param name="rmask">The red mask for the format.</param>
			/// <param name="gmask">The green mask for the format.</param>
			/// <param name="bmask">The blue mask for the format.</param>
			/// <param name="amask">The alpha mask for the format.</param>
			/// <returns>true on success or false if the conversion wasn't
			/// possible.</returns>
			static bool PixelFormatEnumToMasks(PixelFormatEnum format, [Out]int% bpp, [Out]Uint32% rmask, [Out]Uint32% gmask, [Out]Uint32% bmask, [Out]Uint32% amask);

			/// <summary>
			/// Set a range of colors in a palette.
			/// </summary>
			/// <param name="palette">The <see cref="Palette"/> structure to
			/// modify.</param>
			/// <param name="firstColor">The index of the first palette entry
			/// to modify.</param>
			/// <param name="colors">An array of
			/// <see cref="NETSDL2::Video::Color"/> structures to copy into the
			/// palette.</param>
			/// <returns>None on success or error code if not all of the colors
			/// could be set.</returns>
			static Result<None^, int> SetPaletteColors(Palette* palette, int firstColor, ...array<NETSDL2::Video::Color>^ colors);

			/// <summary>
			/// Set the palette for a pixel format structure.
			/// </summary>
			/// <param name="format">The <see cref="PixelFormat"/> structure
			/// that will use the palette.</param>
			/// <param name="palette">The <see cref="Palette"/> structure that
			/// will be used.</param>
			/// <returns>None on success or error code if not all of the
			/// colors could be set.</returns>
			static Result<None^, int> SetPixelFormatPalette(PixelFormat* format, Palette* palette);

			/// <summary>
			/// Copy a block of pixels of one format to another format.
			/// </summary>
			/// <param name="width">The width of the block to copy, in pixels.
			/// </param>
			/// <param name="height">The height of the block to copy, in pixels.
			/// </param>
			/// <param name="srcFormat">A <see cref="PixelFormatEnum"/> value of
			/// the src pixels format.</param>
			/// <param name="src">A pointer to the source pixels.</param>
			/// <param name="srcPitch">The pitch of the source pixels, in bytes.
			/// </param>
			/// <param name="dstFormat">A <see cref="PixelFormatEnum"/> value of
			/// the dst pixels format.</param>
			/// <param name="dst">A pointer to be filled in with new pixel data.
			/// </param>
			/// <param name="dstPitch">The pitch of the destination pixels, in
			/// bytes.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> ConvertPixels(
				int width, int height, PixelFormatEnum srcFormat,
				System::IntPtr src, int srcPitch,
				PixelFormatEnum dstFormat, System::IntPtr dst, int dstPitch
			);
		};

		/// <summary>
		/// Safe wrapper of <see cref="PixelFormat"/> pointer.
		/// </summary>
		public ref class PixelFormatWrapper
		{
		private:
			PixelFormat* format;

		public:
			PixelFormatWrapper(PixelFormat* format);
			~PixelFormatWrapper();
			!PixelFormatWrapper();

			/// <summary>
			/// Native pointer of pixel format.
			/// </summary>
			property PixelFormat* Format
			{
				PixelFormat* get();
			}

			static operator PixelFormat* (PixelFormatWrapper^ wrapper);
		};

		/// <summary>
		/// Safe wrapper of <see cref="Palette"/> pointer.
		/// </summary>
		public ref class PaletteWrapper
		{
		private:
			NETSDL2::Video::Palette* palette;

		public:
			PaletteWrapper(Palette* palette);
			~PaletteWrapper();
			!PaletteWrapper();

			/// <summary>
			/// Native pointer of palette.
			/// </summary>
			property NETSDL2::Video::Palette* Palette
			{
				NETSDL2::Video::Palette* get();
			}

			static operator NETSDL2::Video::Palette* (PaletteWrapper^ wrapper);
		};
	}
}