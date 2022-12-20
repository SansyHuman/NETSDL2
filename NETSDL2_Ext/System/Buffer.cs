using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Systems
{
    /// <summary>
    /// Safe wrapper of native heap memory.
    /// </summary>
    public class Buffer : IDisposable
    {
        private IntPtr buffer;
        private ulong size;
        private bool aligned;

        private bool disposedValue;

        /// <summary>
        /// Create a buffer with the byte size.
        /// </summary>
        /// <param name="size">Size of the memory to allocate in bytes.</param>
        /// <param name="aligned">If true, the memory is aligned for SIMD-friendly use.</param>
        /// <exception cref="Exception">Throw on failed creation.</exception>
        public Buffer(ulong size, bool aligned = false)
        {
            var result = aligned ? CPUInfo.SIMDAlloc(size) : Stdinc.Malloc(size);
            if (result.IsFailure)
                throw new Exception(Error.GetError());

            buffer = result.ResultValue;
            this.size = size;
            this.aligned = aligned;
        }

        /// <summary>
        /// Create a buffer with the number of objects.
        /// </summary>
        /// <param name="count">The number of objects.</param>
        /// <param name="size">Size of each object.</param>
        /// <param name="aligned">If true, the memory is aligned for SIMD-friendly use.</param>
        /// <exception cref="Exception">Throw on failed creation.</exception>
        public Buffer(ulong count, ulong size, bool aligned = false)
        {
            var result = aligned ? CPUInfo.SIMDAlloc(count * size) : Stdinc.Calloc(count, size);
            if (result.IsFailure)
                throw new Exception(Error.GetError());

            buffer = result.ResultValue;
            this.size = count * size;
            this.aligned = aligned;
        }

        /// <summary>
        /// Get the pointer to the buffer.
        /// </summary>
        public IntPtr Pointer
        {
            get
            {
                return buffer;
            }
        }

        /// <summary>
        /// Get the byte size of the buffer.
        /// </summary>
        public ulong Size
        {
            get
            {
                return size;
            }
        }

        /// <summary>
        /// Get whether the buffer memory is aligned.
        /// </summary>
        public bool Aligned
        {
            get
            {
                return aligned;
            }
        }

        internal bool Disposed
        {
            get
            {
                return disposedValue;
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    
                }

                if (aligned)
                    CPUInfo.SIMDFree(buffer);
                else
                    Stdinc.Free(buffer);

                buffer = IntPtr.Zero;
                disposedValue = true;
            }
        }

        ~Buffer()
        {
            // 이 코드를 변경하지 마세요. 'Dispose(bool disposing)' 메서드에 정리 코드를 입력합니다.
            Dispose(disposing: false);
        }

        public void Dispose()
        {
            // 이 코드를 변경하지 마세요. 'Dispose(bool disposing)' 메서드에 정리 코드를 입력합니다.
            Dispose(disposing: true);
            GC.SuppressFinalize(this);
        }

        /// <summary>
        /// Resize the buffer
        /// </summary>
        /// <param name="size">The new size of the buffer.</param>
        /// <returns>Success or Failure.</returns>
        public Result<None, None> ResizeBuffer(ulong size)
        {
            var result = aligned ? CPUInfo.SIMDRealloc(buffer, size) : Stdinc.Realloc(buffer, size);
            if (result.IsFailure)
                return Result<None, None>.MakeFailure(None.Value);

            buffer = result.ResultValue;
            this.size = size;
            return None.Value;
        }

        /// <summary>
        /// Resize the buffer
        /// </summary>
        /// <param name="count">The number of objects.</param>
        /// <param name="size">Size of each object.</param>
        /// <returns>Success or Failure.</returns>
        public Result<None, None> ResizeBuffer(ulong count, ulong size)
        {
            var result = aligned ? CPUInfo.SIMDRealloc(buffer, count * size) : Stdinc.Realloc(buffer, count * size);
            if (result.IsFailure)
                return Result<None, None>.MakeFailure(None.Value);

            buffer = result.ResultValue;
            this.size = count * size;
            return None.Value;
        }

        /// <summary>
        /// Get the object at the index.
        /// </summary>
        /// <typeparam name="T">The type of the object.</typeparam>
        /// <param name="index">Index of the object.</param>
        /// <returns>Object at the index or None on out of range.</returns>
        public unsafe Result<T, None> Get<T>(ulong index) where T : unmanaged
        {
            if (buffer == IntPtr.Zero)
                return Result<T, None>.MakeFailure(None.Value);

            int size = sizeof(T);
            if ((ulong)size * (index + 1) > this.size)
                return Result<T, None>.MakeFailure(None.Value);

            return ((T*)buffer.ToPointer())[index];
        }

        /// <summary>
        /// Set the object at the index.
        /// </summary>
        /// <typeparam name="T">The type of the object.</typeparam>
        /// <param name="index">Index to set.</param>
        /// <param name="value">Value of the object to set.</param>
        /// <returns>Previous object value at index or None on out of range.</returns>
        public unsafe Result<T, None> Set<T>(ulong index, in T value) where T : unmanaged
        {
            if (buffer == IntPtr.Zero)
                return Result<T, None>.MakeFailure(None.Value);

            int size = sizeof(T);
            if ((ulong)size * (index + 1) > this.size)
                return Result<T, None>.MakeFailure(None.Value);

            T* buff = (T*)buffer.ToPointer();
            T prev = buff[index];
            buff[index] = value;
            return prev;
        }

        /// <summary>
        /// Create new buffer view.
        /// </summary>
        /// <typeparam name="T">Type of the buffer view.</typeparam>
        /// <returns>New buffer view.</returns>
        public BufferView<T> CreateBufferView<T>() where T : unmanaged
        {
            return new BufferView<T>(this);
        }
    }
}
