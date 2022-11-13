#include "../../include/system/Stdinc.h"

using namespace NETSDL2::Systems;

Uint32 NETSDL2::Systems::Stdinc::FourCC(Uint8 a, Uint8 b, Uint8 c, Uint8 d)
{
	return SDL_FOURCC(a, b, c, d);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Stdinc::Malloc(size_t size)
{
	void* result = SDL_malloc(size);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Stdinc::Calloc(size_t nmemb, size_t size)
{
	void* result = SDL_calloc(nmemb, size);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Stdinc::Realloc(System::IntPtr mem, size_t size)
{
	void* result = SDL_realloc(mem.ToPointer(), size);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

void NETSDL2::Systems::Stdinc::Free(System::IntPtr mem)
{
	SDL_free(mem.ToPointer());
}

void NETSDL2::Systems::Stdinc::GetOriginalMemoryFunctions(SDL_malloc_func% mallocFunc, SDL_calloc_func% callocFunc, SDL_realloc_func% reallocFunc, SDL_free_func% freeFunc)
{
	SDL_malloc_func malloc;
	SDL_calloc_func calloc;
	SDL_realloc_func realloc;
	SDL_free_func free;

	SDL_GetOriginalMemoryFunctions(&malloc, &calloc, &realloc, &free);

	mallocFunc = malloc;
	callocFunc = calloc;
	reallocFunc = realloc;
	freeFunc = free;
}

void NETSDL2::Systems::Stdinc::GetMemoryFunctions(SDL_malloc_func% mallocFunc, SDL_calloc_func% callocFunc, SDL_realloc_func% reallocFunc, SDL_free_func% freeFunc)
{
	SDL_malloc_func malloc;
	SDL_calloc_func calloc;
	SDL_realloc_func realloc;
	SDL_free_func free;

	SDL_GetMemoryFunctions(&malloc, &calloc, &realloc, &free);

	mallocFunc = malloc;
	callocFunc = calloc;
	reallocFunc = realloc;
	freeFunc = free;
}

Result<None^, int> NETSDL2::Systems::Stdinc::SetMemoryFunctions(SDL_malloc_func mallocFunc, SDL_calloc_func callocFunc, SDL_realloc_func reallocFunc, SDL_free_func freeFunc)
{
	int result = SDL_SetMemoryFunctions(mallocFunc, callocFunc, reallocFunc, freeFunc);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

int Stdinc::NumAllocations::get()
{
	return SDL_GetNumAllocations();
}

Uint16 NETSDL2::Systems::Stdinc::CRC16(Uint16 crc, System::IntPtr data, size_t len)
{
	return SDL_crc16(crc, data.ToPointer(), len);
}

Uint32 NETSDL2::Systems::Stdinc::CRC32(Uint32 crc, System::IntPtr data, size_t len)
{
	return SDL_crc32(crc, data.ToPointer(), len);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Stdinc::Memset(System::IntPtr dst, unsigned char c, size_t len)
{
	void* result = SDL_memset(dst.ToPointer(), (int)c, len);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

void NETSDL2::Systems::Stdinc::Memset4(System::IntPtr dst, Uint32 val, size_t dwords)
{
	SDL_memset4(dst.ToPointer(), val, dwords);
}

void NETSDL2::Systems::Stdinc::Memcpy(System::IntPtr dst, System::IntPtr src, size_t len)
{
	SDL_memcpy(dst.ToPointer(), src.ToPointer(), len);
}

void NETSDL2::Systems::Stdinc::Memmove(System::IntPtr dst, System::IntPtr src, size_t len)
{
	SDL_memmove(dst.ToPointer(), src.ToPointer(), len);
}

void NETSDL2::Systems::Stdinc::Memcpy4(System::IntPtr dst, System::IntPtr src, size_t dwords)
{
	SDL_memcpy4(dst.ToPointer(), src.ToPointer(), dwords);
}
