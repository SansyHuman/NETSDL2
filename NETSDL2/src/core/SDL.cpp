#include "../../include/core/SDL.h"
#include "../../include/core/None.h"
#include "../../include/core/Result.h"
#include "../../include/core/Log.h"

using namespace NETSDL2::Core;

Result<None^, int> SDL::Init(SubSystems flags)
{
	return InitSubsystem(flags);
}

Result<None^, int> NETSDL2::Core::SDL::InitSubsystem(SubSystems flags)
{
	int result = SDL_InitSubSystem(static_cast<Uint32>(flags));

	if(result < 0)
	{
		return Result<None^, int>::MakeFailure(result);
	}

	Logging::Init();

	return None::Value;
}

void NETSDL2::Core::SDL::Quit()
{
	Logging::Quit();

	SDL_Quit();
}

void NETSDL2::Core::SDL::QuitSubSystem(SubSystems flags)
{
	SDL_QuitSubSystem((Uint32)flags);
}

void NETSDL2::Core::SDL::SetMainReady()
{
	SDL_SetMainReady();
}

SubSystems NETSDL2::Core::SDL::WasInit(SubSystems flags)
{
	return (SubSystems)SDL_WasInit(static_cast<Uint32>(flags));
}
