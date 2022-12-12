#pragma once

#include <SDL_mixer.h>

#include "MusicType.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::IO;

		/// <summary>
		/// The internal format for a music chunk interpreted via codecs.
		/// </summary>
		public ref class Music
		{
		private:
			Mix_Music* music;

		internal:
			property Mix_Music* NativeMusic
			{
				Mix_Music* get();
			}

		public:
			/// <summary>
			/// Load a supported audio format into a music object.
			/// </summary>
			/// <param name="file">A file path from where to load music data.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Music(System::String^ file);

			/// <summary>
			/// Load a supported audio format into a music object.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// false to leave it open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Music(RWops^ src, bool freesrc);

			/// <summary>
			/// Load an audio format into a music object, assuming a specific format.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="type">The type of audio data provided by src.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// false to leave it open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Music(RWops^ src, MusicType type, bool freesrc);

			~Music();
			!Music();

			/// <summary>
			/// Get the album name for a music object.
			/// </summary>
			property System::String^ AlbumTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the artist name for a music object.
			/// </summary>
			property System::String^ ArtistTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the copyright text for a music object.
			/// </summary>
			property System::String^ CopyrightTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the loop end time position of music stream, in seconds.
			/// </summary>
			/// <returns>The loop end time or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			Result<double, None^> GetLoopEndTime();

			/// <summary>
			/// Get the loop time length of music stream, in seconds.
			/// </summary>
			/// <returns>The loop time length or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			Result<double, None^> GetLoopLengthTime();

			/// <summary>
			/// Get the loop start time position of music stream, in seconds.
			/// </summary>
			/// <returns>The loop start time or None if this feature is not used for this
			/// music or not supported for some codec.</returns>
			Result<double, None^> GetLoopStartTime();

			/// <summary>
			/// Get the time current position of music stream, in seconds.
			/// </summary>
			/// <returns>The time current position or None if this feature is not
			/// supported for some codec.</returns>
			Result<double, None^> GetPosition();

			/// <summary>
			/// Get the title for a music object, or its filename.
			/// </summary>
			property System::String^ Title
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the title for a music object.
			/// </summary>
			property System::String^ TitleTag
			{
				System::String^ get();
			}

			/// <summary>
			/// Find out the format of a mixer music.
			/// </summary>
			property MusicType Type
			{
				MusicType get();
			}

			/// <summary>
			/// Query the current volume value for a music object.
			/// </summary>
			property int Volume
			{
				int get();
			}

			/// <summary>
			/// Get a music object's duration, in seconds.
			/// </summary>
			/// <returns>Music duration in seconds, or None on error.</returns>
			Result<double, None^> Duration();
		};
	}
}