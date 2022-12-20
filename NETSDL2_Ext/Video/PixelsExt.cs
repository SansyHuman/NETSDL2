using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Video
{
    /// <summary>
    /// Additional functions for handling pixel formats and palettes.
    /// </summary>
    public static class PixelsExt
    {
        /// <summary>
        /// Create an <see cref="PixelFormat"/> structure corresponding to
        /// a pixel format.
        /// </summary>
        /// <param name="pixelFormat">One of the
        /// <see cref="PixelFormatEnum"/> values.</param>
        /// <returns>New <see cref="PixelFormat"/> structure or None on
        /// failure.</returns>
        public static unsafe Result<PixelFormatWrapper, None> AllocFormat(PixelFormatEnum pixelFormat)
        {
            PixelFormat* format = Pixels.AllocFormat(pixelFormat);
            if (format == null)
                return Result<PixelFormatWrapper, None>.MakeFailure(None.Value);

            return new PixelFormatWrapper(format);
        }

        /// <summary>
        /// Create a palette structure with the specified number of color
        /// entries.
        /// </summary>
        /// <param name="nColors">The number of color entries in the color
        /// palette.</param>
        /// <returns>New <see cref="Palette"/> structure on success or null
        /// on failure.</returns>
        public static unsafe Result<PaletteWrapper, None> AllocPalette(int nColors)
        {
            Palette* palette = Pixels.AllocPalette(nColors);
            if (palette == null)
                return Result<PaletteWrapper, None>.MakeFailure(None.Value);

            return new PaletteWrapper(palette);
        }

        /// <summary>
        /// Get RGB values from a pixel in the specified format.
        /// </summary>
        /// <param name="pixel">A pixel value.</param>
        /// <param name="format">An <see cref="PixelFormat"/> structure
        /// describing the format of the pixel.</param>
        /// <param name="r">The red component.</param>
        /// <param name="g">The green component.</param>
        /// <param name="b">The blue component.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe void GetRGB(uint pixel, PixelFormatWrapper format, out byte r, out byte g, out byte b)
        {
            Pixels.GetRGB(pixel, format.PixelFormat, out r, out g, out b);
        }

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
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe void GetRGBA(uint pixel, PixelFormatWrapper format, out byte r, out byte g, out byte b, out byte a)
        {
            Pixels.GetRGBA(pixel, format.PixelFormat, out r, out g, out b, out a);
        }

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
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe uint MapRGB(PixelFormatWrapper format, byte r, byte g, byte b)
        {
            return Pixels.MapRGB(format.PixelFormat, r, g, b);
        }

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
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe uint MapRGBA(PixelFormatWrapper format, byte r, byte g, byte b, byte a)
        {
            return Pixels.MapRGBA(format.PixelFormat, r, g, b, a);
        }

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
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe Result<None, int> SetPaletteColors(PaletteWrapper palette, int firstColor, params Color[] colors)
        {
            return Pixels.SetPaletteColors(palette.Palette, firstColor, colors);
        }

        /// <summary>
        /// Set the palette for a pixel format structure.
        /// </summary>
        /// <param name="format">The <see cref="PixelFormat"/> structure
        /// that will use the palette.</param>
        /// <param name="palette">The <see cref="Palette"/> structure that
        /// will be used.</param>
        /// <returns>None on success or error code if not all of the
        /// colors could be set.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe Result<None, int> SetPixelFormatPalette(PixelFormatWrapper format, PaletteWrapper palette)
        {
            return Pixels.SetPixelFormatPalette(format.PixelFormat, palette.Palette);
        }
    }
}
