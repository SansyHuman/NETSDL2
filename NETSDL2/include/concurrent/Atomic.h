#pragma once

#include <SDL.h>

#include "../core/None.h"
#include "../core/Result.h"

using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics::CodeAnalysis;

namespace NETSDL2
{
	namespace Concurrent
	{
		using namespace NETSDL2::Core;

		/// <summary>
		/// A structure representing an atomic integer value.
		/// </summary>
		public value struct Atomic
		{
		private:
			int value;

		public:
			/// <summary>
			/// Create atomic variable.
			/// </summary>
			/// <param name="value">Initial value of the variable.</param>
			Atomic(int value);

			/// <summary>
			/// Add to an atomic variable.
			/// </summary>
			/// <param name="v">The desired value to add.</param>
			/// <returns>The previous value of the atomic variable.</returns>
			int Add(int v);

			/// <summary>
			/// Set an atomic variable to a new value if it is currently an old value.
			/// </summary>
			/// <param name="oldval">The old value.</param>
			/// <param name="newval">The new value.</param>
			/// <returns>true if the atomic variable was set, false otherwise.</returns>
			bool CAS(int oldval, int newval);

			/// <summary>
			/// Set a pointer to a new value if it is currently an old value.
			/// </summary>
			/// <param name="a">A pointer to a pointer.</param>
			/// <param name="oldval">The old pointer value.</param>
			/// <param name="newval">The new pointer value.</param>
			/// <returns>true if the pointer was set, false otherwise.</returns>
			static bool CASPtr(void** a, void* oldval, void* newval);

			/// <summary>
			/// Use this function to decrement an atomic variable used as a reference
			/// count.
			/// </summary>
			/// <returns>true if the variable reached zero after decrementing, false
			/// otherwise.</returns>
			bool DecRef();

			/// <summary>
			/// Get the value of an atomic variable.
			/// </summary>
			/// <returns>The current value of an atomic variable.</returns>
			int Get();

			/// <summary>
			/// Get the value of a pointer atomically.
			/// </summary>
			/// <param name="a">A pointer to a pointer.</param>
			/// <returns>The current value of a pointer.</returns>
			static void* GetPtr(void** a);

			/// <summary>
			/// Use this function to increment an atomic variable used as a reference
			/// count.
			/// </summary>
			void IncRef();

			/// <summary>
			/// Set an atomic variable to a value.
			/// </summary>
			/// <param name="v">The desired value.</param>
			/// <returns>The previous value of the atomic variable.</returns>
			int Set(int v);

			/// <summary>
			/// Set a pointer to a value atomically.
			/// </summary>
			/// <param name="a">A pointer to a pointer.</param>
			/// <param name="v">The desired pointer value.</param>
			/// <returns>The previous value of the pointer.</returns>
			static void* SetPtr(void** a, void* v);

			/// <summary>
			/// Use this function to prevent the compiler from reordering reads and
			/// writes to globally visible variables across the call.
			/// </summary>
			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void CompilerBarrier();

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void MemoryBarrierReleaseFunction();

			[MethodImpl(MethodImplOptions::AggressiveInlining)]
			static void MemoryBarrierAcquireFunction();
		};
	}
}