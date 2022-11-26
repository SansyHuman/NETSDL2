#include "../../include/events/Mouse.h"

#include "../../include/video/Window.h"
#include "../../include/events/Cursor.h"

using namespace NETSDL2::Events;

Result<None^, None^> NETSDL2::Events::Mouse::CaptureMouse(bool enabled)
{
	int result = SDL_CaptureMouse(enabled ? SDL_TRUE : SDL_FALSE);
	if(result == -1)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<Cursor^, None^> NETSDL2::Events::Mouse::GetCursor()
{
	SDL_Cursor* result = SDL_GetCursor();
	if(result == __nullptr)
	{
		return Result<Cursor^, None^>::MakeFailure(None::Value);
	}

	Cursor^ cursor = Cursor::GetCursorFromNative(result);
	if(cursor == nullptr)
	{
		cursor = gcnew Cursor(result, false);
	}

	return cursor;
}

Result<Cursor^, None^> NETSDL2::Events::Mouse::GetDefaultCursor()
{
	SDL_Cursor* result = SDL_GetDefaultCursor();
	if(result == __nullptr)
	{
		return Result<Cursor^, None^>::MakeFailure(None::Value);
	}

	Cursor^ cursor = Cursor::GetCursorFromNative(result);
	if(cursor == nullptr)
	{
		cursor = gcnew Cursor(result, false);
	}

	return cursor;
}

ButtonState NETSDL2::Events::Mouse::GetGlobalMouseState(int% x, int% y)
{
	int xp, yp;
	Uint32 state = SDL_GetGlobalMouseState(&xp, &yp);
	x = xp;
	y = yp;
	return (ButtonState)state;
}

Result<Window^, None^> NETSDL2::Events::Mouse::GetMouseFocus()
{
	Window^ window = Window::GetMouseFocus();
	if(window == nullptr)
	{
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	return window;
}

ButtonState NETSDL2::Events::Mouse::GetMouseState(int% x, int% y)
{
	int xp, yp;
	Uint32 state = SDL_GetMouseState(&xp, &yp);
	x = xp;
	y = yp;
	return (ButtonState)state;
}

bool Mouse::RelativeMouseMode::get()
{
	return SDL_GetRelativeMouseMode() == SDL_TRUE;
}

ButtonState NETSDL2::Events::Mouse::GetRelativeMouseState(int% x, int% y)
{
	int xp, yp;
	Uint32 state = SDL_GetRelativeMouseState(&xp, &yp);
	x = xp;
	y = yp;
	return (ButtonState)state;
}

void NETSDL2::Events::Mouse::SetCursor(Cursor^ cursor)
{
	SDL_SetCursor(cursor == nullptr ? __nullptr : cursor->NativeCursor);
}

Result<None^, int> NETSDL2::Events::Mouse::SetRelativeMouseMode(bool enabled)
{
	int result = SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<CursorState, int> NETSDL2::Events::Mouse::ShowCursor(CursorState toggle)
{
	int result = SDL_ShowCursor((int)toggle);
	if(result < 0)
	{
		return Result<CursorState, int>::MakeFailure(result);
	}

	return (CursorState)result;
}

Result<None^, int> NETSDL2::Events::Mouse::WarpMouseGlobal(int x, int y)
{
	int result = SDL_WarpMouseGlobal(x, y);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Events::Mouse::WarpMouseInWindow(Window^ window, int x, int y)
{
	if(window == nullptr)
		SDL_WarpMouseInWindow(__nullptr, x, y);
	else
		window->WarpMouseInWindow(x, y);
}
