using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace NETSDL2.Video
{

    /// <summary>
    /// Safe wrapper of <see cref="NETSDL2.Video.Palette"/> pointer.
    /// </summary>
    public unsafe class PaletteWrapper : IDisposable
    {
        private Palette* palette;
        private bool disposedValue;

        public PaletteWrapper(Palette* palette)
        {
            this.palette = palette;
        }

        /// <summary>
        /// Get the native pallete.
        /// </summary>
        public Palette* Palette
        {
            get
            {
                return palette;
            }
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!disposedValue)
            {
                if (disposing)
                {

                }

                Pixels.FreePalette(palette);
                palette = null;
                disposedValue = true;
            }
        }

        ~PaletteWrapper()
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

        public static implicit operator Palette*(PaletteWrapper wrapper)
        {
            return wrapper.palette;
        }
    }
}
