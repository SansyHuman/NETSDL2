#include "../../include/video/Rect.h"

using namespace NETSDL2::Video;

NETSDL2::Video::Rect::Rect(int x, int y, int w, int h)
	: X(x), Y(y), W(w), H(h)
{
	
}

System::String^ NETSDL2::Video::Rect::ToString()
{
	return "{" + System::String::Format("{0}, {1}, {2}, {3}", X, Y, W, H) + "}";
}

bool Rect::Empty::get()
{
	pin_ptr<Rect> self = &(*this);
	return SDL_RectEmpty((const SDL_Rect*)self) == SDL_TRUE;
}

bool NETSDL2::Video::Rect::Equals(NETSDL2::Video::Rect other)
{
	pin_ptr<Rect> self = &(*this);
	return SDL_RectEquals((const SDL_Rect*)self, (const SDL_Rect*)&other) == SDL_TRUE;
}

NETSDL2::Video::Point::Point(int x, int y)
	: X(x), Y(y)
{
	
}

System::String^ NETSDL2::Video::Point::ToString()
{
	return "{" + System::String::Format("{0}, {1}", X, Y) + "}";
}

NETSDL2::Video::FPoint::FPoint(float x, float y)
	: X(x), Y(y)
{
	
}

System::String^ NETSDL2::Video::FPoint::ToString()
{
	return "{" + System::String::Format("{0}, {1}", X, Y) + "}";
}

NETSDL2::Video::FRect::FRect(float x, float y, float w, float h)
	: X(x), Y(y), W(w), H(h)
{
	
}

System::String^ NETSDL2::Video::FRect::ToString()
{
	return "{" + System::String::Format("{0}, {1}, {2}, {3}", X, Y, W, H) + "}";
}

bool FRect::Empty::get()
{
	pin_ptr<FRect> self = &(*this);
	return SDL_FRectEmpty((const SDL_FRect*)self) == SDL_TRUE;
}

bool NETSDL2::Video::FRect::Equals(NETSDL2::Video::FRect other)
{
	pin_ptr<FRect> self = &(*this);
	return SDL_FRectEquals((const SDL_FRect*)self, (const SDL_FRect*)&other) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::EncloseFPoints(array<FPoint>^ points, System::Nullable<FRect> clip, FRect% result)
{
	pin_ptr<FPoint> pPoints = &points[0];
	pin_ptr<FRect> pResult = &result;

	if(clip.HasValue)
	{
		FRect cl = clip.Value;
		return SDL_EncloseFPoints((const SDL_FPoint*)pPoints, points->Length, (const SDL_FRect*)&cl, (SDL_FRect*)pResult) == SDL_TRUE;
	}
	else
	{
		return SDL_EncloseFPoints((const SDL_FPoint*)pPoints, points->Length, __nullptr, (SDL_FRect*)pResult) == SDL_TRUE;
	}
}

bool NETSDL2::Video::RectOps::EnclosePoints(array<Point>^ points, System::Nullable<Rect> clip, Rect% result)
{
	pin_ptr<Point> pPoints = &points[0];
	pin_ptr<Rect> pResult = &result;

	if(clip.HasValue)
	{
		Rect cl = clip.Value;
		return SDL_EnclosePoints((const SDL_Point*)pPoints, points->Length, (const SDL_Rect*)&cl, (SDL_Rect*)pResult) == SDL_TRUE;
	}
	else
	{
		return SDL_EnclosePoints((const SDL_Point*)pPoints, points->Length, __nullptr, (SDL_Rect*)pResult) == SDL_TRUE;
	}
}

bool NETSDL2::Video::RectOps::HasIntersection(Rect a, Rect b)
{
	return SDL_HasIntersection((const SDL_Rect*)&a, (const SDL_Rect*)&b) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::HasIntersectionF(FRect a, FRect b)
{
	return SDL_HasIntersectionF((const SDL_FRect*)&a, (const SDL_FRect*)&b) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::IntersectFRect(FRect a, FRect b, FRect% result)
{
	pin_ptr<FRect> pResult = &result;
	return SDL_IntersectFRect((const SDL_FRect*)&a, (const SDL_FRect*)&b, (SDL_FRect*)pResult) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::IntersectFRectAndLine(FRect rect, float x1, float y1, float x2, float y2)
{
	return SDL_IntersectFRectAndLine((const SDL_FRect*)&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::IntersectRect(Rect a, Rect b, Rect% result)
{
	pin_ptr<Rect> pResult = &result;
	return SDL_IntersectRect((const SDL_Rect*)&a, (const SDL_Rect*)&b, (SDL_Rect*)pResult) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::IntersectRectAndLine(Rect rect, int x1, int y1, int x2, int y2)
{
	return SDL_IntersectRectAndLine((const SDL_Rect*)&rect, &x1, &y1, &x2, &y2) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::PointInFRect(FPoint p, FRect r)
{
	return SDL_PointInFRect((const SDL_FPoint*)&p, (const SDL_FRect*)&r) == SDL_TRUE;
}

bool NETSDL2::Video::RectOps::PointInRect(Point p, Rect r)
{
	return SDL_PointInRect((const SDL_Point*)&p, (const SDL_Rect*)&r) == SDL_TRUE;
}

void NETSDL2::Video::RectOps::UnionFRect(FRect a, FRect b, FRect% result)
{
	pin_ptr<FRect> pResult = &result;

	SDL_UnionFRect((const SDL_FRect*)&a, (const SDL_FRect*)&b, (SDL_FRect*)pResult);
}

void NETSDL2::Video::RectOps::UnionRect(Rect a, Rect b, Rect% result)
{
	pin_ptr<Rect> pResult = &result;

	SDL_UnionRect((const SDL_Rect*)&a, (const SDL_Rect*)&b, (SDL_Rect*)pResult);
}
