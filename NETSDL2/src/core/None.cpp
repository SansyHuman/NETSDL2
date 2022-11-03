#include "../../include/core/None.h"

using namespace NETSDL2::Core;

None^ None::Create()
{
	return gcnew None();
}

System::String^ NETSDL2::Core::None::ToString()
{
	return "None";
}

None^ None::Value::get()
{
	return None::value->Value;
}
