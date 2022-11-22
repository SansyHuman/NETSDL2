#include "../../include/events/Finger.h"

using namespace NETSDL2::Events;

System::String^ NETSDL2::Events::Finger::ToString()
{
	return System::String::Format("Finger {0} [x: {1}, y: {2}, p: {3}]", ID, X, Y, Pressure);
}
