#include "../include/Music.h"

using namespace NETSDL2::Audio;
using namespace NETSDL2::Internal;

Mix_Music* Music::NativeMusic::get()
{
	return music;
}

NETSDL2::Audio::Music::Music(System::String^ file)
{
	StringMarshal context;
	music = Mix_LoadMUS(context.ManagedToUTF8Native(file));
	if(music == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Audio::Music::Music(RWops^ src, bool freesrc)
{
	music = Mix_LoadMUS_RW(src->NativeOps, freesrc ? 1 : 0);
	if(freesrc)
	{
		delete src;
	}

	if(music == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Audio::Music::Music(RWops^ src, MusicType type, bool freesrc)
{
	music = Mix_LoadMUSType_RW(src->NativeOps, (Mix_MusicType)type, freesrc ? 1 : 0);
	if(freesrc)
	{
		delete src;
	}

	if(music == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Audio::Music::~Music()
{
	this->!Music();
}

NETSDL2::Audio::Music::!Music()
{
	Mix_FreeMusic(music);
	music = __nullptr;
}

System::String^ Music::AlbumTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicAlbumTag(music));
}

System::String^ Music::ArtistTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicArtistTag(music));
}

System::String^ Music::CopyrightTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicCopyrightTag(music));
}

Result<double, None^> NETSDL2::Audio::Music::GetLoopEndTime()
{
	double result = Mix_GetMusicLoopEndTime(music);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<double, None^> NETSDL2::Audio::Music::GetLoopLengthTime()
{
	double result = Mix_GetMusicLoopLengthTime(music);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;

}

Result<double, None^> NETSDL2::Audio::Music::GetLoopStartTime()
{
	double result = Mix_GetMusicLoopStartTime(music);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<double, None^> NETSDL2::Audio::Music::GetPosition()
{
	double result = Mix_GetMusicPosition(music);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

System::String^ Music::Title::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicTitle(music));
}

System::String^ Music::TitleTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicTitleTag(music));
}

MusicType Music::Type::get()
{
	return (MusicType)Mix_GetMusicType(music);
}

int Music::Volume::get()
{
	return Mix_GetMusicVolume(music);
}

Result<double, None^> NETSDL2::Audio::Music::Duration()
{
	double result = Mix_MusicDuration(music);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}
