#pragma once

#include <SDL_net.h>

#include "IPAddress.h"
#include "UDPPacket.h"
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
		/// UDP network socket.
		/// </summary>
		public ref class UDPSocket : IGenericSocket
		{
		private:
			UDPsocket socket;

			UDPSocket(UDPsocket socket);

		public:
			virtual property SDLNet_GenericSocket NativeSocket
			{
				SDLNet_GenericSocket get();
			}

		public:
			/// <summary>
			/// The maximum channels on a a UDP socket.
			/// </summary>
			literal int MaxUDPChannels = SDLNET_MAX_UDPCHANNELS;

			/// <summary>
			/// The maximum addresses bound to a single UDP socket channel.
			/// </summary>
			literal int MaxUDPAddresses = SDLNET_MAX_UDPADDRESSES;

			/// <summary>
			/// Open a UDP network socket.
			/// </summary>
			/// <param name="port">The UDP port to bind this socket to.</param>
			/// <exception cref="System::Exception">Thrown when failed creation.
			/// </exception>
			UDPSocket(Uint16 port);

			~UDPSocket();
			!UDPSocket();

			/// <summary>
			/// Set the percentage of simulated packet loss for packets sent on the socket.
			/// </summary>
			property int PacketLoss
			{
				void set(int value);
			}

			/// <summary>
			/// Bind an address to the requested channel on the UDP socket.
			/// </summary>
			/// <param name="channel">The channel of the socket to bind to, or -1 to use the first
			/// available channel.</param>
			/// <param name="address">The address to bind to the socket's channel.</param>
			/// <returns>The channel which was bound, or None on error.</returns>
			Result<int, None^> Bind(int channel, IPAddress address);

			/// <summary>
			/// Unbind all addresses from the given channel.
			/// </summary>
			/// <param name="channel">The channel of the socket to unbind.</param>
			void Unbind(int channel);

			/// <summary>
			/// Get the IP address of the remote system for a socket and channel.
			/// </summary>
			/// <param name="channel">The channel of the socket.</param>
			/// <returns>The address bound to the socket's channel, or None if the channel is not bound.
			/// </returns>
			Result<IPAddress, None^> GetPeerAddress(int channel);

			/// <summary>
			/// Send a vector of packets to the the channels specified within the packet.
			/// Each packet will be updated with the status of the packet after it has been sent, -1 if the
			/// packet send failed.
			/// </summary>
			/// <param name="packets">An array of packets to send to the network.</param>
			/// <param name="npackets">The number of packets in the `packets` array.</param>
			/// <returns>The number of packets successfully sent from this machine.</returns>
			int SendV(UDPPacket** packets, int npackets);

			/// <summary>
			/// Send a single UDP packet to the specified channel.
			/// </summary>
			/// <param name="channel">The channel of the socket.</param>
			/// <param name="packet">A single packet to send to the network.</param>
			/// <returns>Success if the packet was sent, or Failure on error.</returns>
			Result<None^, None^> Send(int channel, UDPPacket* packet);

			/// <summary>
			/// Receive a vector of pending packets from a UDP socket.
			/// </summary>
			/// <param name="packets">An array of packets, null terminated.</param>
			/// <returns>The number of packets read from the network, or None on error. 0 means no packets
			/// were currently available.</returns>
			Result<int, None^> RecvV(UDPPacket** packets);

			/// <summary>
			/// Receive a single packet from a UDP socket.
			/// </summary>
			/// <param name="packet">A single packet to receive data into from the network.</param>
			/// <returns>1 if a new packet is available, or None on error. 0 means no packets were currently
			/// available.</returns>
			Result<int, None^> Recv(UDPPacket* packet);

			/// <summary>
			/// Close a UDP socket.
			/// </summary>
			void Close();
		};
	}
}