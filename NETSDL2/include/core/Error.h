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
			/// Get the last error message that was set for the current thread.
			/// </summary>
			/// <param name="errstr">A buffer to fill with the last error message that was set for the
			/// current thread.</param>
			/// <param name="maxlen">The size of the buffer pointed to by the errstr parameter.</param>
			/// <returns>The pointer passed in as the errstr parameter.</returns>
			static char* GetErrorMsg(char* errstr, int maxlen);

			/// <summary>
			/// Set the SDL error message for the current thread.
			/// </summary>
			/// <param name="format">Message format string.</param>
			/// <param name="args">Additional parameters of format string.</param>
			static void SetError(System::String^ format, ...array<Object^>^ args);
		};
	}
}