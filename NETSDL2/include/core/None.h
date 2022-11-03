#pragma once

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Represents no value.
		/// </summary>
		public ref class None
		{
		private:
			static System::Lazy<None^>^ value = gcnew System::Lazy<None^>(gcnew System::Func<None^>(&None::Create));

			None() {}
			static None^ Create();

		public:
			/// <summary>
			/// Gets the unique None value.
			/// </summary>
			static property None^ Value
			{
				None^ get();
			}

			virtual System::String^ ToString() override;
		};
	}
}