#pragma once

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Internal
	{
		ref class StringMarshal
		{
		private:
			System::Collections::Generic::List<GCHandle>^ clearList;

		internal:
			StringMarshal();
			~StringMarshal();

			// Convert native UTF8 string to managed string.
			static System::String^ UTF8NativeToManaged(const char* str);

			// Convert managed string to native UTF8 string.
			char* ManagedToUTF8Native(System::String^ str);

			// Convert native ASCII string to managed string.
			static System::String^ ASCIINativeToManaged(const char* str);

			// Convert managed string to native ASCII string.
			char* ManagedToASCIINative(System::String^ str);
		};
	}
}