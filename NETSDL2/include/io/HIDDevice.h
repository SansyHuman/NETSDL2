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
		/// An open HID device.
		/// </summary>
		public ref class HIDDevice
		{
		private:
			SDL_hid_device* device;

		public:
			/// <summary>
			/// Open a HID device using a Vendor ID (VID), Product ID (PID) and optionally a serial number.
			/// </summary>
			/// <param name="vendorID">The Vendor ID (VID) of the device to open.</param>
			/// <param name="productID">The Product ID (PID) of the device to open.</param>
			/// <param name="serialNumber">The Serial Number of the device to open (Optionally null).</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			HIDDevice(unsigned short vendorID, unsigned short productID, System::String^ serialNumber);

			/// <summary>
			/// Open a HID device by its path name.
			/// </summary>
			/// <param name="path">The path name of the device to open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			HIDDevice(System::String^ path);

			~HIDDevice();
			!HIDDevice();

			/// <summary>
			/// Write an Output report to a HID device.
			/// </summary>
			/// <param name="data">The data to send, including the report number as the first byte.</param>
			/// <param name="length">The length in bytes of the data to send.</param>
			/// <returns>The actual number of bytes written and None on error.</returns>
			Result<int, None^> Write(unsigned char* data, size_t length);

			/// <summary>
			/// Write an Output report to a HID device.
			/// </summary>
			/// <param name="data">The data array to send, including the report number as the first byte.
			/// </param>
			/// <param name="offset">The offset from the start of the data array to send.</param>
			/// <param name="length">The length in bytes of the data to send.</param>
			/// <returns>The actual number of bytes written and None on error.</returns>
			Result<int, None^> Write(array<unsigned char>^ data, size_t offset, size_t length);

			/// <summary>
			/// Read an Input report from a HID device with timeout.
			/// </summary>
			/// <param name="data">A buffer to put the read data into.</param>
			/// <param name="length">The number of bytes to read. For devices with multiple reports, make
			/// sure to read an extra byte for the report number.</param>
			/// <param name="milliseconds">Timeout in milliseconds or -1 for blocking wait.</param>
			/// <returns>The actual number of bytes read and None on error. If no packet was available to be
			/// read within the timeout period, this function returns 0. </returns>
			Result<int, None^> ReadTimeout(unsigned char* data, size_t length, int milliseconds);

			/// <summary>
			/// Read an Input report from a HID device with timeout.
			/// </summary>
			/// <param name="data">A buffer to put the read data into.</param>
			/// <param name="offset">The offset from the start of the data array to read.</param>
			/// <param name="length">The number of bytes to read. For devices with multiple reports, make
			/// sure to read an extra byte for the report number.</param>
			/// <param name="milliseconds">Timeout in milliseconds or -1 for blocking wait.</param>
			/// <returns>The actual number of bytes read and None on error. If no packet was available to be
			/// read within the timeout period, this function returns 0.</returns>
			Result<int, None^> ReadTimeout(array<unsigned char>^ data, size_t offset, size_t length, int milliseconds);

			/// <summary>
			/// Read an Input report from a HID device.
			/// </summary>
			/// <param name="data">A buffer to put the read data into.</param>
			/// <param name="length">The number of bytes to read. For devices with multiple reports, make
			/// sure to read an extra byte for the report number.</param>
			/// <returns>The actual number of bytes read and None on error. If no packet was available to be
			/// read and the handle is in non-blocking mode, this function returns 0.</returns>
			Result<int, None^> Read(unsigned char* data, size_t length);

			/// <summary>
			/// Read an Input report from a HID device.
			/// </summary>
			/// <param name="data">A buffer to put the read data into.</param>
			/// <param name="offset">The offset from the start of the data array to read.</param>
			/// <param name="length">The number of bytes to read. For devices with multiple reports, make
			/// sure to read an extra byte for the report number.</param>
			/// <returns>The actual number of bytes read and None on error. If no packet was available to be
			/// read and the handle is in non-blocking mode, this function returns 0. </returns>
			Result<int, None^> Read(array<unsigned char>^ data, size_t offset, size_t length);

			/// <summary>
			/// Set the device handle to be non-blocking.
			/// </summary>
			/// <param name="nonblock">true to enable nonblocking false to disable nonblocking.</param>
			/// <returns>Success or Failure on error.</returns>
			Result<None^, None^> SetNonblocking(bool nonblock);

			/// <summary>
			/// Send a Feature report to the device.
			/// </summary>
			/// <param name="data">The data to send, including the report number as the first byte.</param>
			/// <param name="length">The length in bytes of the data to send.</param>
			/// <returns>The actual number of bytes written and None on error.</returns>
			Result<int, None^> SendFeatureReport(unsigned char* data, size_t length);

			/// <summary>
			/// Send a Feature report to the device.
			/// </summary>
			/// <param name="data">The data array to send, including the report number as the first byte.
			/// </param>
			/// <param name="offset">The offset from the start of the data array to send.</param>
			/// <param name="length">The length in bytes of the data to send.</param>
			/// <returns>The actual number of bytes written and None on error.</returns>
			Result<int, None^> SendFeatureReport(array<unsigned char>^ data, size_t offset, size_t length);

			/// <summary>
			/// Get a feature report from a HID device.
			/// </summary>
			/// <param name="data">A buffer to put the read data into, including the Report ID. Set the first
			/// byte of `data` to the Report ID of the report to be read, or set it to zero if your device
			/// does not use numbered reports.</param>
			/// <param name="length">The number of bytes to read, including an extra byte for the report ID.
			/// The buffer can be longer than the actual report.</param>
			/// <returns>The number of bytes read plus one for the report ID (which is still in the first
			/// byte), or -1 on error.</returns>
			Result<int, None^> GetFeatureReport(unsigned char* data, size_t length);

			/// <summary>
			/// Get a feature report from a HID device.
			/// </summary>
			/// <param name="data">A buffer to put the read data into, including the Report ID. Set the first
			/// byte of `data` to the Report ID of the report to be read, or set it to zero if your device
			/// does not use numbered reports.</param>
			/// <param name="offset">The offset from the start of the data array to read.</param>
			/// <param name="length">The number of bytes to read. For devices with multiple reports, make
			/// sure to read an extra byte for the report number.</param>
			/// <returns>The number of bytes read plus one for the report ID (which is still in the first
			/// byte), or -1 on error.</returns>
			Result<int, None^> GetFeatureReport(array<unsigned char>^ data, size_t offset, size_t length);

			/// <summary>
			/// Get The Manufacturer String from a HID device.
			/// </summary>
			/// <returns>The manufacturer string on success or None on error.</returns>
			Result<System::String^, None^> GetManufacturerString();

			/// <summary>
			/// Get The Product String from a HID device.
			/// </summary>
			/// <returns>The product string on success or None on error.</returns>
			Result<System::String^, None^> GetProductString();

			/// <summary>
			/// Get The Serial Number String from a HID device.
			/// </summary>
			/// <returns>The serial number string on success or None on error.</returns>
			Result<System::String^, None^> GetSerialNumberString();

			/// <summary>
			/// Get a string from a HID device, based on its string index.
			/// </summary>
			/// <param name="stringIndex">The index of the string to get.</param>
			/// <returns>The string on success or None on error.</returns>
			Result<System::String^, None^> GetIndexedString(int stringIndex);
		};
	}
}