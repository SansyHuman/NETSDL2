#include "../../include/audio/Audio.h"
#include "../../include/io/RWops.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Audio;
using namespace NETSDL2::IO;
using namespace NETSDL2::Internal;

Result<None^, int> NETSDL2::Audio::Audio::Init(System::String^ driverName)
{
	StringMarshal context;

	int result = SDL_AudioInit(context.ManagedToUTF8Native(driverName));
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Audio::Audio::Quit()
{
	SDL_AudioQuit();
}

Result<int, int> NETSDL2::Audio::Audio::BuildAudioCVT(AudioCVT% cvt, AudioFormat srcFormat, Uint8 srcChannels, int srcRate, AudioFormat dstFormat, Uint8 dstChannels, int dstRate)
{
	pin_ptr<AudioCVT> pCvt = &cvt;
	int result = SDL_BuildAudioCVT((SDL_AudioCVT*)pCvt, (SDL_AudioFormat)srcFormat, srcChannels, srcRate, (SDL_AudioFormat)dstFormat, dstChannels, dstRate);
	pCvt = nullptr;

	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

void NETSDL2::Audio::Audio::ClearQueuedAudio(SDL_AudioDeviceID dev)
{
	SDL_ClearQueuedAudio(dev);
}

void NETSDL2::Audio::Audio::CloseAudio()
{
	SDL_CloseAudio();
}

void NETSDL2::Audio::Audio::CloseAudioDevice(SDL_AudioDeviceID dev)
{
	SDL_CloseAudioDevice(dev);
}

Result<None^, int> NETSDL2::Audio::Audio::ConvertAudio(AudioCVT% cvt)
{
	pin_ptr<AudioCVT> pCvt = &cvt;
	int result = SDL_ConvertAudio((SDL_AudioCVT*)pCvt);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Uint32 NETSDL2::Audio::Audio::DequeueAudio(SDL_AudioDeviceID dev, System::IntPtr data, Uint32 len)
{
	return SDL_DequeueAudio(dev, data.ToPointer(), len);
}

void NETSDL2::Audio::Audio::FreeWAV(Uint8* audioBuf)
{
	SDL_FreeWAV(audioBuf);
}

Result<System::String^, None^> NETSDL2::Audio::Audio::GetAudioDeviceName(int index, bool iscapture)
{
	const char* name = SDL_GetAudioDeviceName(index, iscapture ? 1 : 0);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<None^, int> NETSDL2::Audio::Audio::GetAudioDeviceSpec(int index, bool iscapture, AudioSpec% spec)
{
	pin_ptr<AudioSpec> pSpec = &spec;
	int result = SDL_GetAudioDeviceSpec(index, iscapture ? 1 : 0, (SDL_AudioSpec*)pSpec);
	pSpec = nullptr;

	if(result != 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Audio::Audio::GetDefaultAudioInfo(System::String^% name, AudioSpec% spec, bool iscapture)
{
	char* pName = __nullptr;

	try
	{
		pin_ptr<AudioSpec> pSpec = &spec;
		int result = SDL_GetDefaultAudioInfo(&pName, (SDL_AudioSpec*)pSpec, iscapture ? 1 : 0);
		pSpec = nullptr;

		if(result != 0)
		{
			return Result<None^, int>::MakeFailure(result);
		}

		name = StringMarshal::UTF8NativeToManaged(pName);

		return None::Value;
	}
	finally
	{
		if(pName != __nullptr)
		{
			SDL_free(pName);
		}
	}
}

AudioStatus NETSDL2::Audio::Audio::GetAudioDeviceStatus(SDL_AudioDeviceID dev)
{
	return (AudioStatus)SDL_GetAudioDeviceStatus(dev);
}

Result<System::String^, None^> NETSDL2::Audio::Audio::GetAudioDriver(int index)
{
	const char* name = SDL_GetAudioDriver(index);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

AudioStatus NETSDL2::Audio::Audio::GetAudioStatus()
{
	return (AudioStatus)SDL_GetAudioStatus();
}

Result<System::String^, None^> NETSDL2::Audio::Audio::GetCurrentAudioDriver()
{
	const char* name = SDL_GetCurrentAudioDriver();
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<int, None^> NETSDL2::Audio::Audio::GetNumAudioDevices(bool iscapture)
{
	int result = SDL_GetNumAudioDevices(iscapture ? 1 : 0);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

int NETSDL2::Audio::Audio::GetNumAudioDrivers()
{
	return SDL_GetNumAudioDrivers();
}

Uint32 NETSDL2::Audio::Audio::GetQueuedAudioSize(SDL_AudioDeviceID dev)
{
	return SDL_GetQueuedAudioSize(dev);
}

Result<None^, None^> NETSDL2::Audio::Audio::LoadWAV(System::String^ file, AudioSpec% spec, Uint8*% audioBuf, Uint32% audioLen)
{
	StringMarshal context;

	pin_ptr<AudioSpec> pSpec = &spec;
	Uint8* buf = __nullptr;
	Uint32 len = 0;

	SDL_AudioSpec* result = SDL_LoadWAV(context.ManagedToUTF8Native(file), (SDL_AudioSpec*)pSpec, &buf, &len);
	pSpec = nullptr;

	if(result == __nullptr)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	audioBuf = buf;
	audioLen = len;

	return None::Value;
}

Result<None^, None^> NETSDL2::Audio::Audio::LoadWAV(RWops^ src, bool freesrc, AudioSpec% spec, Uint8*% audioBuf, Uint32% audioLen)
{
	pin_ptr<AudioSpec> pSpec = &spec;
	Uint8* buf = __nullptr;
	Uint32 len = 0;

	SDL_AudioSpec* result = SDL_LoadWAV_RW(src->NativeOps, freesrc ? 1 : 0, (SDL_AudioSpec*)pSpec, &buf, &len);
	pSpec = nullptr;

	if(freesrc)
	{
		delete src;
	}

	if(result == __nullptr)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	audioBuf = buf;
	audioLen = len;

	return None::Value;
}

void NETSDL2::Audio::Audio::LockAudio()
{
	SDL_LockAudio();
}

void NETSDL2::Audio::Audio::LockAudioDevice(SDL_AudioDeviceID dev)
{
	SDL_LockAudioDevice(dev);
}

void NETSDL2::Audio::Audio::MixAudio(Uint8* dst, Uint8* src, Uint32 len, int volume)
{
	SDL_MixAudio(dst, src, len, volume);
}

void NETSDL2::Audio::Audio::MixAudioFormat(Uint8* dst, Uint8* src, AudioFormat format, Uint32 len, int volume)
{
	SDL_MixAudioFormat(dst, src, (SDL_AudioFormat)format, len, volume);
}

Result<None^, int> NETSDL2::Audio::Audio::OpenAudio(AudioSpec% desired, AudioSpec* obtained)
{
	pin_ptr<AudioSpec> pDesired = &desired;
	int result = SDL_OpenAudio((SDL_AudioSpec*)pDesired, (SDL_AudioSpec*)obtained);
	pDesired = nullptr;

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<SDL_AudioDeviceID, None^> NETSDL2::Audio::Audio::OpenAudioDevice(System::String^ device, bool iscapture, AudioSpec% desired, AudioSpec% obtained, AudioOpenFlags allowedChanges)
{
	StringMarshal context;

	pin_ptr<AudioSpec> pDesired = &desired;
	pin_ptr<AudioSpec> pObtained = &obtained;
	const char* pDevice = device == nullptr ? __nullptr : context.ManagedToUTF8Native(device);
	SDL_AudioDeviceID result = SDL_OpenAudioDevice(pDevice, iscapture ? 1 : 0, (SDL_AudioSpec*)pDesired, (SDL_AudioSpec*)pObtained, (int)allowedChanges);
	pDesired = nullptr;
	pObtained = nullptr;

	if(result == 0)
	{
		return Result<SDL_AudioDeviceID, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Audio::Audio::PauseAudio(bool pause)
{
	SDL_PauseAudio(pause ? 1 : 0);
}

void NETSDL2::Audio::Audio::PauseAudioDevice(SDL_AudioDeviceID dev, bool pause)
{
	SDL_PauseAudioDevice(dev, pause ? 1 : 0);
}

Result<None^, int> NETSDL2::Audio::Audio::QueueAudio(SDL_AudioDeviceID dev, System::IntPtr data, Uint32 len)
{
	int result = SDL_QueueAudio(dev, data.ToPointer(), len);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

void NETSDL2::Audio::Audio::UnlockAudio()
{
	SDL_UnlockAudio();
}

void NETSDL2::Audio::Audio::UnlockAudioDevice(SDL_AudioDeviceID dev)
{
	SDL_UnlockAudioDevice(dev);
}
