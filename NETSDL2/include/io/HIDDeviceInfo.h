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

		/// <summary>
		/// Information about a connected HID device.
		/// </summary>
		public value struct HIDDeviceInfo
		{
        public:
            /// <summary>
            /// Platform-specific device path.
            /// </summary>
            System::String^ Path;
            
            /// <summary>
            /// Device Vendor ID.
            /// </summary>
            unsigned short VendorID;
            
            /// <summary>
            /// Device Product ID.
            /// </summary>
            unsigned short ProductID;
            
            /// <summary>
            /// Serial Number.
            /// </summary>
            System::String^ SerialNumber;

            /// <summary>
            /// Device Release Number in binary-coded decimal, also known as Device Version Number.
            /// </summary>
            unsigned short ReleaseNumber;
            
            /// <summary>
            /// Manufacturer String.
            /// </summary>
            System::String^ ManufacturerString;
            
            /// <summary>
            /// Product string.
            /// </summary>
            System::String^ ProductString;
            
            /// <summary>
            /// Usage Page for this Device/Interface(Windows / Mac only).
            /// </summary>
            unsigned short UsagePage;
            
            /// <summary>
            /// Usage for this Device/Interface(Windows / Mac only).
            /// </summary>
            unsigned short Usage;
            
            /// <summary>
            /// The USB interface which this logical device represents.
            /// </summary>
            int InterfaceNumber;

            /// <summary>
            /// Additional information about the USB interface.
            /// </summary>
            int InterfaceClass;

            /// <summary>
            /// Additional information about the USB interface.
            /// </summary>
            int InterfaceSubclass;

            /// <summary>
            /// Additional information about the USB interface.
            /// </summary>
            int InterfaceProtocol;

        internal:
            HIDDeviceInfo(SDL_hid_device_info* info);
		};
	}
}