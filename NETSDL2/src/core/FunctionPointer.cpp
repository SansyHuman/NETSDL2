#include "../../include/core/FunctionPointer.h"

using namespace NETSDL2::Core;

generic<class F> where F : System::Delegate
FunctionPointer<F>::FunctionPointer(F delegate)
	: delegate(delegate)
{
	handle = GCHandle::Alloc(this->delegate);
	pointer = Marshal::GetFunctionPointerForDelegate(this->delegate);
}

generic<class F> where F : System::Delegate
NETSDL2::Core::FunctionPointer<F>::~FunctionPointer()
{
	this->!FunctionPointer();
}

generic<class F> where F : System::Delegate
NETSDL2::Core::FunctionPointer<F>::!FunctionPointer()
{
	pointer = System::IntPtr::Zero;
	handle.Free();
}

generic<class F> where F : System::Delegate
System::IntPtr FunctionPointer<F>::Pointer::get()
{
	return pointer;
}
