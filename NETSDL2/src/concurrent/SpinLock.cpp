#include "../../include/concurrent/SpinLock.h"

using namespace NETSDL2::Concurrent;

NETSDL2::Concurrent::SpinLock::SpinLock()
	: lock(0)
{
	
}

void NETSDL2::Concurrent::SpinLock::Lock()
{
	pin_ptr<SDL_SpinLock> pLock = &lock;
	SDL_AtomicLock((SDL_SpinLock*)pLock);
}

bool NETSDL2::Concurrent::SpinLock::TryLock()
{
	pin_ptr<SDL_SpinLock> pLock = &lock;
	return SDL_AtomicTryLock((SDL_SpinLock*)pLock) == SDL_TRUE;
}

void NETSDL2::Concurrent::SpinLock::Unlock()
{
	pin_ptr<SDL_SpinLock> pLock = &lock;
	SDL_AtomicUnlock((SDL_SpinLock*)pLock);
}
