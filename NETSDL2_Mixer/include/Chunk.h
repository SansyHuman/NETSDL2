#pragma once

#include <SDL_mixer.h>

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Audio
	{
		using namespace NETSDL2::IO;

		/// <summary>
		/// The internal format for an audio chunk.
		/// </summary>
		public ref class Chunk
		{
		private:
			Mix_Chunk* chunk;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Chunk^>^ nativeChunkConnections;

			static Chunk()
			{
				nativeChunkConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Chunk^>();
			}

			void InitChunk(Mix_Chunk* chunk);

		internal:
			property Mix_Chunk* NativeChunk
			{
				Mix_Chunk* get();
			}

			static Chunk^ GetChunkFromNative(Mix_Chunk* chunk);

		public:
			/// <summary>
			/// Load a supported audio format into a chunk.
			/// </summary>
			/// <param name="file">The filesystem path to load data from.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(System::String^ file);

			/// <summary>
			/// Load a supported audio format into a chunk.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// false to leave it open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(RWops^ src, bool freesrc);

			/// <summary>
			/// Load a raw audio data from memory as quickly as possible.
			/// </summary>
			/// <param name="mem">Memory buffer containing raw PCM data.</param>
			/// <param name="len">Length of buffer pointed to by mem, in bytes.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(Uint8* mem, Uint32 len);

			/// <summary>
			/// Load a raw audio data from memory as quickly as possible.
			/// </summary>
			/// <param name="mem">Memory buffer array containing raw PCM data.</param>
			/// <param name="offset">Offset from the start of the mem.</param>
			/// <param name="len">Length of raw audio data in bytes.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(array<Uint8>^ mem, Uint32 offset, Uint32 len);

			/// <summary>
			/// Load a WAV file from memory as quickly as possible.
			/// </summary>
			/// <param name="mem">Memory buffer containing of a WAV file.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(Uint8* mem);

			/// <summary>
			/// Load a WAV file from memory as quickly as possible.
			/// </summary>
			/// <param name="mem">Memory buffer arrat containing of a WAV file.</param>
			/// <param name="offset">Offset from the start of the mem.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Chunk(array<Uint8>^ mem, Uint32 offset);

			~Chunk();
			!Chunk();

			/// <summary>
			/// Set the volume for a specific chunk.
			/// </summary>
			/// <param name="volume">The new volume, between 0 and
			/// <see cref="MaxVolume"/>, or -1 to query.</param>
			/// <returns>The previous volume. If the specified volume is -1, this
			/// returns the current volume.</returns>
			int Volume(int volume);
		};
	}
}