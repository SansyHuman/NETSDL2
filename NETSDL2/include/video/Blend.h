#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"
#include "RendererInfo.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of blend factors used when creating a custom blend
		/// mode.
		/// </summary>
		public enum class BlendFactor
		{
			/// <summary>
			/// 0, 0, 0, 0
			/// </summary>
			Zero = SDL_BLENDFACTOR_ZERO,

			/// <summary>
			/// 1, 1, 1, 1
			/// </summary>
			One = SDL_BLENDFACTOR_ONE,

			/// <summary>
			/// srcR, srcG, srcB, srcA
			/// </summary>
			SrcColor = SDL_BLENDFACTOR_SRC_COLOR,

			/// <summary>
			/// 1-srcR, 1-srcG, 1-srcB, 1-srcA
			/// </summary>
			OneMinusSrcColor = SDL_BLENDFACTOR_ONE_MINUS_SRC_COLOR,

			/// <summary>
			/// srcA, srcA, srcA, srcA
			/// </summary>
			SrcAlpha = SDL_BLENDFACTOR_SRC_ALPHA,

			/// <summary>
			/// 1-srcA, 1-srcA, 1-srcA, 1-srcA
			/// </summary>
			OneMinusSrcAlpha = SDL_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,

			/// <summary>
			/// dstR, dstG, dstB, dstA
			/// </summary>
			DstColor = SDL_BLENDFACTOR_DST_COLOR,

			/// <summary>
			/// 1-dstR, 1-dstG, 1-dstB, 1-dstA
			/// </summary>
			OneMinusDstColor = SDL_BLENDFACTOR_ONE_MINUS_DST_COLOR,

			/// <summary>
			/// dstA, dstA, dstA, dstA
			/// </summary>
			DstAlpha = SDL_BLENDFACTOR_DST_ALPHA,

			/// <summary>
			/// 1-dstA, 1-dstA, 1-dstA, 1-dstA
			/// </summary>
			OneMinusDstAlpha = SDL_BLENDFACTOR_ONE_MINUS_DST_ALPHA,
		};

		/// <summary>
		/// An enumeration of blend operations used when creating a custom
		/// blend mode.
		/// </summary>
		public enum class BlendOperation
		{
			/// <summary>
			/// dst + src
			/// </summary>
			Add = SDL_BLENDOPERATION_ADD,

			/// <summary>
			/// dst - src
			/// </summary>
			Subtract = SDL_BLENDOPERATION_SUBTRACT,

			/// <summary>
			/// src - dst
			/// </summary>
			RevSubtract = SDL_BLENDOPERATION_REV_SUBTRACT,

			/// <summary>
			/// min(dst, src)
			/// </summary>
			Minimum = SDL_BLENDOPERATION_MINIMUM,

			/// <summary>
			/// max(dst, src)
			/// </summary>
			Maximum = SDL_BLENDOPERATION_MAXIMUM,
		};

		/// <summary>
		/// An enumeration of blend modes.
		/// </summary>
		public enum class BlendMode
		{
			/// <summary>
			/// dstRGBA = srcRGBA
			/// </summary>
			None = SDL_BLENDMODE_NONE,

			/// <summary>
			/// dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA)),
			/// dstA = srcA + (dstA * (1-srcA))
			/// </summary>
			Blend = SDL_BLENDMODE_BLEND,

			/// <summary>
			/// dstRGB = (srcRGB * srcA) + dstRGB, dstA = dstA
			/// </summary>
			Add = SDL_BLENDMODE_ADD,

			/// <summary>
			/// dstRGB = srcRGB * dstRGB, dstA = dstA
			/// </summary>
			Mod = SDL_BLENDMODE_MOD,

			/// <summary>
			/// dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA)),
			/// dstA = (srcA * dstA) + (dstA * (1-srcA))
			/// </summary>
			Mul = SDL_BLENDMODE_MUL,
		};

		/// <summary>
		/// Functions to make custom blend modes.
		/// </summary>
		public ref struct Blend abstract sealed
		{
		public:
			/// <summary>
			/// Compose a custom blend mode for renderers.
			/// </summary>
			/// <param name="srcColorFactor">The <see cref="BlendFactor"/>
			/// applied to the red, green, and blue components of the source
			/// pixels.</param>
			/// <param name="dstColorFactor">The <see cref="BlendFactor"/>
			/// applied to the red, green, and blue components of the destination
			/// pixels.</param>
			/// <param name="colorOperation">The <see cref="BlendOperation"/>
			/// used to combine the red, green, and blue components of the
			/// source and destination pixels.</param>
			/// <param name="srcAlphaFactor">The <see cref="BlendFactor"/>
			/// applied to the alpha component of the source pixels.</param>
			/// <param name="dstAlphaFactor">The <see cref="BlendFactor"/>
			/// applied to the alpha component of the destination pixels.</param>
			/// <param name="alphaOperation">The <see cref="BlendOperation"/>
			/// used to combine the alpha component of the source and
			/// destination pixels.</param>
			/// <returns><see cref="BlendMode"/> that represents the chosen
			/// factors and operations.</returns>
			static BlendMode ComposeCustomBlendMode(
				BlendFactor srcColorFactor,
				BlendFactor dstColorFactor,
				BlendOperation colorOperation,
				BlendFactor srcAlphaFactor,
				BlendFactor dstAlphaFactor,
				BlendOperation alphaOperation
			);
		};
	}
}
