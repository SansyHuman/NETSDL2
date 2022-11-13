#include "../../include/video/ICCProfile.h"

using namespace NETSDL2::Video;

NETSDL2::Video::ICCProfile::ICCProfile(void* profile, size_t size)
	: profile(profile), size(size)
{
	
}

NETSDL2::Video::ICCProfile::~ICCProfile()
{
	this->!ICCProfile();
}

NETSDL2::Video::ICCProfile::!ICCProfile()
{
	SDL_free(profile.ToPointer());
}

System::IntPtr ICCProfile::Profile::get()
{
	return profile;
}

size_t ICCProfile::Size::get()
{
	return size;
}
