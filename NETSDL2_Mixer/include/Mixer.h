#pragma once

#include <SDL_mixer.h>

#include "InitFlags.h"
#include "Fading.h"
#include "MusicType.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		using namespace NETSDL2::Core;

		ref class Chunk;
		ref class Music;

		/// <summary>
		/// NETSDL2_Mmage global functions.
		/// </summary>
		public ref struct Mixer abstract sealed
		{
		public:
			/// <summary>
			/// Maximum volume.
			/// </summary>
			literal int MaxVolume = MIX_MAX_VOLUME;

			literal int ChannelPost = MIX_CHANNEL_POST;

			/// <summary>
			/// Initialize SDL_mixer.
			/// </summary>
			/// <param name="flags">Initialization flags, OR'd together.</param>
			/// <returns>All currently initialized flags.</returns>
			static MixerInitFlags Init(MixerInitFlags flags);

			/// <summary>
			/// Dynamically change the number of channels managed by the mixer.
			/// </summary>
			/// <param name="numchans">The new number of channels, or less than 0 to
			/// query current channel count.</param>
			/// <returns>The new number of allocated channels.</returns>
			static int AllocateChannels(int numchans);

			/// <summary>
			/// Set a callback that runs when a channel has finished playing.
			/// </summary>
			/// <param name="channelFinished">The callback function to become the new
			/// notification mechanism.</param>
			static void ChannelFinished(void (SDLCALL* channelFinished)(int channel));

			/// <summary>
			/// Close the mixer, halting all playing audio.
			/// </summary>
			static void CloseAudio();

			/// <summary>
			/// Iterate SoundFonts paths to use by supported MIDI backends.
			/// </summary>
			/// <param name="function">The callback function to call once per path.
			/// </param>
			/// <param name="data">A pointer to pass to the callback for its own personal
			/// use.</param>
			/// <returns>Non-zero if callback ever returned non-zero, None on error or
			/// the callback never returned non-zero.</returns>
			static Result<int, None^> EachSoundFont(int (SDLCALL* function)(const char*, void*), System::IntPtr data);

			/// <summary>
			/// Change the expiration delay for a particular channel.
			/// </summary>
			/// <param name="channel">The channel to change the expiration time on.
			/// </param>
			/// <param name="ticks">Number of milliseconds from now to let channel play
			/// before halting, -1 to not halt.</param>
			/// <returns>The number of channels that changed expirations.</returns>
			static int ExpireChannel(int channel, int ticks);

			/// <summary>
			/// Play an audio chunk on a specific channel, fading in the audio.
			/// </summary>
			/// <param name="channel">The channel on which to play the new chunk, or -1
			/// to find any available.</param>
			/// <param name="chunk">The new chunk to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <param name="ms">The number of milliseconds to spend fading in.</param>
			/// <returns>Which channel was used to play the sound, or None if sound
			/// could not be played.</returns>
			static Result<int, None^> FadeInChannel(int channel, Chunk^ chunk, int loops, int ms);

			/// <summary>
			/// Play an audio chunk on a specific channel, fading in the audio, for a
			/// maximum time.
			/// </summary>
			/// <param name="channel">The channel on which to play the new chunk, or -1
			/// to find any available.</param>
			/// <param name="chunk">The new chunk to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <param name="ms">The number of milliseconds to spend fading in.</param>
			/// <param name="ticks">The maximum number of milliseconds of this chunk to
			/// mix for playback.</param>
			/// <returns>Which channel was used to play the sound, or None if sound
			/// could not be played.</returns>
			static Result<int, None^> FadeInChannelTimed(int channel, Chunk^ chunk, int loops, int ms, int ticks);

			/// <summary>
			/// Play a new music object, fading in the audio.
			/// </summary>
			/// <param name="music">The new music object to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <param name="ms">The number of milliseconds to spend fading in.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> FadeInMusic(Music^ music, int loops, int ms);

			/// <summary>
			/// Play a new music object, fading in the audio, from a starting position.
			/// </summary>
			/// <param name="music">The new music object to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <param name="ms">The number of milliseconds to spend fading in.</param>
			/// <param name="position">The start position within the music, in seconds,
			/// where playback should start.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> FadeInMusicPos(Music^ music, int loops, int ms, double position);

			/// <summary>
			/// Halt a channel after fading it out for a specified time.
			/// </summary>
			/// <param name="which">The channel to fade out.</param>
			/// <param name="ms">Number of milliseconds to fade before halting the
			/// channel.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> FadeOutChannel(int which, int ms);

			/// <summary>
			/// Halt a playing group of channels by arbitrary tag, after fading them
			/// out for a specified time.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// for.</param>
			/// <param name="ms">Number of milliseconds to fade before halting the
			/// group.</param>
			/// <returns>The number of channels that were scheduled for fading.
			/// </returns>
			static int FadeOutGroup(int tag, int ms);

			/// <summary>
			/// Halt the music stream after fading it out for a specified time.
			/// </summary>
			/// <param name="ms">Number of milliseconds to fade before halting the
			/// channel.</param>
			/// <returns>Success if music was scheduled to fade, Failure otherwise.
			/// </returns>
			static Result<None^, None^> FadeOutMusic(int ms);

			/// <summary>
			/// Query the fading status of a channel.
			/// </summary>
			/// <param name="which">The channel to query.</param>
			/// <returns>The current fading status of the channel.</returns>
			static Fading FadingChannel(int which);

			/// <summary>
			/// Query the fading status of the music stream.
			/// </summary>
			static property Fading FadingMusic
			{
				Fading get();
			}

			/// <summary>
			/// Get the Chunk currently associated with a mixer channel.
			/// </summary>
			/// <param name="channel">The channel to query.</param>
			/// <returns>The associated chunk, if any, or None if it's an invalid
			/// channel.</returns>
			static Result<Chunk^, None^> GetChunk(int channel);

			/// <summary>
			/// Get a chunk decoder's name.
			/// </summary>
			/// <param name="index">Index of the chunk decoder.</param>
			/// <returns>The chunk decoder's name or None on invalid index.</returns>
			static Result<System::String^, None^> GetChunkDecoder(int index);

			/// <summary>
			/// Get the album name for a currently-playing music object.
			/// </summary>
			static property System::String^ CurrentMusicAlbumTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the artist name for a currently-playing music object.
			/// </summary>
			static property System::String^ CurrentMusicArtistTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the copyright text for a currently-playing music object.
			/// </summary>
			static property System::String^ CurrentMusicCopyrightTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get a music decoder's name.
			/// </summary>
			/// <param name="index">Index of the music decoder.</param>
			/// <returns>The music decoder's name or None on invalid index.</returns>
			static Result<System::String^, None^> GetMusicDecoder(int index);

			/// <summary>
			/// Get a pointer to the user data for the current music hook.
			/// </summary>
			/// <returns>Pointer to the user data previously passed to
			/// <see cref="HookMusic"/> or None if that function has never been called.
			/// </returns>
			static Result<System::IntPtr, None^> GetMusicHookData();

			/// <summary>
			/// Get the loop end time position of current playing music stream, in
			/// seconds.
			/// </summary>
			/// <returns>The loop end time or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			static Result<double, None^> GetCurrentMusicLoopEndTime();

			/// <summary>
			/// Get the loop time length of current playing music stream, in seconds.
			/// </summary>
			/// <returns>The loop time length or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			static Result<double, None^> GetCurrentMusicLoopLengthTime();

			/// <summary>
			/// Get the loop start time position of current playing music stream, in
			/// seconds.
			/// </summary>
			/// <returns>The loop start time or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			static Result<double, None^> GetCurrentMusicLoopStartTime();

			/// <summary>
			/// Get the title for a currently-playing music object, or its filename.
			/// </summary>
			static property System::String^ CurrentMusicTitle
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the title for a currently-playing music object.
			/// </summary>
			static property System::String^ CurrentMusicTitleTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Find out the format of a currently-playing mixer music.
			/// </summary>
			static property MusicType CurrentMusicType
			{
				MusicType get();
			}

			/// <summary>
			/// Get the number of chunk decoders that this build of SDL_mixer provides.
			/// </summary>
			static property int NumChunkDecoders
			{
				int get();
			}

			/// <summary>
			/// Get the number of music decoders that this build of SDL_mixer provides.
			/// </summary>
			static property int NumMusicDecoders
			{
				int get();
			}

			/// <summary>
			/// Get SoundFonts paths to use by supported MIDI backends.
			/// </summary>
			/// <returns>Semicolon-separated list of sound font paths or None on error.
			/// </returns>
			static Result<System::String^, None^> GetSoundFonts();

			/// <summary>
			/// This function does nothing, do not use.
			/// </summary>
			static property int SynchroValue
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Get full path of a previously-specified Timidity config file.
			/// </summary>
			/// <returns>The previously-specified path, or None if not set.</returns>
			static Result<System::String^, None^> GetTimidityCfg();

			/// <summary>
			/// Finds the first available channel in a group of channels.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// for.</param>
			/// <returns>First available channel, or None if none are available.</returns>
			static Result<int, None^> GroupAvailable(int tag);

			/// <summary>
			/// Assign a tag to a channel.
			/// </summary>
			/// <param name="which">The channel to set the tag on.</param>
			/// <param name="tag">An arbitrary value to assign a channel.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> GroupChannel(int which, int tag);

			/// <summary>
			/// Assign several consecutive channels to the same tag.
			/// </summary>
			/// <param name="from">The first channel to set the tag on.</param>
			/// <param name="to">The last channel to set the tag on, inclusive.</param>
			/// <param name="tag">An arbitrary value to assign a channel.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> GroupChannels(int from, int to, int tag);

			/// <summary>
			/// Returns the number of channels in a group.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// for.</param>
			/// <returns>Returns the number of channels assigned the specified tag.
			/// </returns>
			static int GroupCount(int tag);

			/// <summary>
			/// Find the "most recent" sample playing in a group of channels.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// through.</param>
			/// <returns>The "most recent" sample playing in a group of channels or
			/// None if no channel with the tag is currently playing.</returns>
			static Result<int, None^> GroupNewer(int tag);

			/// <summary>
			/// Find the "oldest" sample playing in a group of channels.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// through.</param>
			/// <returns>The "oldest" sample playing in a group of channels or
			/// None if no channel with the tag is currently playing.</returns>
			static Result<int, None^> GroupOldest(int tag);

			/// <summary>
			/// Halt playing of a particular channel.
			/// </summary>
			/// <param name="channel">Channel to halt, or -1 to halt all channels.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> HaltChannel(int channel);

			/// <summary>
			/// Halt playing of a group of channels by arbitrary tag.
			/// </summary>
			/// <param name="tag">An arbitrary value, assigned to channels, to search
			/// for.</param>
			static void HaltGroup(int tag);

			/// <summary>
			/// Halt playing of the music stream.
			/// </summary>
			static void HaltMusic();

			/// <summary>
			/// Check if a chunk decoder is available by name.
			/// </summary>
			/// <param name="name">The decoder name to query.</param>
			/// <returns>true if a decoder by that name is available, false otherwise.
			/// </returns>
			static bool HasChunkDecoder(System::String^ name);

			/// <summary>
			/// Check if a music decoder is available by name.
			/// </summary>
			/// <param name="name">The decoder name to query.</param>
			/// <returns>true if a decoder by that name is available, false otherwise.
			/// </returns>
			static bool HasMusicDecoder(System::String^ name);

			/// <summary>
			/// Add your own music player or additional mixer function.
			/// </summary>
			/// <param name="mixFunc">The callback function to become the new post-mix
			/// callback.</param>
			/// <param name="arg">A pointer that is passed, untouched, to the callback.
			/// </param>
			static void HookMusic(void (SDLCALL* mixFunc)(void* udata, Uint8* stream, int len), System::IntPtr arg);

			/// <summary>
			/// Set a callback that runs when a music object has stopped playing.
			/// </summary>
			/// <param name="musicFinished">The callback function to become the new
			/// notification mechanism.</param>
			static void HookMusicFinished(void (SDLCALL* musicFinished)(void));

			/// <summary>
			/// Query the version of SDL_mixer that the program is linked against.
			/// </summary>
			static property SDLVersion LinkedVersion
			{
				SDLVersion get();
			}

			/// <summary>
			/// Query the version of SDL_mixer that the program is compiled.
			/// </summary>
			static property SDLVersion Version
			{
				SDLVersion get();
			}

			/// <summary>
			/// Set the master volume for all channels.
			/// </summary>
			/// <param name="volume">The new volume, between 0 and
			/// <see cref="MaxVolume"/>, or -1 to query.</param>
			/// <returns>The previous volume. If the specified volume is -1, this
			/// returns the current volume.</returns>
			static int MasterVolume(int volume);

			/// <summary>
			/// Jump to a given order in mod music.
			/// </summary>
			/// <param name="order">Order</param>
			/// <returns>Success or Failure if failed or isn't implemented.</returns>
			static Result<None^, None^> ModMusicJumpToOrder(int order);

			/// <summary>
			/// Open the default audio device for playback.
			/// </summary>
			/// <param name="frequency">The frequency to playback audio at (in Hz).
			/// </param>
			/// <param name="format">Audio format.</param>
			/// <param name="channels">Number of channels (1 is mono, 2 is stereo,
			/// etc).</param>
			/// <param name="chunksize">Audio buffer size in sample FRAMES (total
			/// samples divided by channel count).</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> OpenAudio(int frequency, AudioFormat format, int channels, int chunksize);

			/// <summary>
			/// Open a specific audio device for playback.
			/// </summary>
			/// <param name="frequency">The frequency to playback audio at (in Hz).
			/// </param>
			/// <param name="format">Audio format.</param>
			/// <param name="channels">Number of channels (1 is mono, 2 is stereo,
			/// etc).</param>
			/// <param name="chunksize">Audio buffer size in sample FRAMES (total
			/// samples divided by channel count).</param>
			/// <param name="device">The device name to open, or null to choose a
			/// reasonable default.</param>
			/// <param name="allowedChanges">Allow change flags.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> OpenAudioDevice(int frequency, AudioFormat format, int channels, int chunksize, System::String^ device, AudioOpenFlags allowedChanges);

			/// <summary>
			/// Pause a particular channel.
			/// </summary>
			/// <param name="channel">The channel to pause, or -1 to pause all
			/// channels.</param>
			static void Pause(int channel);

			/// <summary>
			/// Query whether a particular channel is paused.
			/// </summary>
			/// <param name="channel">The channel to query, or -1 to query all
			/// channels.</param>
			/// <returns>1 if channel paused, 0 otherwise. If channel is -1, returns
			/// the number of paused channels.</returns>
			static int Paused(int channel);

			/// <summary>
			/// Query whether the music stream is paused.
			/// </summary>
			static property bool PausedMusic
			{
				bool get();
			}

			/// <summary>
			/// Play an audio chunk on a specific channel.
			/// </summary>
			/// <param name="channel">The channel on which to play the new chunk.
			/// </param>
			/// <param name="chunk">The new chunk to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <returns>Which channel was used to play the sound, or None if sound
			/// could not be played.</returns>
			static Result<int, None^> PlayChannel(int channel, Chunk^ chunk, int loops);

			/// <summary>
			/// Play an audio chunk on a specific channel for a maximum time.
			/// </summary>
			/// <param name="channel">The channel on which to play the new chunk.
			/// </param>
			/// <param name="chunk">The new chunk to play.</param>
			/// <param name="loops">The number of times the chunk should loop, -1 to
			/// loop (not actually) infinitely.</param>
			/// <param name="ticks">The maximum number of milliseconds of this chunk
			/// to mix for playback.</param>
			/// <returns>Which channel was used to play the sound, or None if sound
			/// could not be played.</returns>
			static Result<int, None^> PlayChannelTimed(int channel, Chunk^ chunk, int loops, int ticks);

			/// <summary>
			/// Check the playing status of a specific channel.
			/// </summary>
			/// <param name="channel">Channel.</param>
			/// <returns>Non-zero if channel is playing, zero otherwise. If channel
			/// is -1, return the total number of channel playings.</returns>
			static int Playing(int channel);

			/// <summary>
			/// Check the playing status of the music stream.
			/// </summary>
			static property bool PlayingMusic
			{
				bool get();
			}

			/// <summary>
			/// Play a new music object.
			/// </summary>
			/// <param name="music">The new music object to schedule for mixing.
			/// </param>
			/// <param name="loops">The number of loops to play the music for (0 means
			/// "play once and stop").</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> PlayMusic(Music^ music, int loops);

			/// <summary>
			/// Find out what the actual audio device parameters are.
			/// </summary>
			/// <param name="frequency">On return, will be filled with the audio
			/// device's frequency in Hz.</param>
			/// <param name="format">On return, will be filled with the audio device's
			/// format.</param>
			/// <param name="channels"> On return, will be filled with the audio
			/// device's channel count.</param>
			/// <returns>Success if the audio device has been opened, Failure
			/// otherwise.</returns>
			static Result<None^, None^> QuerySpec([Out]int% frequency, [Out]AudioFormat% format, [Out]int% channels);

			/// <summary>
			/// Deinitialize SDL_mixer.
			/// </summary>
			static void Quit();

			/// <summary>
			/// Register a special effect function.
			/// </summary>
			/// <param name="chan">The channel to register an effect to, or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="f">Effect the callback to run when more of this channel is
			/// to be mixed.</param>
			/// <param name="d">Effect done callback.</param>
			/// <param name="arg">Argument.</param>
			/// <returns>Success if added or Failure if error.</returns>
			static Result<None^, None^> RegisterEffect(int chan, Mix_EffectFunc_t f, Mix_EffectDone_t d, System::IntPtr arg);

			/// <summary>
			/// Reserve the first channels for the application.
			/// </summary>
			/// <param name="num">Number of channels to reserve, starting at index zero.
			/// </param>
			/// <returns>The number of reserved channels.</returns>
			static int ReserveChannels(int num);

			/// <summary>
			/// Resume a particular channel.
			/// </summary>
			/// <param name="channel">The channel to resume, or -1 to resume all paused
			/// channels.</param>
			static void Resume(int channel);

			/// <summary>
			/// Resume the music stream.
			/// </summary>
			static void ResumeMusic();

			/// <summary>
			/// Rewind the music stream.
			/// </summary>
			static void RewindMusic();

			/// <summary>
			/// Set the "distance" of a channel.
			/// </summary>
			/// <param name="channel">The mixer channel to attenuate, or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="distance">Distance; 0 is the listener, 255 is maxiumum
			/// distance away.</param>
			/// <returns>Success if position effect is enabled, or Failure if error.
			/// </returns>
			static Result<None^, None^> SetDistance(int channel, Uint8 distance);

			/// <summary>
			/// Run an external command as the music stream.
			/// </summary>
			/// <param name="command">Command.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> SetMusicCMD(System::String^ command);

			/// <summary>
			/// Set the current position in the music stream, in seconds.
			/// </summary>
			/// <param name="position">The new position, in seconds (as a double).</param>
			/// <returns>Success or Failure if it failed or not implemented.</returns>
			static Result<None^, None^> SetMusicPosition(double position);

			/// <summary>
			/// Set the panning of a channel.
			/// </summary>
			/// <param name="channel">The mixer channel to pan or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="left">Volume of stereo left channel, 0 is silence, 255 is
			/// full volume.</param>
			/// <param name="right">Volume of stereo right channel, 0 is silence, 255 is
			/// full volume.</param>
			/// <returns>Success if panning effect enabled or Failure if error.</returns>
			static Result<None^, None^> SetPanning(int channel, Uint8 left, Uint8 right);

			/// <summary>
			/// Set the position of a channel.
			/// </summary>
			/// <param name="channel">The mixer channel to position, or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="angle">Angle, in degrees. North is 0, and goes clockwise.
			/// </param>
			/// <param name="distance">Distance; 0 is the listener, 255 is maxiumum
			/// distance away.</param>
			/// <returns>Success if position effect enabled or Failure if error.</returns>
			static Result<None^, None^> SetPosition(int channel, Sint16 angle, Uint8 distance);

			/// <summary>
			/// Set a function that is called after all mixing is performed.
			/// </summary>
			/// <param name="mixFunc">The callback function to become the new post-mix
			/// callback.</param>
			/// <param name="arg">A pointer that is passed, untouched, to the callback.
			/// </param>
			static void SetPostMix(void (SDLCALL* mixFunc)(void* udata, Uint8* stream, int len), System::IntPtr arg);

			/// <summary>
			/// Cause a channel to reverse its stereo.
			/// </summary>
			/// <param name="channel">The mixer channel to reverse, or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="flip">true to reverse stereo, false to disable this effect.
			/// </param>
			/// <returns>Success if reversing effect enabled or Failure if error.
			/// </returns>
			static Result<None^, None^> SetReverseStereo(int channel, bool flip);

			/// <summary>
			/// Set SoundFonts paths to use by supported MIDI backends.
			/// </summary>
			/// <param name="paths">Paths on the filesystem where SoundFonts are
			/// available, separated by semicolons.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> SetSoundFonts(System::String^ paths);

			/// <summary>
			/// Set full path of the Timidity config file.
			/// </summary>
			/// <param name="path">Path to a Timidity config file.</param>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> SetTimidityCfg(System::String^ path);

			/// <summary>
			/// Explicitly unregister all special effect functions.
			/// </summary>
			/// <param name="channel">The channel to unregister all effects on, or
			/// <see cref="ChannelPost"/>.</param>
			/// <returns>Success if all effects removed or Failure if error.</returns>
			static Result<None^, None^> UnregisterAllEffects(int channel);

			/// <summary>
			/// Explicitly unregister a special effect function.
			/// </summary>
			/// <param name="channel">The channel to unregister an effect on, or
			/// <see cref="ChannelPost"/>.</param>
			/// <param name="f">Effect the callback stop calling in future mixing
			/// iterations.</param>
			/// <returns>Success if removed or Failure if error.</returns>
			static Result<None^, None^> UnregisterEffect(int channel, Mix_EffectFunc_t f);

			/// <summary>
			/// Set the volume for a specific channel.
			/// </summary>
			/// <param name="channel">The channel on set/query the volume on, or -1 for
			/// all channels.</param>
			/// <param name="volume">The new volume, between 0 and
			/// <see cref="MaxVolume"/>, or -1 to query.</param>
			/// <returns>The previous volume. If the specified volume is -1, this
			/// returns the current volume. If channel is -1, this returns the average
			/// of all channels.</returns>
			static int Volume(int channel, int volume);

			/// <summary>
			/// Set the volume for the music channel.
			/// </summary>
			/// <param name="volume">The new volume, between 0 and
			/// <see cref="MaxVolume"/>, or -1 to query.</param>
			/// <returns>The previous volume. If the specified volume is -1, this returns
			/// the current volume.</returns>
			static int VolumeMusic(int volume);
		};
	}
}