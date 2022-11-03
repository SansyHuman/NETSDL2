#include "../../include/video/DisplayMode.h"

using namespace NETSDL2::Video;

System::String^ NETSDL2::Video::DisplayMode::ToString()
{
	Object^ format = System::Enum::GetName(PixelFormatEnum::typeid, (Uint32)Format);

	return System::String::Format("Pixel format: {0}, Size: ({1}, {2}), Refresh rate: {3}, Driver data address: 0x{4:x}", format, W, H, RefreshRate, Driverdata);
}
