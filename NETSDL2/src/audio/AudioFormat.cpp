#include "../../include/audio/AudioFormat.h"

using namespace NETSDL2::Audio;

Uint16 NETSDL2::Audio::AudioFormatHelper::Bitsize(AudioFormat format)
{
	return SDL_AUDIO_BITSIZE((Uint16)format);
}

bool NETSDL2::Audio::AudioFormatHelper::IsFloat(AudioFormat format)
{
	return SDL_AUDIO_ISFLOAT((Uint16)format) != 0;
}

bool NETSDL2::Audio::AudioFormatHelper::IsBigEndian(AudioFormat format)
{
	return SDL_AUDIO_ISBIGENDIAN((Uint16)format) != 0;
}

bool NETSDL2::Audio::AudioFormatHelper::IsSigned(AudioFormat format)
{
	return SDL_AUDIO_ISSIGNED((Uint16)format) != 0;
}

bool NETSDL2::Audio::AudioFormatHelper::IsInt(AudioFormat format)
{
	return SDL_AUDIO_ISINT((Uint16)format);
}

bool NETSDL2::Audio::AudioFormatHelper::IsLittleEndian(AudioFormat format)
{
	return SDL_AUDIO_ISLITTLEENDIAN((Uint16)format);
}

bool NETSDL2::Audio::AudioFormatHelper::IsUnsigned(AudioFormat format)
{
	return SDL_AUDIO_ISUNSIGNED((Uint16)format);
}
