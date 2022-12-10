#include "../include/Animation.h"

using namespace NETSDL2::Image;
using namespace NETSDL2::Internal;

void NETSDL2::Image::Animation::InitAnimation(IMG_Animation* anim)
{
    this->anim = anim;
    int cnt = anim->count;
    frames = gcnew array<Surface^>(cnt);

    for(int i = 0; i < cnt; i++)
    {
        frames[i] = gcnew Surface(anim->frames[i], false);
    }
}

NETSDL2::Image::Animation::Animation(IMG_Animation* anim)
{
    InitAnimation(anim);
}

NETSDL2::Image::Animation::Animation(System::String^ file)
{
    StringMarshal context;

    IMG_Animation* anim = IMG_LoadAnimation(context.ManagedToUTF8Native(file));
    if(anim == __nullptr)
    {
        throw gcnew System::Exception(Error::GetError());
    }

    InitAnimation(anim);
}

NETSDL2::Image::Animation::Animation(RWops^ src, bool freesrc)
{
    IMG_Animation* anim = IMG_LoadAnimation_RW(src->NativeOps, freesrc ? 1 : 0);
    if(freesrc)
    {
        delete src;
    }

    if(anim == __nullptr)
    {
        throw gcnew System::Exception(Error::GetError());
    }

    InitAnimation(anim);
}

NETSDL2::Image::Animation::Animation(RWops^ src, bool freesrc, System::String^ type)
{
    StringMarshal context;

    IMG_Animation* anim = IMG_LoadAnimationTyped_RW(src->NativeOps, freesrc ? 1 : 0, context.ManagedToUTF8Native(type));
    if(freesrc)
    {
        delete src;
    }

    if(anim == __nullptr)
    {
        throw gcnew System::Exception(Error::GetError());
    }

    InitAnimation(anim);
}

NETSDL2::Image::Animation::~Animation()
{
    int cnt = anim->count;
    for(int i = 0; i < cnt; i++)
    {
        delete frames[i];
        frames[i] = nullptr;
    }

    this->!Animation();
}

NETSDL2::Image::Animation::!Animation()
{
    IMG_FreeAnimation(anim);
    anim = __nullptr;
}

int Animation::Width::get()
{
    return anim->w;
}

int Animation::Height::get()
{
    return anim->h;
}

int Animation::Count::get()
{
    return anim->count;
}

Surface^ Animation::default::get(int index)
{
    return frames[index];
}

int NETSDL2::Image::Animation::GetDelay(int frame)
{
    if(frame < 0 || frame >= anim->count)
    {
        throw gcnew System::IndexOutOfRangeException("Frame index is out of range.");
    }

    return anim->delays[frame];
}

Result<Animation^, None^> NETSDL2::Image::Animation::LoadGIFAnimation(RWops^ src)
{
    IMG_Animation* anim = IMG_LoadGIFAnimation_RW(src->NativeOps);
    if(anim == __nullptr)
    {
        return Result<Animation^, None^>::MakeFailure(None::Value);
    }

    return gcnew Animation(anim);
}
