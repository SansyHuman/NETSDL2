#include "../../include/video/Clipboard.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Internal;

using namespace NETSDL2::Video;

System::String^ NETSDL2::Video::Clipboard::GetClipboardText()
{
	char* text = SDL_GetClipboardText();
	System::String^ result = StringMarshal::UTF8NativeToManaged(text);
	SDL_free(text);

	return result;
}

bool Clipboard::HasClipboardText::get()
{
	return SDL_HasClipboardText() == SDL_TRUE;
}

Result<None^, int> NETSDL2::Video::Clipboard::SetClipboardText(System::String^ text)
{
	StringMarshal context;
	int result = SDL_SetClipboardText(context.ManagedToUTF8Native(text));
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}
