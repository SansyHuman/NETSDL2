using NETSDL2.Core;

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Systems
{
    /// <summary>
    /// View of the buffer.
    /// </summary>
    /// <typeparam name="T">Element of the buffer.</typeparam>
    public struct BufferView<T> where T : unmanaged
    {
        internal Buffer inner;
        internal int elementSize;

        internal unsafe BufferView(Buffer inner)
        {
            this.inner = inner;
            elementSize = sizeof(T);
        }

        /// <summary>
        /// Get whether the buffer that the view points is valid.
        /// </summary>
        public bool Valid
        {
            get
            {
                return !inner.Disposed;
            }
        }

        /// <summary>
        /// Get the native pointer to the buffer that the view points.
        /// </summary>
        public IntPtr InnerPointer
        {
            get
            {
                return inner.Pointer;
            }
        }

        /// <summary>
        /// Get the number of elements that the buffer can store.
        /// </summary>
        public ulong Size
        {
            get
            {
                return inner.Size / (ulong)elementSize;
            }
        }

        /// <summary>
        /// Get whether the buffer memory is aligned.
        /// </summary>
        public bool Aligned
        {
            get
            {
                return inner.Aligned;
            }
        }

        /// <summary>
        /// Get the object at the index.
        /// </summary>
        /// <param name="index">Index of the object.</param>
        /// <returns>Object at the index or None on out of range.</returns>
        public Result<T, None> Get(ulong index)
        {
            return inner.Get<T>(index);
        }

        /// <summary>
        /// Set the object at the index.
        /// </summary>
        /// <param name="index">Index to set.</param>
        /// <param name="value">Value of the object to set.</param>
        /// <returns>Previous object value at index or None on out of range.</returns>
        public Result<T, None> Set(ulong index, in T value)
        {
            return inner.Set(index, value);
        }

        /// <summary>
        /// Create new buffer view with other type.
        /// </summary>
        /// <typeparam name="U">New buffer view type.</typeparam>
        /// <returns>New buffer view on the same buffer with this.</returns>
        public BufferView<U> Transform<U>() where U : unmanaged
        {
            return new BufferView<U>(inner);
        }

        public static implicit operator FloatBufferView(in BufferView<T> view)
        {
            return new FloatBufferView(view.inner);
        }

        public static implicit operator IntBufferView(in BufferView<T> view)
        {
            return new IntBufferView(view.inner);
        }
    }

    /// <summary>
    /// Buffer view with float type.
    /// </summary>
    public struct FloatBufferView
    {
        private BufferView<float> innerView;

        internal FloatBufferView(Buffer inner)
        {
            innerView = new BufferView<float>(inner);
        }

        /// <summary>
        /// Get whether the buffer that the view points is valid.
        /// </summary>
        public bool Valid
        {
            get
            {
                return innerView.Valid;
            }
        }

        /// <summary>
        /// Get the native pointer to the buffer that the view points.
        /// </summary>
        public IntPtr InnerPointer
        {
            get
            {
                return innerView.InnerPointer;
            }
        }

        /// <summary>
        /// Get the number of elements that the buffer can store.
        /// </summary>
        public ulong Size
        {
            get
            {
                return innerView.Size;
            }
        }

        /// <summary>
        /// Get whether the buffer memory is aligned.
        /// </summary>
        public bool Aligned
        {
            get
            {
                return innerView.Aligned;
            }
        }

        /// <summary>
        /// Get the object at the index.
        /// </summary>
        /// <param name="index">Index of the object.</param>
        /// <returns>Object at the index or None on out of range.</returns>
        public Result<float, None> Get(ulong index)
        {
            return innerView.Get(index);
        }

        /// <summary>
        /// Set the object at the index.
        /// </summary>
        /// <param name="index">Index to set.</param>
        /// <param name="value">Value of the object to set.</param>
        /// <returns>Previous object value at index or None on out of range.</returns>
        public Result<float, None> Set(ulong index, float value)
        {
            return innerView.Set(index, value);
        }

        public static implicit operator BufferView<float>(in FloatBufferView view)
        {
            return view.innerView;
        }

        public static implicit operator IntBufferView(in FloatBufferView view)
        {
            return view.innerView;
        }
    }

    /// <summary>
    /// Buffer view with int type.
    /// </summary>
    public struct IntBufferView
    {
        private BufferView<int> innerView;

        internal IntBufferView(Buffer inner)
        {
            innerView = new BufferView<int>(inner);
        }


        /// <summary>
        /// Get whether the buffer that the view points is valid.
        /// </summary>
        public bool Valid
        {
            get
            {
                return innerView.Valid;
            }
        }

        /// <summary>
        /// Get the native pointer to the buffer that the view points.
        /// </summary>
        public IntPtr InnerPointer
        {
            get
            {
                return innerView.InnerPointer;
            }
        }

        /// <summary>
        /// Get the number of elements that the buffer can store.
        /// </summary>
        public ulong Size
        {
            get
            {
                return innerView.Size;
            }
        }

        /// <summary>
        /// Get whether the buffer memory is aligned.
        /// </summary>
        public bool Aligned
        {
            get
            {
                return innerView.Aligned;
            }
        }

        /// <summary>
        /// Get the object at the index.
        /// </summary>
        /// <param name="index">Index of the object.</param>
        /// <returns>Object at the index or None on out of range.</returns>
        public Result<int, None> Get(ulong index)
        {
            return innerView.Get(index);
        }

        /// <summary>
        /// Set the object at the index.
        /// </summary>
        /// <param name="index">Index to set.</param>
        /// <param name="value">Value of the object to set.</param>
        /// <returns>Previous object value at index or None on out of range.</returns>
        public Result<int, None> Set(ulong index, int value)
        {
            return innerView.Set(index, value);
        }

        public static implicit operator BufferView<int>(in IntBufferView view)
        {
            return view.innerView;
        }

        public static implicit operator FloatBufferView(in IntBufferView view)
        {
            return view.innerView;
        }
    }

}
