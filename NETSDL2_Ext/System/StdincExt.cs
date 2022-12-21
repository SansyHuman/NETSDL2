using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Systems
{
    /// <summary>
    /// Malloc function.
    /// </summary>
    /// <param name="size">Size of the memory to allocate in bytes.</param>
    /// <returns>Allocated memory on success or null on failure.</returns>
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate IntPtr MallocFunc(ulong size);

    /// <summary>
    /// Calloc function.
    /// </summary>
    /// <param name="nmemb">The number of objects.</param>
    /// <param name="size">Size of each object.</param>
    /// <returns>Allocated memory on success or null on failure.</returns>
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate IntPtr CallocFunc(ulong nmemb, ulong size);

    /// <summary>
    /// Realloc function.
    /// </summary>
    /// <param name="mem">Pointer to the memory area to be reallocated.</param>
    /// <param name="size">New size of the memory in bytes.</param>
    /// <returns>Allocated memory on success or null on failure.</returns>
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate IntPtr ReallocFunc(IntPtr mem, ulong size);

    /// <summary>
    /// Free function.
    /// </summary>
    /// <param name="mem">Pointer to the memory area to be freed.</param>
    [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
    public delegate void FreeFunc(IntPtr mem);

    /// <summary>
    /// Extension functions of Stdinc.
    /// </summary>
    public static class StdincExt
    {
        /// <summary>
        /// Replace SDL's memory allocation functions with a custom set.
        /// </summary>
        /// <param name="mallocFunc"></param>
        /// <param name="callocFunc"></param>
        /// <param name="reallocFunc"></param>
        /// <param name="freeFunc"></param>
        /// <returns>None on success or error code on failure.</returns>
        [MethodImpl(MethodImplOptions.AggressiveInlining)]
        public static unsafe Result<None, int> SetMemoryFunctions(
            FunctionPointer<MallocFunc> mallocFunc,
            FunctionPointer<CallocFunc> callocFunc,
            FunctionPointer<ReallocFunc> reallocFunc,
            FunctionPointer<FreeFunc> freeFunc)
        {
            return Stdinc.SetMemoryFunctions(
                (delegate* unmanaged[Cdecl]<ulong, void*>)mallocFunc.Pointer.ToPointer(),
                (delegate* unmanaged[Cdecl]<ulong, ulong, void*>)callocFunc.Pointer.ToPointer(),
                (delegate* unmanaged[Cdecl]<void*, ulong, void*>)reallocFunc.Pointer.ToPointer(),
                (delegate* unmanaged[Cdecl]<void*, void>)freeFunc.Pointer.ToPointer());
        }
    }
}
