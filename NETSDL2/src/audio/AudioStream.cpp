#include "../../include/audio/AudioStream.h"
#include "../../include/core/Error.h"

using namespace NETSDL2::Core;
using namespace NETSDL2::Audio;

NETSDL2::Audio::AudioStream::AudioStream(AudioFormat srcFormat, Uint8 srcChannels, int srcRate, AudioFormat dstFormat, Uint8 dstChannels, int dstRate)
{
	stream = SDL_NewAudioStream((SDL_AudioFormat)srcFormat, srcChannels, srcRate, (SDL_AudioFormat)dstFormat, dstChannels, dstRate);
	if(stream == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Audio::AudioStream::~AudioStream()
{
	this->!AudioStream();
}

NETSDL2::Audio::AudioStream::!AudioStream()
{
	SDL_FreeAudioStream(stream);
	stream = __nullptr;
}

Result<None^, None^> NETSDL2::Audio::AudioStream::Put(System::IntPtr buf, int len)
{
	int result = SDL_AudioStreamPut(stream, buf.ToPointer(), len);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

int AudioStream::Available::get()
{
	return SDL_AudioStreamAvailable(stream);
}

Result<int, None^> NETSDL2::Audio::AudioStream::Get(System::IntPtr buf, int len)
{
	int result = SDL_AudioStreamGet(stream, buf.ToPointer(), len);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Audio::AudioStream::Flush()
{
	SDL_AudioStreamFlush(stream);
}

void NETSDL2::Audio::AudioStream::Clear()
{
	SDL_AudioStreamClear(stream);
}
