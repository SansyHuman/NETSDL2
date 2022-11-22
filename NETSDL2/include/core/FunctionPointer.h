#pragma once

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Wrapper of native function pointer of delegate.
		/// </summary>
		/// <typeparam name="F">Delegate to get function
		/// pointer.</typeparam>
		generic<class F> where F : System::Delegate
		public ref class FunctionPointer
		{
		private:
			F delegate;
			GCHandle handle;
			System::IntPtr pointer;

		public:
			/// <summary>
			/// Create a function pointer of the delegate.
			/// </summary>
			/// <param name="delegate">Delegate to gain
			/// function pointer.</param>
			FunctionPointer(F delegate);

			~FunctionPointer();
			!FunctionPointer();

			/// <summary>
			/// Get native function pointer of the
			/// delegate.
			/// </summary>
			property System::IntPtr Pointer
			{
				System::IntPtr get();
			}
		};
	}
}