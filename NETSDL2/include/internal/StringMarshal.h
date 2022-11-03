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

			static System::String^ UTF8NativeToManaged(const char* str);
			char* ManagedToUTF8Native(System::String^ str);
		};
	}
}