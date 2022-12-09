#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Haptic
	{
		/// <summary>
		/// An interface of structs that contains the template for haptic effect.
		/// </summary>
		public interface class HapticEffect
		{

		};

		/// <summary>
		/// Enum of haptic direction types.
		/// </summary>
		public enum class HapticType : Uint8
		{
			/// <summary>
			/// Uses polar coordinates for the direction.
			/// </summary>
			Polar = SDL_HAPTIC_POLAR,

			/// <summary>
			/// Uses cartesian coordinates for the direction.
			/// </summary>
			Cartesian = SDL_HAPTIC_CARTESIAN,

			/// <summary>
			/// Uses spherical coordinates for the direction.
			/// </summary>
			Spherical = SDL_HAPTIC_SPHERICAL,

			/// <summary>
			/// Use this value to play an effect on the steering wheel axis. This 
			/// provides better compatibility across platformsand devices as SDL will
			/// guess the correct axis.
			/// </summary>
			SteeringAxis = SDL_HAPTIC_STEERING_AXIS,
		};

		/// <summary>
		/// A structure that contains a haptic direction.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticDirection
		{
			/// <summary>
			/// The type of encoding.
			/// </summary>
			HapticType Type;

			/// <summary>
			/// The encoded direction.
			/// </summary>
			Sint32 Dir1;

			/// <summary>
			/// The encoded direction.
			/// </summary>
			Sint32 Dir2;

			/// <summary>
			/// The encoded direction.
			/// </summary>
			Sint32 Dir3;
		};

		/// <summary>
		/// Enum of condition effect types.
		/// </summary>
		public enum class HapticConditionType : Uint16
		{
			/// <summary>
			/// Effect based on axis position.
			/// </summary>
			Spring = SDL_HAPTIC_SPRING,

			/// <summary>
			/// Effect based on axis velocity.
			/// </summary>
			Damper = SDL_HAPTIC_DAMPER,

			/// <summary>
			/// Effect based on axis acceleration.
			/// </summary>
			Inertia = SDL_HAPTIC_INERTIA,

			/// <summary>
			/// Effect based on axis movement.
			/// </summary>
			Friction = SDL_HAPTIC_FRICTION,
		};

		/// <summary>
		/// A structure that contains a template for a condition effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticCondition : HapticEffect
		{
			/// <summary>
			/// One of the effects handled by this structure.
			/// </summary>
			HapticConditionType Type;

			/// <summary>
			/// Direction of the effect.
			/// </summary>
			HapticDirection Direction;

			/// <summary>
			/// Duration of the effect.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Delay before starting the effect.
			/// </summary>
			Uint16 Delay;

			/// <summary>
			/// Button that triggers the effect.
			/// </summary>
			Uint16 Button;

			/// <summary>
			/// How soon it can be triggered again after button.
			/// </summary>
			Uint16 Interval; 

			/// <summary>
			/// Level when joystick is to the positive side; max 0xFFFF.
			/// </summary>
			Uint16 RightSat1;

			/// <summary>
			/// Level when joystick is to the positive side; max 0xFFFF.
			/// </summary>
			Uint16 RightSat2;

			/// <summary>
			/// Level when joystick is to the positive side; max 0xFFFF.
			/// </summary>
			Uint16 RightSat3;

			/// <summary>
			/// Level when joystick is to the negative side; max 0xFFFF.
			/// </summary>
			Uint16 LeftSat1;

			/// <summary>
			/// Level when joystick is to the negative side; max 0xFFFF.
			/// </summary>
			Uint16 LeftSat2;

			/// <summary>
			/// Level when joystick is to the negative side; max 0xFFFF.
			/// </summary>
			Uint16 LeftSat3;

			/// <summary>
			/// How fast to increase the force towards the positive side.
			/// </summary>
			Sint16 RightCoeff1;

			/// <summary>
			/// How fast to increase the force towards the positive side.
			/// </summary>
			Sint16 RightCoeff2;

			/// <summary>
			/// How fast to increase the force towards the positive side.
			/// </summary>
			Sint16 RightCoeff3;

			/// <summary>
			/// How fast to increase the force towards the negative side.
			/// </summary>
			Sint16 LeftCoeff1;

			/// <summary>
			/// How fast to increase the force towards the negative side.
			/// </summary>
			Sint16 LeftCoeff2;

			/// <summary>
			/// How fast to increase the force towards the negative side.
			/// </summary>
			Sint16 LeftCoeff3;

			/// <summary>
			/// Size of the dead zone; max 0xFFFF: whole axis-range when 0-centered.
			/// </summary>
			Uint16 Deadband1;

			/// <summary>
			/// Size of the dead zone; max 0xFFFF: whole axis-range when 0-centered.
			/// </summary>
			Uint16 Deadband2;

			/// <summary>
			/// Size of the dead zone; max 0xFFFF: whole axis-range when 0-centered.
			/// </summary>
			Uint16 Deadband3;

			/// <summary>
			/// Position of the dead zone.
			/// </summary>
			Sint16 Center1;

			/// <summary>
			/// Position of the dead zone.
			/// </summary>
			Sint16 Center2;

			/// <summary>
			/// Position of the dead zone.
			/// </summary>
			Sint16 Center3;
		};

		/// <summary>
		/// Enum of constant effect types.
		/// </summary>
		public enum class HapticConstantType : Uint16
		{
			Constant = SDL_HAPTIC_CONSTANT,
		};

		/// <summary>
		/// A structure that contains a template for a constant effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticConstant : HapticEffect
		{
			/// <summary>
			/// <see cref="HapticConstantType::Constant"/>.
			/// </summary>
			HapticConstantType Type;

			/// <summary>
			/// Direction of the effect.
			/// </summary>
			HapticDirection Direction;

			/// <summary>
			/// Duration of the effect.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Delay before starting the effect.
			/// </summary>
			Uint16 Delay;

			/// <summary>
			/// Button that triggers the effect.
			/// </summary>
			Uint16 Button;

			/// <summary>
			/// How soon it can be triggered again after button.
			/// </summary>
			Uint16 Interval;

			/// <summary>
			/// Strength of the constant effect.
			/// </summary>
			Sint16 Level;

			/// <summary>
			/// Duration of the attack.
			/// </summary>
			Uint16 AttackLength;

			/// <summary>
			/// Level at the start of the attack.
			/// </summary>
			Uint16 AttackLevel;

			/// <summary>
			/// Duration of the fade.
			/// </summary>
			Uint16 FadeLength;

			/// <summary>
			/// Level at the end of the fade.
			/// </summary>
			Uint16 FadeLevel;
		};

		/// <summary>
		/// Enum of custom effect types.
		/// </summary>
		public enum class HapticCustomType : Uint16
		{
			Custom = SDL_HAPTIC_CUSTOM,
		};

		/// <summary>
		/// A structure that contains a template for the custom effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticCustom : HapticEffect
		{
			/// <summary>
			/// <see cref="HapticCustomType::Custom"/>.
			/// </summary>
			HapticCustomType Type;

			/// <summary>
			/// Direction of the effect.
			/// </summary>
			HapticDirection Direction;

			/// <summary>
			/// Duration of the effect.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Delay before starting the effect.
			/// </summary>
			Uint16 Delay;

			/// <summary>
			/// Button that triggers the effect.
			/// </summary>
			Uint16 Button;

			/// <summary>
			/// How soon it can be triggered again after button.
			/// </summary>
			Uint16 Interval;

			/// <summary>
			/// Axes to use, minimum of one.
			/// </summary>
			Uint8 Channels;

			/// <summary>
			/// Sample periods.
			/// </summary>
			Uint16 Period;

			/// <summary>
			/// Amount of samples.
			/// </summary>
			Uint16 Samples;

			/// <summary>
			/// Should contain Channels*Samples items.
			/// </summary>
			Uint16* Data;

			/// <summary>
			/// Duration of the attack.
			/// </summary>
			Uint16 AttackLength;

			/// <summary>
			/// Level at the start of the attack.
			/// </summary>
			Uint16 AttackLevel;

			/// <summary>
			/// Duration of the fade.
			/// </summary>
			Uint16 FadeLength;

			/// <summary>
			/// Level at the end of the fade.
			/// </summary>
			Uint16 FadeLevel;
		};

		/// <summary>
		/// Enum of left/right effect types.
		/// </summary>
		public enum class HapticLeftRightType : Uint16
		{
			LeftRight = SDL_HAPTIC_LEFTRIGHT,
		};

		/// <summary>
		/// A structure that contains a template for a left/right effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticLeftRight : HapticEffect
		{
			/// <summary>
			/// <see cref="HapticLeftRightType::LeftRight"/>.
			/// </summary>
			HapticLeftRightType Type;

			/// <summary>
			/// Duration of the effect in milliseconds.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Control of the large controller motor.
			/// </summary>
			Uint16 LargeMagnitude;

			/// <summary>
			/// Control of the small controller motor.
			/// </summary>
			Uint16 SmallMagnitude;
		};

		/// <summary>
		/// Enum of periodic effect types.
		/// </summary>
		public enum class HapticPeriodicType : Uint16
		{
			/// <summary>
			/// Periodic haptic effect that simulates sine waves.
			/// </summary>
			Sine = SDL_HAPTIC_SINE,

			/// <summary>
			/// Periodic haptic effect that simulates triangular waves.
			/// </summary>
			Triangle = SDL_HAPTIC_TRIANGLE,

			/// <summary>
			/// Periodic haptic effect that simulates saw tooth up waves.
			/// </summary>
			SawToothUp = SDL_HAPTIC_SAWTOOTHUP,

			/// <summary>
			/// Periodic haptic effect that simulates saw tooth down waves.
			/// </summary>
			SawToothDown = SDL_HAPTIC_SAWTOOTHDOWN,
		};

		/// <summary>
		/// A structure that contains a template for a periodic effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticPeriodic : HapticEffect
		{
			/// <summary>
			/// The shape of the waves.
			/// </summary>
			HapticPeriodicType Type;

			/// <summary>
			/// Direction of the effect.
			/// </summary>
			HapticDirection Direction;

			/// <summary>
			/// Duration of the effect.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Delay before starting the effect.
			/// </summary>
			Uint16 Delay;

			/// <summary>
			/// Button that triggers the effect.
			/// </summary>
			Uint16 Button;

			/// <summary>
			/// How soon it can be triggered again after button.
			/// </summary>
			Uint16 Interval;

			/// <summary>
			/// Period of the wave.
			/// </summary>
			Uint16 Period;

			/// <summary>
			/// Peak value; if negative, equivalent to 180 degrees extra phase shift.
			/// </summary>
			Sint16 Magnitude;

			/// <summary>
			/// Mean value of the wave.
			/// </summary>
			Sint16 Offset;

			/// <summary>
			/// Positive phase shift given by hundredth of a degree.
			/// </summary>
			Uint16 Phase;

			/// <summary>
			/// Duration of the attack.
			/// </summary>
			Uint16 AttackLength;

			/// <summary>
			/// Level at the start of the attack.
			/// </summary>
			Uint16 AttackLevel;

			/// <summary>
			/// Duration of the fade.
			/// </summary>
			Uint16 FadeLength;

			/// <summary>
			/// Level at the end of the fade.
			/// </summary>
			Uint16 FadeLevel;
		};

		/// <summary>
		/// Enum of ramp effect types.
		/// </summary>
		public enum class HapticRampType : Uint16
		{
			Ramp = SDL_HAPTIC_RAMP,
		};

		/// <summary>
		/// A structure that contains a template for a periodic effect.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct HapticRamp : HapticEffect
		{
			/// <summary>
			/// <see cref="HapticRampType::Ramp"/>.
			/// </summary>
			HapticRampType Type;

			/// <summary>
			/// Direction of the effect.
			/// </summary>
			HapticDirection Direction;

			/// <summary>
			/// Duration of the effect.
			/// </summary>
			Uint32 Length;

			/// <summary>
			/// Delay before starting the effect.
			/// </summary>
			Uint16 Delay;

			/// <summary>
			/// Button that triggers the effect.
			/// </summary>
			Uint16 Button;

			/// <summary>
			/// How soon it can be triggered again after button.
			/// </summary>
			Uint16 Interval;

			/// <summary>
			/// Beginning strength level.
			/// </summary>
			Sint16 Start;

			/// <summary>
			/// Ending strength level.
			/// </summary>
			Sint16 End;

			/// <summary>
			/// Duration of the attack.
			/// </summary>
			Uint16 AttackLength;

			/// <summary>
			/// Level at the start of the attack.
			/// </summary>
			Uint16 AttackLevel;

			/// <summary>
			/// Duration of the fade.
			/// </summary>
			Uint16 FadeLength;

			/// <summary>
			/// Level at the end of the fade.
			/// </summary>
			Uint16 FadeLevel;
		};
	}
}