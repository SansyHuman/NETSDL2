#pragma once

#include <SDL.h>

#include "PixelFormat.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of flags used when creating a rendering context.
		/// </summary>
		[System::Flags]
		public enum class RendererFlags : Uint32
		{
			None = 0,

			/// <summary>
			/// The renderer is a software fallback.
			/// </summary>
			Software = SDL_RENDERER_SOFTWARE,

			/// <summary>
			/// The renderer uses hardware acceleration.
			/// </summary>
			Accelerated = SDL_RENDERER_ACCELERATED,

			/// <summary>
			/// Present is synchronized with the refresh rate.
			/// </summary>
			PresentVsync = SDL_RENDERER_PRESENTVSYNC,

			/// <summary>
			/// The renderer supports rendering to texture.
			/// </summary>
			TargetTexture = SDL_RENDERER_TARGETTEXTURE,
		};

		/// <summary>
		/// An enumeration of flags that can be used in the flip parameter.
		/// </summary>
		[System::Flags]
		public enum class RendererFlip
		{
			/// <summary>
			/// Do not flip.
			/// </summary>
			None = SDL_FLIP_NONE,

			/// <summary>
			/// Flip horizontally.
			/// </summary>
			Horizontal = SDL_FLIP_HORIZONTAL,

			/// <summary>
			/// Flip vertically.
			/// </summary>
			Vertical = SDL_FLIP_VERTICAL,
		};

		/// <summary>
		/// A structure that contains information on the capabilities of a
		/// render driver or the current render context.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct RendererInfo
		{
		public:
			[StructLayout(LayoutKind::Sequential, Size = 64)]
			[CompilerGenerated]
			[UnsafeValueType]
			value struct e__FixedBuffer
			{
				PixelFormatEnum FixedElementField;

				property PixelFormatEnum default[int]
				{
					PixelFormatEnum get(int index);
				}
			};

		private:
			char* name;

		public:
			/// <summary>
			/// A mask of supported renderer flags.
			/// </summary>
			RendererFlags Flags;

			/// <summary>
			/// The number of available texture formats.
			/// </summary>
			Uint32 NumTextureFormats;
			
			/// <summary>
			/// The available texture formats.
			/// </summary>
			[FixedBuffer(PixelFormatEnum::typeid, 16)]
			e__FixedBuffer TextureFormats;

			/// <summary>
			/// The maximum texture width.
			/// </summary>
			int MaxTextureWidth;

			/// <summary>
			/// The maximum texture height.
			/// </summary>
			int MaxTextureHeight;

			/// <summary>
			/// The name of the renderer.
			/// </summary>
			property System::String^ Name
			{
				System::String^ get();
			}

			virtual System::String^ ToString() override;
		};
	}
}