using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
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
        /// Set the palette used by a surface.
        /// </summary>
        /// <param name="palette">The <see cref="Palette"/> structure to use.
        /// </param>
        /// <returns>None on success or error code on failure.</returns>
        public static unsafe Result<None, int> SetSurfacePalette(this Surface obj, PaletteWrapper palette)
        {
            return obj.SetSurfacePalette(palette.Palette);
        }
    }
}
