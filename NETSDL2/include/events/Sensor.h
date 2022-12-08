#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "Joysticks.h"
#include "Event.h"
#include "Button.h"
#include "Sensors.h"
#include "../core/GUID.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Sensor class.
		/// </summary>
		public ref class Sensor
		{
		private:
			SDL_Sensor* sensor;
			static System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Sensor^>^ nativeSensorConnections;

			static Sensor()
			{
				nativeSensorConnections = gcnew System::Collections::Concurrent::ConcurrentDictionary<System::IntPtr, Sensor^>();
			}

			void InitSensor(SDL_Sensor* sensor);

		public:
			/// <summary>
			/// Standard gravitational acceleration.
			/// </summary>
			literal float StandardGravity = SDL_STANDARD_GRAVITY;

			/// <summary>
			/// Open a sensor for use.
			/// </summary>
			/// <param name="deviceIndex">The index of a device, up to
			/// <see cref="Joystick::NumJoysticks"/>.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Sensor(int deviceIndex);

			~Sensor();
			!Sensor();

			/// <summary>
			/// Locking for multi-threaded access to the sensor API.
			/// </summary>
			static void Lock();

			/// <summary>
			/// Unlocking for multi-threaded access to the sensor API
			/// </summary>
			static void Unlock();

			/// <summary>
			/// Count the number of sensors attached to the system right now.
			/// </summary>
			static property int NumSensors
			{
				int get();
			}

			/// <summary>
			/// Return the Sensor associated with an instance id.
			/// </summary>
			/// <param name="instanceID">The sensor from instance id.</param>
			/// <returns>A Sensor object or None on error.</returns>
			static Result<Sensor^, None^> SensorFromInstanceID(SDL_SensorID instanceID);

			/// <summary>
			/// Get the current state of an opened sensor.
			/// </summary>
			/// <param name="data">A pointer filled with the current sensor state.
			/// </param>
			/// <param name="numValues">The number of values to write to data.</param>
			/// <returns>Success or Failure if an error occured.</returns>
			Result<None^, None^> GetData(float* data, int numValues);

			/// <summary>
			/// Get the current state of an opened sensor.
			/// </summary>
			/// <param name="data">An array filled with the current sensor state.</param>
			/// <param name="offset">Offset from the start of the array.</param>
			/// <param name="numValues">The number of values to write to data.</param>
			/// <returns>Success or Failure if an error occured.</returns>
			Result<None^, None^> GetData(array<float>^ data, int offset, int numValues);

			/// <summary>
			/// Get the instance ID of a sensor.
			/// </summary>
			/// <param name="deviceIndex">The sensor to get instance id from.</param>
			/// <returns>The sensor instance ID, or None if device index is out of
			/// range.</returns>
			static Result<SDL_SensorID, None^> GetDeviceInstanceID(int deviceIndex);

			/// <summary>
			/// Get the implementation dependent name of a sensor.
			/// </summary>
			/// <param name="deviceIndex">The sensor to obtain name from.</param>
			/// <returns>The sensor name, or None if device index is out of range.
			/// </returns>
			static Result<System::String^, None^> GetDeviceName(int deviceIndex);

			/// <summary>
			/// Get the platform dependent type of a sensor.
			/// </summary>
			/// <param name="deviceIndex">The sensor to check.</param>
			/// <returns>The sensor platform dependent type, or None if device index
			/// is out of range.</returns>
			static Result<int, None^> GetDeviceNonPortableType(int deviceIndex);

			/// <summary>
			/// Get the type of a sensor.
			/// </summary>
			/// <param name="deviceIndex">The sensor to get the type from.</param>
			/// <returns>The <see cref="SensorType"/>, or
			/// <see cref="SensorType::Invalid"/> if device index is out of range.
			/// </returns>
			static SensorType GetDeviceType(int deviceIndex);

			/// <summary>
			/// Get the instance ID of a sensor.
			/// </summary>
			property SDL_SensorID InstanceID
			{
				SDL_SensorID get();
			}

			/// <summary>
			/// Get the implementation dependent name of a sensor
			/// </summary>
			property System::String^ Name
			{
				System::String^ get();
			}

			/// <summary>
			/// Get the platform dependent type of a sensor.
			/// </summary>
			property int NonPortableType
			{
				int get();
			}

			/// <summary>
			/// Get the type of a sensor.
			/// </summary>
			property SensorType Type
			{
				SensorType get();
			}

			/// <summary>
			/// Update the current state of the open sensors.
			/// </summary>
			static void Update();
		};
	}
}
