#include "../include/Image.h"

using namespace NETSDL2::Image;
using namespace NETSDL2::Core;

InitFlags NETSDL2::Image::Image::Init(InitFlags flags)
{
	return (InitFlags)IMG_Init((int)flags);
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
