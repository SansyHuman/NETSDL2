#pragma once

#include <SDL.h>

namespace NETSDL2
{
	namespace Core
	{
		ref class None;
		generic<class Success, class Failure>
		value class Result;

		[System::Flags]
		/// <summary>
		/// Subsystems of SDL2.
		/// </summary>
		public enum class SubSystems : Uint32
		{
			/// <summary>
			/// No subsystem. Zero.
			/// </summary>
			None = 0U,

			/// <summary>
			/// Timer subsystem.
			/// </summary>
			Timer = SDL_INIT_TIMER,

			/// <summary>
			/// Audio subsystem.
			/// </summary>
			Audio = SDL_INIT_AUDIO,

			/// <summary>
			/// Video subsystem. Automatically initializes events subsystem.
			/// </summary>
			Video = SDL_INIT_VIDEO,
			
			/// <summary>
			/// Joystick subsystem. Automatically initializes events subsystem.
			/// </summary>
			Joystick = SDL_INIT_JOYSTICK,
			
			/// <summary>
			/// Haptic (force feedback) subsystem.
			/// </summary>
			Haptic = SDL_INIT_HAPTIC,
			
			/// <summary>
			/// Controller subsystem. Automatically initializes joystick subsystem.
			/// </summary>
			GameController = SDL_INIT_GAMECONTROLLER,
			
			/// <summary>
			/// Events subsystem.
			/// </summary>
			Events = SDL_INIT_EVENTS,

			/// <summary>
			/// All subsystems.
			/// </summary>
			Everything = SDL_INIT_EVERYTHING
		};

		/// <summary>
		/// Core SDL functions.
		/// </summary>
		public ref struct SDL abstract sealed
		{
		public:
			/// <summary>
			/// Initialize the SDL library.
			/// </summary>
			/// <param name="flags">Subsystems to initialize.</param>
			/// <returns>None if succeeded, error code if failed.</returns>
			static Result<None^, int> Init(SubSystems flags);

			/// <summary>
			/// Initialize the SDL library.
			/// </summary>
			/// <param name="flags">Subsystems to initialize.</param>
			/// <returns>None if succeeded, error code if failed.</returns>
			static Result<None^, int> InitSubsystem(SubSystems flags);

			/// <summary>
			/// Clean up all initialized subsystems.
			/// </summary>
			static void Quit();

			/// <summary>
			/// Shut down specific SDL subsystems.
			/// </summary>
			/// <param name="flags">Subsystems to shut down.</param>
			static void QuitSubSystem(SubSystems flags);

			/// <summary>
			/// Circumvent failure of SDL::Init() when not using SDL_main() as an
			/// entry point.
			/// </summary>
			static void SetMainReady();

			/// <summary>
			/// Get a mask of the specified subsystems which are currently
			/// initialized.
			/// </summary>
			/// <param name="flags">any of the flags used by SDL::Init().</param>
			/// <returns>A mask of all initialized subsystems if flags is 0,
			/// otherwise it returns the initialization status of the specified
			/// subsystems.</returns>
			static SubSystems WasInit(SubSystems flags);

			/// <summary>
			/// Gets and sets whether to throw exception on failure results if
			/// the function returns <see cref="NETSDL2::Core::Result"/> value.
			/// </summary>
			static property bool ThrowOnFailure;
		};
	}
}