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
