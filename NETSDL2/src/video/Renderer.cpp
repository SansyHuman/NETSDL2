#include "../../include/video/Renderer.h"

#include "../../include/video/Window.h"
#include "../../include/video/Surface.h"
#include "../../include/video/Texture.h"

#include "../../include/core/Error.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

NETSDL2::Video::Renderer::Renderer(SDL_Renderer* renderer, bool releaseOnDestroy)
	: releaseOnDestroy(releaseOnDestroy)
{
	InitRenderer(renderer);
}

Renderer^ NETSDL2::Video::Renderer::GetRendererFromNative(SDL_Renderer* renderer)
{
	Renderer^ rend = nullptr;
	bool found = nativeRendererConnections->TryGetValue(System::IntPtr(renderer), rend);
	if(found)
		return rend;
	else
		return nullptr;
}

void NETSDL2::Video::Renderer::InitRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	nativeRendererConnections[System::IntPtr(renderer)] = this;
}

NETSDL2::Video::Renderer::Renderer(Window^ window, int index, RendererFlags flags)
	: releaseOnDestroy(true)
{
	SDL_Renderer* renderer = window->CreateRenderer(index, (Uint32)flags);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitRenderer(renderer);
}

NETSDL2::Video::Renderer::Renderer(Surface^ surface)
	: releaseOnDestroy(true)
{
	SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface->NativeSurface);
	if(renderer == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitRenderer(renderer);
}

NETSDL2::Video::Renderer::~Renderer()
{
	Renderer^ dummy = nullptr;
	nativeRendererConnections->TryRemove(System::IntPtr(renderer), dummy);
	this->!Renderer();
}

NETSDL2::Video::Renderer::!Renderer()
{
	if(releaseOnDestroy)
		SDL_DestroyRenderer(renderer);
	renderer = __nullptr;
}

Result<Window^, None^> NETSDL2::Video::Renderer::GetWindow()
{
	SDL_Window* window = SDL_RenderGetWindow(renderer);
	if(window == __nullptr)
	{
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	Window^ result = Window::GetWindowFromNative(window);
	if(result == nullptr)
	{
		Error::SetError("The window associated with the renderer is not made from managed code.");
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<BlendMode, int> NETSDL2::Video::Renderer::GetDrawBlendMode()
{
	SDL_BlendMode mode;
	int result = SDL_GetRenderDrawBlendMode(renderer, &mode);
	if(result < 0)
	{
		return Result<BlendMode, int>::MakeFailure(result);
	}

	return (BlendMode)mode;
}

Result<None^, int> NETSDL2::Video::Renderer::GetDrawColor(Uint8% r, Uint8% g, Uint8% b, Uint8% a)
{
	Uint8 red, green, blue, alpha;

	int result = SDL_GetRenderDrawColor(renderer, &red, &green, &blue, &alpha);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	r = red;
	g = green;
	b = blue;
	a = alpha;

	return None::Value;
}

Result<RendererInfo, int> NETSDL2::Video::Renderer::GetRendererInfo()
{
	RendererInfo info;

	int result = SDL_GetRendererInfo(renderer, (SDL_RendererInfo*)&info);
	if(result < 0)
	{
		return Result<RendererInfo, int>::MakeFailure(result);
	}

	return info;
}

Result<None^, int> NETSDL2::Video::Renderer::GetRendererOutputSize(int% w, int% h)
{
	int width, height;

	int result = SDL_GetRendererOutputSize(renderer, &width, &height);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	w = width;
	h = height;
	return None::Value;
}

Texture^ NETSDL2::Video::Renderer::GetRenderTarget()
{
	SDL_Texture* target = SDL_GetRenderTarget(renderer);
	if(target == __nullptr)
		return nullptr;

	Texture^ managedTarget = Texture::GetTextureFromNative(target);
	if(managedTarget == nullptr)
	{
		managedTarget = gcnew Texture(target, false);
	}

	return managedTarget;
}

Result<None^, int> NETSDL2::Video::Renderer::Clear()
{
	int result = SDL_RenderClear(renderer);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::Copy(Texture^ texture, System::Nullable<NETSDL2::Video::Rect> srcRect, System::Nullable<NETSDL2::Video::Rect> dstRect)
{
	int result = SDL_RenderCopy(renderer, texture->NativeTexture,
		srcRect.HasValue ? (const SDL_Rect*)&srcRect.Value : __nullptr,
		dstRect.HasValue ? (const SDL_Rect*)&dstRect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::CopyEx(Texture^ texture, System::Nullable<NETSDL2::Video::Rect> srcRect, System::Nullable<NETSDL2::Video::Rect> dstRect, double angle, System::Nullable<NETSDL2::Video::Point> center, RendererFlip flip)
{
	int result = SDL_RenderCopyEx(renderer, texture->NativeTexture,
		srcRect.HasValue ? (const SDL_Rect*)&srcRect.Value : __nullptr,
		dstRect.HasValue ? (const SDL_Rect*)&dstRect.Value : __nullptr,
		angle,
		center.HasValue ? (const SDL_Point*)&center.Value : __nullptr,
		(SDL_RendererFlip)flip);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::CopyExF(Texture^ texture, System::Nullable<NETSDL2::Video::Rect> srcRect, System::Nullable<NETSDL2::Video::FRect> dstRect, double angle, System::Nullable<NETSDL2::Video::FPoint> center, RendererFlip flip)
{
	int result = SDL_RenderCopyExF(renderer, texture->NativeTexture,
		srcRect.HasValue ? (const SDL_Rect*)&srcRect.Value : __nullptr,
		dstRect.HasValue ? (const SDL_FRect*)&dstRect.Value : __nullptr,
		angle,
		center.HasValue ? (const SDL_FPoint*)&center.Value : __nullptr,
		(SDL_RendererFlip)flip);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::CopyF(Texture^ texture, System::Nullable<NETSDL2::Video::Rect> srcRect, System::Nullable<NETSDL2::Video::FRect> dstRect)
{
	int result = SDL_RenderCopyF(renderer, texture->NativeTexture,
		srcRect.HasValue ? (const SDL_Rect*)&srcRect.Value : __nullptr,
		dstRect.HasValue ? (const SDL_FRect*)&dstRect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawLine(int x1, int y1, int x2, int y2)
{
	int result = SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawLineF(float x1, float y1, float x2, float y2)
{
	int result = SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawLines(...array<NETSDL2::Video::Point>^ points)
{
	if(points->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Point> pPoints = &points[0];
	int result = SDL_RenderDrawLines(renderer, (const SDL_Point*)pPoints, points->Length);
	pPoints = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawLinesF(...array<NETSDL2::Video::FPoint>^ points)
{
	if(points->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::FPoint> pPoints = &points[0];
	int result = SDL_RenderDrawLinesF(renderer, (const SDL_FPoint*)pPoints, points->Length);
	pPoints = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawPoint(int x, int y)
{
	int result = SDL_RenderDrawPoint(renderer, x, y);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawPointF(float x, float y)
{
	int result = SDL_RenderDrawPointF(renderer, x, y);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawPoints(...array<NETSDL2::Video::Point>^ points)
{
	if(points->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Point> pPoints = &points[0];
	int result = SDL_RenderDrawPoints(renderer, (const SDL_Point*)pPoints, points->Length);
	pPoints = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawPointsF(...array<NETSDL2::Video::FPoint>^ points)
{
	if(points->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::FPoint> pPoints = &points[0];
	int result = SDL_RenderDrawPointsF(renderer, (const SDL_FPoint*)pPoints, points->Length);
	pPoints = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawRect(System::Nullable<NETSDL2::Video::Rect> rect)
{
	int result = SDL_RenderDrawRect(renderer, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawRectF(System::Nullable<NETSDL2::Video::FRect> rect)
{
	int result = SDL_RenderDrawRectF(renderer, rect.HasValue ? (const SDL_FRect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawRects(...array<NETSDL2::Video::Rect>^ rects)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Rect> pRects = &rects[0];
	int result = SDL_RenderDrawRects(renderer, (const SDL_Rect*)pRects, rects->Length);
	pRects = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::DrawRectsF(...array<NETSDL2::Video::FRect>^ rects)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::FRect> pRects = &rects[0];
	int result = SDL_RenderDrawRectsF(renderer, (const SDL_FRect*)pRects, rects->Length);
	pRects = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::FillRect(System::Nullable<NETSDL2::Video::Rect> rect)
{
	int result = SDL_RenderFillRect(renderer, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::FillRectF(System::Nullable<NETSDL2::Video::FRect> rect)
{
	int result = SDL_RenderFillRectF(renderer, rect.HasValue ? (const SDL_FRect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::FillRects(...array<NETSDL2::Video::Rect>^ rects)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::Rect> pRects = &rects[0];
	int result = SDL_RenderFillRects(renderer, (const SDL_Rect*)pRects, rects->Length);
	pRects = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::FillRectsF(...array<NETSDL2::Video::FRect>^ rects)
{
	if(rects->Length == 0)
		return None::Value;

	pin_ptr<NETSDL2::Video::FRect> pRects = &rects[0];
	int result = SDL_RenderFillRectsF(renderer, (const SDL_FRect*)pRects, rects->Length);
	pRects = nullptr;
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::RenderGeometry(Texture^ texture, array<Vertex>^ vertices, array<int>^ indices)
{
	if(vertices->Length == 0)
		return None::Value;

	if(indices != nullptr && indices->Length == 0)
		return None::Value;

	pin_ptr<Vertex> pVertices = &vertices[0];
	pin_ptr<int> pIndices = indices == nullptr ? nullptr : &indices[0];

	int result = SDL_RenderGeometry(renderer,
		texture == nullptr ? __nullptr : texture->NativeTexture,
		(const SDL_Vertex*)pVertices, vertices->Length,
		indices == nullptr ? nullptr : (const int*)pIndices,
		indices == nullptr ? 0 : indices->Length);

	pVertices = nullptr;
	pIndices = nullptr;

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::RenderGeometryRaw(Texture^ texture, float* xy, int xyStride, NETSDL2::Video::Color* color, int colorStride, float* uv, int uvStride, int numVertices, void* indices, int numIndices, int sizeIndices)
{
	int result = SDL_RenderGeometryRaw(renderer,
		texture == nullptr ? __nullptr : texture->NativeTexture,
		xy, xyStride, (const SDL_Color*)color, colorStride, uv, uvStride,
		numVertices, indices, numIndices, sizeIndices);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

NETSDL2::Video::Rect NETSDL2::Video::Renderer::GetClipRect()
{
	NETSDL2::Video::Rect rect;
	SDL_RenderGetClipRect(renderer, (SDL_Rect*)&rect);

	return rect;
}

bool NETSDL2::Video::Renderer::GetIntegerScale()
{
	return SDL_RenderGetIntegerScale(renderer) == SDL_TRUE;
}

void NETSDL2::Video::Renderer::GetLogicalSize(int% w, int% h)
{
	int width, height;
	SDL_RenderGetLogicalSize(renderer, &width, &height);
	w = width;
	h = height;
}

void NETSDL2::Video::Renderer::GetScale(float% scaleX, float% scaleY)
{
	float x, y;
	SDL_RenderGetScale(renderer, &x, &y);
	scaleX = x;
	scaleY = y;
}

NETSDL2::Video::Rect NETSDL2::Video::Renderer::GetViewport()
{
	NETSDL2::Video::Rect rect;
	SDL_RenderGetViewport(renderer, (SDL_Rect*)&rect);
	return rect;
}

bool Renderer::IsClipEnabled::get()
{
	return SDL_RenderIsClipEnabled(renderer) == SDL_TRUE;
}

void NETSDL2::Video::Renderer::WindowToLogical(int windowX, int windowY, float% logicalX, float% logicalY)
{
	float lx, ly;
	SDL_RenderWindowToLogical(renderer, windowX, windowY, &lx, &ly);
	logicalX = lx;
	logicalY = ly;
}

void NETSDL2::Video::Renderer::LogicalToWindow(float logicalX, float logicalY, int% windowX, int% windowY)
{
	int wx, wy;
	SDL_RenderLogicalToWindow(renderer, logicalX, logicalY, &wx, &wy);
	windowX = wx;
	windowY = wy;
}

void NETSDL2::Video::Renderer::Present()
{
	SDL_RenderPresent(renderer);
}

Result<None^, int> NETSDL2::Video::Renderer::Flush()
{
	int result = SDL_RenderFlush(renderer);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<System::IntPtr, None^> NETSDL2::Video::Renderer::GetMetalLayer()
{
	void* result = SDL_RenderGetMetalLayer(renderer);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Video::Renderer::GetMetalCommandEncoder()
{
	void* result = SDL_RenderGetMetalCommandEncoder(renderer);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<None^, int> NETSDL2::Video::Renderer::ReadPixels(System::Nullable<NETSDL2::Video::Rect> rect, PixelFormatEnum format, System::IntPtr pixels, int pitch)
{
	int result = SDL_RenderReadPixels(renderer,
		rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr,
		(Uint32)format, pixels.ToPointer(), pitch);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetClipRect(System::Nullable<NETSDL2::Video::Rect> rect)
{
	int result = SDL_RenderSetClipRect(renderer, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetIntegerScale(bool enable)
{
	int result = SDL_RenderSetIntegerScale(renderer, enable ? SDL_TRUE : SDL_FALSE);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetLogicalSize(int w, int h)
{
	int result = SDL_RenderSetLogicalSize(renderer, w, h);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetScale(float scaleX, float scaleY)
{
	int result = SDL_RenderSetScale(renderer, scaleX, scaleY);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetViewport(System::Nullable<NETSDL2::Video::Rect> rect)
{
	int result = SDL_RenderSetViewport(renderer, rect.HasValue ? (const SDL_Rect*)&rect.Value : __nullptr);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

bool Renderer::RenderTargetSupported::get()
{
	return SDL_RenderTargetSupported(renderer) == SDL_TRUE;
}

Result<None^, int> NETSDL2::Video::Renderer::SetDrawBlendMode(BlendMode blendMode)
{
	int result = SDL_SetRenderDrawBlendMode(renderer, (SDL_BlendMode)blendMode);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	int result = SDL_SetRenderDrawColor(renderer, r, g, b, a);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetRenderTarget(Texture^ texture)
{
	int result = SDL_SetRenderTarget(renderer, texture == nullptr ? __nullptr : texture->NativeTexture);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Video::Renderer::SetVSync(int vsync)
{
	int result = SDL_RenderSetVSync(renderer, vsync);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

SDL_Texture* NETSDL2::Video::Renderer::CreateTexture(PixelFormatEnum format, TextureAccess access, int w, int h)
{
	return SDL_CreateTexture(renderer, (Uint32)format, (int)access, w, h);
}

SDL_Texture* NETSDL2::Video::Renderer::CreateTextureFromSurface(Surface^ surface)
{
	return SDL_CreateTextureFromSurface(renderer, surface->NativeSurface);
}
