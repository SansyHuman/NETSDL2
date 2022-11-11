#pragma once

#include <SDL.h>

#include "Palette.h"
#include "Rect.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// Vertex structure
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct Vertex
		{
			/// <summary>
			/// Vertex position, in Renderer coordinates.
			/// </summary>
			NETSDL2::Video::FPoint Position;

			/// <summary>
			/// Vertex color
			/// </summary>
			NETSDL2::Video::Color Color;

			/// <summary>
			/// Normalized texture coordinates, if needed (Range from 0 to 1, i.ie
			/// for a 64x64px texture, beginning at 32x32px will be entered as
			/// 0.5,0,5)
			/// </summary>
			NETSDL2::Video::FPoint TexCoord;

			Vertex(
				[In][IsReadOnly]NETSDL2::Video::FPoint% position,
				[In][IsReadOnly]NETSDL2::Video::Color% color,
				[In][IsReadOnly]NETSDL2::Video::FPoint% texCoord);

			virtual System::String^ ToString() override;
		};
	}
}