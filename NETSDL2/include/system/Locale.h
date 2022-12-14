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
		/// Locale information.
		/// </summary>
		public value struct Locale
		{
			/// <summary>
			/// A language name, like "en" for English.
			/// </summary>
			System::String^ Language;

			/// <summary>
			/// A country, like "US" for America. Can be null.
			/// </summary>
			System::String^ Country;

			/// <summary>
			/// Report the user's preferred locale.
			/// </summary>
			/// <returns>Array of locales or None on error.</returns>
			static Result<array<Locale>^, None^> GetPreferredLocales();

			virtual System::String^ ToString() override;
		};

	}
}