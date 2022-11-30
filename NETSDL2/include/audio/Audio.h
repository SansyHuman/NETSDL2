#pragma once

#include <SDL.h>

#include "AudioFormat.h"
#include "AudioCVT.h"
#include "AudioStatus.h"
#include "AudioSpec.h"

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace IO
	{
		ref class RWops;
	}

	namespace Audio
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::IO;

		/// <summary>
		/// Flags used when opening audio device.
		/// </summary>
		[System::Flags]
		public enum class AudioOpenFlags : int
		{
			None = 0,
			AllowFrequencyChange = SDL_AUDIO_ALLOW_FREQUENCY_CHANGE,
			AllowFormatChange = SDL_AUDIO_ALLOW_FORMAT_CHANGE,
			AllowChannelsChange = SDL_AUDIO_ALLOW_CHANNELS_CHANGE,
			AllowSamplesChange = SDL_AUDIO_ALLOW_SAMPLES_CHANGE,
			AllowAnyChange = SDL_AUDIO_ALLOW_ANY_CHANGE,
		};

		/// <summary>
		/// Functions for handling audio devices and audio input/output.
		/// </summary>
		public ref struct Audio abstract sealed
		{
		public:
			/// <summary>
			/// Use this function to initialize a particular audio driver.
			/// </summary>
			/// <param name="driverName">The name of the desired audio driver.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> Init(System::String^ driverName);

			/// <summary>
			/// Use this function to shut down audio if you initialized it with
			/// <see cref="Audio::Init"/>.
			/// </summary>
			static void Quit();

			/// <summary>
			/// Initialize an AudioCVT structure for conversion.
			/// </summary>
			/// <param name="cvt">An AudioCVT structure filled in with audio conversion
			/// information.</param>
			/// <param name="srcFormat">The source format of the audio data.</param>
			/// <param name="srcChannels">The number of channels in the source.</param>
			/// <param name="srcRate">The frequency (sample-frames-per-second) of the
			/// source.</param>
			/// <param name="dstFormat">The destination format of the audio data.</param>
			/// <param name="dstChannels">The number of channels in the destination.
			/// </param>
			/// <param name="dstRate">The frequency (sample-frames-per-second) of the
			/// destination.</param>
			/// <returns>1 if the audio filter is prepared, 0 if no conversion is needed,
			/// or a negative error code on failure.</returns>
			static Result<int, int> BuildAudioCVT(
				[Out]AudioCVT% cvt,
				AudioFormat srcFormat, Uint8 srcChannels, int srcRate,
				AudioFormat dstFormat, Uint8 dstChannels, int dstRate
			);

			/// <summary>
			/// Drop any queued audio data waiting to be sent to the hardware.
			/// </summary>
			/// <param name="dev">The device ID of which to clear the audio queue.</param>
			static void ClearQueuedAudio(SDL_AudioDeviceID dev);

			/// <summary>
			/// This function is a legacy means of closing the audio device.
			/// </summary>
			static void CloseAudio();

			/// <summary>
			/// Use this function to shut down audio processing and close the audio
			/// device.
			/// </summary>
			/// <param name="dev">An audio device previously opened with
			/// <see cref="OpenAudioDevice"/>.</param>
			static void CloseAudioDevice(SDL_AudioDeviceID dev);

			/// <summary>
			/// Convert audio data to a desired audio format.
			/// </summary>
			/// <param name="cvt">A <see cref="AudioCVT"/> structure that was previously
			/// set up by <see cref="BuildAudioCVT"/>.</param>
			/// <returns>None if the conversion was completed successfully or a negative
			/// error code on failure.</returns>
			static Result<None^, int> ConvertAudio([In][IsReadOnly]AudioCVT% cvt);

			/// <summary>
			/// Dequeue more audio on non-callback devices.
			/// </summary>
			/// <param name="dev">The device ID from which we will dequeue audio.</param>
			/// <param name="data">A pointer into where audio data should be copied.
			/// </param>
			/// <param name="len">The number of bytes (not samples!) to which data
			/// points.</param>
			/// <returns>The number of bytes dequeued, which could be less than
			/// requested.</returns>
			static Uint32 DequeueAudio(SDL_AudioDeviceID dev, System::IntPtr data, Uint32 len);

			/// <summary>
			/// Free data previously allocated with <see cref="LoadWAV"/>.
			/// </summary>
			/// <param name="audioBuf">A pointer to the buffer created by
			/// <see cref="LoadWAV"/>.</param>
			static void FreeWAV(Uint8* audioBuf);

			/// <summary>
			/// Get the human-readable name of a specific audio device.
			/// </summary>
			/// <param name="index">The index of the audio device.</param>
			/// <param name="iscapture">true to query the list of recording devices,
			/// false to query the list of output devices.</param>
			/// <returns>The name of the audio device at the requested index, or None on
			/// error.</returns>
			static Result<System::String^, None^> GetAudioDeviceName(int index, bool iscapture);

			/// <summary>
			/// Get the preferred audio format of a specific audio device.
			/// </summary>
			/// <param name="index">The index of the audio device.</param>
			/// <param name="iscapture">true to query the list of recording devices, false to query the list
			/// of output devices.</param>
			/// <param name="spec">The <see cref="AudioSpec"/> to be initialized by this function.</param>
			/// <returns>None on success, nonzero on error.</returns>
			static Result<None^, int> GetAudioDeviceSpec(int index, bool iscapture, [Out]AudioSpec% spec);

			/// <summary>
			/// Get the name and preferred format of the default audio device.
			/// </summary>
			/// <param name="name">The name of the default device.</param>
			/// <param name="spec">The <see cref="AudioSpec"/> to be initialized by this function.</param>
			/// <param name="iscapture">true to query the default recording device, false to query the
			/// default output device.</param>
			/// <returns>None on success, nonzero on error.</returns>
			static Result<None^, int> GetDefaultAudioInfo([Out]System::String^% name, [Out]AudioSpec% spec, bool iscapture);

			/// <summary>
			/// Use this function to get the current audio state of an audio device.
			/// </summary>
			/// <param name="dev">The ID of an audio device previously opened with
			/// <see cref="OpenAudioDevice"/></param>
			/// <returns></returns>
			static AudioStatus GetAudioDeviceStatus(SDL_AudioDeviceID dev);

			/// <summary>
			/// Use this function to get the name of a built in audio driver.
			/// </summary>
			/// <param name="index">The name of the audio driver at the requested index,
			/// or None if an invalid index was specified.</param>
			/// <returns></returns>
			static Result<System::String^, None^> GetAudioDriver(int index);

			/// <summary>
			/// This function is a legacy means of querying the audio device.
			/// </summary>
			/// <returns>The <see cref="AudioStatus"/> of the audio device opened by
			/// <see cref="OpenAudio"/>.</returns>
			static AudioStatus GetAudioStatus();

			/// <summary>
			/// Get the name of the current audio driver.
			/// </summary>
			/// <returns>The name of the current audio driver or None if no driver has
			/// been initialized.</returns>
			static Result<System::String^, None^> GetCurrentAudioDriver();

			/// <summary>
			/// Get the number of built-in audio devices.
			/// </summary>
			/// <param name="iscapture">false to request playback devices, true to
			/// request recording devices.</param>
			/// <returns>The number of available devices exposed by the current driver or
			/// None if an explicit list of devices can't be determined.</returns>
			static Result<int, None^> GetNumAudioDevices(bool iscapture);

			/// <summary>
			/// Use this function to get the number of built-in audio drivers.
			/// </summary>
			/// <returns>The number of built-in audio drivers.</returns>
			static int GetNumAudioDrivers();

			/// <summary>
			/// Get the number of bytes of still-queued audio.
			/// </summary>
			/// <param name="dev">The device ID of which we will query queued audio size.
			/// </param>
			/// <returns>The number of bytes (not samples!) of queued audio.</returns>
			static Uint32 GetQueuedAudioSize(SDL_AudioDeviceID dev);

			/// <summary>
			/// Use this function to load a WAVE from a file.
			/// </summary>
			/// <param name="file">The name of the file to load.</param>
			/// <param name="spec">An <see cref="AudioSpec"/> structure that will be
			/// filled in with the wave file's format details.</param>
			/// <param name="audioBuf">The audio buffer.</param>
			/// <param name="audioLen">The length of the audio buffer in bytes.</param>
			/// <returns>Success or Failure if the .WAV file cannot be opened, uses an
			/// unknown data format, or is corrupt.</returns>
			static Result<None^, None^> LoadWAV(System::String^ file, [Out]AudioSpec% spec, [Out]Uint8*% audioBuf, [Out]Uint32% audioLen);

			/// <summary>
			/// Load the audio data of a WAVE file into memory.
			/// </summary>
			/// <param name="src">The data source for the WAVE data.</param>
			/// <param name="freesrc">If true, SDL will _always_ free the data source.
			/// </param>
			/// <param name="spec">An <see cref="AudioSpec"/> structure that will be
			/// filled in with the wave file's format details.</param>
			/// <param name="audioBuf">The audio buffer.</param>
			/// <param name="audioLen">The length of the audio buffer in bytes.</param>
			/// <returns>Success or Failure if the .WAV file cannot be opened, uses an
			/// unknown data format, or is corrupt.</returns>
			static Result<None^, None^> LoadWAV(RWops^ src, bool freesrc, [Out]AudioSpec% spec, [Out]Uint8*% audioBuf, [Out]Uint32% audioLen);

			/// <summary>
			/// This function is a legacy means of locking the audio device.
			/// </summary>
			static void LockAudio();

			/// <summary>
			/// Use this function to lock out the audio callback function for a
			/// specified device.
			/// </summary>
			/// <param name="dev">The ID of the device to be locked.</param>
			static void LockAudioDevice(SDL_AudioDeviceID dev);

			/// <summary>
			/// This function is a legacy means of mixing audio.
			/// </summary>
			/// <param name="dst">The destination for the mixed audio.</param>
			/// <param name="src">The source audio buffer to be mixed.</param>
			/// <param name="len">The length of the audio buffer in bytes.</param>
			/// <param name="volume">Ranges from 0 - 128.</param>
			static void MixAudio(Uint8* dst, Uint8* src, Uint32 len, int volume);

			/// <summary>
			/// Mix audio data in a specified format.
			/// </summary>
			/// <param name="dst">The destination for the mixed audio.</param>
			/// <param name="src">The source audio buffer to be mixed.</param>
			/// <param name="format">The <see cref="AudioFormat"/> representing the
			/// desired audio format.</param>
			/// <param name="len">The length of the audio buffer in bytes.</param>
			/// <param name="volume">Ranges from 0 - 128.</param>
			static void MixAudioFormat(Uint8* dst, Uint8* src, AudioFormat format, Uint32 len, int volume);

			/// <summary>
			/// This function is a legacy means of opening the audio device.
			/// </summary>
			/// <param name="desired">An <see cref="AudioSpec"/> structure
			/// representing the desired output format.</param>
			/// <param name="obtained">An <see cref="AudioSpec"/> structure filled in
			/// with the actual parameters, or null.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> OpenAudio([In][IsReadOnly]AudioSpec% desired, AudioSpec* obtained);

			/// <summary>
			/// Open a specific audio device.
			/// </summary>
			/// <param name="device">A string reported by
			/// <see cref="GetAudioDeviceName"/> or a driver-specific name as
			/// appropriate. null requests the most reasonable default device.</param>
			/// <param name="iscapture">true to specify a device should be opened for
			/// recording, not playback.</param>
			/// <param name="desired">An <see cref="AudioSpec"/> structure
			/// representing the desired output format.</param>
			/// <param name="obtained">An <see cref="AudioSpec"/> structure filled in
			/// with the actual parameters, or null.</param>
			/// <param name="allowedChanges">None, or one or more flags OR'd
			/// together.</param>
			/// <returns>A valid device ID that is > 0 on success or None on failure.
			/// </returns>
			static Result<SDL_AudioDeviceID, None^> OpenAudioDevice(
				System::String^ device, bool iscapture,
				[In][IsReadOnly]AudioSpec% desired, [Out]AudioSpec% obtained,
				AudioOpenFlags allowedChanges
			);

			/// <summary>
			/// This function is a legacy means of pausing the audio device.
			/// </summary>
			/// <param name="pause">true to pause, false to unpause.</param>
			static void PauseAudio(bool pause);

			/// <summary>
			/// Use this function to pause and unpause audio playback on a specified
			/// device.
			/// </summary>
			/// <param name="dev">A device opened by <see cref="OpenAudioDevice"/>.
			/// </param>
			/// <param name="pause">true to pause, false to unpause.</param>
			static void PauseAudioDevice(SDL_AudioDeviceID dev, bool pause);

			/// <summary>
			/// Queue more audio on non-callback devices.
			/// </summary>
			/// <param name="dev">The device ID to which we will queue audio.</param>
			/// <param name="data">The data to queue to the device for later
			/// playback.</param>
			/// <param name="len">The number of bytes (not samples!) to which data
			/// points.</param>
			/// <returns>None on success or error code on failure.</returns>
			static Result<None^, int> QueueAudio(SDL_AudioDeviceID dev, System::IntPtr data, Uint32 len);

			/// <summary>
			/// This function is a legacy means of unlocking the audio device.
			/// </summary>
			static void UnlockAudio();

			/// <summary>
			/// Use this function to unlock the audio callback function for a
			/// specified device.
			/// </summary>
			/// <param name="dev">The ID of the device to be unlocked.</param>
			static void UnlockAudioDevice(SDL_AudioDeviceID dev);
		};
	}
}