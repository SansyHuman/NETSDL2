#include "../../include/events/Joystick.h"
#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

void NETSDL2::Events::Joystick::InitJoystick(SDL_Joystick* joystick)
{
	this->joystick = joystick;
	nativeJoystickConnections[System::IntPtr(joystick)] = this;
}

NETSDL2::Events::Joystick::Joystick(int deviceIndex)
{
	SDL_Joystick* joystick = SDL_JoystickOpen(deviceIndex);
	if(joystick == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitJoystick(joystick);
}

NETSDL2::Events::Joystick::~Joystick()
{
	Joystick^ dummy = nullptr;
	nativeJoystickConnections->TryRemove(System::IntPtr(joystick), dummy);
	this->!Joystick();
}

NETSDL2::Events::Joystick::!Joystick()
{
	SDL_JoystickClose(joystick);
	joystick = __nullptr;
}

void NETSDL2::Events::Joystick::Lock()
{
	SDL_LockJoysticks();
}

void NETSDL2::Events::Joystick::Unlock()
{
	SDL_UnlockJoysticks();
}

JoystickPowerLevel Joystick::CurrentPowerLevel::get()
{
	return (JoystickPowerLevel)SDL_JoystickCurrentPowerLevel(joystick);
}

Result<bool, int> NETSDL2::Events::Joystick::EventState(NETSDL2::Events::EventState state)
{
	int result = SDL_JoystickEventState((int)state);
	if(result < 0)
	{
		return Result<bool, int>::MakeFailure(result);
	}

	return result == 1;
}

Result<Joystick^, None^> NETSDL2::Events::Joystick::JoystickFromInstanceID(SDL_JoystickID instanceID)
{
	SDL_Joystick* joystick = SDL_JoystickFromInstanceID(instanceID);
	Joystick^ stick = nullptr;
	bool found = nativeJoystickConnections->TryGetValue(System::IntPtr(joystick), stick);

	if(!found)
	{
		return Result<Joystick^, None^>::MakeFailure(None::Value);
	}

	return stick;
}

Result<Joystick^, None^> NETSDL2::Events::Joystick::JoystickFromPlayerIndex(int playerIndex)
{
	SDL_Joystick* joystick = SDL_JoystickFromPlayerIndex(playerIndex);
	Joystick^ stick = nullptr;
	bool found = nativeJoystickConnections->TryGetValue(System::IntPtr(joystick), stick);

	if(!found)
	{
		return Result<Joystick^, None^>::MakeFailure(None::Value);
	}

	return stick;
}

Result<int, None^> NETSDL2::Events::Joystick::AttachVirtual(JoystickType type, int naxes, int nbuttons, int nhats)
{
	int result = SDL_JoystickAttachVirtual((SDL_JoystickType)type, naxes, nbuttons, nhats);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Events::Joystick::AttachVirtualEx(VirtualJoystickDesc% desc)
{
	pin_ptr<VirtualJoystickDesc> pDesc = &desc;
	int result = SDL_JoystickAttachVirtualEx((SDL_VirtualJoystickDesc*)pDesc);
	pDesc = nullptr;

	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<None^, None^> NETSDL2::Events::Joystick::DetachVirtual(int deviceIndex)
{
	int result = SDL_JoystickDetachVirtual(deviceIndex);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool NETSDL2::Events::Joystick::IsVirtual(int deviceIndex)
{
	return SDL_JoystickIsVirtual(deviceIndex) == SDL_TRUE;
}

Result<None^, None^> NETSDL2::Events::Joystick::SetVirtualAxis(int axis, Sint16 value)
{
	int result = SDL_JoystickSetVirtualAxis(joystick, axis, value);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Joystick::SetVirtualButton(int button, bool value)
{
	int result = SDL_JoystickSetVirtualButton(joystick, button, value ? 1 : 0);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Joystick::SetVirtualHat(int hat, HatPosition value)
{
	int result = SDL_JoystickSetVirtualHat(joystick, hat, (Uint8)value);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool Joystick::Attached::get()
{
	return SDL_JoystickGetAttached(joystick) == SDL_TRUE;
}

Result<Sint16, None^> NETSDL2::Events::Joystick::GetAxis(int axis)
{
	Sint16 result = SDL_JoystickGetAxis(joystick, axis);
	if(result == 0)
	{
		return Result<Sint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Sint16, None^> NETSDL2::Events::Joystick::GetAxisInitialState(int axis)
{
	Sint16 state = 0;
	SDL_bool result = SDL_JoystickGetAxisInitialState(joystick, axis, &state);
	if(result == SDL_FALSE)
	{
		return Result<Sint16, None^>::MakeFailure(None::Value);
	}

	return state;
}

Result<None^, int> NETSDL2::Events::Joystick::GetBall(int ball, int% dx, int% dy)
{
	int x = 0, y = 0;
	int result = SDL_JoystickGetBall(joystick, ball, &x, &y);
	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	dx = x;
	dy = y;
	return None::Value;
}

bool NETSDL2::Events::Joystick::GetButton(int button)
{
	return SDL_JoystickGetButton(joystick, button) == 1;
}

Result<None^, None^> NETSDL2::Events::Joystick::Rumble(Uint16 lowFrequencyRumble, Uint16 highFrequencyRumble, Uint32 duration)
{
	int result = SDL_JoystickRumble(joystick, lowFrequencyRumble, highFrequencyRumble, duration);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Joystick::RumbleTriggers(Uint16 leftRumble, Uint16 rightRumble, Uint32 duration)
{
	int result = SDL_JoystickRumbleTriggers(joystick, leftRumble, rightRumble, duration);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool Joystick::HasLED::get()
{
	return SDL_JoystickHasLED(joystick) == SDL_TRUE;
}

bool Joystick::HasRumble::get()
{
	return SDL_JoystickHasRumble(joystick) == SDL_TRUE;
}

bool Joystick::HasRumbleTriggers::get()
{
	return SDL_JoystickHasRumbleTriggers(joystick) == SDL_TRUE;
}

Result<None^, None^> NETSDL2::Events::Joystick::SetLED(Uint8 red, Uint8 green, Uint8 blue)
{
	int result = SDL_JoystickSetLED(joystick, red, green, blue);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Joystick::SendEffect(System::IntPtr data, int size)
{
	int result = SDL_JoystickSendEffect(joystick, data.ToPointer(), size);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

NETSDL2::Core::GUID NETSDL2::Events::Joystick::GetDeviceGUID(int deviceIndex)
{
	SDL_JoystickGUID guid = SDL_JoystickGetDeviceGUID(deviceIndex);
	return *((NETSDL2::Core::GUID*)&guid);
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetDeviceVendor(int deviceIndex)
{
	Uint16 result = SDL_JoystickGetDeviceVendor(deviceIndex);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetDeviceProduct(int deviceIndex)
{
	Uint16 result = SDL_JoystickGetDeviceProduct(deviceIndex);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetDeviceProductVersion(int deviceIndex)
{
	Uint16 result = SDL_JoystickGetDeviceProductVersion(deviceIndex);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

JoystickType NETSDL2::Events::Joystick::GetDeviceType(int deviceIndex)
{
	return (JoystickType)SDL_JoystickGetDeviceType(deviceIndex);
}

Result<SDL_JoystickID, None^> NETSDL2::Events::Joystick::GetDeviceInstanceID(int deviceIndex)
{
	SDL_JoystickID id = SDL_JoystickGetDeviceInstanceID(deviceIndex);
	if(id <= 0)
	{
		return Result<SDL_JoystickID, None^>::MakeFailure(None::Value);
	}

	return id;
}

NETSDL2::Core::GUID Joystick::Guid::get()
{
	SDL_JoystickGUID guid = SDL_JoystickGetGUID(joystick);
	return *((NETSDL2::Core::GUID*)&guid);
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetVendor()
{
	Uint16 result = SDL_JoystickGetVendor(joystick);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetProduct()
{
	Uint16 result = SDL_JoystickGetProduct(joystick);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetProductVersion()
{
	Uint16 result = SDL_JoystickGetProductVersion(joystick);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::Joystick::GetFirmwareVersion()
{
	Uint16 result = SDL_JoystickGetFirmwareVersion(joystick);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<System::String^, None^> NETSDL2::Events::Joystick::GetSerial()
{
	const char* result = SDL_JoystickGetSerial(joystick);
	if(result == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

JoystickType Joystick::Type::get()
{
	return (JoystickType)SDL_JoystickGetType(joystick);
}

HatPosition NETSDL2::Events::Joystick::GetHat(int hat)
{
	return (HatPosition)SDL_JoystickGetHat(joystick, hat);
}

Result<SDL_JoystickID, int> NETSDL2::Events::Joystick::InstanceID()
{
	SDL_JoystickID id = SDL_JoystickInstanceID(joystick);
	if(id < 0)
	{
		return Result<SDL_JoystickID, int>::MakeFailure(id);
	}

	return id;
}

Result<System::String^, None^> NETSDL2::Events::Joystick::Name()
{
	const char* name = SDL_JoystickName(joystick);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<System::String^, None^> NETSDL2::Events::Joystick::Path()
{
	const char* path = SDL_JoystickPath(joystick);
	if(path == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(path);
}

Result<int, None^> NETSDL2::Events::Joystick::GetPlayerIndex()
{
	int result = SDL_JoystickGetPlayerIndex(joystick);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Events::Joystick::SetPlayerIndex(int playerIndex)
{
	SDL_JoystickSetPlayerIndex(joystick, playerIndex);
}

Result<System::String^, None^> NETSDL2::Events::Joystick::NameForIndex(int deviceIndex)
{
	const char* name = SDL_JoystickNameForIndex(deviceIndex);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<System::String^, None^> NETSDL2::Events::Joystick::PathForIndex(int deviceIndex)
{
	const char* name = SDL_JoystickPathForIndex(deviceIndex);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<int, None^> NETSDL2::Events::Joystick::GetDevicePlayerIndex(int deviceIndex)
{
	int result = SDL_JoystickGetDevicePlayerIndex(deviceIndex);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, int> NETSDL2::Events::Joystick::NumAxes()
{
	int result = SDL_JoystickNumAxes(joystick);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Events::Joystick::NumBalls()
{
	int result = SDL_JoystickNumBalls(joystick);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Events::Joystick::NumHats()
{
	int result = SDL_JoystickNumHats(joystick);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

Result<int, int> NETSDL2::Events::Joystick::NumButtons()
{
	int result = SDL_JoystickNumButtons(joystick);
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}

void NETSDL2::Events::Joystick::Update()
{
	SDL_JoystickUpdate();
}

Result<int, int> NETSDL2::Events::Joystick::NumJoysticks()
{
	int result = SDL_NumJoysticks();
	if(result < 0)
	{
		return Result<int, int>::MakeFailure(result);
	}

	return result;
}
