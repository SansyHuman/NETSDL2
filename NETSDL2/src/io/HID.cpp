#include "../../include/io/HID.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::IO;
using namespace NETSDL2::Internal;

Result<None^, None^> NETSDL2::IO::HIDAPI::Init()
{
	int result = SDL_hid_init();
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::IO::HIDAPI::Exit()
{
	int result = SDL_hid_exit();
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<array<HIDDeviceInfo>^, None^> NETSDL2::IO::HIDAPI::Enumerate(unsigned short vendorID, unsigned short productID)
{
	SDL_hid_device_info* info = __nullptr;
	try
	{
		info = SDL_hid_enumerate(vendorID, productID);
		if(info == __nullptr)
		{
			return Result<array<HIDDeviceInfo>^, None^>::MakeFailure(None::Value);
		}

		int cnt = 0;
		for(SDL_hid_device_info* curr = info; curr != __nullptr; cnt++, curr = curr->next) {}

		array<HIDDeviceInfo>^ infos = gcnew array<HIDDeviceInfo>(cnt);

		SDL_hid_device_info* curr = info;
		for(int i = 0; i < cnt; i++, curr = curr->next)
		{
			infos[i] = HIDDeviceInfo(curr);
		}

		return infos;
	}
	finally
	{
		if(info != __nullptr)
		{
			SDL_hid_free_enumeration(info);
		}
	}
}

Uint32 HIDAPI::DeviceChangeCount::get()
{
	return SDL_hid_device_change_count();
}

void NETSDL2::IO::HIDAPI::BLEScan(bool active)
{
	SDL_hid_ble_scan(active ? SDL_TRUE : SDL_FALSE);
}
