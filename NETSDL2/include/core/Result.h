#pragma once

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Core
	{
		/// <summary>
		/// Object that represents succeeded result or error.
		/// </summary>
		/// <typeparam name="Success">Type of succeeded result.</typeparam>
		/// <typeparam name="Failure">Type of error value.</typeparam>
		generic<class Success, class Failure>
		public value class Result
		{
		public:
			/// <summary>
			/// Type of the result.
			/// </summary>
			enum class Type
			{
				Succeeded, Failed
			};
		private:
			Success result;
			Failure error;
			Type resultType;

		public:
			/// <summary>
			/// Make succeeded result.
			/// </summary>
			/// <param name="result">Result value.</param>
			/// <returns>Result.</returns>
			static Result MakeResult(Success result);

			/// <summary>
			/// Make error.
			/// </summary>
			/// <param name="error">Error value.</param>
			/// <returns>Result.</returns>
			/// <exception cref="InvalidOperationException">Thrown when the result
			/// is not success and throwOnFailure is true.</exception>
			static Result MakeFailure(Failure error);

			/// <summary>
			/// Gets the type of the result.
			/// </summary>
			property Type ResultType
			{
				Type get();
			}

			/// <summary>
			/// Gets true if the result is success.
			/// </summary>
			property bool IsSuccess
			{
				bool get();
			}

			/// <summary>
			/// Gets true if the result is failure.
			/// </summary>
			property bool IsFailure
			{
				bool get();
			}

			/// <summary>
			/// Gets the succeeded value of the result.
			/// </summary>
			/// <exception cref="InvalidOperationException">Thrown when the result
			/// is not success.
			/// </exception>
			property Success ResultValue
			{
				Success get();
			}

			/// <summary>
			/// Gets the error value of the result.
			/// </summary>
			/// <exception cref="InvalidOperationException">Thrown when the result
			/// is not failure.
			/// </exception>
			property Failure ErrorValue
			{
				Failure get();
			}

			virtual System::String^ ToString() override;

			static operator Result(Success result);

			static operator Success([In][IsReadOnly]Result<Success, Failure>% result);
		};
	}
}