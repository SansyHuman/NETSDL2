#pragma once

#include <SDL.h>

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Error handling functions.
		/// </summary>
		public ref struct Error abstract sealed
		{
		public:
			/// <summary>
			/// Clear any previous error message for this thread.
			/// </summary>
			static void ClearError();

			/// <summary>
			/// Retrieve a message about the last error that occurred on the
			/// current thread.
			/// </summary>
			/// <returns>A message with information about the specific error
			/// that occured, or an empy string if there hasn't been an error
			/// message.</returns>
			static System::String^ GetError();

			/// <summary>
			/// Set the SDL error message for the current thread.
			/// </summary>
			/// <param name="format">Message format string.</param>
			/// <param name="args">Additional parameters of format string.</param>
			static void SetError(System::String^ format, ...array<Object^>^ args);
		};
	}
}