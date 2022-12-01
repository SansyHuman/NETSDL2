#include "../../include/concurrent/Atomic.h"

using namespace NETSDL2::Concurrent;

NETSDL2::Concurrent::Atomic::Atomic(int value)
	: value(value)
{
	
}

int NETSDL2::Concurrent::Atomic::Add(int v)
{
	pin_ptr<Atomic> pA = &*this;
	return SDL_AtomicAdd((SDL_atomic_t*)pA, v);
}

bool NETSDL2::Concurrent::Atomic::CAS(int oldval, int newval)
{
	pin_ptr<Atomic> pA = &*this;
	return SDL_AtomicCAS((SDL_atomic_t*)pA, oldval, newval) == SDL_TRUE;
}

bool NETSDL2::Concurrent::Atomic::CASPtr(void** a, void* oldval, void* newval)
{
	return SDL_AtomicCASPtr(a, oldval, newval);
}

bool NETSDL2::Concurrent::Atomic::DecRef()
{
	pin_ptr<Atomic> pA = &*this;
	return SDL_AtomicDecRef((SDL_atomic_t*)pA) == SDL_TRUE;
}

int NETSDL2::Concurrent::Atomic::Get()
{
	pin_ptr<Atomic> pA = &*this;
	return SDL_AtomicGet((SDL_atomic_t*)pA);
}

void* NETSDL2::Concurrent::Atomic::GetPtr(void** a)
{
	return SDL_AtomicGetPtr(a);
}

void NETSDL2::Concurrent::Atomic::IncRef()
{
	pin_ptr<Atomic> pA = &*this;
	SDL_AtomicIncRef((SDL_atomic_t*)pA);
}

int NETSDL2::Concurrent::Atomic::Set(int v)
{
	pin_ptr<Atomic> pA = &*this;
	return SDL_AtomicSet((SDL_atomic_t*)pA, v);
}

void* NETSDL2::Concurrent::Atomic::SetPtr(void** a, void* v)
{
	return SDL_AtomicSetPtr(a, v);
}

void NETSDL2::Concurrent::Atomic::CompilerBarrier()
{
	SDL_CompilerBarrier();
}

void NETSDL2::Concurrent::Atomic::MemoryBarrierReleaseFunction()
{
	SDL_MemoryBarrierReleaseFunction();
}

void NETSDL2::Concurrent::Atomic::MemoryBarrierAcquireFunction()
{
	SDL_MemoryBarrierAcquireFunction();
}
