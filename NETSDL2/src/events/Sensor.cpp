#include "../../include/events/Sensor.h"
#include "../../include/core/Error.h"
#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

void NETSDL2::Events::Sensor::InitSensor(SDL_Sensor* sensor)
{
	this->sensor = sensor;
	nativeSensorConnections[System::IntPtr(sensor)] = this;
}

NETSDL2::Events::Sensor::Sensor(int deviceIndex)
{
	SDL_Sensor* sensor = SDL_SensorOpen(deviceIndex);
	if(sensor == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitSensor(sensor);
}

NETSDL2::Events::Sensor::~Sensor()
{
	Sensor^ dummy = nullptr;
	nativeSensorConnections->TryRemove(System::IntPtr(sensor), dummy);
	this->!Sensor();
}

NETSDL2::Events::Sensor::!Sensor()
{
	SDL_SensorClose(sensor);
	sensor = __nullptr;
}

void NETSDL2::Events::Sensor::Lock()
{
	SDL_LockSensors();
}

void NETSDL2::Events::Sensor::Unlock()
{
	SDL_UnlockSensors();
}

int Sensor::NumSensors::get()
{
	return SDL_NumSensors();
}

Result<Sensor^, None^> NETSDL2::Events::Sensor::SensorFromInstanceID(SDL_SensorID instanceID)
{
	SDL_Sensor* sensor = SDL_SensorFromInstanceID(instanceID);
	if(sensor == __nullptr)
	{
		return Result<Sensor^, None^>::MakeFailure(None::Value);
	}

	Sensor^ sen = nullptr;
	bool found = nativeSensorConnections->TryGetValue(System::IntPtr(sensor), sen);
	if(!found)
	{
		return Result<Sensor^, None^>::MakeFailure(None::Value);
	}

	return sen;
}

Result<None^, None^> NETSDL2::Events::Sensor::GetData(float* data, int numValues)
{
	int result = SDL_SensorGetData(sensor, data, numValues);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Events::Sensor::GetData(array<float>^ data, int offset, int numValues)
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

	if(data->Length <= offset || data->Length < offset + numValues)
	{
		SDL_InvalidParamError(data);
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	pin_ptr<float> pData = &data[offset];
	int result = SDL_SensorGetData(sensor, (float*)pData, numValues);
	pData = nullptr;
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<SDL_SensorID, None^> NETSDL2::Events::Sensor::GetDeviceInstanceID(int deviceIndex)
{
	SDL_SensorID result = SDL_SensorGetDeviceInstanceID(deviceIndex);
	if(result < 0)
	{
		return Result<SDL_SensorID, None^>::MakeFailure(None::Value);
	}

	return result;
}

Result<System::String^, None^> NETSDL2::Events::Sensor::GetDeviceName(int deviceIndex)
{
	const char* result = SDL_SensorGetDeviceName(deviceIndex);
	if(result == __nullptr)
	{
		return Result<System::String^, None^>::MakeFailure(None::Value);
	}

	return StringMarshal::UTF8NativeToManaged(result);
}

Result<int, None^> NETSDL2::Events::Sensor::GetDeviceNonPortableType(int deviceIndex)
{
	int result = SDL_SensorGetDeviceNonPortableType(deviceIndex);
	if(result < 0)
	{
		Result<int, None^>::MakeFailure(None::Value);
	}

	return result;
}

SensorType NETSDL2::Events::Sensor::GetDeviceType(int deviceIndex)
{
	return (SensorType)SDL_SensorGetDeviceType(deviceIndex);
}

SDL_SensorID Sensor::InstanceID::get()
{
	return SDL_SensorGetInstanceID(sensor);
}

System::String^ Sensor::Name::get()
{
	const char* name = SDL_SensorGetName(sensor);
	return StringMarshal::UTF8NativeToManaged(name);
}

int Sensor::NonPortableType::get()
{
	return SDL_SensorGetNonPortableType(sensor);
}

SensorType Sensor::Type::get()
{
	return (SensorType)SDL_SensorGetType(sensor);
}

void NETSDL2::Events::Sensor::Update()
{
	SDL_SensorUpdate();
}
