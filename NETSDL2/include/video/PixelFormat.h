#pragma once

#include <SDL.h>

#include "Palette.h"

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Video
	{
        /// <summary>
        /// An enumeration of pixel formats.
        /// </summary>
        public enum class PixelFormatEnum : Uint32
		{
			Unknown = SDL_PIXELFORMAT_UNKNOWN,
            Index1LSB = SDL_PIXELFORMAT_INDEX1LSB,
            Index1MSB = SDL_PIXELFORMAT_INDEX1MSB,
            Index4LSB = SDL_PIXELFORMAT_INDEX4LSB,
            Index4MSB = SDL_PIXELFORMAT_INDEX4MSB,
            Index8 = SDL_PIXELFORMAT_INDEX8,
            RGB332 = SDL_PIXELFORMAT_RGB332,
            XRGB4444 = SDL_PIXELFORMAT_XRGB4444,
            RGB444 = SDL_PIXELFORMAT_RGB444,
            XBGR4444 = SDL_PIXELFORMAT_XBGR4444,
            BGR444 = SDL_PIXELFORMAT_BGR444,
            XRGB1555 = SDL_PIXELFORMAT_XRGB1555,
            RGB555 = SDL_PIXELFORMAT_RGB555,
            XBGR1555 = SDL_PIXELFORMAT_XBGR1555,
            BGR555 = SDL_PIXELFORMAT_BGR555,
            ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
            RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
            ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
            BGRA4444 = SDL_PIXELFORMAT_BGRA4444,
            ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
            RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
            ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
            BGRA5551 = SDL_PIXELFORMAT_BGRA5551,
            RGB565 = SDL_PIXELFORMAT_RGB565,
            BGR565 = SDL_PIXELFORMAT_BGR565,
            RGB24 = SDL_PIXELFORMAT_RGB24,
            BGR24 = SDL_PIXELFORMAT_BGR24,
            XRGB8888 = SDL_PIXELFORMAT_XRGB8888,
            RGB888 = SDL_PIXELFORMAT_RGB888,
            RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
            XBGR8888 = SDL_PIXELFORMAT_XBGR8888,
            BGR888 = SDL_PIXELFORMAT_BGR888,
            BGRX8888 = SDL_PIXELFORMAT_BGRX8888,
            ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
            RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
            ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
            BGRA8888 = SDL_PIXELFORMAT_BGRA8888,
            ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,
            RGBA32 = SDL_PIXELFORMAT_RGBA32,
            ARGB32 = SDL_PIXELFORMAT_ARGB32,
            BGRA32 = SDL_PIXELFORMAT_BGRA32,
            ABGR32 = SDL_PIXELFORMAT_ABGR32,
            YV12 = SDL_PIXELFORMAT_YV12,
            IYUV = SDL_PIXELFORMAT_IYUV,
            YUY2 = SDL_PIXELFORMAT_YUY2,
            UYVY = SDL_PIXELFORMAT_UYVY,
            YVYU = SDL_PIXELFORMAT_YVYU,
            NV12 = SDL_PIXELFORMAT_NV12,
            NV21 = SDL_PIXELFORMAT_NV21,
            ExternalOES = SDL_PIXELFORMAT_EXTERNAL_OES,
		};

        /// <summary>
        /// Type of the pixel.
        /// </summary>
        public enum class PixelType : Uint32
        {
            Unknown = SDL_PIXELTYPE_UNKNOWN,
            Index1 = SDL_PIXELTYPE_INDEX1,
            Index4 = SDL_PIXELTYPE_INDEX4,
            Index8 = SDL_PIXELTYPE_INDEX8,
            Packed8 = SDL_PIXELTYPE_PACKED8,
            Packed16 = SDL_PIXELTYPE_PACKED16,
            Packed32 = SDL_PIXELTYPE_PACKED32,
            ArrayU8 = SDL_PIXELTYPE_ARRAYU8,
            ArrayU16 = SDL_PIXELTYPE_ARRAYU16,
            ArrayU32 = SDL_PIXELTYPE_ARRAYU32,
            ArrayF16 = SDL_PIXELTYPE_ARRAYF16,
            ArrayF32 = SDL_PIXELTYPE_ARRAYF32,
        };

        /// <summary>
        /// Bitmap pixel order, high bit -> low bit.
        /// </summary>
        public enum class BitmapOrder : Uint32
        {
            None = SDL_BITMAPORDER_NONE,
            Ord4321 = SDL_BITMAPORDER_4321,
            Ord1234 = SDL_BITMAPORDER_1234
        };

        /// <summary>
        /// Packed component order, high bit -> low bit.
        /// </summary>
        public enum class PackedOrder : Uint32
        {
            None = SDL_PACKEDORDER_NONE,
            XRGB = SDL_PACKEDORDER_XRGB,
            RGBX = SDL_PACKEDORDER_RGBX,
            ARGB = SDL_PACKEDORDER_ARGB,
            RGBA = SDL_PACKEDORDER_RGBA,
            XBGR = SDL_PACKEDORDER_XBGR,
            BGRX = SDL_PACKEDORDER_BGRX,
            ABGR = SDL_PACKEDORDER_ABGR,
            BGRA = SDL_PACKEDORDER_BGRA,
        };

        /// <summary>
        /// Array component order, low byte -> high byte.
        /// </summary>
        public enum class ArrayOrder : Uint32
        {
            None = SDL_ARRAYORDER_NONE,
            RGB = SDL_ARRAYORDER_RGB,
            RGBA = SDL_ARRAYORDER_RGBA,
            ARGB = SDL_ARRAYORDER_ARGB,
            BGR = SDL_ARRAYORDER_BGR,
            BGRA = SDL_ARRAYORDER_BGRA,
            ABGR = SDL_ARRAYORDER_ABGR,
        };

        /// <summary>
        /// Packed component layout.
        /// </summary>
        public enum class PackedLayout : Uint32
        {
            None = SDL_PACKEDLAYOUT_NONE,
            Layout332 = SDL_PACKEDLAYOUT_332,
            Layout4444 = SDL_PACKEDLAYOUT_4444,
            Layout1555 = SDL_PACKEDLAYOUT_1555,
            Layout5551 = SDL_PACKEDLAYOUT_5551,
            Layout565 = SDL_PACKEDLAYOUT_565,
            Layout8888 = SDL_PACKEDLAYOUT_8888,
            Layout2101010 = SDL_PACKEDLAYOUT_2101010,
            Layout1010102 = SDL_PACKEDLAYOUT_1010102,
        };

        /// <summary>
        /// A structure that contains pixel format information.
        /// </summary>
        [StructLayout(LayoutKind::Sequential)]
        public value struct PixelFormat
        {
        private:
            PixelFormatEnum format;
            Palette* palette;
            Uint8 bitsPerPixel;
            Uint8 bytesPerPixel;
            Uint8 padding1;
            Uint8 padding2;
            Uint32 rmask;
            Uint32 gmask;
            Uint32 bmask;
            Uint32 amask;
            Uint8 rloss;
            Uint8 gloss;
            Uint8 bloss;
            Uint8 aloss;
            Uint8 rshift;
            Uint8 gshift;
            Uint8 bshift;
            Uint8 ashift;
            int refcount;
            PixelFormat* next;

        public:
            /// <summary>
            /// One of the <see cref="PixelFormatEnum"/> values.
            /// </summary>
            property PixelFormatEnum Format
            {
                PixelFormatEnum get();
            }

            /// <summary>
            /// An <see cref="Palette"/> structure associated with this pixel
            /// format, or null if the format doesn't have a palette
            /// </summary>
            property NETSDL2::Video::Palette* Palette
            {
                NETSDL2::Video::Palette* get();
            }

            /// <summary>
            /// The number of significant bits in a pixel value.
            /// </summary>
            property Uint8 BitsPerPixel
            {
                Uint8 get();
            }

            /// <summary>
            /// The number of bytes required to hold a pixel value.
            /// </summary>
            property Uint8 BytesPerPixel
            {
                Uint8 get();
            }

            /// <summary>
            /// A mask representing the location of the red component of the
            /// pixel.
            /// </summary>
            property Uint32 Rmask
            {
                Uint32 get();
            }

            /// <summary>
            /// A mask representing the location of the green component of
            /// the pixel.
            /// </summary>
            property Uint32 Gmask
            {
                Uint32 get();
            }

            /// <summary>
            /// A mask representing the location of the blue component of
            /// the pixel.
            /// </summary>
            property Uint32 Bmask
            {
                Uint32 get();
            }

            /// <summary>
            /// A mask representing the location of the alpha component of the
            /// pixel or 0 if the pixel format doesn't have any alpha
            /// information.
            /// </summary>
            property Uint32 Amask
            {
                Uint32 get();
            }

            property Uint8 Rloss
            {
                Uint8 get();
            }

            property Uint8 Gloss
            {
                Uint8 get();
            }

            property Uint8 Bloss
            {
                Uint8 get();
            }

            property Uint8 Aloss
            {
                Uint8 get();
            }

            property Uint8 Rshift
            {
                Uint8 get();
            }

            property Uint8 Gshift
            {
                Uint8 get();
            }

            property Uint8 Bshift
            {
                Uint8 get();
            }

            property Uint8 Ashift
            {
                Uint8 get();
            }
        };

        /// <summary>
        /// Functions to obtain information of pixel format.
        /// </summary>
        public ref struct PixelFormatInfo abstract sealed
        {
        public:
            /// <summary>
            /// Get the type of the pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>Type of the pixel format.</returns>
            static PixelType GetPixelType(PixelFormatEnum format);

            /// <summary>
            /// Get the bitmap pixel ordering of channels or bits in the
            /// pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>Bitmap order of pixel format.</returns>
            static BitmapOrder GetBitmapOrder(PixelFormatEnum format);

            /// <summary>
            /// Get the packed component ordering of channels or bits in the
            /// pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>Packed order of pixel format.</returns>
            static PackedOrder GetPackedOrder(PixelFormatEnum format);

            /// <summary>
            /// Get the array component ordering of channels or bits in the
            /// pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>Array order of pixel format.</returns>
            static ArrayOrder GetArrayOrder(PixelFormatEnum format);

            /// <summary>
            /// Get the channel bit pattern of the pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>Packed layout of the pixel format.</returns>
            static PackedLayout GetPackedLayout(PixelFormatEnum format);

            /// <summary>
            /// Get the number of bits of color information in the pixel format.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>The number of bits of color information in the pixel
            /// format.</returns>
            static Uint32 GetBitsPerPixel(PixelFormatEnum format);

            /// <summary>
            /// Get the number of bytes used to represent a pixel.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>The number of bytes used to represent a pixel.</returns>
            static Uint32 GetBytesPerPixel(PixelFormatEnum format);

            /// <summary>
            /// Gets whether pixel formats have a palette.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>true for pixel formats that have a palette.</returns>
            static bool IsPixelFormatIndexed(PixelFormatEnum format);

            /// <summary>
            /// Gets whether pixel formats have an alpha channel.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>true for pixel formats that have an alpha channel.
            /// </returns>
            static bool IsPixelFormatAlpha(PixelFormatEnum format);

            /// <summary>
            /// Gets whether pixel formats is representing unique formats, for
            /// example YUV formats.
            /// </summary>
            /// <param name="format">Pixel format.</param>
            /// <returns>true for pixel formats representing unique formats,
            /// for example YUV formats.
            /// </returns>
            static bool IsPixelFormatFourCC(PixelFormatEnum format);
        };
	}
}