#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace IO
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Functions for getting commonly used paths such as the application
		/// directory and the user write directory.
		/// </summary>
		public ref struct Filesystem abstract sealed
		{
		public:
			/// <summary>
			/// Get the directory where the application was run from.
			/// </summary>
			/// <returns>An absolute path to the application data directory or
			/// None on error or when the platform doesn't implement this
			/// functionallity.</returns>
			static Result<System::String^, None^> GetBasePath();

			/// <summary>
			/// Get the user-and-app-specific path where files can be written.
			/// </summary>
			/// <param name="org">The name of your organization.</param>
			/// <param name="app">The name of your application.</param>
			/// <returns>A string of the user directory in platform-dependent
			/// notation. None if there's a problem.</returns>
			static Result<System::String^, None^> GetPrefPath(System::String^ org, System::String^ app);
		};
	}
}