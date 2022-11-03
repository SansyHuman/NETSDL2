#include "../../include/internal/StringMarshal.h"
#include <Windows.h>

using namespace NETSDL2::Internal;

NETSDL2::Internal::StringMarshal::StringMarshal()
{
	clearList = gcnew System::Collections::Generic::List<GCHandle>();
}

NETSDL2::Internal::StringMarshal::~StringMarshal()
{
	for each(auto% e in clearList)
	{
		e.Free();
	}
}

System::String^ NETSDL2::Internal::StringMarshal::UTF8NativeToManaged(const char* str)
{
	return gcnew System::String(str, 0, lstrlenA(str), System::Text::Encoding::UTF8);
}

char* NETSDL2::Internal::StringMarshal::ManagedToUTF8Native(System::String^ str)
{
	auto bytes = System::Text::Encoding::UTF8->GetBytes(str);
	GCHandle handle = GCHandle::Alloc(bytes, GCHandleType::Pinned);
	clearList->Add(handle);

	return (char*)handle.AddrOfPinnedObject().ToPointer();
}
