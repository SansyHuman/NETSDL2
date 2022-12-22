using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.IO
{
    /// <summary>
    /// Extensions of <see cref="RWops"/>.
    /// </summary>
    public static class RWopsExt
    {
        /// <summary>
        /// Read from a data source asynchronously.
        /// </summary>
        /// <param name="ptr">A pointer to a buffer to read data into.</param>
        /// <param name="size">The size of each object to read, in bytes.
        /// </param>
        /// <param name="maxnum">The maximum number of objects to be read.
        /// </param>
        /// <returns>The number of objects read, or 0 at error or end of
        /// file.</returns>
        public static Task<ulong> ReadAsync(this RWops obj, IntPtr ptr, ulong size, ulong maxnum)
        {
            return Task<ulong>.Factory.StartNew(() => obj.Read(ptr, size, maxnum));
        }

        /// <summary>
        /// Read from a data source asynchronously.
        /// </summary>
        /// <typeparam name="T">Type of object to read.</typeparam>
        /// <param name="arr">The buffer to read data into.</param>
        /// <param name="offset">The array index offset to start read into.
        /// </param>
        /// <param name="maxnum">The maximum number of objects to be read.
        /// </param>
        /// <returns>The number of objects read, or 0 at error or end of
        /// file.</returns>
        public static Task<ulong> ReadAsync<T>(this RWops obj, T[] arr, ulong offset, ulong maxnum) where T : struct
        {
            return Task<ulong>.Factory.StartNew(() => obj.Read(arr, offset, maxnum));
        }

        /// <summary>
        /// Write to an RWops data stream asynchronously.
        /// </summary>
        /// <param name="ptr">A pointer to a buffer containing data to write.</param>
        /// <param name="size">The size of an object to write, in bytes.</param>
        /// <param name="num">The number of objects to write.</param>
        /// <returns>The number of objects written, which will be less than num
        /// on error.</returns>
        public static Task<ulong> WriteAsync(this RWops obj, IntPtr ptr, ulong size, ulong num)
        {
            return Task<ulong>.Factory.StartNew(() => obj.Write(ptr, size, num));
        }

        /// <summary>
        /// Write to an RWops data stream asynchronously.
        /// </summary>
        /// <typeparam name="T">Type of object to write.</typeparam>
        /// <param name="arr">The buffer that contains data to write.</param>
        /// <param name="offset">The array index offset to start write.</param>
        /// <param name="num">The number of objects to write.</param>
        /// <returns>The number of objects written, which will be less than num
        /// on error.</returns>
        public static Task<ulong> WriteAsync<T>(this RWops obj, T[] arr, ulong offset, ulong num) where T : struct
        {
            return Task<ulong>.Factory.StartNew(() => obj.Write(arr, offset, num));
        }

        /// <summary>
        /// Load all the data from an SDL data stream.
        /// </summary>
        /// <param name="src">The RWops to read all available data from.</param>
        /// <param name="freesrc">If true close the source stream before returning.</param>
        /// <returns>The data and the number of bytes read, or None if there was an error.
        /// The returned data should be freed with 
        /// <see cref="NETSDL2.Systems.Stdinc.Free"/>.</returns>
        public static Result<(IntPtr data, ulong datasize), None> LoadFile(RWops src, bool freesrc)
        {
            return RWops.LoadFile(src, out ulong datasize, freesrc)
                .Map(data => (data, datasize));
        }

        /// <summary>
        /// Load all the data from an SDL data stream asynchronously.
        /// </summary>
        /// <param name="src">The RWops to read all available data from.</param>
        /// <param name="freesrc">If true close the source stream before returning.</param>
        /// <returns>The data and the number of bytes read, or None if there was an error.
        /// The returned data should be freed with 
        /// <see cref="NETSDL2.Systems.Stdinc.Free"/>.</returns>
        public static Task<Result<(IntPtr data, ulong datasize), None>> LoadFileAsync(RWops src, bool freesrc)
        {
            return Task<Result<(IntPtr, ulong), None>>.Factory.StartNew(() => LoadFile(src, freesrc));
        }

        /// <summary>
        /// Load all the data from an SDL data stream asynchronously.
        /// </summary>
        /// <param name="src">The RWops to read all available data from.</param>
        /// <param name="freesrc">If true close the source stream before returning.</param>
        /// <returns>The data array, or None if there was an error.</returns>
        public static Task<Result<byte[], None>> LoadFileToBytesAsync(RWops src, bool freesrc)
        {
            return Task<Result<byte[], None>>.Factory.StartNew(() => RWops.LoadFile(src, freesrc));
        }

        /// <summary>
        /// Load all the data from a file path.
        /// </summary>
        /// <param name="file">The path to read all available data from.</param>
        /// <returns>The data and the number of bytes read, or None if there was an error.
        /// The returned data should be freed with 
        /// <see cref="NETSDL2.Systems.Stdinc.Free"/>.</returns>
        public static Result<(IntPtr data, ulong datasize), None> LoadFile(string file)
        {
            return RWops.LoadFile(file, out ulong datasize)
                .Map(data => (data, datasize));
        }

        /// <summary>
        /// Load all the data from a file path asynchronously.
        /// </summary>
        /// <param name="file">The path to read all available data from.</param>
        /// <returns>The data and the number of bytes read, or None if there was an error.
        /// The returned data should be freed with 
        /// <see cref="NETSDL2.Systems.Stdinc.Free"/>.</returns>
        public static Task<Result<(IntPtr data, ulong datasize), None>> LoadFileAsync(string file)
        {
            return Task<Result<(IntPtr, ulong), None>>.Factory.StartNew(() => LoadFile(file));
        }

        /// <summary>
        /// Load all the data from a file path asynchronously.
        /// </summary>
        /// <param name="file">The path to read all available data from.</param>
        /// <returns>The data array, or None if there was an error.</returns>
        public static Task<Result<byte[], None>> LoadFileToBytesAsync(string file)
        {
            return Task<Result<byte[], None>>.Factory.StartNew(() => RWops.LoadFile(file));
        }
    }
}
