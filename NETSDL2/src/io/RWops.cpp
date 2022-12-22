#include "../../include/io/RWops.h"

#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::IO;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

Sint64 NETSDL2::IO::RWops::NativeSize(SDL_RWops* context)
{
	RWops^ con = nullptr;
	bool found = nativeRWopsConnections->TryGetValue(System::IntPtr(context), con);
	if(!found || con != this)
		return -1;

	return SizeFn(con);
}

Sint64 NETSDL2::IO::RWops::NativeSeek(SDL_RWops* context, Sint64 offset, int whence)
{
	RWops^ con = nullptr;
	bool found = nativeRWopsConnections->TryGetValue(System::IntPtr(context), con);
	if(!found || con != this)
		return -1;

	return SeekFn(con, offset, (SeekFrom)whence);
}

size_t NETSDL2::IO::RWops::NativeRead(SDL_RWops* context, void* ptr, size_t size, size_t maxnum)
{
	RWops^ con = nullptr;
	bool found = nativeRWopsConnections->TryGetValue(System::IntPtr(context), con);
	if(!found || con != this)
		return 0;

	return ReadFn(con, System::IntPtr(ptr), size, maxnum);
}

size_t NETSDL2::IO::RWops::NativeWrite(SDL_RWops* context, const void* ptr, size_t size, size_t num)
{
	RWops^ con = nullptr;
	bool found = nativeRWopsConnections->TryGetValue(System::IntPtr(context), con);
	if(!found || con != this)
		return 0;

	return WriteFn(con, System::IntPtr(const_cast<void*>(ptr)), size, num);
}

int NETSDL2::IO::RWops::NativeClose(SDL_RWops* context)
{
	RWops^ con = nullptr;
	bool found = nativeRWopsConnections->TryGetValue(System::IntPtr(context), con);
	if(!found || con != this)
		return -1;

	return CloseFn(con);
}

void NETSDL2::IO::RWops::InitCallbacks()
{
	NativeSizeFunc^ nsize = gcnew NativeSizeFunc(this, &RWops::NativeSize);
	NativeSeekFunc^ nseek = gcnew NativeSeekFunc(this, &RWops::NativeSeek);
	NativeReadFunc^ nread = gcnew NativeReadFunc(this, &RWops::NativeRead);
	NativeWriteFunc^ nwrite = gcnew NativeWriteFunc(this, &RWops::NativeWrite);
	NativeCloseFunc^ nclose = gcnew NativeCloseFunc(this, &RWops::NativeClose);

	sizeHandle = GCHandle::Alloc(nsize);
	seekHandle = GCHandle::Alloc(nseek);
	readHandle = GCHandle::Alloc(nread);
	writeHandle = GCHandle::Alloc(nwrite);
	closeHandle = GCHandle::Alloc(nclose);

	ops->size = (Sint64 (SDLCALL*) (SDL_RWops*))Marshal::GetFunctionPointerForDelegate(nsize).ToPointer();
	ops->seek = (Sint64 (SDLCALL*) (SDL_RWops*, Sint64, int))Marshal::GetFunctionPointerForDelegate(nseek).ToPointer();
	ops->read = (size_t (SDLCALL*) (SDL_RWops*, void*, size_t, size_t))Marshal::GetFunctionPointerForDelegate(nread).ToPointer();
	ops->write = (size_t (SDLCALL*) (SDL_RWops*, const void*, size_t, size_t))Marshal::GetFunctionPointerForDelegate(nwrite).ToPointer();
	ops->close = (int (SDLCALL*) (SDL_RWops*))Marshal::GetFunctionPointerForDelegate(nclose).ToPointer();
}

void NETSDL2::IO::RWops::ClearCallbacks()
{
	if(!userDefined)
		return;

	sizeHandle.Free();
	seekHandle.Free();
	readHandle.Free();
	writeHandle.Free();
	closeHandle.Free();
}

void NETSDL2::IO::RWops::InitOps(SDL_RWops* ops)
{
	this->ops = ops;
	nativeRWopsConnections[System::IntPtr(ops)] = this;
}

SDL_RWops* RWops::NativeOps::get()
{
	return ops;
}

RWops::RWops()
	: userDefined(true)
{
	SDL_RWops* ops = SDL_AllocRW();
	if(ops == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitOps(ops);
	InitCallbacks();
}

NETSDL2::IO::RWops::RWops(System::IntPtr mem, int size, bool readonly)
	: userDefined(false)
{
	SDL_RWops* ops = __nullptr;
	if(readonly)
	{
		ops = SDL_RWFromMem(mem.ToPointer(), size);
	}
	else
	{
		ops = SDL_RWFromConstMem(mem.ToPointer(), size);
	}

	if(ops == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitOps(ops);
}

NETSDL2::IO::RWops::RWops(System::String^ file, FileMode mode)
{
	const char* filemode;
	switch(mode)
	{
	case FileMode::Read:
		filemode = "r";
		break;
	case FileMode::Write:
		filemode = "w";
		break;
	case FileMode::Append:
		filemode = "a";
		break;
	case FileMode::ReadWrite:
		filemode = "r+";
		break;
	case FileMode::ReadWriteCreate:
		filemode = "w+";
		break;
	case FileMode::ReadAppend:
		filemode = "a+";
		break;
	}

	StringMarshal context;

	SDL_RWops* ops = SDL_RWFromFile(context.ManagedToUTF8Native(file), filemode);
	if(ops == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitOps(ops);
}

NETSDL2::IO::RWops::RWops(System::IntPtr fp, bool autoclose)
{
	SDL_RWops* ops = SDL_RWFromFP(fp.ToPointer(), autoclose ? SDL_TRUE : SDL_FALSE);
	if(ops == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitOps(ops);
}

NETSDL2::IO::RWops::~RWops()
{
	RWops^ dummy = nullptr;
	nativeRWopsConnections->TryRemove(System::IntPtr(ops), dummy);
	this->!RWops();
}

NETSDL2::IO::RWops::!RWops()
{
	ClearCallbacks();

	SDL_FreeRW(ops);
	ops = __nullptr;
}

RWopsType RWops::Type::get()
{
	return (RWopsType)ops->type;
}

void RWops::Type::set(RWopsType value)
{
	ops->type = (Uint32)value;
}

System::IntPtr RWops::Data1::get()
{
	return System::IntPtr(ops->hidden.unknown.data1);
}

void RWops::Data1::set(System::IntPtr value)
{
	ops->hidden.unknown.data1 = value.ToPointer();
}

System::IntPtr RWops::Data2::get()
{
	return System::IntPtr(ops->hidden.unknown.data2);
}

void RWops::Data2::set(System::IntPtr value)
{
	ops->hidden.unknown.data2 = value.ToPointer();
}

Uint16 NETSDL2::IO::RWops::ReadBE16()
{
	return SDL_ReadBE16(ops);
}

Uint32 NETSDL2::IO::RWops::ReadBE32()
{
	return SDL_ReadBE32(ops);
}

Uint64 NETSDL2::IO::RWops::ReadBE64()
{
	return SDL_ReadBE64(ops);
}

Uint16 NETSDL2::IO::RWops::ReadLE16()
{
	return SDL_ReadLE16(ops);
}

Uint32 NETSDL2::IO::RWops::ReadLE32()
{
	return SDL_ReadLE32(ops);
}

Uint64 NETSDL2::IO::RWops::ReadLE64()
{
	return SDL_ReadLE64(ops);
}

Uint8 NETSDL2::IO::RWops::ReadU8()
{
	return SDL_ReadU8(ops);
}

Result<None^, int> NETSDL2::IO::RWops::Close()
{
	int result = SDL_RWclose(ops);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	delete this;
	return None::Value;
}

size_t NETSDL2::IO::RWops::Read(System::IntPtr ptr, size_t size, size_t maxnum)
{
	return SDL_RWread(ops, ptr.ToPointer(), size, maxnum);
}

generic<class T> where T : value class
size_t NETSDL2::IO::RWops::Read(array<T>^ arr, size_t offset, size_t maxnum)
{
	size_t size = sizeof(T);
	if(arr->Length == 0)
	{
		SDL_InvalidParamError(arr);
		return 0;
	}

	if(offset >= arr->Length)
	{
		SDL_InvalidParamError(offset);
		return 0;
	}

	if(offset + maxnum > arr->Length)
	{
		maxnum = arr->Length - offset;
	}

	pin_ptr<T> ptr = &arr[offset];
	return SDL_RWread(ops, (void*)ptr, size, maxnum);
}

Sint64 NETSDL2::IO::RWops::Seek(Sint64 offset, SeekFrom whence)
{
	return SDL_RWseek(ops, offset, (int)whence);
}

Sint64 RWops::Size::get()
{
	return SDL_RWsize(ops);
}

Sint64 RWops::Tell::get()
{
	return SDL_RWtell(ops);
}

size_t NETSDL2::IO::RWops::Write(System::IntPtr ptr, size_t size, size_t num)
{
	return SDL_RWwrite(ops, ptr.ToPointer(), size, num);
}

generic<class T> where T : value class
size_t NETSDL2::IO::RWops::Write(array<T>^ arr, size_t offset, size_t num)
{
	size_t size = sizeof(T);
	if(arr->Length == 0)
	{
		SDL_InvalidParamError(arr);
		return 0;
	}

	if(offset >= arr->Length)
	{
		SDL_InvalidParamError(offset);
		return 0;
	}

	bool writeless = false;

	if(offset + num > arr->Length)
	{
		num = arr->Length - offset;
		writeless = true;
	}

	pin_ptr<T> ptr = &arr[offset];
	size_t write = SDL_RWwrite(ops, (void*)ptr, size, num);
	if(write == num && writeless)
	{
		SDL_InvalidParamError(num);
	}

	return write;
}

Result<System::IntPtr, None^> NETSDL2::IO::RWops::LoadFile(RWops^ src, size_t% datasize, bool freesrc)
{
	size_t size = 0;
	void* result = SDL_LoadFile_RW(src->ops, &size, freesrc ? 1 : 0);
	if(freesrc)
		delete src;

	datasize = size;
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<array<Uint8>^, None^> NETSDL2::IO::RWops::LoadFile(RWops^ src, bool freesrc)
{
	size_t size = 0;
	void* result = __nullptr;

	try
	{
		result = SDL_LoadFile_RW(src->ops, &size, freesrc ? 1 : 0);
		if(freesrc)
			delete src;

		if(result == __nullptr)
		{
			return Result<array<Uint8>^, None^>::MakeFailure(None::Value);
		}

		array<Uint8>^ data = gcnew array<Uint8>(size);
		if(size == 0)
			return data;

		pin_ptr<Uint8> pData = &data[0];
		System::Buffer::MemoryCopy(result, (void*)pData, size, size);
		pData = nullptr;

		return data;
	}
	finally
	{
		if(result != __nullptr)
		{
			SDL_free(result);
		}
	}
}

Result<System::IntPtr, None^> NETSDL2::IO::RWops::LoadFile(System::String^ file, size_t% datasize)
{
	StringMarshal context;

	size_t size = 0;
	void* result = SDL_LoadFile(context.ManagedToUTF8Native(file), &size);

	datasize = size;
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<array<Uint8>^, None^> NETSDL2::IO::RWops::LoadFile(System::String^ file)
{
	StringMarshal context;

	size_t size = 0;
	void* result = __nullptr;

	try
	{
		result = SDL_LoadFile(context.ManagedToUTF8Native(file), &size);
		if(result == __nullptr)
		{
			return Result<array<Uint8>^, None^>::MakeFailure(None::Value);
		}

		array<Uint8>^ data = gcnew array<Uint8>(size);
		if(size == 0)
			return data;

		pin_ptr<Uint8> pData = &data[0];
		System::Buffer::MemoryCopy(result, (void*)pData, size, size);
		pData = nullptr;

		return data;
	}
	finally
	{
		if(result != __nullptr)
		{
			SDL_free(result);
		}
	}
}

size_t NETSDL2::IO::RWops::WriteU8(Uint8 value)
{
	return SDL_WriteU8(ops, value);
}

size_t NETSDL2::IO::RWops::WriteLE16(Uint16 value)
{
	return SDL_WriteLE16(ops, value);
}

size_t NETSDL2::IO::RWops::WriteBE16(Uint16 value)
{
	return SDL_WriteBE16(ops, value);
}

size_t NETSDL2::IO::RWops::WriteLE32(Uint32 value)
{
	return SDL_WriteLE32(ops, value);
}

size_t NETSDL2::IO::RWops::WriteBE32(Uint32 value)
{
	return SDL_WriteBE32(ops, value);
}

size_t NETSDL2::IO::RWops::WriteLE64(Uint64 value)
{
	return SDL_WriteLE64(ops, value);
}

size_t NETSDL2::IO::RWops::WriteBE64(Uint64 value)
{
	return SDL_WriteBE64(ops, value);
}
