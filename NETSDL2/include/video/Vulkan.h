#pragma once

#include <SDL.h>
#include <SDL_vulkan.h>
#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		using namespace NETSDL2::Core;

		ref class Window;

		public ref struct Vulkan abstract sealed
		{
		public:
			/// <summary>
			/// Create a Vulkan rendering surface for a window.
			/// </summary>
			/// <param name="window">The window to which to attach the Vulkan
			/// surface.</param>
			/// <param name="instance">The Vulkan instance handle.</param>
			/// <param name="surface">A pointer to a VkSurfaceKHR handle to
			/// output the newly created surface</param>
			/// <returns>true on success, false on error.</returns>
			static bool CreateSurface(Window^ window, void* instance, void** surface);

			/// <summary>
			/// Get the size of the window's underlying drawable dimensions in
			/// pixels.
			/// </summary>
			/// <param name="window">A window for which the size is to be
			/// queried.</param>
			/// <param name="w">The width.</param>
			/// <param name="h">The height.</param>
			static void GetDrawableSize(Window^ window, [Out]int% w, [Out]int% h);

			/// <summary>
			/// Get the names of the Vulkan instance extensions needed to create a surface with <see cref="CreateSurface"/>.
			/// </summary>
			/// <param name="window">A window for which the required Vulkan
			/// instance extensions should be retrieved.</param>
			/// <returns>An array of extensions on success or None on error.
			/// </returns>
			static Result<array<System::String^>^, None^> GetInstanceExtensions(Window^ window);

			/// <summary>
			/// Get the address of the ```vkGetInstanceProcAddr``` function.
			/// </summary>
			/// <returns>A pointer to the vkGetInstanceProcAddr which can be
			/// used to load Vulkan function pointers at runtime.</returns>
			static void* GetVkGetInstanceProcAddr();

			/// <summary>
			/// Dynamically load the Vulkan loader library.
			/// </summary>
			/// <param name="path">The platform dependent Vulkan loader
			/// library name or null.</param>
			/// <returns>None on success or -1 if the library couldn't be
			/// loaded.</returns>
			static Result<None^, int> LoadLibrary(System::String^ path);

			/// <summary>
			/// Unload the Vulkan library previously loaded by
			/// <see cref="LoadLibrary"/>.
			/// </summary>
			static void UnloadLibrary();
		};
	}
}