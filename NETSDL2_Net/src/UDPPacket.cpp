#include "../include/UDPPacket.h"

using namespace NETSDL2::Net;

UDPPacket* NETSDL2::Net::UDPPacket::AllocPacket(int size)
{
	return (UDPPacket*)SDLNet_AllocPacket(size);
}

int NETSDL2::Net::UDPPacket::ResizePacket(UDPPacket* packet, int newsize)
{
	return SDLNet_ResizePacket((UDPpacket*)packet, newsize);
}

void NETSDL2::Net::UDPPacket::FreePacket(UDPPacket* packet)
{
	SDLNet_FreePacket((UDPpacket*)packet);
}

UDPPacket** NETSDL2::Net::UDPPacket::AllocPacketV(int howmany, int size)
{
	return (UDPPacket**)SDLNet_AllocPacketV(howmany, size);
}

void NETSDL2::Net::UDPPacket::FreePacketV(UDPPacket** packetV)
{
	SDLNet_FreePacketV((UDPpacket**)packetV);
}
