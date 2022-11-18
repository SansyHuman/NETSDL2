#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// The different sensors defined by SDL.
		/// </summary>
		public enum class SensorType : Sint32
		{
			/// <summary>
			/// Returned for an invalid sensor.
			/// </summary>
			Invalid = SDL_SENSOR_INVALID,

			/// <summary>
			/// Unknown sensor type.
			/// </summary>
			Unknown = SDL_SENSOR_UNKNOWN,

			/// <summary>
			/// Accelerometer.
			/// </summary>
			Accel = SDL_SENSOR_ACCEL,

			/// <summary>
			/// Gyroscope.
			/// </summary>
			Gyro = SDL_SENSOR_GYRO,
		};
	}
}