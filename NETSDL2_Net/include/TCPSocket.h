#pragma once

#include <SDL_net.h>

#include "IPAddress.h"
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
		/// TCP network socket.
		/// </summary>
		public ref class TCPSocket : IGenericSocket
		{
		private:
			TCPsocket socket;

			TCPSocket(TCPsocket socket);

		public:
			virtual property SDLNet_GenericSocket NativeSocket
			{
				SDLNet_GenericSocket get();
			}

		public:
			/// <summary>
			/// Open a TCP network socket.
			/// </summary>
			/// <param name="ip">The address to open a connection to (or to host a server on).</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			TCPSocket(IPAddress ip);

			~TCPSocket();
			!TCPSocket();

			/// <summary>
			/// Accept an incoming connection on the given server socket.
			/// </summary>
			/// <returns>The newly created socket, or None if there was an error.</returns>
			Result<TCPSocket^, None^> Accept();

			/// <summary>
			/// Get the IP address of the remote system associated with the socket.
			/// </summary>
			/// <returns>The address information for the socket or None if the socket is a server socket.
			/// </returns>
			Result<IPAddress, None^> GetPeerAddress();

			/// <summary>
			/// Send data over a non-server socket.
			/// </summary>
			/// <param name="data">A pointer to the bytes to send.</param>
			/// <param name="len">The number of bytes, pointed to by `data`, to transmit.</param>
			/// <returns>Number of bytes sent, which might be less if there was a problem or connection
			/// failure. If the socket is invalid, this function can return None.</returns>
			Result<int, None^> Send(System::IntPtr data, int len);

			/// <summary>
			/// Receive data from a non-server socket.
			/// </summary>
			/// <param name="data">A pointer to where to store received data.</param>
			/// <param name="maxlen">The maximum number of bytes that can be stored at `data`.</param>
			/// <returns>Number of bytes received, which might be less than `maxlen`. If the remote
			/// connection was closed, or an unknown socket error occurred, this returns None.</returns>
			Result<int, None^> Recv(System::IntPtr data, int maxlen);

			/// <summary>
			/// Close a TCP network socket.
			/// </summary>
			void Close();
		};
	}
}