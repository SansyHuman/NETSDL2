#include "../../include/events/GameController.h"
#include "../../include/events/Joystick.h"
#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"
#include "../../include/io/RWops.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Core;
using namespace NETSDL2::IO;
using namespace NETSDL2::Internal;

void NETSDL2::Events::GameController::InitGameController(SDL_GameController* controller)
{
	this->controller = controller;
	nativeGameControllerConnections[System::IntPtr(controller)] = this;
}

NETSDL2::Events::GameController::GameController(int joystickIndex)
{
	SDL_GameController* controller = SDL_GameControllerOpen(joystickIndex);
	if(controller == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitGameController(controller);
}

NETSDL2::Events::GameController::~GameController()
{
	GameController^ dummy = nullptr;
	nativeGameControllerConnections->TryRemove(System::IntPtr(controller), dummy);
	this->!GameController();
}

NETSDL2::Events::GameController::!GameController()
{
	SDL_GameControllerClose(controller);
	controller = __nullptr;
}

Result<int, None^> NETSDL2::Events::GameController::AddMapping(System::String^ mappingString)
{
	StringMarshal context;
	int result = SDL_GameControllerAddMapping(context.ManagedToUTF8Native(mappingString));
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

int GameController::NumMappings::get()
{
	return SDL_GameControllerNumMappings();
}

Result<System::String^, None^> NETSDL2::Events::GameController::MappingForIndex(int mappingIndex)
{
	char* str = SDL_GameControllerMappingForIndex(mappingIndex);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	System::String^ mapping = StringMarshal::UTF8NativeToManaged(str);
	SDL_free(str);
	return mapping;
}

Result<int, None^> NETSDL2::Events::GameController::AddMappingsFromFile(System::String^ filename)
{
	StringMarshal context;
	int result = SDL_GameControllerAddMappingsFromFile(context.ManagedToUTF8Native(filename));
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<int, None^> NETSDL2::Events::GameController::AddMappingsFromRW(RWops^ rw, bool freerw)
{
	int result = SDL_GameControllerAddMappingsFromRW(rw->NativeOps, freerw ? 1 : 0);
	if(freerw)
	{
		delete rw;
	}

	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<bool, int> NETSDL2::Events::GameController::EventState(NETSDL2::Events::EventState state)
{
	int result = SDL_GameControllerEventState((int)state);
	if(result < 0)
	{
		return Result<bool, int>::MakeFailure(result);
	}

	return result == (int)SDL_ENABLE;
}

Result<GameController^, None^> NETSDL2::Events::GameController::GameControllerFromInstanceID(SDL_JoystickID joyid)
{
	SDL_GameController* controller = SDL_GameControllerFromInstanceID(joyid);
	GameController^ con = nullptr;
	bool found = nativeGameControllerConnections->TryGetValue(System::IntPtr(controller), con);

	if(!found)
	{
		return Result<GameController^, None^>::MakeFailure(None::Value);
	}

	return con;
}

Result<GameController^, None^> NETSDL2::Events::GameController::GameControllerFromPlayerIndex(int playerIndex)
{
	SDL_GameController* controller = SDL_GameControllerFromPlayerIndex(playerIndex);
	GameController^ con = nullptr;
	bool found = nativeGameControllerConnections->TryGetValue(System::IntPtr(controller), con);

	if(!found)
	{
		return Result<GameController^, None^>::MakeFailure(None::Value);
	}

	return con;
}

bool GameController::Attached::get()
{
	return SDL_GameControllerGetAttached(controller) == SDL_TRUE;
}

Sint16 NETSDL2::Events::GameController::GetAxis(GameControllerAxis axis)
{
	return SDL_GameControllerGetAxis(controller, (SDL_GameControllerAxis)axis);
}

GameControllerAxis NETSDL2::Events::GameController::GetAxisFromString(System::String^ str)
{
	StringMarshal context;

	return (GameControllerAxis)SDL_GameControllerGetAxisFromString(context.ManagedToUTF8Native(str));
}

GameControllerButtonBind NETSDL2::Events::GameController::GetBindForAxis(GameControllerAxis axis)
{
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForAxis(controller, (SDL_GameControllerAxis)axis);
	return *((GameControllerButtonBind*)&bind);
}

bool NETSDL2::Events::GameController::HasAxis(GameControllerAxis axis)
{
	return SDL_GameControllerHasAxis(controller, (SDL_GameControllerAxis)axis) == SDL_TRUE;
}

GameControllerButtonBind NETSDL2::Events::GameController::GetBindForButton(GameControllerButton button)
{
	SDL_GameControllerButtonBind bind = SDL_GameControllerGetBindForButton(controller, (SDL_GameControllerButton)button);
	return *((GameControllerButtonBind*)&bind);
}

bool NETSDL2::Events::GameController::HasButton(GameControllerButton button)
{
	return SDL_GameControllerHasButton(controller, (SDL_GameControllerButton)button) == SDL_TRUE;
}

bool NETSDL2::Events::GameController::GetButton(GameControllerButton button)
{
	return SDL_GameControllerGetButton(controller, (SDL_GameControllerButton)button) == 1;
}

int GameController::NumTouchpads::get()
{
	return SDL_GameControllerGetNumTouchpads(controller);
}

int NETSDL2::Events::GameController::GetNumTouchpadFingers(int touchpad)
{
	return SDL_GameControllerGetNumTouchpadFingers(controller, touchpad);
}

Result<int, None^> NETSDL2::Events::GameController::GetTouchpadFinger(int touchpad, int finger, Uint8% state, float% x, float% y, float% pressure)
{
	Uint8 s = 0;
	float fx = 0, fy = 0, p = 0;
	int result = SDL_GameControllerGetTouchpadFinger(controller, touchpad, finger, &s, &fx, &fy, &p);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	state = s;
	x = fx;
	y = fy;
	pressure = p;
	return result;
}

bool NETSDL2::Events::GameController::HasSensor(SensorType type)
{
	return SDL_GameControllerHasSensor(controller, (SDL_SensorType)type) == SDL_TRUE;
}

Result<None^, None^> NETSDL2::Events::GameController::SetSensorEnabled(SensorType type, bool enabled)
{
	int result = SDL_GameControllerSetSensorEnabled(controller, (SDL_SensorType)type, enabled ? SDL_TRUE : SDL_FALSE);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool NETSDL2::Events::GameController::IsSensorEnabled(SensorType type)
{
	return SDL_GameControllerIsSensorEnabled(controller, (SDL_SensorType)type);
}

float NETSDL2::Events::GameController::GetSensorDataRate(SensorType type)
{
	return SDL_GameControllerGetSensorDataRate(controller, (SDL_SensorType)type);
}

Result<None^, None^> NETSDL2::Events::GameController::GetSensorData(SensorType type, float* data, int numValues)
{
	int result = SDL_GameControllerGetSensorData(controller, (SDL_SensorType)type, data, numValues);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::GameController::GetSensorData(SensorType type, array<float>^ data, int offset, int numValues)
{
	if(numValues == 0)
	{
		return None::Value;
	}

	if(numValues < 0)
	{
		SDL_InvalidParamError(numValues);
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	if(offset < 0)
	{
		SDL_InvalidParamError(offset);
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	if(data->Length < offset + numValues)
	{
		SDL_InvalidParamError(data);
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	pin_ptr<float> pData = &data[offset];
	int result = SDL_GameControllerGetSensorData(controller, (SDL_SensorType)type, (float*)pData, numValues);
	pData = nullptr;
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::GameController::Rumble(Uint16 lowFrequencyRumble, Uint16 highFrequencyRumble, Uint32 duration)
{
	int result = SDL_GameControllerRumble(controller, lowFrequencyRumble, highFrequencyRumble, duration);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::GameController::RumbleTriggers(Uint16 leftRumble, Uint16 rightRumble, Uint32 duration)
{
	int result = SDL_GameControllerRumbleTriggers(controller, leftRumble, rightRumble, duration);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

bool GameController::HasLED::get()
{
	return SDL_GameControllerHasLED(controller) == SDL_TRUE;
}

bool GameController::HasRumble::get()
{
	return SDL_GameControllerHasRumble(controller) == SDL_TRUE;
}

bool GameController::HasRumbleTriggers::get()
{
	return SDL_GameControllerHasRumbleTriggers(controller) == SDL_TRUE;
}

Result<None^, None^> NETSDL2::Events::GameController::SetLED(Uint8 red, Uint8 green, Uint8 blue)
{
	int result = SDL_GameControllerSetLED(controller, red, green, blue);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::GameController::SendEffect(System::IntPtr data, int size)
{
	int result = SDL_GameControllerSendEffect(controller, data.ToPointer(), size);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

GameControllerButton NETSDL2::Events::GameController::GetButtonFromString(System::String^ str)
{
	StringMarshal context;

	return (GameControllerButton)SDL_GameControllerGetButtonFromString(context.ManagedToUTF8Native(str));
}

Result<Joystick^, None^> NETSDL2::Events::GameController::GetJoystick()
{
	SDL_Joystick* stick = SDL_GameControllerGetJoystick(controller);
	if(stick == __nullptr)
	{
		return Result<Joystick^, None^>::MakeFailure(None::Value);
	}

	Joystick^ joystick = Joystick::GetJoystickFromNative(stick);
	if(joystick == nullptr)
	{
		joystick = gcnew Joystick(stick, false);
	}

	return joystick;
}

Result<System::String^, None^> NETSDL2::Events::GameController::GetStringForAxis(GameControllerAxis axis)
{
	const char* str = SDL_GameControllerGetStringForAxis((SDL_GameControllerAxis)axis);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

Result<System::String^, None^> NETSDL2::Events::GameController::GetStringForButton(GameControllerButton button)
{
	const char* str = SDL_GameControllerGetStringForButton((SDL_GameControllerButton)button);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

Result<System::String^, None^> NETSDL2::Events::GameController::Mapping()
{
	char* str = SDL_GameControllerMapping(controller);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	System::String^ mapping = StringMarshal::UTF8NativeToManaged(str);
	SDL_free(str);
	return mapping;
}

Result<System::String^, None^> NETSDL2::Events::GameController::MappingForGUID(NETSDL2::Core::GUID guid)
{
	char* str = SDL_GameControllerMappingForGUID(*((SDL_JoystickGUID*)&guid));
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	System::String^ mapping = StringMarshal::UTF8NativeToManaged(str);
	SDL_free(str);
	return mapping;
}

Result<System::String^, None^> NETSDL2::Events::GameController::Name()
{
	const char* str = SDL_GameControllerName(controller);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

Result<System::String^, None^> NETSDL2::Events::GameController::Path()
{
	const char* str = SDL_GameControllerPath(controller);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

GameControllerType NETSDL2::Events::GameController::Type::get()
{
	return (GameControllerType)SDL_GameControllerGetType(controller);
}

Result<int, None^> NETSDL2::Events::GameController::GetPlayerIndex()
{
	int result = SDL_GameControllerGetPlayerIndex(controller);
	if(result < 0)
	{
		return Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

void NETSDL2::Events::GameController::SetPlayerIndex(int playerIndex)
{
	SDL_GameControllerSetPlayerIndex(controller, playerIndex);
}

Result<Uint16, None^> NETSDL2::Events::GameController::GetVendor()
{
	Uint16 result = SDL_GameControllerGetVendor(controller);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::GameController::GetProduct()
{
	Uint16 result = SDL_GameControllerGetProduct(controller);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::GameController::GetProductVersion()
{
	Uint16 result = SDL_GameControllerGetProductVersion(controller);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<Uint16, None^> NETSDL2::Events::GameController::GetFirmwareVersion()
{
	Uint16 result = SDL_GameControllerGetFirmwareVersion(controller);
	if(result == 0)
	{
		return Result<Uint16, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<System::String^, None^> NETSDL2::Events::GameController::GetSerial()
{
	const char* str = SDL_GameControllerGetSerial(controller);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

Result<System::String^, None^> NETSDL2::Events::GameController::NameForIndex(int joystickIndex)
{
	const char* str = SDL_GameControllerNameForIndex(joystickIndex);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

Result<System::String^, None^> NETSDL2::Events::GameController::PathForIndex(int joystickIndex)
{
	const char* str = SDL_GameControllerPathForIndex(joystickIndex);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(str);
}

GameControllerType NETSDL2::Events::GameController::TypeForIndex(int joystickIndex)
{
	return (GameControllerType)SDL_GameControllerTypeForIndex(joystickIndex);
}

Result<System::String^, None^> NETSDL2::Events::GameController::MappingForDeviceIndex(int joystickIndex)
{
	char* str = SDL_GameControllerMappingForDeviceIndex(joystickIndex);
	if(str == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	System::String^ mapping = StringMarshal::UTF8NativeToManaged(str);
	SDL_free(str);
	return mapping;
}

void NETSDL2::Events::GameController::Update()
{
	SDL_GameControllerUpdate();
}

bool NETSDL2::Events::GameController::IsGameController(int joystickIndex)
{
	return SDL_IsGameController(joystickIndex) == SDL_TRUE;
}

Result<System::String^, None^> NETSDL2::Events::GameController::GetAppleSFSymbolsNameForButton(GameControllerButton button)
{
	const char* name = SDL_GameControllerGetAppleSFSymbolsNameForButton(controller, (SDL_GameControllerButton)button);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}

Result<System::String^, None^> NETSDL2::Events::GameController::GetAppleSFSymbolsNameForAxis(GameControllerAxis axis)
{
	const char* name = SDL_GameControllerGetAppleSFSymbolsNameForAxis(controller, (SDL_GameControllerAxis)axis);
	if(name == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(name);
}
