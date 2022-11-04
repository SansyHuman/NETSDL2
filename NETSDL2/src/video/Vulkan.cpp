#include "../../include/video/Vulkan.h"

#include "../../include/internal/StringMarshal.h"

#include "../../include/video/Window.h"

using namespace NETSDL2::Internal;

using namespace NETSDL2::Video;

bool NETSDL2::Video::Vulkan::CreateSurface(Window^ window, void* instance, void** surface)
{
	return window->CreateVulkanSurface(instance, surface);
}

void NETSDL2::Video::Vulkan::GetDrawableSize(Window^ window, int% w, int% h)
{
	window->GetVulkanDrawableSize(w, h);
}

Result<array<System::String^>^, None^> NETSDL2::Video::Vulkan::GetInstanceExtensions(Window^ window)
{
	return window->GetVulkanInstanceExtensions();
}

void* NETSDL2::Video::Vulkan::GetVkGetInstanceProcAddr()
{
	return SDL_Vulkan_GetVkGetInstanceProcAddr();
}

#ifdef LoadLibrary
#undef LoadLibrary
#endif

Result<None^, int> NETSDL2::Video::Vulkan::LoadLibrary(System::String^ path)
{
	StringMarshal context;
	int result = SDL_Vulkan_LoadLibrary(context.ManagedToUTF8Native(path));
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}
	return None::Value;
}

#ifndef LoadLibrary
#ifdef UNICODE
#define LoadLibrary  LoadLibraryW
#else
#define LoadLibrary  LoadLibraryA
#endif
#endif

void NETSDL2::Video::Vulkan::UnloadLibrary()
{
	SDL_Vulkan_UnloadLibrary();
}
