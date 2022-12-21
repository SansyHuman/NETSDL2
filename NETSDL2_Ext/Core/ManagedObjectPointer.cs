using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Core
{
    /// <summary>
    /// Wrapper of managed (reference type) object to obtain <see cref="IntPtr"/> representation.
    /// </summary>
    /// <typeparam name="T">Type of reference type object.</typeparam>
    public class ManagedObjectPointer<T> : IDisposable where T : class
    {
        private GCHandle objHandle;

        private bool disposedValue;

        /// <summary>
        /// Make managed object pointer.
        /// </summary>
        /// <param name="obj">Object to make pointer.</param>
        public ManagedObjectPointer(T obj)
        {
            objHandle = GCHandle.Alloc(obj, GCHandleType.Normal);
        }

        /// <summary>
        /// Get whether the pointer is valid.
        /// </summary>
        public bool Valid
        {
            get
            {
                return objHandle.IsAllocated;
            }
        }

        /// <summary>
        /// Get the <see cref="IntPtr"/> representation of the object.
        /// </summary>
        /// <returns>Pointer of the object or None if the pointer is not valid.</returns>
        public Result<IntPtr, None> GetPointer()
        {
            if (!Valid)
                return Result<IntPtr, None>.MakeFailure(None.Value);

            return GCHandle.ToIntPtr(objHandle);
        }

        /// <summary>
        /// Get the object from the pointer.
        /// </summary>
        /// <param name="ptr">Pointer of the object.</param>
        /// <returns>Object from the pointer or None if the object is not the type
        /// <typeparamref name="T"/> or the pointer is not valid.</returns>
        public static Result<T, None> GetObject(IntPtr ptr)
        {
            try
            {
                GCHandle handle = GCHandle.FromIntPtr(ptr);
                object? obj = handle.Target;
                if (obj == null)
                    return Result<T, None>.MakeFailure(None.Value);

                if (obj is T tobj)
                {
                    return tobj;
                }

                return Result<T, None>.MakeFailure(None.Value);
            }
            catch(Exception)
            {
                return Result<T, None>.MakeFailure(None.Value);
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    // TODO: 관리형 상태(관리형 개체)를 삭제합니다.
                }

                if (objHandle.IsAllocated)
                    objHandle.Free();

                disposedValue = true;
            }
        }

        // TODO: 비관리형 리소스를 해제하는 코드가 'Dispose(bool disposing)'에 포함된 경우에만 종료자를 재정의합니다.
        ~ManagedObjectPointer()
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
    }
}
