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
	if(str == __nullptr)
		return System::String::Empty;

	return gcnew System::String(str, 0, lstrlenA(str), System::Text::Encoding::UTF8);
}

char* NETSDL2::Internal::StringMarshal::ManagedToUTF8Native(System::String^ str)
{
	if(str == nullptr)
		return __nullptr;

	int len = System::Text::Encoding::UTF8->GetByteCount(str);
	array<unsigned char>^ bytes = gcnew array<unsigned char>(len + 1);
	bytes[len] = 0;

	System::Text::Encoding::UTF8->GetBytes(str, 0, str->Length, bytes, 0);
	GCHandle handle = GCHandle::Alloc(bytes, GCHandleType::Pinned);
	clearList->Add(handle);

	return (char*)handle.AddrOfPinnedObject().ToPointer();
}

System::String^ NETSDL2::Internal::StringMarshal::ASCIINativeToManaged(const char* str)
{
	if(str == __nullptr)
		return System::String::Empty;

	return gcnew System::String(str, 0, lstrlenA(str), System::Text::Encoding::ASCII);
}

char* NETSDL2::Internal::StringMarshal::ManagedToASCIINative(System::String^ str)
{
	if(str == nullptr)
		return __nullptr;

	int len = System::Text::Encoding::ASCII->GetByteCount(str);
	array<unsigned char>^ bytes = gcnew array<unsigned char>(len + 1);
	bytes[len] = 0;

	System::Text::Encoding::ASCII->GetBytes(str, 0, str->Length, bytes, 0);
	GCHandle handle = GCHandle::Alloc(bytes, GCHandleType::Pinned);
	clearList->Add(handle);

	return (char*)handle.AddrOfPinnedObject().ToPointer();
}
