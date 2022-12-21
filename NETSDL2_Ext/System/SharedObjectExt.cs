using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Systems
{
    /// <summary>
    /// Extensions of <see cref="SharedObject"/>.
    /// </summary>
    public static unsafe class SharedObjectExt
    {
        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<void> LoadFunctionStdcall(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T">Type of first parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T, void> LoadFunctionStdcall<T>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, void> LoadFunctionStdcall<T1, T2>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, void> LoadFunctionStdcall<T1, T2, T3>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, void> LoadFunctionStdcall<T1, T2, T3, T4>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, void> LoadFunctionStdcall<T1, T2, T3, T4, T5>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, void> LoadFunctionStdcall<T1, T2, T3, T4, T5, T6>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, void> LoadFunctionStdcall<T1, T2, T3, T4, T5, T6, T7>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="T8">Type of eighth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, T8, void> LoadFunctionStdcall<T1, T2, T3, T4, T5, T6, T7, T8>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, T8, void>)result.ResultValue.ToPointer();
        }


        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<void> LoadFunctionCdecl(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T">Type of first parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T, void> LoadFunctionCdecl<T>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, void> LoadFunctionCdecl<T1, T2>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, void> LoadFunctionCdecl<T1, T2, T3>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, void> LoadFunctionCdecl<T1, T2, T3, T4>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, void> LoadFunctionCdecl<T1, T2, T3, T4, T5>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, void> LoadFunctionCdecl<T1, T2, T3, T4, T5, T6>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, void> LoadFunctionCdecl<T1, T2, T3, T4, T5, T6, T7>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, void>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="T8">Type of eighth parameter.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, void> LoadFunctionCdecl<T1, T2, T3, T4, T5, T6, T7, T8>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, void>)result.ResultValue.ToPointer();
        }



        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<R> LoadFunctionRetStdcall<R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T">Type of first parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T, R> LoadFunctionRetStdcall<T, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, R> LoadFunctionRetStdcall<T1, T2, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, R> LoadFunctionRetStdcall<T1, T2, T3, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, R> LoadFunctionRetStdcall<T1, T2, T3, T4, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, R> LoadFunctionRetStdcall<T1, T2, T3, T4, T5, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, R> LoadFunctionRetStdcall<T1, T2, T3, T4, T5, T6, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, R> LoadFunctionRetStdcall<T1, T2, T3, T4, T5, T6, T7, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with stdcall convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="T8">Type of eighth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, T8, R> LoadFunctionRetStdcall<T1, T2, T3, T4, T5, T6, T7, T8, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Stdcall]<T1, T2, T3, T4, T5, T6, T7, T8, R>)result.ResultValue.ToPointer();
        }


        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<R> LoadFunctionRetCdecl<R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T">Type of first parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T, R> LoadFunctionRetCdecl<T, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, R> LoadFunctionRetCdecl<T1, T2, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, R> LoadFunctionRetCdecl<T1, T2, T3, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, R> LoadFunctionRetCdecl<T1, T2, T3, T4, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, R> LoadFunctionRetCdecl<T1, T2, T3, T4, T5, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, R> LoadFunctionRetCdecl<T1, T2, T3, T4, T5, T6, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, R> LoadFunctionRetCdecl<T1, T2, T3, T4, T5, T6, T7, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, R>)result.ResultValue.ToPointer();
        }

        /// <summary>
        /// Look up the address of the named function in a shared object with cdecl convention.
        /// </summary>
        /// <typeparam name="T1">Type of first parameter.</typeparam>
        /// <typeparam name="T2">Type of second parameter.</typeparam>
        /// <typeparam name="T3">Type of third parameter.</typeparam>
        /// <typeparam name="T4">Type of fourth parameter.</typeparam>
        /// <typeparam name="T5">Type of fifth parameter.</typeparam>
        /// <typeparam name="T6">Type of sixth parameter.</typeparam>
        /// <typeparam name="T7">Type of seventh parameter.</typeparam>
        /// <typeparam name="T8">Type of eighth parameter.</typeparam>
        /// <typeparam name="R">Type of return value.</typeparam>
        /// <param name="obj"></param>
        /// <param name="name">The name of the function to look up.</param>
        /// <returns>A pointer to the function or null if there was an error.</returns>
        public static delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, R> LoadFunctionRetCdecl<T1, T2, T3, T4, T5, T6, T7, T8, R>(this SharedObject obj, string name)
        {
            var result = obj.LoadFunction(name);
            if (result.IsFailure)
                return null;

            return (delegate* unmanaged[Cdecl]<T1, T2, T3, T4, T5, T6, T7, T8, R>)result.ResultValue.ToPointer();
        }
    }
}
