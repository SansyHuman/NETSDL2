using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Video
{

	/// <summary>
	/// Safe wrapper of <see cref="NETSDL2.Video.PixelFormat"/> pointer.
	/// </summary>
	public unsafe class PixelFormatWrapper : IDisposable
    {
		private PixelFormat* format;
        private bool disposedValue;

        public PixelFormatWrapper(PixelFormat* format)
        {
			this.format = format;
        }

        /// <summary>
        /// Get the native pixel format.
        /// </summary>
        public PixelFormat* PixelFormat
        {
            get
            {
                return format;
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {
                    
                }

                Pixels.FreeFormat(format);
                format = null;
                disposedValue = true;
            }
        }

        ~PixelFormatWrapper()
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

        public static implicit operator PixelFormat*(PixelFormatWrapper wrapper)
        {
            return wrapper.format;
        }
    }
}
