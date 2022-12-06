#include "../../include/system/Platform.h"

#include "../../include/internal/StringMarshal.h"
#include "../../include/core/Error.h"
#include "../../include/video/Renderer.h"

using namespace NETSDL2::Systems;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;

System::String^ NETSDL2::Systems::Platform::GetPlatform()
{
	return StringMarshal::UTF8NativeToManaged(SDL_GetPlatform());
}

void NETSDL2::Systems::Platform::SetWindowsMessageHook(SDL_WindowsMessageHook callback, System::IntPtr userdata)
{
	SDL_SetWindowsMessageHook(callback, userdata.ToPointer());
}

Result<int, int> NETSDL2::Systems::Platform::Direct3D9GetAdapterIndex(int displayIndex)
{
	int result = SDL_Direct3D9GetAdapterIndex(displayIndex);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<System::IntPtr, None^> NETSDL2::Systems::Platform::GetD3D9Device(Renderer^ renderer)
{
	IDirect3DDevice9* result = renderer->GetD3D9Device();
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Platform::GetD3D11Device(Renderer^ renderer)
{
	ID3D11Device* result = renderer->GetD3D11Device();
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<System::IntPtr, None^> NETSDL2::Systems::Platform::GetD3D12Device(Renderer^ renderer)
{
	ID3D12Device* result = renderer->GetD3D12Device();
	if(result == __nullptr)
	{
		return Result<System::IntPtr, None^>::MakeFailure(None::Value);
	}

	return System::IntPtr(result);
}

Result<None^, None^> NETSDL2::Systems::Platform::GetDXGIOutputInfo(int displayIndex, int% adapterIndex, int% outputIndex)
{
	int a = 0, o = 0;
	SDL_bool result = SDL_DXGIGetOutputInfo(displayIndex, &a, &o);
	if(result == SDL_FALSE)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	adapterIndex = a;
	outputIndex = o;
	return None::Value;
}

bool NETSDL2::Systems::Platform::IsTablet()
{
	return SDL_IsTablet() == SDL_TRUE;
}
