#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "HIDDeviceInfo.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace IO
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// HIDAPI functions.
		/// </summary>
		public ref struct HID abstract sealed
		{
		public:
			/// <summary>
			/// Initialize the HIDAPI library.
			/// </summary>
			/// <returns>Success or Failure on error.</returns>
			static Result<None^, None^> Init();

			/// <summary>
			/// Finalize the HIDAPI library.
			/// </summary>
			/// <returns></returns>
			static Result<None^, None^> Exit();

			/// <summary>
			/// Check to see if devices may have been added or removed.
			/// </summary>
			static property Uint32 DeviceChangeCount
			{
				Uint32 get();
			}

			/// <summary>
			/// Enumerate the HID Devices.
			/// </summary>
			/// <param name="vendorID">The Vendor ID (VID) of the types of device to open.</param>
			/// <param name="productID">The Product ID (PID) of the types of device to open.</param>
			/// <returns>A list of type information about the HID devices attached to the system, or None in
			/// the case of failure.</returns>
			Result<array<HIDDeviceInfo>^, None^> Enumerate(unsigned short vendorID, unsigned short productID);
		};
	}
}