#include "../../include/video/RendererInfo.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Video;
using namespace NETSDL2::Internal;

PixelFormatEnum RendererInfo::e__FixedBuffer::default::get(int index)
{
	if(index < 0 || index >= 16)
		throw gcnew System::IndexOutOfRangeException();

	return System::Runtime::CompilerServices::Unsafe::Add(FixedElementField, index);
}

System::String^ RendererInfo::Name::get()
{
	return StringMarshal::UTF8NativeToManaged(name);
}

System::String^ NETSDL2::Video::RendererInfo::ToString()
{
	auto stringBuilder = gcnew System::Text::StringBuilder();
	stringBuilder->Append(Name);
	stringBuilder->Append("\n{\n");

	stringBuilder->AppendFormat("\tRender flags: {0}\n", Flags);
	stringBuilder->Append("\tTexture formats: [");
	for(Uint32 i = 0; i < NumTextureFormats; i++)
	{
		stringBuilder->AppendFormat("{0}, ", TextureFormats[i]);
	}
	stringBuilder->Append("]\n");
	stringBuilder->AppendFormat("\tMax texture size: ({0}, {1})\n", MaxTextureWidth, MaxTextureHeight);
	stringBuilder->Append("}");

	return stringBuilder->ToString();
}
