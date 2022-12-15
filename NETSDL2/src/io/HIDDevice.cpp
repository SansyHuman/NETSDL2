#include "../../include/io/HIDDevice.h"

#include "../../include/internal/StringMarshal.h"
#include "../../include/core/Error.h"
#include <msclr/marshal.h>

using namespace NETSDL2::IO;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;
using namespace msclr::interop;

NETSDL2::IO::HIDDevice::HIDDevice(unsigned short vendorID, unsigned short productID, System::String^ serialNumber)
{
	marshal_context context;

	device = SDL_hid_open(vendorID, productID, serialNumber == nullptr ? __nullptr : context.marshal_as<const wchar_t*>(serialNumber));
	if(device == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::IO::HIDDevice::HIDDevice(System::String^ path)
{
	StringMarshal context;

	device = SDL_hid_open_path(context.ManagedToUTF8Native(path), false);
	if(device == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::IO::HIDDevice::~HIDDevice()
{
	this->!HIDDevice();
}

NETSDL2::IO::HIDDevice::!HIDDevice()
{
	SDL_hid_close(device);
	device = __nullptr;
}

Result<int, None^> NETSDL2::IO::HIDDevice::Write(unsigned char* data, size_t length)
{
	int result = SDL_hid_write(device, data, length);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::Write(array<unsigned char>^ data, size_t offset, size_t length)
{
	if(data->Length == 0)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	if(data->Length <= offset || data->Length < offset + length)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	pin_ptr<unsigned char> pData = &data[offset];
	int result = SDL_hid_write(device, (unsigned char*)pData, length);
	pData = nullptr;
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::ReadTimeout(unsigned char* data, size_t length, int milliseconds)
{
	int result = SDL_hid_read_timeout(device, data, length, milliseconds);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::ReadTimeout(array<unsigned char>^ data, size_t offset, size_t length, int milliseconds)
{
	if(data->Length == 0)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	if(data->Length <= offset || data->Length < offset + length)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	pin_ptr<unsigned char> pData = &data[offset];
	int result = SDL_hid_read_timeout(device, (unsigned char*)pData, length, milliseconds);
	pData = nullptr;
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::Read(unsigned char* data, size_t length)
{
	int result = SDL_hid_read(device, data, length);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::Read(array<unsigned char>^ data, size_t offset, size_t length)
{
	if(data->Length == 0)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	if(data->Length <= offset || data->Length < offset + length)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	pin_ptr<unsigned char> pData = &data[offset];
	int result = SDL_hid_read(device, (unsigned char*)pData, length);
	pData = nullptr;
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::IO::HIDDevice::SetNonblocking(bool nonblock)
{
	int result = SDL_hid_set_nonblocking(device, nonblock ? 1 : 0);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<int, None^> NETSDL2::IO::HIDDevice::SendFeatureReport(unsigned char* data, size_t length)
{
	int result = SDL_hid_send_feature_report(device, data, length);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::SendFeatureReport(array<unsigned char>^ data, size_t offset, size_t length)
{
	if(data->Length == 0)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	if(data->Length <= offset || data->Length < offset + length)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	pin_ptr<unsigned char> pData = &data[offset];
	int result = SDL_hid_send_feature_report(device, (unsigned char*)pData, length);
	pData = nullptr;
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::GetFeatureReport(unsigned char* data, size_t length)
{
	int result = SDL_hid_get_feature_report(device, data, length);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::IO::HIDDevice::GetFeatureReport(array<unsigned char>^ data, size_t offset, size_t length)
{
	if(data->Length == 0)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	if(data->Length <= offset || data->Length < offset + length)
	{
		SDL_InvalidParamError(data);
		return Result<int, None^>::MakeFailure(None::Value);
	}

	pin_ptr<unsigned char> pData = &data[offset];
	int result = SDL_hid_get_feature_report(device, (unsigned char*)pData, length);
	pData = nullptr;
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

#ifndef MAX_STRING_ITER
#define MAX_STRING_ITER 4
#endif

Result<System::String^, None^> NETSDL2::IO::HIDDevice::GetManufacturerString()
{
	int maxlen = 256;
	wchar_t* string = __nullptr;

	try
	{
		for(int i = 0; i < MAX_STRING_ITER; i++, maxlen *= 2)
		{
			string = (wchar_t*)SDL_malloc(sizeof(wchar_t) * maxlen);
			SDL_memset(string, 0, sizeof(wchar_t) * maxlen);

			int result = SDL_hid_get_manufacturer_string(device, string, maxlen);
			if(result == 0)
			{
				return marshal_as<System::String^>(string);
			}

			SDL_free(string);
			string = __nullptr;
		}

		return Result<System::String^, None^>::MakeFailure(None::Value);
	}
	finally
	{
		if(string != __nullptr)
		{
			SDL_free(string);
		}
	}
}

Result<System::String^, None^> NETSDL2::IO::HIDDevice::GetProductString()
{
	int maxlen = 256;
	wchar_t* string = __nullptr;

	try
	{
		for(int i = 0; i < MAX_STRING_ITER; i++, maxlen *= 2)
		{
			string = (wchar_t*)SDL_malloc(sizeof(wchar_t) * maxlen);
			SDL_memset(string, 0, sizeof(wchar_t) * maxlen);

			int result = SDL_hid_get_product_string(device, string, maxlen);
			if(result == 0)
			{
				return marshal_as<System::String^>(string);
			}

			SDL_free(string);
			string = __nullptr;
		}

		return Result<System::String^, None^>::MakeFailure(None::Value);
	}
	finally
	{
		if(string != __nullptr)
		{
			SDL_free(string);
		}
	}
}

Result<System::String^, None^> NETSDL2::IO::HIDDevice::GetSerialNumberString()
{
	int maxlen = 256;
	wchar_t* string = __nullptr;

	try
	{
		for(int i = 0; i < MAX_STRING_ITER; i++, maxlen *= 2)
		{
			string = (wchar_t*)SDL_malloc(sizeof(wchar_t) * maxlen);
			SDL_memset(string, 0, sizeof(wchar_t) * maxlen);

			int result = SDL_hid_get_serial_number_string(device, string, maxlen);
			if(result == 0)
			{
				return marshal_as<System::String^>(string);
			}

			SDL_free(string);
			string = __nullptr;
		}

		return Result<System::String^, None^>::MakeFailure(None::Value);
	}
	finally
	{
		if(string != __nullptr)
		{
			SDL_free(string);
		}
	}
}

Result<System::String^, None^> NETSDL2::IO::HIDDevice::GetIndexedString(int stringIndex)
{
	int maxlen = 256;
	wchar_t* string = __nullptr;

	try
	{
		for(int i = 0; i < MAX_STRING_ITER; i++, maxlen *= 2)
		{
			string = (wchar_t*)SDL_malloc(sizeof(wchar_t) * maxlen);
			SDL_memset(string, 0, sizeof(wchar_t) * maxlen);

			int result = SDL_hid_get_indexed_string(device, stringIndex, string, maxlen);
			if(result == 0)
			{
				return marshal_as<System::String^>(string);
			}

			SDL_free(string);
			string = __nullptr;
		}

		return Result<System::String^, None^>::MakeFailure(None::Value);
	}
	finally
	{
		if(string != __nullptr)
		{
			SDL_free(string);
		}
	}
}
