#include "../../include/video/Palette.h"

using namespace NETSDL2::Video;

NETSDL2::Video::Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	: R(r), G(g), B(b), A(a)
{
	
}

System::String^ NETSDL2::Video::Color::ToString()
{
	return System::String::Format("({0}, {1}, {2}, {3})", R, G, B, A);
}

int Palette::NumColors::get()
{
	return nColors;
}

Color Palette::default::get(int index)
{
	if(index < 0 || index >= nColors)
		throw gcnew System::IndexOutOfRangeException();

	return Colors[index];
}
