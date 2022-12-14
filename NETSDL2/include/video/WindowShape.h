#pragma once

#include <SDL.h>
#include "Palette.h"

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enum denoting the specific type of contents present in an
		/// <see cref="WindowShapeParams"/> union.
		/// </summary>
		public enum class ShapeMode
		{
			/// <summary>
			/// The default mode, a binarized alpha cutoff of 1.
			/// </summary>
			Default = ShapeModeDefault,

			/// <summary>
			/// A binarized alpha cutoff with a given integer value.
			/// </summary>
			BinarizeAlpha = ShapeModeBinarizeAlpha,

			/// <summary>
			/// A binarized alpha cutoff with a given integer value, but with the
			/// opposite comparison.
			/// </summary>
			ReverseBinarizeAlpha = ShapeModeReverseBinarizeAlpha,

			/// <summary>
			/// A color key is applied.
			/// </summary>
			ColorKey = ShapeModeColorKey,
		};

		/// <summary>
		/// Shaped window errors.
		/// </summary>
		public enum class ShapedWindowError
		{
			/// <summary>
			/// Window given does not reference a valid shaped window.
			/// </summary>
			NonshapeableWindow = SDL_NONSHAPEABLE_WINDOW,

			/// <summary>
			/// An invalid shape argument
			/// </summary>
			InvalidShapeArgument = SDL_INVALID_SHAPE_ARGUMENT,

			/// <summary>
			/// Window given is a shapeable window currently lacking a shape.
			/// </summary>
			WindowLacksShape = SDL_WINDOW_LACKS_SHAPE,
		};

		/// <summary>
		/// Placeholder for creating shaped window.
		/// </summary>
		public value struct CreateShapedWindow
		{

		};

		/// <summary>
		/// A union containing parameters for shaped windows.
		/// </summary>
		[StructLayout(LayoutKind::Explicit, Size = sizeof(SDL_WindowShapeParams))]
		public value struct WindowShapeParams
		{
			/// <summary>
			/// A cutoff alpha value for binarization of the window shape's alpha channel.
			/// </summary>
			[FieldOffset(0)] Uint8 BinarizationCutoff;

			/// <summary>
			/// Color key value.
			/// </summary>
			[FieldOffset(0)] NETSDL2::Video::Color ColorKey;
		};

		/// <summary>
		/// A struct that tags the <see cref="WindowShapeParams"/> union with an enum describing the type
		/// of its contents.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct SDLWindowShapeMode
		{
			/// <summary>
			/// The mode of these window-shape parameters.
			/// </summary>
			ShapeMode Mode;

			/// <summary>
			/// Window-shape parameters.
			/// </summary>
			WindowShapeParams Parameters;
		};
	}
}