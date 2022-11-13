#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// Wrapper of native ICCProfile pointer
		/// </summary>
		public ref class ICCProfile
		{
		private:
			System::IntPtr profile;
			size_t size;

		internal:
			ICCProfile(void* profile, size_t size);

		public:
			~ICCProfile();
			!ICCProfile();

			/// <summary>
			/// Native profile pointer.
			/// </summary>
			property System::IntPtr Profile
			{
				System::IntPtr get();
			}

			/// <summary>
			/// Size of the profile.
			/// </summary>
			property size_t Size
			{
				size_t get();
			}
		};
	}
}