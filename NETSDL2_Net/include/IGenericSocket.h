#pragma once

#include <SDL_net.h>

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Net
	{
		public interface class IGenericSocket
		{
			property SDLNet_GenericSocket NativeSocket
			{
				SDLNet_GenericSocket get();
			}
		};
	}
}