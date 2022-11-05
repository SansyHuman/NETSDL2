#include "../../include/events/Keysym.h"

using namespace NETSDL2::Events;

System::String^ NETSDL2::Events::Keysym::ToString()
{
	return System::String::Format("[Physical key: {0}  Virtual key: {1}  Modifiers: {2}]", Scancode, Sym, Mod);
}
