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

NETSDL2::Video::Point::Point(int x, int y)
	: X(x), Y(y)
{
	
}

System::String^ NETSDL2::Video::Point::ToString()
{
	return "{" + System::String::Format("{0}, {1}", X, Y) + "}";
}
