#include "../../include/video/Blend.h"

using namespace NETSDL2::Video;

BlendMode NETSDL2::Video::Blend::ComposeCustomBlendMode(BlendFactor srcColorFactor, BlendFactor dstColorFactor, BlendOperation colorOperation, BlendFactor srcAlphaFactor, BlendFactor dstAlphaFactor, BlendOperation alphaOperation)
{
	return (BlendMode)SDL_ComposeCustomBlendMode((SDL_BlendFactor)srcColorFactor, (SDL_BlendFactor)dstColorFactor, (SDL_BlendOperation)colorOperation, (SDL_BlendFactor)srcAlphaFactor, (SDL_BlendFactor)dstAlphaFactor, (SDL_BlendOperation)alphaOperation);
}
