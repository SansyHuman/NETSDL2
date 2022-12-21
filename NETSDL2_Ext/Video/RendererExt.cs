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
    /// Struct of size.
    /// </summary>
    public struct Size
    {
        /// <summary>
        /// Width.
        /// </summary>
        public int W;

        /// <summary>
        /// Height.
        /// </summary>
        public int H;

        public Size(int w, int h)
        {
            W = w;
            H = h;
        }

        public override string ToString()
        {
            return $"{{Width: {W}, Height: {H}}}";
        }
    }

    /// <summary>
    /// Extensions of <see cref="Renderer"/>.
    /// </summary>
    public static class RendererExt
    {
        /// <summary>
        /// Get the color used for drawing operations (Rect, Line and Clear).
        /// </summary>
        /// <returns>Draw color or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<Color, int> GetDrawColor(this Renderer obj)
        {
            return obj.GetDrawColor(out byte r, out byte g, out byte b, out byte a)
                .Map(_ => new Color(r, g, b, a));
        }

        /// <summary>
        /// Get the output size in pixels of a rendering context.
        /// </summary>
        /// <returns>Output size on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<Size, int> GetRendererOutputSize(this Renderer obj)
        {
            return obj.GetRendererOutputSize(out int w, out int h)
                .Map(_ => new Size(w, h));
        }

        /// <summary>
        /// Draw a line on the current rendering target.
        /// </summary>
        /// <param name="p1">The start point.</param>
        /// <param name="p2">The end point.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> DrawLine(this Renderer obj, in Point p1, in Point p2)
        {
            return obj.DrawLine(p1.X, p1.Y, p2.X, p2.Y);
        }

        /// <summary>
        /// Draw a line on the current rendering target at subpixel precision.
        /// </summary>
        /// <param name="p1">The start point.</param>
        /// <param name="p2">The end point.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> DrawLineF(this Renderer obj, in FPoint p1, in FPoint p2)
        {
            return obj.DrawLineF(p1.X, p1.Y, p2.X, p2.Y);
        }

        /// <summary>
        /// Draw a point on the current rendering target.
        /// </summary>
        /// <param name="p">The point.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> DrawPoint(this Renderer obj, in Point p)
        {
            return obj.DrawPoint(p.X, p.Y);
        }

        /// <summary>
        /// Draw a point on the current rendering target at subpixel precision.
        /// </summary>
        /// <param name="p">The point.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> DrawPointF(this Renderer obj, in FPoint p)
        {
            return obj.DrawPointF(p.X, p.Y);
        }

        /// <summary>
        /// Get device independent resolution for rendering.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>Device independent resolution.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Size GetLogicalSize(this Renderer obj)
        {
            obj.GetLogicalSize(out int w, out int h);
            return new Size(w, h);
        }

        /// <summary>
        /// Get the drawing scale for the current target.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>(scaleX, scaleY) tuple.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static (float scaleX, float scaleY) GetScale(this Renderer obj)
        {
            obj.GetScale(out float x, out float y);
            return (x, y);
        }

        /// <summary>
        /// Get logical coordinates of point in renderer when given real coordinates of point in
        /// window.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="window">The real coordinate in the window.</param>
        /// <returns>The logical coordinate.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static FPoint WindowToLogical(this Renderer obj, in Point window)
        {
            obj.WindowToLogical(window.X, window.Y, out float x, out float y);
            return new FPoint(x, y);
        }

        /// <summary>
        /// Get real coordinates of point in window when given logical coordinates of point in
        /// wirendererndow.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="logical">The logical coordinate.</param>
        /// <returns>The real coordinate in the window.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Point LogicalToWindow(this Renderer obj, in FPoint logical)
        {
            obj.LogicalToWindow(logical.X, logical.Y, out int x, out int y);
            return new Point(x, y);
        }

        /// <summary>
        /// Set a device independent resolution for rendering.
        /// </summary>
        /// <param name="size">The logical resolution.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> SetLogicalSize(this Renderer obj, in Size size)
        {
            return obj.SetLogicalSize(size.W, size.H);
        }

        /// <summary>
        /// Set the color used for drawing operations (Rect, Line and Clear).
        /// </summary>
        /// <param name="color">The color value used to draw on the rendering
        /// target.</param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<None, int> SetDrawColor(this Renderer obj, Color color)
        {
            return obj.SetDrawColor(color.R, color.G, color.B, color.A);
        }
    }
}
