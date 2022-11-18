#include "../../include/events/Event.h"

#include "../../include/internal/StringMarshal.h"

using namespace NETSDL2::Events;
using namespace NETSDL2::Internal;

char TextEditingEvent::e__FixedBuffer::default::get(int index)
{
	if (index < 0 || index >= SDL_TEXTEDITINGEVENT_TEXT_SIZE)
		throw gcnew System::IndexOutOfRangeException();

	return System::Runtime::CompilerServices::Unsafe::Add(FixedElementField, index);
}

System::String^ TextEditingEvent::ManagedText::get()
{
	pin_ptr<char> pText = &Text.FixedElementField;
	return StringMarshal::UTF8NativeToManaged((char*)pText);
}

System::String^ TextEditingExtEvent::ManagedText::get()
{
	return StringMarshal::UTF8NativeToManaged(Text);
}

char TextInputEvent::e__FixedBuffer::default::get(int index)
{
	if (index < 0 || index >= SDL_TEXTEDITINGEVENT_TEXT_SIZE)
		throw gcnew System::IndexOutOfRangeException();

	return System::Runtime::CompilerServices::Unsafe::Add(FixedElementField, index);
}

System::String^ TextInputEvent::ManagedText::get()
{
	pin_ptr<char> pText = &Text.FixedElementField;
	return StringMarshal::UTF8NativeToManaged((char*)pText);
}

System::String^ DropEvent::ManagedFile::get()
{
	return StringMarshal::UTF8NativeToManaged(File);
}
