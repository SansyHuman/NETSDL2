#pragma once

#include <SDL_net.h>
#include "IGenericSocket.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Net
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// Hooks for checking sockets for available data.
		/// </summary>
		public ref class SocketSet
		{
		private:
			SDLNet_SocketSet set;

		public:
			/// <summary>
			/// Allocate a socket set.
			/// </summary>
			/// <param name="maxsockets">The maximum amount of sockets to include in this set.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			SocketSet(int maxsockets);

			~SocketSet();
			!SocketSet();

			/// <summary>
			/// Add a socket to a socket set, to be checked for available data.
			/// </summary>
			/// <param name="sock">The socket to add to the set.</param>
			/// <returns>The total number of sockets contained in the set (including this new one), or None
			/// if the set is already full.</returns>
			Result<int, None^> AddSocket(IGenericSocket^ sock);

			/// <summary>
			/// Remove a socket from a set of sockets to be checked for available data.
			/// </summary>
			/// <param name="sock">The socket to remove from the set.</param>
			/// <returns>The total number of sockets contained in the set (after `sock`'s removal), or None if
			/// `sock` was not in the set.</returns>
			Result<int, None^> DelSocket(IGenericSocket^ sock);

			/// <summary>
			/// Check a socket set for data availability.
			/// </summary>
			/// <param name="timeout">The time to wait in milliseconds for new data to arrive. A timeout of
			/// zero checks for new dataand returns without blocking.</param>
			/// <returns>The number of sockets ready for reading, or None if there was an error with the
			/// select() system call.</returns>
			Result<int, None^> CheckSockets(Uint32 timeout);
		};
	}
}