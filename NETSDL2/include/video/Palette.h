#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// A structure that represents a color.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Color
		{
			/// <summary>
			/// The red component in the range 0-255.
			/// </summary>
			Uint8 R;

			/// <summary>
			/// The green component in the range 0-255.
			/// </summary>
			Uint8 G;

			/// <summary>
			/// The blue component in the range 0-255.
			/// </summary>
			Uint8 B;

			/// <summary>
			/// The alpha component in the range 0-255.
			/// </summary>
			Uint8 A;

			Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

			virtual System::String^ ToString() override;
		};

		/// <summary>
		/// A structure that contains palette information.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Palette
		{
		private:
			int nColors;
			Color* Colors;
			Uint32 Version;
			int Refcount;

		public:
			/// <summary>
			/// The number of colors in the palette.
			/// </summary>
			property int NumColors
			{
				int get();
			}

			/// <summary>
			/// Color element in the palette.
			/// </summary>
			/// <exception cref="System::IndexOutOfRangeException">
			/// Thrown when the index is out of bound.
			/// </exception>
			property Color default[int]
			{
				Color get(int index);
			}
		};
	}
}