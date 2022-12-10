#pragma once

#include <SDL_image.h>

namespace NETSDL2
{
	namespace Image
	{
		/// <summary>
		/// Initialization flags
		/// </summary>
		[System::Flags]
		public enum class ImageInitFlags : int
		{
			None = 0,
			Jpg = IMG_INIT_JPG,
			Png = IMG_INIT_PNG,
			Tif = IMG_INIT_TIF,
			Webp = IMG_INIT_WEBP,
			Jxl = IMG_INIT_JXL,
			Avif = IMG_INIT_AVIF,
		};
	}
}