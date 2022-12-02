#include "../../include/system/CPUInfo.h"

using namespace NETSDL2::Systems;

int CPUInfo::CPUCacheLineSize::get()
{
	return SDL_GetCPUCacheLineSize();
}

int CPUInfo::CPUCount::get()
{
	return SDL_GetCPUCount();
}

int CPUInfo::SystemRAM::get()
{
	return SDL_GetSystemRAM();
}

size_t CPUInfo::SIMDAlignment::get()
{
	return SDL_SIMDGetAlignment();
}

Result<System::IntPtr, None^> NETSDL2::Systems::CPUInfo::SIMDAlloc(size_t len)
{
	void* result = SDL_SIMDAlloc(len);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Systems::CPUInfo::SIMDRealloc(System::IntPtr mem, size_t len)
{
	void* result = SDL_SIMDRealloc(mem.ToPointer(), len);
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

void NETSDL2::Systems::CPUInfo::SIMDFree(System::IntPtr ptr)
{
	SDL_SIMDFree(ptr.ToPointer());
}

bool CPUInfo::Has3DNow::get()
{
	return SDL_Has3DNow() == SDL_TRUE;
}

bool CPUInfo::HasAltiVec::get()
{
	return SDL_HasAltiVec() == SDL_TRUE;
}

bool CPUInfo::HasAVX::get()
{
	return SDL_HasAVX() == SDL_TRUE;
}

bool CPUInfo::HasAVX2::get()
{
	return SDL_HasAVX2() == SDL_TRUE;
}

bool CPUInfo::HasAVX512F::get()
{
	return SDL_HasAVX512F() == SDL_TRUE;
}

bool CPUInfo::HasARMSIMD::get()
{
	return SDL_HasARMSIMD() == SDL_TRUE;
}

bool CPUInfo::HasNEON::get()
{
	return SDL_HasNEON() == SDL_TRUE;
}

bool CPUInfo::HasLSX::get()
{
	return SDL_HasLSX() == SDL_TRUE;
}

bool CPUInfo::HasLASX::get()
{
	return SDL_HasLASX() == SDL_TRUE;
}

bool CPUInfo::HasMMX::get()
{
	return SDL_HasMMX() == SDL_TRUE;
}

bool CPUInfo::HasRDTSC::get()
{
	return SDL_HasRDTSC() == SDL_TRUE;
}

bool CPUInfo::HasSSE::get()
{
	return SDL_HasSSE() == SDL_TRUE;
}

bool CPUInfo::HasSSE2::get()
{
	return SDL_HasSSE2() == SDL_TRUE;
}

bool CPUInfo::HasSSE3::get()
{
	return SDL_HasSSE3() == SDL_TRUE;
}

bool CPUInfo::HasSSE41::get()
{
	return SDL_HasSSE41() == SDL_TRUE;
}

bool CPUInfo::HasSSE42::get()
{
	return SDL_HasSSE42() == SDL_TRUE;
}
