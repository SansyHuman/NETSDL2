#include "../../include/events/Cursor.h"

#include "../../include/video/Surface.h"
#include "../../include/core/Error.h"

using namespace NETSDL2::Events;

SDL_Cursor* Cursor::NativeCursor::get()
{
	return cursor;
}

Cursor^ NETSDL2::Events::Cursor::GetCursorFromNative(SDL_Cursor* cursor)
{
	Cursor^ mcursor = nullptr;
	bool found = nativeCursorConnections->TryGetValue(System::IntPtr(cursor), mcursor);
	if(found)
		return mcursor;
	else
		return nullptr;
}

void NETSDL2::Events::Cursor::InitCursor(SDL_Cursor* cursor)
{
	this->cursor = cursor;
	nativeCursorConnections[System::IntPtr(cursor)] = this;
}

NETSDL2::Events::Cursor::Cursor(SDL_Cursor* cursor, bool releaseOnDestroy)
	: releaseOnDestroy(releaseOnDestroy)
{
	InitCursor(cursor);
}

NETSDL2::Events::Cursor::Cursor(Surface^ surface, int hotX, int hotY)
	: releaseOnDestroy(true)
{
	SDL_Cursor* cursor = SDL_CreateColorCursor(surface->NativeSurface, hotX, hotY);
	if(cursor == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitCursor(cursor);
}

NETSDL2::Events::Cursor::Cursor(Uint8* data, Uint8* mask, int w, int h, int hotX, int hotY)
	: releaseOnDestroy(true)
{
	SDL_Cursor* cursor = SDL_CreateCursor(data, mask, w, h, hotX, hotY);
	if(cursor == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitCursor(cursor);
}

NETSDL2::Events::Cursor::Cursor(SystemCursor id)
	: releaseOnDestroy(true)
{
	SDL_Cursor* cursor = SDL_CreateSystemCursor((SDL_SystemCursor)id);
	if(cursor == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitCursor(cursor);
}

NETSDL2::Events::Cursor::~Cursor()
{
	Cursor^ dummy = nullptr;
	nativeCursorConnections->TryRemove(System::IntPtr(cursor), dummy);

	this->!Cursor();
}

NETSDL2::Events::Cursor::!Cursor()
{
	if(releaseOnDestroy)
		SDL_FreeCursor(cursor);

	cursor = __nullptr;
}
