#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Systems
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Shared objet.
		/// </summary>
		public ref class SharedObject
		{
		private:
			void* object;

		public:
			/// <summary>
			/// Dynamically load a shared object.
			/// </summary>
			/// <param name="sofile">A system-dependent name of the object file.</param>
			/// <exception cref="System::Exception">Thrown when failed load.
			/// </exception>
			SharedObject(System::String^ sofile);

			~SharedObject();
			!SharedObject();

			/// <summary>
			/// Look up the address of the named function in a shared object.
			/// </summary>
			/// <param name="name">The name of the function to look up.</param>
			/// <returns>A pointer to the function or None if there was an error.</returns>
			Result<System::IntPtr, None^> LoadFunction(System::String^ name);
		};
	}
}