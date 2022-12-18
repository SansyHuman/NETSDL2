#include "../include/TTF.h"

using namespace NETSDL2::Text;

void NETSDL2::Text::TTF::ByteSwappedUnicode(bool swapped)
{
	TTF_ByteSwappedUNICODE(swapped ? SDL_TRUE : SDL_FALSE);
}

void NETSDL2::Text::TTF::GetFreeTypeVersion(int% major, int% minor, int% patch)
{
	int ma = 0, mi = 0, pa = 0;
	TTF_GetFreeTypeVersion(&ma, &mi, &pa);
	major = ma;
	minor = mi;
	patch = pa;
}

void NETSDL2::Text::TTF::GetHarfBuzzVersion(int% major, int% minor, int% patch)
{
	int ma = 0, mi = 0, pa = 0;
	TTF_GetHarfBuzzVersion(&ma, &mi, &pa);
	major = ma;
	minor = mi;
	patch = pa;
}

Result<None^, None^> NETSDL2::Text::TTF::Init()
{
	int result = TTF_Init();
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

SDLVersion TTF::LinkedVersion::get()
{
	return *((const SDLVersion*)TTF_Linked_Version());
}

SDLVersion TTF::Version::get()
{
	SDL_version version = {};
	SDL_TTF_VERSION(&version);
	return *((SDLVersion*)&version);
}

void NETSDL2::Text::TTF::Quit()
{
	TTF_Quit();
}

Result<None^, None^> NETSDL2::Text::TTF::SetDirection(TTFDirection direction)
{
	int result = TTF_SetDirection((int)direction);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Text::TTF::SetScript(int script)
{
	int result = TTF_SetScript(script);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int NETSDL2::Text::TTF::WasInit::get()
{
	return TTF_WasInit();
}
