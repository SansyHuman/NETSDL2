#include "../../include/events/Keyboard.h"

#include "../../include/video/Window.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Internal;

NETSDL2::Events::Keyboard::KeyboardState::KeyboardState(Uint8* states, int numkeys)
	: states(states), numkeys(numkeys)
{
	
}

Uint8 Keyboard::KeyboardState::default::get(Scancode index)
{
	int ind = (int)index;
	if(ind < 0 || ind >= numkeys)
		return 0;

	return states[ind];
}

int Keyboard::KeyboardState::NumKeys::get()
{
	return numkeys;
}

Result<Window^, None^> NETSDL2::Events::Keyboard::GetKeyboardFocus()
{
	Window^ window = Window::GetKeyboardFocus();
	if(window == nullptr)
	{
		return Result<Window^, None^>::MakeFailure(None::Value);
	}

	return window;
}

Uint8* NETSDL2::Events::Keyboard::GetKeyboardState(int% numkeys)
{
	int num = 0;
	const Uint8* state = SDL_GetKeyboardState(&num);

	numkeys = num;
	return const_cast<Uint8*>(state);
}

Keyboard::KeyboardState NETSDL2::Events::Keyboard::GetKeyboardState()
{
	int num = 0;
	const Uint8* state = SDL_GetKeyboardState(&num);

	return Keyboard::KeyboardState(const_cast<Uint8*>(state), num);
}

void NETSDL2::Events::Keyboard::ResetKeyboard()
{
	SDL_ResetKeyboard();
}

Keycode NETSDL2::Events::Keyboard::GetKeyFromName(System::String^ name)
{
	StringMarshal context;

	return (Keycode)SDL_GetKeyFromName(context.ManagedToUTF8Native(name));
}

Keycode NETSDL2::Events::Keyboard::GetKeyFromScancode(Scancode scancode)
{
	return (Keycode)SDL_GetKeyFromScancode((SDL_Scancode)scancode);
}

System::String^ NETSDL2::Events::Keyboard::GetKeyName(Keycode key)
{
	return StringMarshal::UTF8NativeToManaged(SDL_GetKeyName((SDL_Keycode)key));
}

Keymod NETSDL2::Events::Keyboard::GetModState()
{
	return (Keymod)SDL_GetModState();
}

Scancode NETSDL2::Events::Keyboard::GetScancodeFromKey(Keycode key)
{
	return (Scancode)SDL_GetScancodeFromKey((SDL_Keycode)key);
}

Scancode NETSDL2::Events::Keyboard::GetScancodeFromName(System::String^ name)
{
	StringMarshal context;

	return (Scancode)SDL_GetScancodeFromName(context.ManagedToUTF8Native(name));
}

System::String^ NETSDL2::Events::Keyboard::GetScancodeName(Scancode scancode)
{
	return StringMarshal::UTF8NativeToManaged(SDL_GetScancodeName((SDL_Scancode)scancode));
}

bool Keyboard::HasScreenKeyboardSupport::get()
{
	return SDL_HasScreenKeyboardSupport() == SDL_TRUE;
}

bool NETSDL2::Events::Keyboard::IsScreenKeyboardShown(Window^ window)
{
	return window->IsScreenKeyboardShown();
}

bool Keyboard::IsTextInputActive::get()
{
	return SDL_IsTextInputActive() == SDL_TRUE;
}

void NETSDL2::Events::Keyboard::SetModState(Keymod modstate)
{
	SDL_SetModState((SDL_Keymod)modstate);
}

void NETSDL2::Events::Keyboard::SetTextInputRect(NETSDL2::Video::Rect rect)
{
	SDL_SetTextInputRect((const SDL_Rect*)&rect);
}

void NETSDL2::Events::Keyboard::StartTextInput()
{
	SDL_StartTextInput();
}

void NETSDL2::Events::Keyboard::StopTextInput()
{
	SDL_StopTextInput();
}

void NETSDL2::Events::Keyboard::ClearComposition()
{
	SDL_ClearComposition();
}

bool Keyboard::IsTextInputShown::get()
{
	return SDL_IsTextInputShown() == SDL_TRUE;
}
