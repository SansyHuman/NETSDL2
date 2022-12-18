#pragma once

#include <SDL_net.h>

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Net
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// IPv4 hostname.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct IPAddress
		{
			/// <summary>
			/// 32-bit IPv4 host address.
			/// </summary>
			Uint32 Host;

			/// <summary>
			/// 16-bit protocol port.
			/// </summary>
			Uint16 Port;

			/// <summary>
			/// Create new IPv4 address.
			/// </summary>
			/// <param name="host">32-bit IPv4 host address.</param>
			/// <param name="port">16-bit protocol port.</param>
			IPAddress(Uint32 host, Uint16 port);

			/// <summary>
			/// Create new IPv4 address.
			/// </summary>
			/// <param name="h1">First 8-bit of 32-bit IPv4 host address.</param>
			/// <param name="h1">Second 8-bit of 32-bit IPv4 host address.</param>
			/// <param name="h1">Third 8-bit of 32-bit IPv4 host address.</param>
			/// <param name="h1">Fourth 8-bit of 32-bit IPv4 host address.</param>
			/// <param name="port">16-bit protocol port.</param>
			IPAddress(Uint8 h1, Uint8 h2, Uint8 h3, Uint8 h4, Uint16 port);

			/// <summary>
			/// Resolve a host name and port to an IP address in network form.
			/// </summary>
			/// <param name="host">The hostname to lookup.</param>
			/// <param name="port">The port intended to be connected to, to fill into address.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			IPAddress(System::String^ host, Uint16 port);

			literal Uint32 Any = INADDR_ANY;
			literal Uint32 None = INADDR_NONE;
			literal Uint32 Loopback = INADDR_LOOPBACK;
			literal Uint32 Broadcast = INADDR_BROADCAST;

			virtual System::String^ ToString() override;

			/// <summary>
			/// Resolve an IP address to a host name in canonical form.
			/// </summary>
			/// <returns>The hostname or None if the IP could not be resolved.</returns>
			Result<System::String^, NETSDL2::Core::None^> ResolveIP();
		};

	}
}