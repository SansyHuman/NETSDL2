#include "../../include/io/HIDDeviceInfo.h"

#include "../../include/internal/StringMarshal.h"
#include <msclr/marshal.h>

using namespace NETSDL2::IO;
using namespace NETSDL2::Internal;
using namespace msclr::interop;

NETSDL2::IO::HIDDeviceInfo::HIDDeviceInfo(SDL_hid_device_info* info)
{
	Path = StringMarshal::UTF8NativeToManaged(info->path);
	VendorID = info->vendor_id;
	ProductID = info->product_id;
	SerialNumber = marshal_as<System::String^>(info->serial_number);
	ReleaseNumber = info->release_number;
	ManufacturerString = marshal_as<System::String^>(info->manufacturer_string);
	ProductString = marshal_as<System::String^>(info->product_string);
	UsagePage = info->usage_page;
	Usage = info->usage;
	InterfaceNumber = info->interface_number;
	InterfaceClass = info->interface_class;
	InterfaceSubclass = info->interface_subclass;
	InterfaceProtocol = info->interface_protocol;
}
