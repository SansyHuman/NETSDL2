#include "../../include/system/Bits.h"

using namespace NETSDL2::Systems;

int NETSDL2::Systems::Bits::MostSignificantBitIndex32(Uint32 x)
{
	return SDL_MostSignificantBitIndex32(x);
}

bool NETSDL2::Systems::Bits::HasExactlyOneBitSet32(Uint32 x)
{
	return SDL_HasExactlyOneBitSet32(x) == SDL_TRUE;
}
