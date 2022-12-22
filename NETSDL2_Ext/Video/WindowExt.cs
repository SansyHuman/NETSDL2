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
    /// Extensions of <see cref="Window"/>
    /// </summary>
    public static class WindowExt
    {
        /// <summary>
        /// Get the shape parameters of a shaped window.
        /// </summary>
        /// <returns>Shape parameters if the window has a shape,
        /// <see cref="ShapedWindowError.NonshapeableWindow"/> if
        /// the window is not a shaped window, or <see cref="ShapedWindowError.WindowLacksShape"/> if
        /// the window is a shapeable window currently lacking a shape.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<SDLWindowShapeMode, ShapedWindowError> GetShapedWindowMode(this Window obj)
        {
            return obj.GetShapedWindowMode(out SDLWindowShapeMode shapeMode)
                .Map(_ => shapeMode);
        }

        /// <summary>
        /// Get the size of a window's borders (decorations) around the
        /// client area.
        /// </summary>
        /// <returns>Top, left, bottom, right border size on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Result<(int top, int left, int bottom, int right), int> GetWindowBordersSize(this Window obj)
        {
            return obj.GetWindowBordersSize(out int top, out int left, out int bottom, out int right)
                .Map(_ => (top, left, bottom, right));
        }

        /// <summary>
        /// Get the maximum size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>The maximum size of a window.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Size GetWindowMaximumSize(this Window obj)
        {
            obj.GetWindowMaximumSize(out int w, out int h);
            return new Size(w, h);
        }

        /// <summary>
        /// Get the minimum size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>The minimum size of a window.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Size GetWindowMinimumSize(this Window obj)
        {
            obj.GetWindowMinimumSize(out int w, out int h);
            return new Size(w, h);
        }

        /// <summary>
        /// Get the position of a window.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>Position of the window in screen coordinates.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Point GetWindowPosition(this Window obj)
        {
            obj.GetWindowPosition(out int x, out int y);
            return new Point(x, y);
        }

        /// <summary>
        /// Get the size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns>Size of the window in screen coordinates.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static Size GetWindowSize(this Window obj)
        {
            obj.GetWindowSize(out int w, out int h);
            return new Size(w, h);
        }

        /// <summary>
        /// Set the maximum size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="maxSize">The maximum size of the window in pixels.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void SetWindowMaximumSize(this Window obj, in Size maxSize)
        {
            obj.SetWindowMaximumSize(maxSize.W, maxSize.H);
        }

        /// <summary>
        /// Set the minimum size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="minSize">The minimum size of the window in pixels.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void SetWindowMinimumSize(this Window obj, in Size minSize)
        {
            obj.SetWindowMinimumSize(minSize.W, minSize.H);
        }

        /// <summary>
        /// Set the position of a window.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="pos">The position of the window in screen coordinates.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void SetWindowPosition(this Window obj, in Point pos)
        {
            obj.SetWindowPosition(pos.X, pos.Y);
        }

        /// <summary>
        /// Set the size of a window's client area.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="size">The size of the window in pixels in screen coordinates.</param>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static void SetWindowSize(this Window obj, in Size size)
        {
            obj.SetWindowSize(size.W, size.H);
        }
    }
}
