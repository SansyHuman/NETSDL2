#include "../../include/system/Locale.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Internal;

Result<array<Locale>^, None^> NETSDL2::Systems::Locale::GetPreferredLocales()
{
	SDL_Locale* locale = __nullptr;

	try
	{
		locale = SDL_GetPreferredLocales();
		if(locale == __nullptr)
		{
			return Result<array<Locale>^, None^>::MakeFailure(None::Value);
		}

		int cnt = 0;
		for(SDL_Locale* curr = locale; curr->language != __nullptr; cnt++, curr++)
		{

		}

		array<Locale>^ locArr = gcnew array<Locale>(cnt);
		for(int i = 0; i < cnt; i++)
		{
			Locale% curr = locArr[i];
			curr.Language = StringMarshal::UTF8NativeToManaged(locale[i].language);
			curr.Country = locale[i].country == __nullptr ? nullptr : StringMarshal::UTF8NativeToManaged(locale[i].country);
		}

		return locArr;
	}
	finally
	{
		if(locale != __nullptr)
		{
			SDL_free(locale);
		}
	}
}

System::String^ NETSDL2::Systems::Locale::ToString()
{
	if(Country == nullptr)
	{
		return Language;
	}

	return System::String::Format("{0}_{1}", Language, Country);
}
