#include "../include/Image.h"

using namespace NETSDL2::Image;
using namespace NETSDL2::Core;
using namespace NETSDL2::Internal;

ImageInitFlags NETSDL2::Image::Image::Init(ImageInitFlags flags)
{
	return (ImageInitFlags)IMG_Init((int)flags);
}

bool NETSDL2::Image::Image::IsAVIF(RWops^ src)
{
	int result = IMG_isAVIF(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsBMP(RWops^ src)
{
	int result = IMG_isBMP(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsCUR(RWops^ src)
{
	int result = IMG_isCUR(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsGIF(RWops^ src)
{
	int result = IMG_isGIF(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsICO(RWops^ src)
{
	int result = IMG_isICO(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsJPG(RWops^ src)
{
	int result = IMG_isJPG(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsJXL(RWops^ src)
{
	int result = IMG_isJXL(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsLBM(RWops^ src)
{
	int result = IMG_isLBM(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsPCX(RWops^ src)
{
	int result = IMG_isPCX(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsPNG(RWops^ src)
{
	int result = IMG_isPNG(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsPNM(RWops^ src)
{
	int result = IMG_isPNM(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsQOI(RWops^ src)
{
	int result = IMG_isQOI(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsSVG(RWops^ src)
{
	int result = IMG_isSVG(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsTIF(RWops^ src)
{
	int result = IMG_isTIF(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsWEBP(RWops^ src)
{
	int result = IMG_isWEBP(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsXCF(RWops^ src)
{
	int result = IMG_isXCF(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsXPM(RWops^ src)
{
	int result = IMG_isXPM(src->NativeOps);
	return result != 0;
}

bool NETSDL2::Image::Image::IsXV(RWops^ src)
{
	int result = IMG_isXV(src->NativeOps);
	return result != 0;
}

SDLVersion NETSDL2::Image::Image::LinkedVersion::get()
{
	return *((SDLVersion*)IMG_Linked_Version());
}

SDLVersion NETSDL2::Image::Image::Version::get()
{
	SDL_version version = {};
	SDL_IMAGE_VERSION(&version);
	return *((SDLVersion*)&version);
}

Result<Surface^, None^> NETSDL2::Image::Image::Load(System::String^ file)
{
	StringMarshal context;
	SDL_Surface* surface = IMG_Load(context.ManagedToUTF8Native(file));
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::Load(RWops^ src, bool freesrc)
{
	SDL_Surface* surface = IMG_Load_RW(src->NativeOps, freesrc ? 1 : 0);
	if(freesrc)
	{
		delete src;
	}

	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadAVIF(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadAVIF_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadBMP(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadBMP_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadCUR(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadCUR_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadGIF(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadGIF_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadICO(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadICO_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadJPG(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadJPG_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadJXL(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadJXL_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadLBM(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadLBM_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadPCX(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadPCX_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadPNG(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadPNG_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadPNM(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadPNM_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadQOI(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadQOI_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadSizedSVG(RWops^ src, int width, int height)
{
	SDL_Surface* surface = IMG_LoadSizedSVG_RW(src->NativeOps, width, height);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadSVG(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadSVG_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Texture^, None^> NETSDL2::Image::Image::LoadTexture(Renderer^ renderer, System::String^ file)
{
	StringMarshal context;
	SDL_Texture* tex = IMG_LoadTexture((SDL_Renderer*)renderer->NativeRenderer, context.ManagedToUTF8Native(file));
	if(tex == __nullptr)
	{
		return Result<Texture^, None^>::MakeFailure(None::Value);
	}

	return gcnew Texture((void*)tex, true);
}

Result<Texture^, None^> NETSDL2::Image::Image::LoadTexture(Renderer^ renderer, RWops^ src, bool freesrc)
{
	SDL_Texture* tex = IMG_LoadTexture_RW((SDL_Renderer*)renderer->NativeRenderer, src->NativeOps, freesrc ? 1 : 0);
	if(freesrc)
	{
		delete src;
	}

	if(tex == __nullptr)
	{
		return Result<Texture^, None^>::MakeFailure(None::Value);
	}

	return gcnew Texture((void*)tex, true);
}

Result<Texture^, None^> NETSDL2::Image::Image::LoadTexture(Renderer^ renderer, RWops^ src, bool freesrc, System::String^ type)
{
	StringMarshal context;
	SDL_Texture* tex = IMG_LoadTextureTyped_RW((SDL_Renderer*)renderer->NativeRenderer, src->NativeOps, freesrc ? 1 : 0, context.ManagedToUTF8Native(type));
	if(freesrc)
	{
		delete src;
	}

	if(tex == __nullptr)
	{
		return Result<Texture^, None^>::MakeFailure(None::Value);
	}

	return gcnew Texture((void*)tex, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadTGA(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadTGA_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadTIF(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadTIF_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::Load(RWops^ src, bool freesrc, System::String^ type)
{
	StringMarshal context;
	SDL_Surface* surface = IMG_LoadTyped_RW(src->NativeOps, freesrc ? 1 : 0, context.ManagedToUTF8Native(type));
	if(freesrc)
	{
		delete src;
	}

	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadWEBP(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadWEBP_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadXCF(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadXCF_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadXPM(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadXPM_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::LoadXV(RWops^ src)
{
	SDL_Surface* surface = IMG_LoadXV_RW(src->NativeOps);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

void NETSDL2::Image::Image::Quit()
{
	IMG_Quit();
}

Result<Surface^, None^> NETSDL2::Image::Image::ReadXPMFromArray(char** xpm)
{
	SDL_Surface* surface = IMG_ReadXPMFromArray(xpm);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::ReadXPMFromArray(array<System::String^>^ xpm)
{
	StringMarshal context;
	char** ppXpm = __nullptr;

	try
	{
		ppXpm = new char*[xpm->Length];
		for(int i = 0; i < xpm->Length; i++)
		{
			ppXpm[i] = context.ManagedToUTF8Native(xpm[i]);
		}

		SDL_Surface* surface = IMG_ReadXPMFromArray(ppXpm);
		if(surface == __nullptr)
		{
			return Result<Surface^, None^>::MakeFailure(None::Value);
		}

		return gcnew Surface(surface, true);
	}
	finally
	{
		if(ppXpm != __nullptr)
		{
			delete[] ppXpm;
		}
	}
}

Result<Surface^, None^> NETSDL2::Image::Image::ReadXPMFromArrayToRGB888(char** xpm)
{
	SDL_Surface* surface = IMG_ReadXPMFromArrayToRGB888(xpm);
	if(surface == __nullptr)
	{
		return Result<Surface^, None^>::MakeFailure(None::Value);
	}

	return gcnew Surface(surface, true);
}

Result<Surface^, None^> NETSDL2::Image::Image::ReadXPMFromArrayToRGB888(array<System::String^>^ xpm)
{
	StringMarshal context;
	char** ppXpm = __nullptr;

	try
	{
		ppXpm = new char* [xpm->Length];
		for(int i = 0; i < xpm->Length; i++)
		{
			ppXpm[i] = context.ManagedToUTF8Native(xpm[i]);
		}

		SDL_Surface* surface = IMG_ReadXPMFromArrayToRGB888(ppXpm);
		if(surface == __nullptr)
		{
			return Result<Surface^, None^>::MakeFailure(None::Value);
		}

		return gcnew Surface(surface, true);
	}
	finally
	{
		if(ppXpm != __nullptr)
		{
			delete[] ppXpm;
		}
	}
}

Result<None^, None^> NETSDL2::Image::Image::SaveJPG(Surface^ surface, System::String^ file, int quality)
{
	StringMarshal context;
	int result = IMG_SaveJPG(surface->NativeSurface, context.ManagedToUTF8Native(file), quality);
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Image::Image::SaveJPG(Surface^ surface, RWops^ dst, bool freedst, int quality)
{
	int result = IMG_SaveJPG_RW(surface->NativeSurface, dst->NativeOps, freedst ? 1 : 0, quality);
	if(freedst)
	{
		delete dst;
	}

	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Image::Image::SavePNG(Surface^ surface, System::String^ file)
{
	StringMarshal context;
	int result = IMG_SavePNG(surface->NativeSurface, context.ManagedToUTF8Native(file));
	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}

Result<None^, None^> NETSDL2::Image::Image::SavePNG(Surface^ surface, RWops^ dst, bool freedst)
{
	int result = IMG_SavePNG_RW(surface->NativeSurface, dst->NativeOps, freedst ? 1 : 0);
	if(freedst)
	{
		delete dst;
	}

	if(result < 0)
	{
		return Result<None^, None^>::MakeFailure(None::Value);
	}

	return None::Value;
}
