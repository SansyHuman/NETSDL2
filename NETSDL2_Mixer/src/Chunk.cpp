#include "../include/Chunk.h"

using namespace NETSDL2::Core;
using namespace NETSDL2::Audio;
using namespace NETSDL2::Internal;

void NETSDL2::Audio::Chunk::InitChunk(Mix_Chunk* chunk)
{
	this->chunk = chunk;
	nativeChunkConnections[System::IntPtr(chunk)] = this;
}

Mix_Chunk* Chunk::NativeChunk::get()
{
	return chunk;
}

Chunk^ NETSDL2::Audio::Chunk::GetChunkFromNative(Mix_Chunk* chunk)
{
	Chunk^ ch = nullptr;
	bool found = nativeChunkConnections->TryGetValue(System::IntPtr(chunk), ch);
	if(!found)
	{
		return nullptr;
	}

	return ch;
}

NETSDL2::Audio::Chunk::Chunk(System::String^ file)
{
	StringMarshal context;
	Mix_Chunk* chunk = Mix_LoadWAV(context.ManagedToUTF8Native(file));
	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::Chunk(RWops^ src, bool freesrc)
{
	Mix_Chunk* chunk = Mix_LoadWAV_RW(src->NativeOps, freesrc ? 1 : 0);
	if(freesrc)
	{
		delete src;
	}

	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::Chunk(Uint8* mem, Uint32 len)
{
	Mix_Chunk* chunk = Mix_QuickLoad_RAW(mem, len);
	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::Chunk(array<Uint8>^ mem, Uint32 offset, Uint32 len)
{
	if(mem->Length == 0)
	{
		Error::SetError("Invalid parameter mem.");
		throw gcnew System::Exception("Invalid parameter mem.");
	}

	if(mem->Length < offset + len)
	{
		Error::SetError("Invalid parameter mem.");
		throw gcnew System::Exception("Invalid parameter mem.");
	}

	pin_ptr<Uint8> pMem = &mem[offset];
	Mix_Chunk* chunk = Mix_QuickLoad_RAW((Uint8*)pMem, len);
	pMem = nullptr;
	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::Chunk(Uint8* mem)
{
	Mix_Chunk* chunk = Mix_QuickLoad_WAV(mem);
	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::Chunk(array<Uint8>^ mem, Uint32 offset)
{
	if(mem->Length == 0 || mem->Length <= offset)
	{
		Error::SetError("Invalid parameter mem.");
		throw gcnew System::Exception("Invalid parameter mem.");
	}

	pin_ptr<Uint8> pMem = &mem[offset];
	Mix_Chunk* chunk = Mix_QuickLoad_WAV((Uint8*)pMem);
	if(chunk == __nullptr)
	{
		throw gcnew System::Exception(Error::GetError());
	}

	InitChunk(chunk);
}

NETSDL2::Audio::Chunk::~Chunk()
{
	Chunk^ dummy = nullptr;
	nativeChunkConnections->TryRemove(System::IntPtr(chunk), dummy);
	this->!Chunk();
}

NETSDL2::Audio::Chunk::!Chunk()
{
	Mix_FreeChunk(chunk);
	chunk = __nullptr;
}

int NETSDL2::Audio::Chunk::Volume(int volume)
{
	return Mix_VolumeChunk(chunk, volume);
}
