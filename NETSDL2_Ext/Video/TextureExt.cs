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
    /// Extensions of <see cref="Texture"/>.
    /// </summary>
    public static class TextureExt
    {
        /// <summary>
        /// Get the additional color value multiplied into render copy
        /// operations.
        /// </summary>
        /// <returns>Color value on success or error code on failure.</returns>
        /// <remarks>The alpha value is ignored.</remarks>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<Color, int> GetTextureColorMod(this Texture obj)
        {
            return obj.GetTextureColorMod(out byte r, out byte g, out byte b)
                .Map(_ => new Color(r, g, b, 0));
        }

        /// <summary>
        /// Lock a portion of the texture for write-only pixel access.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="rect"></param>
        /// <returns>Pointer to the locked pixels and pitch if success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<(IntPtr pixels, int pitch), int> LockTexture(this Texture obj, Rect? rect)
        {
            return obj.LockTexture(rect, out IntPtr pixels, out int pitch)
                .Map(_ => (pixels, pitch));
        }

        /// <summary>
        /// Lock a portion of the texture for write-only pixel access, and expose it as a SDL
        /// surface.
        /// </summary>
        /// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
        /// representing the area to lock for access; null to lock the entire
        /// texture.</param>
        /// <returns>Surface on success or error code if the texture is not
        /// valid or was not created with
        /// <see cref="TextureAccess.Streaming"/></returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<Surface, int> LockTextureToSurface(this Texture obj, Rect? rect)
        {
            return obj.LockTextureToSurface(rect, out Surface surface)
                .Map(_ => surface);
        }

        /// <summary>
        /// Query the attributes of a texture.
        /// </summary>
        /// <returns>Raw format, access, size of the texture on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<(PixelFormatEnum format, TextureAccess access, Size size), int> QueryTexture(this Texture obj)
        {
            return obj.QueryTexture(out PixelFormatEnum format, out TextureAccess access, out int w, out int h)
                .Map(_ => (format, access, new Size(w, h)));
        }

        /// <summary>
        /// Set an additional color value multiplied into render copy
        /// operations.
        /// </summary>
        /// <param name="color">The color value multiplied into copy
        /// operations.</param>
        /// <returns>None on success or error code on failure.</returns>
        /// <remarks>The alpha value is ignored.</remarks>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> SetTextureColorMod(this Texture obj, Color color)
        {
            return obj.SetTextureColorMod(color.R, color.G, color.B);
        }
    }
}
