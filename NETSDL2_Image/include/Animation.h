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
		/// Animated image support.
		/// </summary>
		public ref class Animation
		{
		private:
			IMG_Animation* anim;
			array<Surface^>^ frames;

			void InitAnimation(IMG_Animation* anim);

		internal:
			Animation(IMG_Animation* anim);

		public:
			/// <summary>
			/// Load an animation from a file.
			/// </summary>
			/// <param name="file">Path on the filesystem containing an animated
			/// image.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Animation(System::String^ file);

			/// <summary>
			/// Load an animation from an RWops.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// false to leave it open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Animation(RWops^ src, bool freesrc);

			/// <summary>
			/// Load an animation from an SDL datasource
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <param name="freesrc">true to close/free the RWops before returning,
			/// false to leave it open.</param>
			/// <param name="type">A filename extension that represent this data
			/// ("GIF", etc).</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Animation(RWops^ src, bool freesrc, System::String^ type);

			~Animation();
			!Animation();

			/// <summary>
			/// Get the width of the image.
			/// </summary>
			property int Width
			{
				int get();
			}

			/// <summary>
			/// Get the height of the image.
			/// </summary>
			property int Height
			{
				int get();
			}

			/// <summary>
			/// Get the frame count of the animation;
			/// </summary>
			property int Count
			{
				int get();
			}

			/// <summary>
			/// Get the frame at the index.
			/// </summary>
			property Surface^ default[int]
			{
				Surface ^get(int index);
			}

			/// <summary>
			/// Get the delay of the frame.
			/// </summary>
			/// <param name="frame">Index of the frame.</param>
			/// <returns>The delay of the frame.</returns>
			int GetDelay(int frame);

			/// <summary>
			/// Load a GIF animation directly.
			/// </summary>
			/// <param name="src">A RWops that data will be read from.</param>
			/// <returns>A new Animation, or None on error.</returns>
			static Result<Animation^, None^> LoadGIFAnimation(RWops^ src);
		};
	}
}