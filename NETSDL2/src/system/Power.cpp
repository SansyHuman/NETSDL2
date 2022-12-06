#include "../../include/system/Power.h"

using namespace NETSDL2::Systems;

PowerState NETSDL2::Systems::Power::GetPowerInfo(int% secs, int% pct)
{
	int s = 0, p = 0;
	SDL_PowerState state = SDL_GetPowerInfo(&s, &p);
	secs = s;
	pct = p;

	return (PowerState)state;
}
