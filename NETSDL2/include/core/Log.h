#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Log categories.
		/// </summary>
		public enum class LogCategory
		{
			Application = SDL_LOG_CATEGORY_APPLICATION,
			Error = SDL_LOG_CATEGORY_ERROR,
			Assert = SDL_LOG_CATEGORY_ASSERT,
			System = SDL_LOG_CATEGORY_SYSTEM,
			Audio = SDL_LOG_CATEGORY_AUDIO,
			Video = SDL_LOG_CATEGORY_VIDEO,
			Render = SDL_LOG_CATEGORY_RENDER,
			Input = SDL_LOG_CATEGORY_INPUT,
			Test = SDL_LOG_CATEGORY_TEST,

			/// <summary>
			/// Reserved for application use.
			/// </summary>
			Custom = SDL_LOG_CATEGORY_CUSTOM
		};

		/// <summary>
		/// Log priprities.
		/// </summary>
		public enum class LogPriority
		{
			Verbose = SDL_LOG_PRIORITY_VERBOSE,
			Debug = SDL_LOG_PRIORITY_DEBUG,
			Info = SDL_LOG_PRIORITY_INFO,
			Warn = SDL_LOG_PRIORITY_WARN,
			Error = SDL_LOG_PRIORITY_ERROR,
			Critical = SDL_LOG_PRIORITY_CRITICAL,
		};

		/// <summary>
		/// Delegate for output function of logging.
		/// </summary>
		/// <param name="userData">User data passed at
		/// <see cref="Loggingg::SetOutputFunction"/>.</param>
		/// <param name="category">Category of the message.</param>
		/// <param name="priority">Priority of the message.</param>
		/// <param name="message">Log message.</param>
		public delegate void LogOutputFunction(System::IntPtr userData, LogCategory category, LogPriority priority, System::String^ message);

		[UnmanagedFunctionPointer(CallingConvention::Cdecl)]
		delegate void NativeLogOutputFunction(void* userdata, int category, SDL_LogPriority priority, const char* message);

		/// <summary>
		/// Functions for handling log messages.
		/// </summary>
		public ref struct Logging abstract sealed
		{
		private:
			static bool logInit = false;

			static SDL_LogOutputFunction nativeCallback;
			static LogOutputFunction^ callback;

			static GCHandle callbackHandle;

			static Object^ logOutputSetLock;

			static void LogOutputNative(void* userdata, int category, SDL_LogPriority priority, const char* message);
			static void DefaultLogOutputFunction(System::IntPtr userData, LogCategory category, LogPriority priority, System::String^ message);
		internal:
			static void Init();
			static void Quit();

		public:
			/// <summary>
			/// Log a message with <see cref="LogCategory::Application"/> and
			/// <see cref="LogPriority::Info"/>.
			/// </summary>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void Log(System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Critical"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogCritical(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Debug"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogDebug(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Error"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogError(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Info"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogInfo(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Verbose"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogVerbose(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with <see cref="LogPriority::Warn"/>.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogWarn(LogCategory category, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Log a message with specified category and priority.
			/// </summary>
			/// <param name="category">Category of the message.</param>
			/// <param name="priority">Priority of the message.</param>
			/// <param name="format">Format string.</param>
			/// <param name="args">Arguments of the format string.</param>
			static void LogMessage(LogCategory category, LogPriority priority, System::String^ format, ...array<Object^>^ args);

			/// <summary>
			/// Get the current log output function.
			/// </summary>
			/// <param name="userdata">A pointer filled in with the pointer that is
			/// passed to callback.</param>
			/// <returns>Current log output function delegate.</returns>
			static LogOutputFunction^ GetOutputFunction([Out]System::IntPtr% userdata);

			/// <summary>
			/// Get the current log output function.
			/// </summary>
			/// <param name="userdata">A pointer filled in with the pointer that is
			/// passed to callback.</param>
			/// <returns>Current log output function delegate.</returns>
			static LogOutputFunction^ GetOutputFunction(void** userdata);

			/// <summary>
			/// Replace the default log output function with one of your own.
			/// </summary>
			/// <param name="callback">A callback function to call instead of the
			/// default.</param>
			/// <param name="userdata">A pointer that is passed to callback.</param>
			static void SetOutputFunction(LogOutputFunction^ callback, System::IntPtr userdata);

			/// <summary>
			/// Replace the default log output function with one of your own.
			/// </summary>
			/// <param name="callback">A callback function to call instead of the
			/// default.</param>
			/// <param name="userdata">A pointer that is passed to callback.</param>
			static void SetOutputFunction(LogOutputFunction^ callback, void* userdata);

			/// <summary>
			/// Get the priority of a particular log category.
			/// </summary>
			/// <param name="category">The category to query.</param>
			/// <returns>Priority of requested category.</returns>
			static LogPriority GetPriority(LogCategory category);

			/// <summary>
			/// Set the priority of a particular log category.
			/// </summary>
			/// <param name="category">The category to assign a priority to.</param>
			/// <param name="priority">The priority to assign.</param>
			static void SetPriority(LogCategory category, LogPriority priority);

			/// <summary>
			/// Set the priority of all log categories.
			/// </summary>
			/// <param name="priority">The priority to assign.</param>
			static void SetAllPriority(LogPriority priority);

			/// <summary>
			/// Reset all priorities to default.
			/// </summary>
			static void ResetPriorities();
		};
	}
}