#include "../../include/audio/AudioSpec.h"

using namespace NETSDL2::Audio;

System::String^ NETSDL2::Audio::AudioSpec::ToString()
{
    return System::String::Format("Audio({0}) [{1} Hz, {2} Ch.]", Format, Freq, Channels);
}
