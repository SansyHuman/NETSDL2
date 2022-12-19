#pragma once

#include <SDL_net.h>

#include "IPAddress.h"

#using "NETSDL2.dll" as_friend

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Net
	{
		/// <summary>
		/// UDP packet structure.
		/// </summary>
		[StructLayout(LayoutKind::Sequential)]
		public value struct UDPPacket
		{
			/// <summary>
			/// The src/dst channel of the packet.
			/// </summary>
			int Channel;

			/// <summary>
			/// The packet data.
			/// </summary>
			Uint8* Data;

			/// <summary>
			/// The length of the packet data.
			/// </summary>
			int Len;

			/// <summary>
			/// The size of the data buffer.
			/// </summary>
			int Maxlen;

			/// <summary>
			/// Packet status after sending.
			/// </summary>
			int Status;

			/// <summary>
			/// The source/dest address of an incoming/outgoing packet.
			/// </summary>
			IPAddress Address;

			/// <summary>
			/// Allocate a single UDP packet.
			/// </summary>
			/// <param name="size">The maximum number of bytes of payload this packet will contain.</param>
			/// <returns>The new packet, or null if the function ran out of memory.</returns>
			static UDPPacket* AllocPacket(int size);

			/// <summary>
			/// Reallocate a UDP packet's payload space.
			/// </summary>
			/// <param name="packet">An existing packet.</param>
			/// <param name="newsize">The new maximum number of bytes of payload this packet will contain.
			/// </param>
			/// <returns>The new maximum payload size, which will be unchanged from the previous if the
			/// system ran out of memory.</returns>
			static int ResizePacket(UDPPacket* packet, int newsize);

			/// <summary>
			/// Dispose of a UDP packet.
			/// </summary>
			/// <param name="packet">The packet to free.</param>
			static void FreePacket(UDPPacket* packet);

			/// <summary>
			/// Allocate a UDP packet vector (array of packets).
			/// </summary>
			/// <param name="howmany">The number of packets to allocate.</param>
			/// <param name="size">The maximum bytes of payload each packet should contain.</param>
			/// <returns>A pointer to the first packet in the array, or null if the function ran out of
			/// memory.</returns>
			static UDPPacket** AllocPacketV(int howmany, int size);

			/// <summary>
			/// Free a UDP packet vector (array of packets).
			/// </summary>
			/// <param name="packetV">An array of packets.</param>
			static void FreePacketV(UDPPacket** packetV);
		};
	}
}