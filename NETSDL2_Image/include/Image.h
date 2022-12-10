#pragma once

#include <SDL_image.h>

#include "InitFlags.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Image
	{
		using namespace NETSDL2::IO;
		using namespace NETSDL2::Core;
		using namespace NETSDL2::Video;

		/// <summary>
		/// NETSDL2_Image global functions.
		/// </summary>
		[Extension]
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
			[Extension]
			static bool IsAVIF(RWops^ src);

			/// <summary>
			/// Detect BMP image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is BMP data, false otherwise.</returns>
			[Extension]
			static bool IsBMP(RWops^ src);

			/// <summary>
			/// Detect CUR image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is CUR data, false otherwise.</returns>
			[Extension]
			static bool IsCUR(RWops^ src);

			/// <summary>
			/// Detect GIF image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is GIF data, false otherwise.</returns>
			[Extension]
			static bool IsGIF(RWops^ src);

			/// <summary>
			/// Detect ICO image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is ICO data, false otherwise.</returns>
			[Extension]
			static bool IsICO(RWops^ src);

			/// <summary>
			/// Detect JPG image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is JPG data, false otherwise.</returns>
			[Extension]
			static bool IsJPG(RWops^ src);

			/// <summary>
			/// Detect JXL image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is JXL data, false otherwise.</returns>
			[Extension]
			static bool IsJXL(RWops^ src);

			/// <summary>
			/// Detect LBM image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is LBM data, false otherwise.</returns>
			[Extension]
			static bool IsLBM(RWops^ src);

			/// <summary>
			/// Detect PCX image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is PCX data, false otherwise.</returns>
			[Extension]
			static bool IsPCX(RWops^ src);

			/// <summary>
			/// Detect PNG image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is PNG data, false otherwise.</returns>
			[Extension]
			static bool IsPNG(RWops^ src);

			/// <summary>
			/// Detect PNM image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is PNM data, false otherwise.</returns>
			[Extension]
			static bool IsPNM(RWops^ src);

			/// <summary>
			/// Detect QOI image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is QOI data, false otherwise.</returns>
			[Extension]
			static bool IsQOI(RWops^ src);

			/// <summary>
			/// Detect SVG image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is SVG data, false otherwise.</returns>
			[Extension]
			static bool IsSVG(RWops^ src);

			/// <summary>
			/// Detect TIFF image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is TIFF data, false otherwise.</returns>
			[Extension]
			static bool IsTIF(RWops^ src);

			/// <summary>
			/// Detect WEBP image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is WEBP data, false otherwise.</returns>
			[Extension]
			static bool IsWEBP(RWops^ src);

			/// <summary>
			/// Detect XCF image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is XCF data, false otherwise.</returns>
			[Extension]
			static bool IsXCF(RWops^ src);

			/// <summary>
			/// Detect XPM image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is XPM data, false otherwise.</returns>
			[Extension]
			static bool IsXPM(RWops^ src);

			/// <summary>
			/// Detect XV image data on a readable/seekable RWops.
			/// </summary>
			/// <param name="src">A seekable/readable RWops to provide image data.
			/// </param>
			/// <returns>true if this is XV data, false otherwise.</returns>
			[Extension]
			static bool IsXV(RWops^ src);

			/// <summary>
			/// This function gets the version of the dynamically linked SDL_image
			/// library.
			/// </summary>
			/// <returns>SDL_image version.</returns>
			static SDLVersion LinkedVersion();

			/// <summary>
			/// Load an image from a filesystem path into a software surface.
			/// </summary>
			/// <param name="file">A path on the filesystem to load an image from.
			/// </param>
			/// <returns>A new SDL surface, or None on error.</returns>
			static Result<Surface^, None^> Load(System::String^ file);

			/// <summary>
			/// Load an image from an SDL data source into a software surface.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// zero to leave it open.</param>
			/// <returns>A new SDL surface, or None on error.</returns>
			static Result<Surface^, None^> Load(RWops^ src, bool freesrc);

			/// <summary>
			/// Load a AVIF image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadAVIF(RWops^ src);

			/// <summary>
			/// Load a BMP image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadBMP(RWops^ src);

			/// <summary>
			/// Load a CUR image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadCUR(RWops^ src);

			/// <summary>
			/// Load a GIF image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadGIF(RWops^ src);

			/// <summary>
			/// Load a ICO image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadICO(RWops^ src);

			/// <summary>
			/// Load a JPG image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadJPG(RWops^ src);

			/// <summary>
			/// Load a JXL image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadJXL(RWops^ src);

			/// <summary>
			/// Load a LBM image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadLBM(RWops^ src);

			/// <summary>
			/// Load a PCX image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadPCX(RWops^ src);

			/// <summary>
			/// Load a PNG image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadPNG(RWops^ src);

			/// <summary>
			/// Load a PNM image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadPNM(RWops^ src);

			/// <summary>
			/// Load a QOI image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadQOI(RWops^ src);

			/// <summary>
			/// Load an SVG image, scaled to a specific size.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <param name="width">Desired width of the generated surface, in pixels.
			/// </param>
			/// <param name="height">Desired height of the generated surface, in pixels.
			/// </param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadSizedSVG(RWops^ src, int width, int height);

			/// <summary>
			/// Load a SVG image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadSVG(RWops^ src);

			/// <summary>
			/// Load an image from a filesystem path into a GPU texture.
			/// </summary>
			/// <param name="renderer">The Renderer to use to create the GPU texture.
			/// </param>
			/// <param name="file">A path on the filesystem to load an image from.
			/// </param>
			/// <returns>A new texture, or None on error.</returns>
			[Extension]
			static Result<Texture^, None^> LoadTexture(Renderer^ renderer, System::String^ file);

			/// <summary>
			/// Load an image from an SDL data source into a GPU texture.
			/// </summary>
			/// <param name="renderer">The Renderer to use to create the GPU texture.
			/// </param>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning
			/// false to leave it open.</param>
			/// <returns>A new texture, or None on error.</returns>
			[Extension]
			static Result<Texture^, None^> LoadTexture(Renderer^ renderer, RWops^ src, bool freesrc);

			/// <summary>
			/// Load an image from an SDL data source into a GPU texture.
			/// </summary>
			/// <param name="renderer">The Renderer to use to create the GPU texture.
			/// </param>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning
			/// false to leave it open.</param>
			/// <param name="type">A filename extension that represent this data
			/// ("BMP", "GIF", "PNG", etc).</param>
			/// <returns>A new texture, or None on error.</returns>
			[Extension]
			static Result<Texture^, None^> LoadTexture(Renderer^ renderer, RWops^ src, bool freesrc, System::String^ type);

			/// <summary>
			/// Load a TGA image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadTGA(RWops^ src);

			/// <summary>
			/// Load a TIFF image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadTIF(RWops^ src);

			/// <summary>
			/// Load an image from an SDL data source into a software surface.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// zero to leave it open.</param>
			/// <param name="type">A filename extension that represent this data
			/// ("BMP", "GIF", "PNG", etc).</param>
			/// <returns>A new SDL surface, or None on error.</returns>
			static Result<Surface^, None^> Load(RWops^ src, bool freesrc, System::String^ type);

			/// <summary>
			/// Load a WEBP image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadWEBP(RWops^ src);

			/// <summary>
			/// Load a XCF image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadXCF(RWops^ src);

			/// <summary>
			/// Load a XPM image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadXPM(RWops^ src);

			/// <summary>
			/// Load a XV image directly.
			/// </summary>
			/// <param name="src">A RWops to load image data from.</param>
			/// <returns>SDL surface, or None on error.</returns>
			[Extension]
			static Result<Surface^, None^> LoadXV(RWops^ src);

			/// <summary>
			/// Deinitialize SDL_image.
			/// </summary>
			static void Quit();

			/// <summary>
			/// Load an XPM image from a memory array.
			/// </summary>
			/// <param name="xpm">A null-terminated array of strings that comprise
			/// XPM data.</param>
			/// <returns>A new SDL surface, or None on error.</returns>
			static Result<Surface^, None^> ReadXPMFromArray(char** xpm);

			/// <summary>
			/// Load an XPM image from a memory array.
			/// </summary>
			/// <param name="xpm">An array of strings that comprise XPM data.</param>
			/// <returns>A new SDL surface, or None on error.</returns>
			static Result<Surface^, None^> ReadXPMFromArray(array<System::String^>^ xpm);

			/// <summary>
			/// Load an XPM image from a memory array.
			/// </summary>
			/// <param name="xpm">A null-terminated array of strings that comprise
			/// XPM data.</param>
			/// <returns>A 32-bit RGB surface, or None on error.</returns>
			static Result<Surface^, None^> ReadXPMFromArrayToRGB888(char** xpm);

			/// <summary>
			/// Load an XPM image from a memory array.
			/// </summary>
			/// <param name="xpm">An array of strings that comprise XPM data.</param>
			/// <returns>A 32-bit RGB surface, or None on error.</returns>
			static Result<Surface^, None^> ReadXPMFromArrayToRGB888(array<System::String^>^ xpm);

			/// <summary>
			/// Save a Surface into a JPEG image file.
			/// </summary>
			/// <param name="surface">The SDL surface to save.</param>
			/// <param name="file">Path on the filesystem to write new file to.</param>
			/// <param name="quality">[0; 33] is Lowest quality, [34; 66] is Middle
			/// quality, [67; 100] is Highest quality.</param>
			/// <returns>Success or Failure on error.</returns>
			[Extension]
			static Result<None^, None^> SaveJPG(Surface^ surface, System::String^ file, int quality);

			/// <summary>
			/// Save a Surface into a JPEG image data, via an RWops.
			/// </summary>
			/// <param name="surface">The SDL surface to save.</param>
			/// <param name="dst">The RWops to save the image data to.</param>
			/// <param name="freedst">true to close/free the RWops before returning,
			/// zero to leave it open.</param>
			/// <param name="quality">[0; 33] is Lowest quality, [34; 66] is Middle
			/// quality, [67; 100] is Highest quality.</param>
			/// <returns>Success or Failure on error.</returns>
			[Extension]
			static Result<None^, None^> SaveJPG(Surface^ surface, RWops^ dst, bool freedst, int quality);

			/// <summary>
			/// Save a Surface into a PNG image file.
			/// </summary>
			/// <param name="surface">The SDL surface to save.</param>
			/// <param name="file">Path on the filesystem to write new file to.</param>
			/// <returns>Success or Failure on error.</returns>
			[Extension]
			static Result<None^, None^> SavePNG(Surface^ surface, System::String^ file);

			/// <summary>
			/// Save a Surface into a PNG image data, via an RWops.
			/// </summary>
			/// <param name="surface">The SDL surface to save.</param>
			/// <param name="dst">The RWops to save the image data to.</param>
			/// <param name="freedst">true to close/free the RWops before returning,
			/// zero to leave it open.</param>
			/// <returns>Success or Failure on error.</returns>
			[Extension]
			static Result<None^, None^> SavePNG(Surface^ surface, RWops^ dst, bool freedst);
		};
	}
}