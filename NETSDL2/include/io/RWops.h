#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace IO
	{
		using namespace NETSDL2::Core;

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate Sint64 NativeSizeFunc(SDL_RWops* context);

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate Sint64 NativeSeekFunc(SDL_RWops* context, Sint64 offset, int whence);

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate size_t NativeReadFunc(SDL_RWops* context, void* ptr, size_t size, size_t maxnum);

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate size_t NativeWriteFunc(SDL_RWops* context, const void* ptr, size_t size, size_t num);

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate int NativeCloseFunc(SDL_RWops* context);

		ref class RWops;

		/// <summary>
		/// The position of seek.
		/// </summary>
		public enum class SeekFrom
		{
			/// <summary>
			/// Seek from the beginning of data.
			/// </summary>
			Set = RW_SEEK_SET,

			/// <summary>
			/// Seek relative to current read point.
			/// </summary>
			Cur = RW_SEEK_CUR,

			/// <summary>
			/// Seek relative to the end of data.
			/// </summary>
			End = RW_SEEK_END,
		};

		/// <summary>
		/// Return the size of the file in this rwops.
		/// </summary>
		/// <param name="context">RWops that is used.</param>
		/// <returns>The size of the file in this rwops, or -1 if unknown.</returns>
		public delegate Sint64 SizeFunc(RWops^ context);

		/// <summary>
		/// Seek to offset relative to whence.
		/// </summary>
		/// <param name="context">RWops that is used.</param>
		/// <param name="offset">Offset from whence in bytes.</param>
		/// <param name="context">Position to seek from.</param>
		/// <returns>The final offset in the data stream, or -1 on error.</returns>
		public delegate Sint64 SeekFunc(RWops^ context, Sint64 offset, SeekFrom whence);

		/// <summary>
		/// Read up to maxnum objects each of size from the data stream to the area pointed at by ptr.
		/// </summary>
		/// <param name="context">RWops that is used.</param>
		/// <param name="ptr">Pointer to the area to write read data.</param>
		/// <param name="size">Byte size of each object to read.</param>
		/// <param name="maxnum">Maximum number of objects to read.</param>
		/// <returns>The number of objects read, or 0 at error or end of file.</returns>
		public delegate size_t ReadFunc(RWops^ context, System::IntPtr ptr, size_t size, size_t maxnum);

		/// <summary>
		/// Write exactly num objects each of size from the area pointed at by ptr to data stream.
		/// </summary>
		/// <param name="context">RWops that is used.</param>
		/// <param name="ptr">Pointer to the area to read data.</param>
		/// <param name="size">Byte size of each object to write.</param>
		/// <param name="num">The number of objects to write.</param>
		/// <returns>The number of objects written, or 0 at error or end of file.</returns>
		public delegate size_t WriteFunc(RWops^ context, System::IntPtr ptr, size_t size, size_t num);

		/// <summary>
		/// Close and free an allocated RWops.
		/// </summary>
		/// <param name="context">RWops that is used.</param>
		/// <returns>0 if successful or -1 on write error when flushing data.</returns>
		public delegate int CloseFunc(RWops^ context);

		/// <summary>
		/// RWops Types.
		/// </summary>
		public enum class RWopsType : Uint32
		{
			/// <summary>
			/// Unknown stream type.
			/// </summary>
			Unknown = SDL_RWOPS_UNKNOWN,

			/// <summary>
			/// Win32 file.
			/// </summary>
			WinFile = SDL_RWOPS_WINFILE,

			/// <summary>
			/// Stdio file.
			/// </summary>
			StdFile = SDL_RWOPS_STDFILE,

			/// <summary>
			/// Android asset.
			/// </summary>
			JNIFile = SDL_RWOPS_JNIFILE,

			/// <summary>
			/// Memory stream.
			/// </summary>
			Memory = SDL_RWOPS_MEMORY,

			/// <summary>
			/// Read-Only memory stream.
			/// </summary>
			MemoryRO = SDL_RWOPS_MEMORY_RO,
		};

		/// <summary>
		/// File open modes.
		/// </summary>
		public enum class FileMode
		{
			/// <summary>
			/// Open a file for reading. The file must exist.
			/// </summary>
			Read,

			/// <summary>
			/// Create an empty file for writing. If a file with the same name
			/// already exists its content is erased and the file is treated as a
			/// new empty file.
			/// </summary>
			Write,

			/// <summary>
			/// Append to a file. Writing operations append data at the end of the
			/// file. The file is created if it does not exist.
			/// </summary>
			Append,

			/// <summary>
			/// Open a file for update both reading and writing. The file must
			/// exist.
			/// </summary>
			ReadWrite,

			/// <summary>
			/// Create an empty file for both reading and writing. If a file with
			/// the same name already exists its content is erased and the file is
			/// treated as a new empty file.
			/// </summary>
			ReadWriteCreate,

			/// <summary>
			/// Open a file for reading and appending. All writing operations are
			/// performed at the end of the file, protecting the previous content
			/// to be overwritten. You can reposition (fseek, rewind) the internal
			/// pointer to anywhere in the file for reading, but writing operation
			/// will move it back to the end of file. The file is created if it
			/// does not exist.
			/// </summary>
			ReadAppend,
		};

		/// <summary>
		/// A class that provides an abstract interface to stream I/O.
		/// </summary>
		public ref class RWops
		{
		private:
			SDL_RWops* ops;
			bool userDefined;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, RWops^>^ nativeRWopsConnections;

			static RWops()
			{
				nativeRWopsConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, RWops^>();
			}

			GCHandle sizeHandle;
			GCHandle seekHandle;
			GCHandle readHandle;
			GCHandle writeHandle;
			GCHandle closeHandle;

			Sint64 NativeSize(SDL_RWops* context);
			Sint64 NativeSeek(SDL_RWops* context, Sint64 offset, int whence);
			size_t NativeRead(SDL_RWops* context, void* ptr, size_t size, size_t maxnum);
			size_t NativeWrite(SDL_RWops* context, const void* ptr, size_t size, size_t num);
			int NativeClose(SDL_RWops* context);

			void InitCallbacks();
			void ClearCallbacks();

			void InitOps(SDL_RWops* ops);

		internal:
			property SDL_RWops* NativeOps
			{
				SDL_RWops* get();
			}

		public:
			/// <summary>
			/// Allocate an empty, unpopulated RWops object.
			/// </summary>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			RWops();

			/// <summary>
			/// Prepare a read-only memory buffer for use with RWops.
			/// </summary>
			/// <param name="mem">A pointer to a read-only buffer to feed an RWops
			/// stream.</param>
			/// <param name="size">The buffer size, in bytes.</param>
			/// <param name="readonly">true if the buffer is readonly, else
			/// false.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			RWops(System::IntPtr mem, int size, bool readonly);

			/// <summary>
			/// Create a new RWops for reading from and/or writing to a named file.
			/// </summary>
			/// <param name="file">The filename to open.</param>
			/// <param name="mode">The mode to be used for opening the file.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			RWops(System::String^ file, FileMode mode);

			/// <summary>
			/// Create an RWops from a standard I/O file pointer.
			/// </summary>
			/// <param name="fp">The FILE* that feeds the RWops stream.</param>
			/// <param name="autoclose">true to close the FILE* when closing the
			/// RWops, false to leave the FILE* open when the RWops is closed.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			RWops(System::IntPtr fp, bool autoclose);
			~RWops();
			!RWops();

			/// <summary>
			/// Type of RWops.
			/// </summary>
			property RWopsType Type
			{
				RWopsType get();
				void set(RWopsType value);
			}

			/// <summary>
			/// User-defined auxillary data.
			/// </summary>
			property System::IntPtr Data1
			{
				System::IntPtr get();
				void set(System::IntPtr value);
			}

			/// <summary>
			/// User-defined auxillary data.
			/// </summary>
			property System::IntPtr Data2
			{
				System::IntPtr get();
				void set(System::IntPtr value);
			}

			/// <summary>
			/// Function pointer that reports the stream's total size in bytes.
			/// </summary>
			property SizeFunc^ SizeFn;

			/// <summary>
			/// Function pointer that positions the next read/write operation
			/// in the stream.
			/// </summary>
			property SeekFunc^ SeekFn;

			/// <summary>
			/// Function pointer that reads from the stream.
			/// </summary>
			property ReadFunc^ ReadFn;

			/// <summary>
			/// Function pointer that writes to the stream.
			/// </summary>
			property WriteFunc^ WriteFn;

			/// <summary>
			/// Function pointer that cleans up the stream.
			/// </summary>
			property CloseFunc^ CloseFn;

			/// <summary>
			/// Use this function to read 16 bits of big-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>16 bits of data in the native byte order of the platform.
			/// </returns>
			Uint16 ReadBE16();

			/// <summary>
			/// Use this function to read 32 bits of big-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>32 bits of data in the native byte order of the platform.
			/// </returns>
			Uint32 ReadBE32();

			/// <summary>
			/// Use this function to read 64 bits of big-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>64 bits of data in the native byte order of the platform.
			/// </returns>
			Uint64 ReadBE64();

			/// <summary>
			/// Use this function to read 16 bits of little-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>16 bits of data in the native byte order of the platform.
			/// </returns>
			Uint16 ReadLE16();

			/// <summary>
			/// Use this function to read 32 bits of little-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>32 bits of data in the native byte order of the platform.
			/// </returns>
			Uint32 ReadLE32();

			/// <summary>
			/// Use this function to read 64 bits of little-endian data and return in
			/// native format.
			/// </summary>
			/// <returns>64 bits of data in the native byte order of the platform.
			/// </returns>
			Uint64 ReadLE64();

			/// <summary>
			/// Use this function to read a byte.
			/// </summary>
			/// <returns>The read byte on success or 0 on failure.</returns>
			Uint8 ReadU8();

			/// <summary>
			/// Close and free an allocated RWops.
			/// </summary>
			/// <returns>None on success or error code on failure.</returns>
			Result<None^, int> Close();

			/// <summary>
			/// Read from a data source.
			/// </summary>
			/// <param name="ptr">A pointer to a buffer to read data into.</param>
			/// <param name="size">The size of each object to read, in bytes.
			/// </param>
			/// <param name="maxnum">The maximum number of objects to be read.
			/// </param>
			/// <returns>The number of objects read, or 0 at error or end of
			/// file.</returns>
			size_t Read(System::IntPtr ptr, size_t size, size_t maxnum);

			/// <summary>
			/// Read from a data source.
			/// </summary>
			/// <typeparam name="T">Type of object to read.</typeparam>
			/// <param name="arr">The buffer to read data into.</param>
			/// <param name="offset">The array index offset to start read into.
			/// </param>
			/// <param name="maxnum">The maximum number of objects to be read.
			/// </param>
			/// <returns>The number of objects read, or 0 at error or end of
			/// file.</returns>
			generic<class T> where T : value class
			size_t Read(array<T>^ arr, size_t offset, size_t maxnum);

			/// <summary>
			/// Seek within an RWops data stream.
			/// </summary>
			/// <param name="offset">An offset in bytes, relative to whence
			/// location.</param>
			/// <param name="whence">The position of seek.</param>
			/// <returns>The final offset in the data stream after the seek or -1
			/// on error.</returns>
			Sint64 Seek(Sint64 offset, SeekFrom whence);

			/// <summary>
			/// Get the size of the data stream.
			/// </summary>
			property Sint64 Size
			{
				Sint64 get();
			}

			/// <summary>
			/// Determine the current read/write offset.
			/// </summary>
			property Sint64 Tell
			{
				Sint64 get();
			}

			/// <summary>
			/// Write to an RWops data stream.
			/// </summary>
			/// <param name="ptr">A pointer to a buffer containing data to write.</param>
			/// <param name="size">The size of an object to write, in bytes.</param>
			/// <param name="num">The number of objects to write.</param>
			/// <returns>The number of objects written, which will be less than num
			/// on error.</returns>
			size_t Write(System::IntPtr ptr, size_t size, size_t num);

			/// <summary>
			/// Write to an RWops data stream.
			/// </summary>
			/// <typeparam name="T">Type of object to write.</typeparam>
			/// <param name="arr">The buffer that contains data to write.</param>
			/// <param name="offset">The array index offset to start write.</param>
			/// <param name="num">The number of objects to write.</param>
			/// <returns>The number of objects written, which will be less than num
			/// on error.</returns>
			generic<class T> where T : value class
			size_t Write(array<T>^ arr, size_t offset, size_t num);

			/// <summary>
			/// Load all the data from an SDL data stream.
			/// </summary>
			/// <param name="src">The RWops to read all available data from.</param>
			/// <param name="datasize">Store the number of bytes read.</param>
			/// <param name="freesrc">If true close the source stream before returning.</param>
			/// <returns>The data, or None if there was an error.
			/// The returned data should be freed with 
			/// <see cref="NETSDL2::Systems::Stdinc::Free"/>.</returns>
			static Result<System::IntPtr, None^> LoadFile(RWops^ src, [Out]size_t% datasize, bool freesrc);

			/// <summary>
			/// Load all the data from an SDL data stream.
			/// </summary>
			/// <param name="src">The RWops to read all available data from.</param>
			/// <param name="freesrc">If true close the source stream before returning.</param>
			/// <returns>The data array, or None if there was an error.</returns>
			static Result<array<Uint8>^, None^> LoadFile(RWops^ src, bool freesrc);

			/// <summary>
			/// Load all the data from a file path.
			/// </summary>
			/// <param name="file">The path to read all available data from.</param>
			/// <param name="datasize">Store the number of bytes read.</param>
			/// <returns>The data, or None if there was an error.
			/// The returned data should be freed with 
			/// <see cref="NETSDL2::Systems::Stdinc::Free"/>.</returns>
			static Result<System::IntPtr, None^> LoadFile(System::String^ file, [Out]size_t% datasize);

			/// <summary>
			/// Load all the data from a file path.
			/// </summary>
			/// <param name="file">The path to read all available data from.</param>
			/// <returns>The data array, or None if there was an error.</returns>
			static Result<array<Uint8>^, None^> LoadFile(System::String^ file);

			/// <summary>
			/// Use this function to write a byte to an RWops.
			/// </summary>
			/// <param name="value">The byte value to write.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteU8(Uint8 value);

			/// <summary>
			/// Use this function to write 16 bits in native format to a RWops as little-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteLE16(Uint16 value);

			/// <summary>
			/// Use this function to write 16 bits in native format to a RWops as big-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteBE16(Uint16 value);

			/// <summary>
			/// Use this function to write 32 bits in native format to a RWops as little-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteLE32(Uint32 value);

			/// <summary>
			/// Use this function to write 32 bits in native format to a RWops as big-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteBE32(Uint32 value);

			/// <summary>
			/// Use this function to write 64 bits in native format to a RWops as little-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteLE64(Uint64 value);

			/// <summary>
			/// Use this function to write 64 bits in native format to a RWops as big-endian data.
			/// </summary>
			/// <param name="value">Value the data to be written, in native format.</param>
			/// <returns>1 on success or 0 on failure.</returns>
			size_t WriteBE64(Uint64 value);
		};
	}
}