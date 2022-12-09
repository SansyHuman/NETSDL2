#pragma once

#include <SDL.h>

#include "../core/Result.h"
#include "../core/None.h"
#include "HapticEffect.h"
#include "HapticFeatures.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		ref class Joystick;
	}

	namespace Haptic
	{
		using namespace NETSDL2::Core;
		using namespace NETSDL2::Events;

		/// <summary>
		/// Placeholder for opening haptic device from the current mouse.
		/// </summary>
		public value struct MouseHaptic
		{

		};

		/// <summary>
		/// Haptic device class.
		/// </summary>
		public ref class Haptic
		{
		private:
			SDL_Haptic* haptic;

		public:
			/// <summary>
			/// Used to play a device an infinite number of times.
			/// </summary>
			literal Uint32 Infinity = SDL_HAPTIC_INFINITY;

			/// <summary>
			/// Open a haptic device for use.
			/// </summary>
			/// <param name="deviceIndex">Index of the device to open.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Haptic(int deviceIndex);

			/// <summary>
			/// Open a haptic device for use from a joystick device.
			/// </summary>
			/// <param name="joystick">The Joystick to create a haptic device from.
			/// </param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Haptic(Joystick^ joystick);

			/// <summary>
			/// Try to open a haptic device from the current mouse.
			/// </summary>
			/// <param name="">Placeholder</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			Haptic(MouseHaptic);

			~Haptic();
			!Haptic();

			/// <summary>
			/// Destroy a haptic effect on the device.
			/// </summary>
			/// <param name="effect">The ID of the haptic effect to destroy.</param>
			void DestroyEffect(int effect);

			/// <summary>
			/// Check to see if an effect is supported by a haptic device.
			/// </summary>
			/// <typeparam name="T">The effect struct type.</typeparam>
			/// <param name="effect">The desired effect to query.</param>
			/// <returns>true if effect is supported, false if it isn't, or a
			/// negative error code on failure.</returns>
			generic<class T> where T : value struct, HapticEffect
			Result<bool, int> EffectSupported([In][IsReadOnly]T% effect);

			/// <summary>
			/// Get the status of the current effect on the specified haptic device.
			/// </summary>
			/// <param name="effect">The ID of the haptic effect to query its status.
			/// </param>
			/// <returns>false if it isn't playing, true if it is playing, or a
			/// negative error code on failure.</returns>
			Result<bool, int> GetEffectStatus(int effect);

			/// <summary>
			/// Get the index of a haptic device.
			/// </summary>
			/// <returns>The index of the specified haptic device or a negative error
			/// code on failure.</returns>
			Result<int, int> HapticIndex();

			/// <summary>
			/// Get the implementation dependent name of a haptic device.
			/// </summary>
			/// <param name="deviceIndex">Index of the device to query.</param>
			/// <returns>The name of the device or None on failure.</returns>
			static Result<System::String^, None^> Name(int deviceIndex);

			/// <summary>
			/// 
			/// </summary>
			/// <typeparam name="T">The effect struct type.</typeparam>
			/// <param name="effect">Effect structure containing the properties of the
			/// effect to create.</param>
			/// <returns>The ID of the effect on success or a negative error code on
			/// failure.</returns>
			generic<class T> where T : value struct, HapticEffect
			Result<int, int> NewEffect([In][IsReadOnly]T% effect);

			/// <summary>
			/// Get the number of haptic axes the device has.
			/// </summary>
			/// <returns>The number of axes on success or a negative error code on
			/// failure.</returns>
			Result<int, int> NumAxes();

			/// <summary>
			/// Get the number of effects a haptic device can store.
			/// </summary>
			/// <returns>The number of effects the haptic device can store or a
			/// negative error code on failure.</returns>
			Result<int, int> NumEffects();

			/// <summary>
			/// Get the number of effects a haptic device can play at the same time.
			/// </summary>
			/// <returns>The number of effects the haptic device can play at the same
			/// time or a negative error code on failure.</returns>
			Result<int, int> NumEffectsPlaying();

			/// <summary>
			/// Check if the haptic device at the designated index has been opened.
			/// </summary>
			/// <param name="deviceIndex">The index of the device to query.</param>
			/// <returns>true if it has been opened, false if it hasn't or on
			/// failure.</returns>
			static bool Opened(int deviceIndex);

			/// <summary>
			/// Pause a haptic device.
			/// </summary>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> Pause();

			/// <summary>
			/// Get the haptic device's supported features in bitwise manner.
			/// </summary>
			property HapticFeatures Query
			{
				HapticFeatures get();
			}

			/// <summary>
			/// Initialize a haptic device for simple rumble playback.
			/// </summary>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> RumbleInit();

			/// <summary>
			/// Run a simple rumble effect on a haptic device.
			/// </summary>
			/// <param name="strength">Strength of the rumble to play as a 0-1 float
			/// value.</param>
			/// <param name="length">Length of the rumble to play in milliseconds.
			/// </param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> RumblePlay(float strength, Uint32 length);

			/// <summary>
			/// Stop the simple rumble on a haptic device.
			/// </summary>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> RumbleStop();

			/// <summary>
			/// Check whether rumble is supported on a haptic device.
			/// </summary>
			/// <returns>true if effect is supported, false if it isn't, or a
			/// negative error code on failure.</returns>
			Result<bool, int> RumbleSupported();

			/// <summary>
			/// Run the haptic effect on its associated haptic device.
			/// </summary>
			/// <param name="effect">The ID of the haptic effect to run.</param>
			/// <param name="iterations">The number of iterations to run the effect;
			/// use <see cref="Haptic::Infinity"/> to repeat forever.</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> RunEffect(int effect, Uint32 iterations);

			/// <summary>
			/// Set the global autocenter of the device.
			/// </summary>
			/// <param name="autocenter">Value to set autocenter to (0-100).</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> SetAutocenter(int autocenter);

			/// <summary>
			/// Set the global gain of the specified haptic device.
			/// </summary>
			/// <param name="gain">Value to set the gain to, should be between 0 and
			/// 100 (0 - 100).</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> SetGain(int gain);

			/// <summary>
			/// Stop all the currently playing effects on a haptic device.
			/// </summary>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> StopAll();

			/// <summary>
			/// Stop the haptic effect on its associated haptic device.
			/// </summary>
			/// <param name="effect">The ID of the haptic effect to stop.</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> StopEffect(int effect);

			/// <summary>
			/// Unpause a haptic device.
			/// </summary>
			/// <returns>None on success or a negative error code on failure.</returns>
			Result<None^, int> Unpause();

			/// <summary>
			/// Update the properties of an effect.
			/// </summary>
			/// <typeparam name="T">The effect struct type.</typeparam>
			/// <param name="effect">The identifier of the effect to update.</param>
			/// <param name="data">An effect structure containing the new effect
			/// properties to use.</param>
			/// <returns>None on success or a negative error code on failure.</returns>
			generic<class T> where T : value struct, HapticEffect
			Result<None^, int> UpdateEffect(int effect, [In][IsReadOnly]T% data);

			/// <summary>
			/// Count the number of haptic devices attached to the system.
			/// </summary>
			/// <returns>The number of haptic devices detected on the system or a
			/// negative error code on failure.</returns>
			static Result<int, int> NumHaptics();
		};
	}
}