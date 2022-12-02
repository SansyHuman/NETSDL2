#include "../../include/system/Endian.h"

using namespace NETSDL2::Systems;

Uint16 NETSDL2::Systems::Endian::Swap16(Uint16 x)
{
	return swap16(x);
}

Uint32 NETSDL2::Systems::Endian::Swap32(Uint32 x)
{
	return swap32(x);
}

Uint64 NETSDL2::Systems::Endian::Swap64(Uint64 x)
{
	return swap64(x);
}

Uint16 NETSDL2::Systems::Endian::SwapBE16(Uint16 x)
{
	return swapBE16(x);
}

Uint32 NETSDL2::Systems::Endian::SwapBE32(Uint32 x)
{
	return swapBE32(x);
}

Uint64 NETSDL2::Systems::Endian::SwapBE64(Uint64 x)
{
	return swapBE64(x);
}

float NETSDL2::Systems::Endian::SwapFloat(float x)
{
	return swapFloat(x);
}

float NETSDL2::Systems::Endian::SwapFloatBE(float x)
{
	return swapFloatBE(x);
}

float NETSDL2::Systems::Endian::SwapFloatLE(float x)
{
	return swapFloatLE(x);
}

Uint16 NETSDL2::Systems::Endian::SwapLE16(Uint16 x)
{
	return swapLE16(x);
}

Uint32 NETSDL2::Systems::Endian::SwapLE32(Uint32 x)
{
	return swapLE32(x);
}

Uint64 NETSDL2::Systems::Endian::SwapLE64(Uint64 x)
{
	return swapLE64(x);
}
