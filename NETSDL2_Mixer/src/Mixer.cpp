#include "../include/Mixer.h"

using namespace NETSDL2::Audio;

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
