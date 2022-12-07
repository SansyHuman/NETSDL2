#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// SDL Guid struct.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct GUID
		{
		public:
			[StructLayout(LayoutKind::Sequential, Size = sizeof(Uint8) * 16)]
			[CompilerGenerated]
			[UnsafeValueType]
			value struct e__FixedBuffer
			{
				Uint8 FixedElementField;
			};

		public:
			[FixedBuffer(Uint8::typeid, 16)]
			e__FixedBuffer Data;

			/// <summary>
			/// onvert a GUID string into a GUID structure.
			/// </summary>
			/// <param name="guid">String containing an ASCII representation of a GUID.</param>
			GUID(System::String^ guid);

			virtual System::String^ ToString() override;
		};
	}
}