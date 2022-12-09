#pragma once

#include <SDL_image.h>

#include "InitFlags.h"

#using "NETSDL2.dll" as_friend

namespace NETSDL2
{
	namespace Image
	{
		using namespace NETSDL2::IO;

		/// <summary>
		/// NETSDL2_Image global functions.
		/// </summary>
		public ref struct Image abstract sealed
		{
		public:
			/// <summary>
			/// Initialize SDL_image.
			/// </summary>
			/// <param name="flags">Initialization flags, OR'd together.</param>
			/// <returns>All currently initialized flags.</returns>
			static InitFlags Init(InitFlags flags);

			/// <summary>
			/// Detect AVIF image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is AVIF data, false otherwise.</returns>
			static bool IsAVIF(RWops^ src);

			/// <summary>
			/// Detect BMP image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is BMP data, false otherwise.</returns>
			static bool IsBMP(RWops^ src);
		};
	}
}