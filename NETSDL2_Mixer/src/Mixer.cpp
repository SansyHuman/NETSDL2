#include "../include/Mixer.h"
#include "../include/Chunk.h"
#include "../include/Music.h"

using namespace NETSDL2::Audio;
using namespace NETSDL2::Internal;

MixerInitFlags NETSDL2::Audio::Mixer::Init(MixerInitFlags flags)
{
	return (MixerInitFlags)Mix_Init((int)flags);
}

int NETSDL2::Audio::Mixer::AllocateChannels(int numchans)
{
	return Mix_AllocateChannels(numchans);
}

void NETSDL2::Audio::Mixer::ChannelFinished(void (SDLCALL* channelFinished)(int channel))
{
	Mix_ChannelFinished(channelFinished);
}

void NETSDL2::Audio::Mixer::CloseAudio()
{
	Mix_CloseAudio();
}

Result<int, None^> NETSDL2::Audio::Mixer::EachSoundFont(int (SDLCALL* function)(const char*, void*), System::IntPtr data)
{
	int result = Mix_EachSoundFont(function, data.ToPointer());
	if(result == 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

int NETSDL2::Audio::Mixer::ExpireChannel(int channel, int ticks)
{
	return Mix_ExpireChannel(channel, ticks);
}

Result<int, None^> NETSDL2::Audio::Mixer::FadeInChannel(int channel, Chunk^ chunk, int loops, int ms)
{
	int result = Mix_FadeInChannel(channel, chunk->NativeChunk, loops, ms);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Audio::Mixer::FadeInChannelTimed(int channel, Chunk^ chunk, int loops, int ms, int ticks)
{
	int result = Mix_FadeInChannelTimed(channel, chunk->NativeChunk, loops, ms, ticks);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Audio::Mixer::FadeInMusic(Music^ music, int loops, int ms)
{
	int result = Mix_FadeInMusic(music->NativeMusic, loops, ms);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::FadeInMusicPos(Music^ music, int loops, int ms, double position)
{
	int result = Mix_FadeInMusicPos(music->NativeMusic, loops, ms, position);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::FadeOutChannel(int which, int ms)
{
	int result = Mix_FadeOutChannel(which, ms);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int NETSDL2::Audio::Mixer::FadeOutGroup(int tag, int ms)
{
	return Mix_FadeOutGroup(tag, ms);
}

Result<None^, None^> NETSDL2::Audio::Mixer::FadeOutMusic(int ms)
{
	int result = Mix_FadeOutMusic(ms);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Fading NETSDL2::Audio::Mixer::FadingChannel(int which)
{
	return (Fading)Mix_FadingChannel(which);
}

Fading Mixer::FadingMusic::get()
{
	return (Fading)Mix_FadingMusic();
}

Result<Chunk^, None^> NETSDL2::Audio::Mixer::GetChunk(int channel)
{
	Mix_Chunk* chunk = Mix_GetChunk(channel);
	if(chunk == __nullptr)
	{
		return Result<Chunk^, None^>::MakeFailure(None::Value);
	}

	Chunk^ ch = Chunk::GetChunkFromNative(chunk);
	if(ch == nullptr)
	{
		return Result<Chunk^, None^>::MakeFailure(None::Value);
	}

	return ch;
}

Result<System::String^, None^> NETSDL2::Audio::Mixer::GetChunkDecoder(int index)
{
	const char* name = Mix_GetChunkDecoder(index);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

System::String^ Mixer::CurrentMusicAlbumTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicAlbumTag(__nullptr));
}

System::String^ Mixer::CurrentMusicArtistTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicArtistTag(__nullptr));
}

System::String^ Mixer::CurrentMusicCopyrightTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicCopyrightTag(__nullptr));
}

Result<System::String^, None^> NETSDL2::Audio::Mixer::GetMusicDecoder(int index)
{
	const char* name = Mix_GetMusicDecoder(index);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<System::IntPtr, None^> NETSDL2::Audio::Mixer::GetMusicHookData()
{
	void* result = Mix_GetMusicHookData();
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<double, None^> NETSDL2::Audio::Mixer::GetCurrentMusicLoopEndTime()
{
	double result = Mix_GetMusicLoopEndTime(__nullptr);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<double, None^> NETSDL2::Audio::Mixer::GetCurrentMusicLoopLengthTime()
{
	double result = Mix_GetMusicLoopLengthTime(__nullptr);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<double, None^> NETSDL2::Audio::Mixer::GetCurrentMusicLoopStartTime()
{
	double result = Mix_GetMusicLoopStartTime(__nullptr);
	if(result < 0.0)
	{
		return Result<double, None^>::MakeFailure(None::Value);
	}

	return result;
}

System::String^ Mixer::CurrentMusicTitle::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicTitle(__nullptr));
}

System::String^ Mixer::CurrentMusicTitleTag::get()
{
	return StringMarshal::UTF8NativeToManaged(Mix_GetMusicTitleTag(__nullptr));
}

MusicType Mixer::CurrentMusicType::get()
{
	return (MusicType)Mix_GetMusicType(__nullptr);
}

int Mixer::NumChunkDecoders::get()
{
	return Mix_GetNumChunkDecoders();
}

int Mixer::NumMusicDecoders::get()
{
	return Mix_GetNumMusicDecoders();
}

Result<System::String^, None^> NETSDL2::Audio::Mixer::GetSoundFonts()
{
	const char* result = Mix_GetSoundFonts();
	if(result == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

int Mixer::SynchroValue::get()
{
	return Mix_GetSynchroValue();
}

void Mixer::SynchroValue::set(int value)
{
	Mix_SetSynchroValue(value);
}

Result<System::String^, None^> NETSDL2::Audio::Mixer::GetTimidityCfg()
{
	const char* result = Mix_GetTimidityCfg();
	if(result == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

Result<int, None^> NETSDL2::Audio::Mixer::GroupAvailable(int tag)
{
	int result = Mix_GroupAvailable(tag);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Audio::Mixer::GroupChannel(int which, int tag)
{
	int result = Mix_GroupChannel(which, tag);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::GroupChannels(int from, int to, int tag)
{
	int result = Mix_GroupChannels(from, to, tag);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int NETSDL2::Audio::Mixer::GroupCount(int tag)
{
	return Mix_GroupCount(tag);
}

Result<int, None^> NETSDL2::Audio::Mixer::GroupNewer(int tag)
{
	int result = Mix_GroupNewer(tag);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Audio::Mixer::GroupOldest(int tag)
{
	int result = Mix_GroupOldest(tag);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Audio::Mixer::HaltChannel(int channel)
{
	int result = Mix_HaltChannel(channel);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

void NETSDL2::Audio::Mixer::HaltGroup(int tag)
{
	Mix_HaltGroup(tag);
}

void NETSDL2::Audio::Mixer::HaltMusic()
{
	Mix_HaltMusic();
}

bool NETSDL2::Audio::Mixer::HasChunkDecoder(System::String^ name)
{
	StringMarshal context;
	return Mix_HasChunkDecoder(context.ManagedToUTF8Native(name)) == SDL_TRUE;
}

bool NETSDL2::Audio::Mixer::HasMusicDecoder(System::String^ name)
{
	StringMarshal context;
	return Mix_HasMusicDecoder(context.ManagedToUTF8Native(name)) == SDL_TRUE;
}

void NETSDL2::Audio::Mixer::HookMusic(void (SDLCALL* mixFunc)(void* udata, Uint8* stream, int len), System::IntPtr arg)
{
	Mix_HookMusic(mixFunc, arg.ToPointer());
}

void NETSDL2::Audio::Mixer::HookMusicFinished(void (SDLCALL* musicFinished)(void))
{
	Mix_HookMusicFinished(musicFinished);
}

SDLVersion Mixer::LinkedVersion::get()
{
	return *((SDLVersion*)Mix_Linked_Version());
}

SDLVersion Mixer::Version::get()
{
	SDL_version version;
	SDL_MIXER_VERSION(&version);
	return *((SDLVersion*)&version);
}

int NETSDL2::Audio::Mixer::MasterVolume(int volume)
{
	return Mix_MasterVolume(volume);
}

Result<None^, None^> NETSDL2::Audio::Mixer::ModMusicJumpToOrder(int order)
{
	int result = Mix_ModMusicJumpToOrder(order);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::OpenAudio(int frequency, AudioFormat format, int channels, int chunksize)
{
	int result = Mix_OpenAudio(frequency, (Uint16)format, channels, chunksize);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::OpenAudioDevice(int frequency, AudioFormat format, int channels, int chunksize, System::String^ device, AudioOpenFlags allowedChanges)
{
	StringMarshal context;
	int result = Mix_OpenAudioDevice(frequency, (Uint16)format, channels, chunksize, device == nullptr ? __nullptr : context.ManagedToUTF8Native(device), (int)allowedChanges);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

void NETSDL2::Audio::Mixer::Pause(int channel)
{
	Mix_Pause(channel);
}

int NETSDL2::Audio::Mixer::Paused(int channel)
{
	return Mix_Paused(channel);
}

bool Mixer::PausedMusic::get()
{
	return Mix_PausedMusic() == 1;
}

Result<int, None^> NETSDL2::Audio::Mixer::PlayChannel(int channel, Chunk^ chunk, int loops)
{
	int result = Mix_PlayChannel(channel, chunk->NativeChunk, loops);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Audio::Mixer::PlayChannelTimed(int channel, Chunk^ chunk, int loops, int ticks)
{
	int result = Mix_PlayChannelTimed(channel, chunk->NativeChunk, loops, ticks);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

int NETSDL2::Audio::Mixer::Playing(int channel)
{
	return Mix_Playing(channel);
}

bool Mixer::PlayingMusic::get()
{
	return Mix_PlayingMusic() != 0;
}

Result<None^, None^> NETSDL2::Audio::Mixer::PlayMusic(Music^ music, int loops)
{
	int result = Mix_PlayMusic(music->NativeMusic, loops);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::QuerySpec(int% frequency, AudioFormat% format, int% channels)
{
	int fr = 0;
	Uint16 fm = 0;
	int ch = 0;

	int result = Mix_QuerySpec(&fr, &fm, &ch);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	frequency = fr;
	format = (AudioFormat)fm;
	channels = ch;
	return None::Value;
}

void NETSDL2::Audio::Mixer::Quit()
{
	Mix_Quit();
}

Result<None^, None^> NETSDL2::Audio::Mixer::RegisterEffect(int chan, Mix_EffectFunc_t f, Mix_EffectDone_t d, System::IntPtr arg)
{
	int result = Mix_RegisterEffect(chan, f, d, arg.ToPointer());
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int NETSDL2::Audio::Mixer::ReserveChannels(int num)
{
	return Mix_ReserveChannels(num);
}

void NETSDL2::Audio::Mixer::Resume(int channel)
{
	Mix_Resume(channel);
}

void NETSDL2::Audio::Mixer::ResumeMusic()
{
	Mix_ResumeMusic();
}

void NETSDL2::Audio::Mixer::RewindMusic()
{
	Mix_RewindMusic();
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetDistance(int channel, Uint8 distance)
{
	int result = Mix_SetDistance(channel, distance);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetMusicCMD(System::String^ command)
{
	StringMarshal context;
	int result = Mix_SetMusicCMD(context.ManagedToUTF8Native(command));
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetMusicPosition(double position)
{
	int result = Mix_SetMusicPosition(position);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetPanning(int channel, Uint8 left, Uint8 right)
{
	int result = Mix_SetPanning(channel, left, right);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetPosition(int channel, Sint16 angle, Uint8 distance)
{
	int result = Mix_SetPosition(channel, angle, distance);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

void NETSDL2::Audio::Mixer::SetPostMix(void (SDLCALL* mixFunc)(void* udata, Uint8* stream, int len), System::IntPtr arg)
{
	Mix_SetPostMix(mixFunc, arg.ToPointer());
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetReverseStereo(int channel, bool flip)
{
	int result = Mix_SetReverseStereo(channel, flip ? 1 : 0);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetSoundFonts(System::String^ paths)
{
	StringMarshal context;
	int result = Mix_SetSoundFonts(context.ManagedToUTF8Native(paths));
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::SetTimidityCfg(System::String^ path)
{
	StringMarshal context;
	int result = Mix_SetTimidityCfg(context.ManagedToUTF8Native(path));
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::UnregisterAllEffects(int channel)
{
	int result = Mix_UnregisterAllEffects(channel);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Mixer::UnregisterEffect(int channel, Mix_EffectFunc_t f)
{
	int result = Mix_UnregisterEffect(channel, f);
	if(result == 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int NETSDL2::Audio::Mixer::Volume(int channel, int volume)
{
	return Mix_Volume(channel, volume);
}

int NETSDL2::Audio::Mixer::VolumeMusic(int volume)
{
	return Mix_VolumeMusic(volume);
}
