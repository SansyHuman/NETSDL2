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
    /// Extension functions of <see cref="Surface"/>
    /// </summary>
    public static class SurfaceExt
    {
        /// <summary>
        /// Get the additional color value multiplied into blit operations.
        /// </summary>
        /// <returns>Color value on success or error code on failure.</returns>
        /// <remarks>The alpha value is ignored.</remarks>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<Color, int> GetSurfaceColorMod(this Surface obj)
        {
            return obj.GetSurfaceColorMod(out byte r, out byte g, out byte b)
                .Map(_ => new Color(r, g, b, 0));
        }

        /// <summary>
        /// Set an additional color value multiplied into blit operations.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="color">The color value multiplied into blit
        /// operations.</param>
        /// <returns>None on success or error code on failure.</returns>
        /// <remarks>The alpha value is ignored.</remarks>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> SetSurfaceColorMod(this Surface obj, Color color)
        {
            return obj.SetSurfaceColorMod(color.R, color.G, color.B);
        }

        /// <summary>
        /// Set the palette used by a surface.
        /// </summary>
        /// <param name="palette">The <see cref="Palette"/> structure to use.
        /// </param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe Result<None, int> SetSurfacePalette(this Surface obj, PaletteWrapper palette)
        {
            return obj.SetSurfacePalette(palette.Palette);
        }
    }
}
