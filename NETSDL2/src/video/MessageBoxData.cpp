#include "../../include/video/MessageBoxData.h"

using namespace NETSDL2::Video;

NETSDL2::Video::MessageBoxColorScheme::MessageBoxColorScheme()
{
	colors = gcnew array<MessageBoxColor>(5);
}

MessageBoxColor MessageBoxColorScheme::default::get(MessageBoxColorType index)
{
	return colors[(int)index];
}

void MessageBoxColorScheme::default::set(MessageBoxColorType index, MessageBoxColor value)
{
	colors[(int)index] = value;
}

NETSDL2::Video::MessageBoxColor::MessageBoxColor(Uint8 r, Uint8 g, Uint8 b)
	: R(r), G(g), B(b)
{
	
}

System::String^ NETSDL2::Video::MessageBoxColor::ToString()
{
	return System::String::Format("({0}, {1}, {2})", R, G, B);
}

NETSDL2::Video::MessageBoxButtonData::MessageBoxButtonData(MessageBoxButtonFlags flags, int id, System::String^ text)
	: Flags(flags), ButtonID(id), Text(text)
{
	
}

System::String^ NETSDL2::Video::MessageBoxButtonData::ToString()
{
	return System::String::Format("Button \"{0}\" [Flags: {1}, ID: {2}]", Text, Flags, ButtonID);
}

NETSDL2::Video::MessageBoxData::MessageBoxData(MessageBoxFlags flags, NETSDL2::Video::Window^ window, System::String^ title, System::String^ message, MessageBoxColorScheme^ colorScheme, ...array<MessageBoxButtonData>^ buttons)
	: Flags(flags), Window(window), Title(title), Message(message), Buttons(buttons), ColorScheme(colorScheme)
{
	
}
