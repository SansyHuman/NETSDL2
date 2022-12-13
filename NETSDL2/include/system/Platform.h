#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "../core/FunctionPointer.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		ref class Renderer;
	}

	namespace Systems
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::Video;

		/// <summary>
		/// Callback for a window message.
		/// </summary>
		/// <param name="userdata">User data passed.</param>
		/// <param name="hwnd">A handle to the window.</param>
		/// <param name="message">Window message.</param>
		/// <param name="wParam">WPARAM.</param>
		/// <param name="wParam">LPARAM.</param>
		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		public delegate void WindowsMessageHook(System::IntPtr userdata, System::IntPtr hwnd, unsigned int message, Uint64 wParam, Sint64 lParam);

		/// <summary>
		/// Functions for handling information about the current platform and advanced, platform-specific
		/// functionality.
		/// </summary>
		[Extension]
		public ref struct Platform abstract sealed
		{
		public:
			/// <summary>
			/// Get the name of the platform.
			/// </summary>
			/// <returns>The name of the platform. If the correct platform name is
			/// not available, returns a string beginning with the text "Unknown".
			/// </returns>
			static System::String^ GetPlatform();

			/// <summary>
			/// Set a callback for every Windows message, run before TranslateMessage.
			/// </summary>
			/// <param name="callback">Callback function to call.</param>
			/// <param name="userdata">A pointer to pass to every iteration of callback.</param>
			static void SetWindowsMessageHook(FunctionPointer<WindowsMessageHook^>^ callback, System::IntPtr userdata);

			/// <summary>
			/// Get the D3D9 adapter index that matches the specified display index.
			/// </summary>
			/// <param name="displayIndex">The display index for which to get the D3D9 adapter index.</param>
			/// <returns>The D3D9 adapter index on success or a negative error code on failure.</returns>
			static Result<int, int> Direct3D9GetAdapterIndex(int displayIndex);

			/// <summary>
			/// Get the D3D9 device associated with a renderer.
			/// </summary>
			/// <param name="renderer">The renderer from which to get the associated D3D device.</param>
			/// <returns>The D3D9 device associated with given renderer or None if it is not a D3D9
			/// renderer.</returns>
			[Extension]
			static Result<System::IntPtr, None^> GetD3D9Device(Renderer^ renderer);

			/// <summary>
			/// Get the D3D11 device associated with a renderer.
			/// </summary>
			/// <param name="renderer">The renderer from which to get the associated D3D device.</param>
			/// <returns>The D3D11 device associated with given renderer or None if it is not a D3D11
			/// renderer.</returns>
			[Extension]
			static Result<System::IntPtr, None^> GetD3D11Device(Renderer^ renderer);

			/// <summary>
			/// Get the D3D12 device associated with a renderer.
			/// </summary>
			/// <param name="renderer">The renderer from which to get the associated D3D device.</param>
			/// <returns>The D3D12 device associated with given renderer or None if it is not a D3D12
			/// renderer.</returns>
			[Extension]
			static Result<System::IntPtr, None^> GetD3D12Device(Renderer^ renderer);

			/// <summary>
			/// Get the DXGI Adapter and Output indices for the specified display index.
			/// </summary>
			/// <param name="displayIndex">The display index for which to get both indices.</param>
			/// <param name="adapterIndex">The adapter index.</param>
			/// <param name="outputIndex">The output index.</param>
			/// <returns>Success or Failure.</returns>
			static Result<None^, None^> GetDXGIOutputInfo(int displayIndex, [Out]int% adapterIndex, [Out]int% outputIndex);

			/// <summary>
			/// Query if the current device is a tablet.
			/// </summary>
			/// <returns>true if the device is a tablet, false otherwise.</returns>
			static bool IsTablet();
		};
	}
}