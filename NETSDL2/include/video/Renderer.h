#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "../core/Error.h"
#include "RendererInfo.h"
#include "PixelFormat.h"
#include "TextureAccess.h"
#include "Blend.h"
#include "Rect.h"
#include "Vertex.h"
#include "Palette.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Window;
		ref class Surface;
		ref class Texture;

		/// <summary>
		/// Renderer.
		/// </summary>
		public ref class Renderer
		{
		private:
			SDL_Renderer* renderer;
			bool releaseOnDestroy;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Renderer^>^ nativeRendererConnections;

			static Renderer()
			{
				nativeRendererConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Renderer^>();
			}

		internal:
			Renderer(SDL_Renderer* renderer, bool releaseOnDestroy);

			// Gets renderer from native surface, or null if not exists.
			static Renderer^ GetRendererFromNative(SDL_Renderer* renderer);

		private:
			void InitRenderer(SDL_Renderer* renderer);

		public:
			/// <summary>
			/// Create a 2D rendering context for a window.
			/// </summary>
			/// <param name="window">The window where rendering is displayed.
			/// </param>
			/// <param name="index">The index of the rendering driver to
			/// initialize, or -1 to initialize the first one supporting the
			/// requested flags.</param>
			/// <param name="flags">0, or one or more <see cref="RendererFlags"/>
			/// OR'd together.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Renderer(Window^ window, int index, RendererFlags flags);

			/// <summary>
			/// Create a 2D software rendering context for a surface.
			/// </summary>
			/// <param name="surface">The surface where rendering is done.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Renderer(Surface^ surface);
			~Renderer();
			!Renderer();

			/// <summary>
			/// Get the window associated with a renderer.
			/// </summary>
			/// <returns>The window on success or None on failure</returns>
			Result<Window^, None^> GetWindow();

			/// <summary>
			/// Get the blend mode used for drawing operations.
			/// </summary>
			/// <returns>Blend mode on success or error code on failure.</returns>
			Result<BlendMode, int> GetDrawBlendMode();

			/// <summary>
			/// Get the color used for drawing operations (Rect, Line and Clear).
			/// </summary>
			/// <param name="r">The red value used to draw on the rendering
			/// target.</param>
			/// <param name="g">The green value used to draw on the rendering
			/// target.</param>
			/// <param name="b">The blue value used to draw on the rendering
			/// target.</param>
			/// <param name="a">The alpha value used to draw on the rendering
			/// target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetDrawColor([Out]Uint8% r, [Out]Uint8% g, [Out]Uint8% b, [Out]Uint8% a);

			/// <summary>
			/// Get information about a rendering context.
			/// </summary>
			/// <returns>Renderer info on success or error code on failure.
			/// </returns>
			Result<RendererInfo, int> GetRendererInfo();

			/// <summary>
			/// Get the output size in pixels of a rendering context.
			/// </summary>
			/// <param name="w">The width.</param>
			/// <param name="h">The height.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> GetRendererOutputSize([Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the current render target.
			/// </summary>
			/// <returns>The current render target or null for the default render
			/// target.</returns>
			Texture^ GetRenderTarget();

			/// <summary>
			/// Clear the current rendering target with the drawing color.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Clear();

			/// <summary>
			/// Copy a portion of the texture to the current rendering target.
			/// </summary>
			/// <param name="texture">The source texture.</param>
			/// <param name="srcRect">The source rectangle or null for the entire
			/// texture.</param>
			/// <param name="dstRect">The destination rectangle or null for the
			/// entire rendering target; the texture will be stretched to fill the
			/// given rectangle.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Copy(Texture^ texture,
				System::Nullable<NETSDL2::Video::Rect> srcRect,
				System::Nullable<NETSDL2::Video::Rect> dstRect);

			/// <summary>
			/// Copy a portion of the texture to the current rendering, with
			/// optional rotation and flipping.
			/// </summary>
			/// <param name="texture">The source texture.</param>
			/// <param name="srcRect">The source rectangle or null for the entire
			/// texture.</param>
			/// <param name="dstRect">The destination rectangle or null for the
			/// entire rendering target.</param>
			/// <param name="angle">An angle in degrees that indicates the rotation
			/// that will be applied to dstrect, rotating it in a clockwise
			/// direction.</param>
			/// <param name="center">A point indicating the point around which
			/// dstRect will be rotated (if null, rotation will be done around
			/// dstRect.w / 2, dstRect.h / 2).</param>
			/// <param name="flip">A <see cref="RendererFlip"/> value stating which
			/// flipping actions should be performed on the texture.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> CopyEx(Texture^ texture,
				System::Nullable<NETSDL2::Video::Rect> srcRect,
				System::Nullable<NETSDL2::Video::Rect> dstRect,
				double angle, System::Nullable<NETSDL2::Video::Point> center,
				RendererFlip flip);

			/// <summary>
			/// Copy a portion of the texture to the current rendering, with
			/// optional rotation and flipping, at subpixel precision.
			/// </summary>
			/// <param name="texture">The source texture.</param>
			/// <param name="srcRect">The source rectangle or null for the entire
			/// texture.</param>
			/// <param name="dstRect">The destination rectangle or null for the
			/// entire rendering target.</param>
			/// <param name="angle">An angle in degrees that indicates the rotation
			/// that will be applied to dstrect, rotating it in a clockwise
			/// direction.</param>
			/// <param name="center">A point indicating the point around which
			/// dstRect will be rotated (if null, rotation will be done around
			/// dstRect.w / 2, dstRect.h / 2).</param>
			/// <param name="flip">A <see cref="RendererFlip"/> value stating which
			/// flipping actions should be performed on the texture.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> CopyExF(Texture^ texture,
				System::Nullable<NETSDL2::Video::Rect> srcRect,
				System::Nullable<NETSDL2::Video::FRect> dstRect,
				double angle, System::Nullable<NETSDL2::Video::FPoint> center,
				RendererFlip flip);

			/// <summary>
			/// Copy a portion of the texture to the current rendering target at
			/// subpixel precision.
			/// </summary>
			/// <param name="texture">The source texture.</param>
			/// <param name="srcRect">The source rectangle or null for the entire
			/// texture.</param>
			/// <param name="dstRect">The destination rectangle or null for the
			/// entire rendering target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> CopyF(Texture^ texture,
				System::Nullable<NETSDL2::Video::Rect> srcRect,
				System::Nullable<NETSDL2::Video::FRect> dstRect);

			/// <summary>
			/// Draw a line on the current rendering target.
			/// </summary>
			/// <param name="x1">The x coordinate of the start point.</param>
			/// <param name="y1">The y coordinate of the start point.</param>
			/// <param name="x2">The x coordinate of the end point.</param>
			/// <param name="y2">The y coordinate of the end point.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawLine(int x1, int y1, int x2, int y2);

			/// <summary>
			/// Draw a line on the current rendering target at subpixel precision.
			/// </summary>
			/// <param name="x1">The x coordinate of the start point.</param>
			/// <param name="y1">The y coordinate of the start point.</param>
			/// <param name="x2">The x coordinate of the end point.</param>
			/// <param name="y2">The y coordinate of the end point.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawLineF(float x1, float y1, float x2, float y2);

			/// <summary>
			/// Draw a series of connected lines on the current rendering target.
			/// </summary>
			/// <param name="points">An array of <see cref="NETSDL2::Video::Point"/>
			/// structures representing points along the lines.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawLines(...array<NETSDL2::Video::Point>^ points);

			/// <summary>
			/// Draw a series of connected lines on the current rendering target at
			/// subpixel precision.
			/// </summary>
			/// <param name="points">An array of <see cref="NETSDL2::Video::FPoint"/>
			/// structures representing points along the lines.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawLinesF(...array<NETSDL2::Video::FPoint>^ points);

			/// <summary>
			/// Draw a point on the current rendering target.
			/// </summary>
			/// <param name="x">The x coordinate of the point.</param>
			/// <param name="y">The y coordinate of the point.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawPoint(int x, int y);

			/// <summary>
			/// Draw a point on the current rendering target at subpixel precision.
			/// </summary>
			/// <param name="x">The x coordinate of the point.</param>
			/// <param name="y">The y coordinate of the point.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawPointF(float x, float y);

			/// <summary>
			/// Draw multiple points on the current rendering target.
			/// </summary>
			/// <param name="points">An array of <see cref="NETSDL2::Video::Point"/>
			/// structures representing points to draw.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawPoints(...array<NETSDL2::Video::Point>^ points);

			/// <summary>
			/// Draw multiple points on the current rendering target at subpixel
			/// precision.
			/// </summary>
			/// <param name="points">An array of <see cref="NETSDL2::Video::FPoint"/>
			/// structures representing points to draw.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawPointsF(...array<NETSDL2::Video::FPoint>^ points);

			/// <summary>
			/// Draw a rectangle on the current rendering target.
			/// </summary>
			/// <param name="rect">An <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the rectangle to draw, or null to outline the entire
			/// rendering target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawRect(System::Nullable<NETSDL2::Video::Rect> rect);

			/// <summary>
			/// Draw a rectangle on the current rendering target at subpixel
			/// precision.
			/// </summary>
			/// <param name="rect">The destination rectangle, or null to outline the
			/// entire rendering target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawRectF(System::Nullable<NETSDL2::Video::FRect> rect);

			/// <summary>
			/// Draw some number of rectangles on the current rendering target.
			/// </summary>
			/// <param name="rects">An array of <see cref="NETSDL2::Video::Rect"/>
			/// structures representing the rectangles to be drawn.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawRects(...array<NETSDL2::Video::Rect>^ rects);

			/// <summary>
			/// Draw some number of rectangles on the current rendering target at
			/// subpixel precision.
			/// </summary>
			/// <param name="rects">An array of <see cref="NETSDL2::Video::FRect"/>
			/// structures representing the rectangles to be drawn.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> DrawRectsF(...array<NETSDL2::Video::FRect>^ rects);

			/// <summary>
			/// Fill a rectangle on the current rendering target with the drawing
			/// color.
			/// </summary>
			/// <param name="rect">An <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the rectangle to fill, or null for the entire rendering
			/// target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRect(System::Nullable<NETSDL2::Video::Rect> rect);

			/// <summary>
			/// Fill a rectangle on the current rendering target with the drawing
			/// color at subpixel precision.
			/// </summary>
			/// <param name="rect">The destination rectangle, or null for the entire
			/// rendering target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRectF(System::Nullable<NETSDL2::Video::FRect> rect);

			/// <summary>
			/// Fill some number of rectangles on the current rendering target with
			/// the drawing color.
			/// </summary>
			/// <param name="rects">An array of <see cref="NETSDL2::Video::Rect"/>
			/// structures representing the rectangles to be filled.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRects(...array<NETSDL2::Video::Rect>^ rects);

			/// <summary>
			/// Fill some number of rectangles on the current rendering target with
			/// the drawing color at subpixel precision.
			/// </summary>
			/// <param name="rects">An array of <see cref="NETSDL2::Video::FRect"/>
			/// structures representing the rectangles to be filled.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> FillRectsF(...array<NETSDL2::Video::FRect>^ rects);

			/// <summary>
			/// Render a list of triangles, optionally using a texture and indices
			/// into the vertex array Color and alpha modulation is done per vertex.
			/// </summary>
			/// <param name="texture">(optional) The SDL texture to use.</param>
			/// <param name="vertices">Vertices.</param>
			/// <param name="indices">An array of integer indices into the
			/// 'vertices' array, if null all vertices will be rendered in
			/// sequential order.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> RenderGeometry(Texture^ texture, array<Vertex>^ vertices, array<int>^ indices);

			/// <summary>
			/// Render a list of triangles, optionally using a texture and indices
			/// into the vertex arrays Color and alpha modulation is done per vertex.
			/// </summary>
			/// <param name="texture">(optional) The SDL texture to use.</param>
			/// <param name="xy">Vertex positions.</param>
			/// <param name="xyStride">Byte size to move from one element to the next
			/// element.</param>
			/// <param name="color">Vertex colors.</param>
			/// <param name="colorStride">Byte size to move from one element to the
			/// next element.</param>
			/// <param name="uv">Vertex normalized texture coordinates.</param>
			/// <param name="uvStride">Byte size to move from one element to the
			/// next element.</param>
			/// <param name="numVertices">Number of vertices.</param>
			/// <param name="indices">An array of indices into the vertices arrays,
			/// if null all vertices will be rendered in sequential order.</param>
			/// <param name="numIndices">Number of indices.</param>
			/// <param name="sizeIndices">Index size: 1 (byte), 2 (short), 4 (int).
			/// </param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> RenderGeometryRaw(Texture^ texture,
				float* xy, int xyStride,
				NETSDL2::Video::Color* color, int colorStride,
				float* uv, int uvStride, int numVertices,
				void* indices, int numIndices, int sizeIndices);

			/// <summary>
			/// Get the clip rectangle for the current target.
			/// </summary>
			/// <returns>A <see cref="NETSDL2::Video::Rect"/> structure filled in
			/// with the current clipping area or an empty rectangle if clipping is
			/// disabled.</returns>
			NETSDL2::Video::Rect GetClipRect();

			/// <summary>
			/// Get whether integer scales are forced for resolution-independent
			/// rendering.
			/// </summary>
			/// <returns>true if integer scales are forced or false if not and on
			/// failure.</returns>
			bool GetIntegerScale();

			/// <summary>
			/// Get device independent resolution for rendering.
			/// </summary>
			/// <param name="w">An int to be filled with the width.</param>
			/// <param name="h">An int to be filled with the height.</param>
			void GetLogicalSize([Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the drawing scale for the current target.
			/// </summary>
			/// <param name="scaleX">The horizontal scaling factor.</param>
			/// <param name="scaleY">The vertical scaling factor.</param>
			void GetScale([Out]float% scaleX, [Out]float% scaleY);

			/// <summary>
			/// Get the drawing area for the current target.
			/// </summary>
			/// <returns>A <see cref="NETSDL2::Video::Rect"/> structure filled in
			/// with the current drawing area.</returns>
			NETSDL2::Video::Rect GetViewport();

			/// <summary>
			/// Get whether clipping is enabled on the given renderer.
			/// </summary>
			property bool IsClipEnabled
			{
				bool get();
			}

			/// <summary>
			/// Get logical coordinates of point in renderer when given real coordinates of point in
			/// window.
			/// </summary>
			/// <param name="windowX">The real X coordinate in the window.</param>
			/// <param name="windowY">The real Y coordinate in the window.</param>
			/// <param name="logicalX">The logical x coordinate.</param>
			/// <param name="logicalY">The logical y coordinate.</param>
			void WindowToLogical(int windowX, int windowY, [Out]float% logicalX, [Out]float% logicalY);

			/// <summary>
			/// Get real coordinates of point in window when given logical coordinates of point in
			/// wirendererndow.
			/// </summary>
			/// <param name="logicalX">The logical x coordinate.</param>
			/// <param name="logicalY">The logical y coordinate.</param>
			/// <param name="windowX">The real X coordinate in the window.</param>
			/// <param name="windowY">The real Y coordinate in the window.</param>
			void LogicalToWindow(float logicalX, float logicalY, [Out]int% windowX, [Out]int% windowY);

			/// <summary>
			/// Update the screen with any rendering performed since the previous
			/// call.
			/// </summary>
			void Present();

			/// <summary>
			/// Force the rendering context to flush any pending commands to the underlying rendering API.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Flush();

			/// <summary>
			/// Get the CAMetalLayer associated with the given Metal renderer.
			/// </summary>
			/// <returns>A CAMetalLayer * on success, or None if the renderer isn't a Metal renderer.
			/// </returns>
			Result<System::IntPtr, None^> GetMetalLayer();

			/// <summary>
			/// Get the Metal command encoder for the current frame.
			/// </summary>
			/// <returns>An MTLRenderCommandEncoder on success, or None if the renderer isn't a Metal
			/// renderer or there was an error.</returns>
			Result<System::IntPtr, None^> GetMetalCommandEncoder();

			/// <summary>
			/// Read pixels from the current rendering target to an array of
			/// pixels.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the area to read, or null for the entire render
			/// target</param>
			/// <param name="format">A <see cref="PixelFormatEnum"/> value of the
			/// desired format of the pixel data, or
			/// <see cref="PixelFormatEnum::Unknown"/> to use the format of the
			/// rendering target.</param>
			/// <param name="pixels">A pointer to the pixel data to copy into.
			/// </param>
			/// <param name="pitch">The pitch of the pixels parameter.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> ReadPixels(System::Nullable<NETSDL2::Video::Rect> rect, PixelFormatEnum format, System::IntPtr pixels, int pitch);

			/// <summary>
			/// Set the clip rectangle for rendering on the specified target.
			/// </summary>
			/// <param name="rect">A <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the clip area, relative to the viewport, or null to
			/// disable clipping.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetClipRect(System::Nullable<NETSDL2::Video::Rect> rect);

			/// <summary>
			/// Set whether to force integer scales for resolution-independent
			/// rendering.
			/// </summary>
			/// <param name="enable">Enable or disable the integer scaling for
			/// rendering.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetIntegerScale(bool enable);

			/// <summary>
			/// Set a device independent resolution for rendering.
			/// </summary>
			/// <param name="w">The width of the logical resolution.</param>
			/// <param name="h">The height of the logical resolution.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetLogicalSize(int w, int h);

			/// <summary>
			/// Set the drawing scale for rendering on the current target.
			/// </summary>
			/// <param name="scaleX">The horizontal scaling factor.</param>
			/// <param name="scaleY">The vertical scaling factor.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetScale(float scaleX, float scaleY);

			/// <summary>
			/// Set the drawing area for rendering on the current target.
			/// </summary>
			/// <param name="rect">The <see cref="NETSDL2::Video::Rect"/> structure
			/// representing the drawing area, or null to set the viewport to the
			/// entire target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetViewport(System::Nullable<NETSDL2::Video::Rect> rect);

			/// <summary>
			/// Determine whether a renderer supports the use of render targets.
			/// </summary>
			property bool RenderTargetSupported
			{
				bool get();
			}

			/// <summary>
			/// Set the blend mode used for drawing operations (Fill and Line).
			/// </summary>
			/// <param name="blendMode">The <see cref="BlendMode"/> to use for
			/// blending.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetDrawBlendMode(BlendMode blendMode);

			/// <summary>
			/// Set the color used for drawing operations (Rect, Line and Clear).
			/// </summary>
			/// <param name="r">The red value used to draw on the rendering
			/// target.</param>
			/// <param name="g">The green value used to draw on the rendering
			/// target.</param>
			/// <param name="b">The blue value used to draw on the rendering
			/// target.</param>
			/// <param name="a">The alpha value used to draw on the rendering
			/// target.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

			/// <summary>
			/// Set a texture as the current rendering target.
			/// </summary>
			/// <param name="texture">The targeted texture, which must be created
			/// with the <see cref="TextureAccess::Target"/> flag, or null to
			/// render to the window instead of a texture.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetRenderTarget(Texture^ texture);

			/// <summary>
			/// Toggle VSync of the given renderer.
			/// </summary>
			/// <param name="vsync">1 for on, 0 for off. All other values are reserved.</param>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> SetVSync(int vsync);

		internal:
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			SDL_Texture* CreateTexture(PixelFormatEnum format, TextureAccess access, int w, int h);

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			SDL_Texture* CreateTextureFromSurface(Surface^ surface);
		};
	}
}