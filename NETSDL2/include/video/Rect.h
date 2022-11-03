#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// A structure that defines a two dimensional point.
		/// </summary>
		public value struct Point
		{
			/// <summary>
			/// The x coordinate of the point.
			/// </summary>
			int X;

			/// <summary>
			/// The y coordinate of the point.
			/// </summary>
			int Y;

			Point(int x, int y);

			virtual System::String^ ToString() override;
		};

		[StructLayout(LayoutKind::Sequential)]
		/// <summary>
		/// A structure that contains the definition of a rectangle, with the
		/// origin at the upper left.
		/// </summary>
		public value struct Rect
		{
			/// <summary>
			/// The x location of the rectangle's upper left corner.
			/// </summary>
			int X;

			/// <summary>
			/// The y location of the rectangle's upper left corner.
			/// </summary>
			int Y;

			/// <summary>
			/// The width of the rectangle.
			/// </summary>
			int W;

			/// <summary>
			/// The height of the rectangle.
			/// </summary>
			int H;

			Rect(int x, int y, int w, int h);

			virtual System::String^ ToString() override;
		};
	}
}