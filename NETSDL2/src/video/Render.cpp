#include "../../include/video/Render.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Core;

Result<int, int> NETSDL2::Video::Render::GetNumRenderDrivers()
{
	int num = SDL_GetNumRenderDrivers();
	if(num < 0)
	{
		return Result<int, int>::MakeFailure(num);
	}

	return num;
}

Result<RendererInfo, int> NETSDL2::Video::Render::GetRenderDriverInfo(int index)
{
	RendererInfo info;
	int result = SDL_GetRenderDriverInfo(index, (SDL_RendererInfo*)&info);
	if(result < 0)
	{
		return Result<RendererInfo, int>::MakeFailure(result);
	}

	return info;
}

array<RendererInfo>^ NETSDL2::Video::Render::GetRenderDriverInfos()
{
	auto cnt = GetNumRenderDrivers();
	if(cnt.IsFailure)
		return gcnew array<RendererInfo>(0);

	System::Collections::Generic::List<RendererInfo>^ renderers = gcnew System::Collections::Generic::List<RendererInfo>(cnt.ResultValue);

	for(int i = 0; i < cnt.ResultValue; i++)
	{
		auto renderer = GetRenderDriverInfo(i);
		if(renderer.IsFailure)
			break;
		renderers->Add(renderer.ResultValue);
	}

	return renderers->ToArray();
}
