#include "../../include/haptic/Haptic.h"
#include "../../include/internal/StringMarshal.h"
#include "../../include/core/Error.h"
#include "../../include/events/Joystick.h"

using namespace NETSDL2::Haptic;
using namespace NETSDL2::Internal;
using namespace NETSDL2::Core;
using namespace NETSDL2::Events;

NETSDL2::Haptic::Haptic::Haptic(int deviceIndex)
{
	haptic = SDL_HapticOpen(deviceIndex);
	if(haptic == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Haptic::Haptic::Haptic(Joystick^ joystick)
{
	haptic = SDL_HapticOpenFromJoystick(joystick->NativeJoystick);
	if(haptic == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Haptic::Haptic::Haptic(MouseHaptic)
{
	haptic = SDL_HapticOpenFromMouse();
	if(haptic == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}
}

NETSDL2::Haptic::Haptic::~Haptic()
{
	this->!Haptic();
}

NETSDL2::Haptic::Haptic::!Haptic()
{
	SDL_HapticClose(haptic);
	haptic = __nullptr;
}

void NETSDL2::Haptic::Haptic::DestroyEffect(int effect)
{
	SDL_HapticDestroyEffect(haptic, effect);
}
generic<class T> where T : value struct, HapticEffect
Result<bool, int> NETSDL2::Haptic::Haptic::EffectSupported(T% effect)
{
	pin_ptr<T> pEffect = &effect;
	int result = SDL_HapticEffectSupported(haptic, (SDL_HapticEffect*)pEffect);
	pEffect = nullptr;

	if(result < 0)
	{
		return Result<bool, int>::MakeFailure(result);
	}

	return result == SDL_TRUE;
}

Result<bool, int> NETSDL2::Haptic::Haptic::GetEffectStatus(int effect)
{
	int result = SDL_HapticGetEffectStatus(haptic, effect);
	if(result < 0)
	{
		return Result<bool, int>::MakeFailure(result);
	}

	return result == 1;
}

Result<int, int> NETSDL2::Haptic::Haptic::HapticIndex()
{
	int result = SDL_HapticIndex(haptic);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<System::String^, None^> NETSDL2::Haptic::Haptic::Name(int deviceIndex)
{
	const char* result = SDL_HapticName(deviceIndex);
	if(result == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

generic<class T> where T : value struct, HapticEffect
Result<int, int> NETSDL2::Haptic::Haptic::NewEffect(T% effect)
{
	pin_ptr<T> pEffect = &effect;
	SDL_HapticEffect* pNEffect = (SDL_HapticEffect*)pEffect;
	int result = SDL_HapticNewEffect(haptic, pNEffect);
	pEffect = nullptr;

	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Haptic::Haptic::NumAxes()
{
	int result = SDL_HapticNumAxes(haptic);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Haptic::Haptic::NumEffects()
{
	int result = SDL_HapticNumEffects(haptic);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Haptic::Haptic::NumEffectsPlaying()
{
	int result = SDL_HapticNumEffectsPlaying(haptic);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

bool NETSDL2::Haptic::Haptic::Opened(int deviceIndex)
{
	return SDL_HapticOpened(deviceIndex) == 1;
}

Result<None^, int> NETSDL2::Haptic::Haptic::Pause()
{
	int result = SDL_HapticPause(haptic);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

HapticFeatures Haptic::Query::get()
{
	return (HapticFeatures)SDL_HapticQuery(haptic);
}

Result<None^, int> NETSDL2::Haptic::Haptic::RumbleInit()
{
	int result = SDL_HapticRumbleInit(haptic);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::RumblePlay(float strength, Uint32 length)
{
	int result = SDL_HapticRumblePlay(haptic, strength, length);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::RumbleStop()
{
	int result = SDL_HapticRumbleStop(haptic);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<bool, int> NETSDL2::Haptic::Haptic::RumbleSupported()
{
	int result = SDL_HapticRumbleSupported(haptic);
	if(result < 0)
	{
		return Result<bool, int>::MakeFailure(result);
	}

	return result == SDL_TRUE;
}

Result<None^, int> NETSDL2::Haptic::Haptic::RunEffect(int effect, Uint32 iterations)
{
	int result = SDL_HapticRunEffect(haptic, effect, iterations);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::SetAutocenter(int autocenter)
{
	int result = SDL_HapticSetAutocenter(haptic, autocenter);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::SetGain(int gain)
{
	int result = SDL_HapticSetGain(haptic, gain);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::StopAll()
{
	int result = SDL_HapticStopAll(haptic);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::StopEffect(int effect)
{
	int result = SDL_HapticStopEffect(haptic, effect);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<None^, int> NETSDL2::Haptic::Haptic::Unpause()
{
	int result = SDL_HapticUnpause(haptic);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

generic<class T> where T : value struct, HapticEffect
Result<None^, int> NETSDL2::Haptic::Haptic::UpdateEffect(int effect, T% data)
{
	pin_ptr<T> pData = &data;
	int result = SDL_HapticUpdateEffect(haptic, effect, (SDL_HapticEffect*)pData);
	pData = nullptr;

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	return None::Value;
}

Result<int, int> NETSDL2::Haptic::Haptic::NumHaptics()
{
	int result = SDL_NumHaptics();
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}
