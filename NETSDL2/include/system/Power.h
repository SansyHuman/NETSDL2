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
		/// An enumeration of the basic state of the system's power supply.
		/// </summary>
		public enum class PowerState
		{
			/// <summary>
			/// Cannot determine power status.
			/// </summary>
			Unknown = SDL_POWERSTATE_UNKNOWN,

			/// <summary>
			/// Not plugged in, running on the battery.
			/// </summary>
			OnBattery = SDL_POWERSTATE_ON_BATTERY,

			/// <summary>
			/// Plugged in, no battery available.
			/// </summary>
			NoBattery = SDL_POWERSTATE_NO_BATTERY,

			/// <summary>
			/// Plugged in, charging battery.
			/// </summary>
			Charging = SDL_POWERSTATE_CHARGING,

			/// <summary>
			/// Plugged in, battery charged.
			/// </summary>
			Charged = SDL_POWERSTATE_CHARGED
		};

		/// <summary>
		/// Functions for handling SDL power management routines.
		/// </summary>
		public ref struct Power abstract sealed
		{
		public:
			/// <summary>
			/// Get the current power supply details.
			/// </summary>
			/// <param name="secs">Seconds of battery life left.</param>
			/// <param name="pct">Percentage of battery life left.</param>
			/// <returns>The current battery state.</returns>
			static PowerState GetPowerInfo([Out]int% secs, [Out]int% pct);
		};
	}
}