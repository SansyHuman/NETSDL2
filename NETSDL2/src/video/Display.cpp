#include "../../include/video/Display.h"

#include "../../include/core/Error.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"
#include "../../include/video/Rect.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

void NETSDL2::Video::Display::DisableScreenSaver()
{
	SDL_DisableScreenSaver();
}

void NETSDL2::Video::Display::EnableScreenSaver()
{
	SDL_EnableScreenSaver();
}

Result<DisplayMode, None^> NETSDL2::Video::Display::GetClosestDisplayMode(int displayIndex, DisplayMode% mode)
{
	pin_ptr<DisplayMode> pMode = &mode;
	DisplayMode closest;

	if(SDL_GetClosestDisplayMode(displayIndex, (const SDL_DisplayMode*)pMode, (SDL_DisplayMode*)&closest) == __nullptr)
	{
		return Result<DisplayMode, None^>::MakeFailure(None::Value);
	}

	pMode = nullptr;

	return closest;
}

Result<int, int> NETSDL2::Video::Display::GetPointDisplayIndex(NETSDL2::Video::Point point)
{
	int result = SDL_GetPointDisplayIndex((const SDL_Point*)&point);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Video::Display::GetRectDisplayIndex(NETSDL2::Video::Rect rect)
{
	int result = SDL_GetRectDisplayIndex((const SDL_Rect*)&rect);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<DisplayMode, int> NETSDL2::Video::Display::GetCurrentDisplayMode(int displayIndex)
{
	DisplayMode current;
	int result = SDL_GetCurrentDisplayMode(displayIndex, (SDL_DisplayMode*)&current);
	
	if(result < 0)
	{
		return Result<DisplayMode, int>::MakeFailure(result);
	}

	return current;
}

System::String^ NETSDL2::Video::Display::GetCurrentVideoDriver()
{
	const char* name = SDL_GetCurrentVideoDriver();
	if(name == __nullptr)
		return "";
	return StringMarshal::UTF8NativeToManaged(name);
}

Result<DisplayMode, int> NETSDL2::Video::Display::GetDesktopDisplayMode(int displayIndex)
{
	DisplayMode current;
	int result = SDL_GetDesktopDisplayMode(displayIndex, (SDL_DisplayMode*)&current);

	if(result < 0)
	{
		return Result<DisplayMode, int>::MakeFailure(result);
	}

	return current;
}

Result<NETSDL2::Video::Rect, int> NETSDL2::Video::Display::GetDisplayBounds(int displayIndex)
{
	NETSDL2::Video::Rect rect;
	int result = SDL_GetDisplayBounds(displayIndex, (SDL_Rect*)&rect);

	if(result < 0)
	{
		return Result<NETSDL2::Video::Rect, int>::MakeFailure(result);
	}

	return rect;
}

Result<None^, int> NETSDL2::Video::Display::GetDisplayDPI(int displayIndex, float% ddpi, float% hdpi, float% vdpi)
{
	float d, h, v;
	int result = SDL_GetDisplayDPI(displayIndex, &d, &h, &v);

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	ddpi = d;
	hdpi = h;
	vdpi = v;

	return None::Value;
}

DisplayOrientation NETSDL2::Video::Display::GetDisplayOrientation(int displayIndex)
{
	return (DisplayOrientation)SDL_GetDisplayOrientation(displayIndex);
}

Result<DisplayMode, int> NETSDL2::Video::Display::GetDisplayMode(int displayIndex, int modeIndex)
{
	DisplayMode mode;
	int result = SDL_GetDisplayMode(displayIndex, modeIndex, (SDL_DisplayMode*)&mode);

	if(result < 0)
	{
		return Result<DisplayMode, int>::MakeFailure(result);
	}

	return mode;
}

array<DisplayMode>^ NETSDL2::Video::Display::GetDisplayModes(int displayIndex)
{
	int numDisplayModes = SDL_GetNumDisplayModes(displayIndex);
	if(numDisplayModes <= 0)
		return gcnew array<DisplayMode>(0);

	System::Collections::Generic::List<DisplayMode>^ list = gcnew System::Collections::Generic::List<DisplayMode>(numDisplayModes);

	int modeIndex = 0;
	while(true)
	{
		Result<DisplayMode, int> result = GetDisplayMode(displayIndex, modeIndex);
		if(result.IsFailure)
			break;

		list->Add(result.ResultValue);
		modeIndex++;
	}

	return list->ToArray();
}

System::String^ NETSDL2::Video::Display::GetDisplayName(int displayIndex)
{
	const char* name = SDL_GetDisplayName(displayIndex);
	if(name == __nullptr)
		return "";
	return StringMarshal::UTF8NativeToManaged(name);
}

Result<Rect, int> NETSDL2::Video::Display::GetDisplayUsableBounds(int displayIndex)
{
	NETSDL2::Video::Rect rect;
	int result = SDL_GetDisplayUsableBounds(displayIndex, (SDL_Rect*)&rect);

	if(result < 0)
	{
		return Result<NETSDL2::Video::Rect, int>::MakeFailure(result);
	}

	return rect;
}

int NETSDL2::Video::Display::GetNumDisplayModes(int displayIndex)
{
	return SDL_GetNumDisplayModes(displayIndex);
}

int Display::NumVideoDisplays::get()
{
	return SDL_GetNumVideoDisplays();
}

int Display::NumVideoDrivers::get()
{
	return SDL_GetNumVideoDrivers();
}

System::String^ NETSDL2::Video::Display::GetVideoDriver(int index)
{
	const char* name = SDL_GetVideoDriver(index);
	return StringMarshal::UTF8NativeToManaged(name);
}

bool Display::IsScreenSaverEnabled::get()
{
	return SDL_IsScreenSaverEnabled() == SDL_TRUE;
}
