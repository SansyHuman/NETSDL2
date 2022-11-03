#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;
using namespace System::Runtime::CompilerServices;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of OpenGL configuration attributes.
		/// </summary>
		public enum class GLAttr
		{
            /// <summary>
            /// The minimum number of bits for the red channel of the color
            /// buffer; defaults to 3.
            /// </summary>
            RedSize = SDL_GL_RED_SIZE,

            /// <summary>
            /// The minimum number of bits for the green channel of the color
            /// buffer; defaults to 3.
            /// </summary>
            GreenSize = SDL_GL_GREEN_SIZE,

            /// <summary>
            /// The minimum number of bits for the blue channel of the color
            /// buffer; defaults to 2.
            /// </summary>
            BlueSize = SDL_GL_BLUE_SIZE,

            /// <summary>
            /// The minimum number of bits for the alpha channel of the color
            /// buffer; defaults to 0.
            /// </summary>
            AlphaSize = SDL_GL_ALPHA_SIZE,

            /// <summary>
            /// The minimum number of bits for frame buffer size; defaults to 0.
            /// </summary>
            BufferSize = SDL_GL_BUFFER_SIZE,

            /// <summary>
            /// Whether the output is single or double buffered; defaults to
            /// double buffering on.
            /// </summary>
            DoubleBuffer = SDL_GL_DOUBLEBUFFER,

            /// <summary>
            /// The minimum number of bits in the depth buffer; defaults to 16.
            /// </summary>
            DepthSize = SDL_GL_DEPTH_SIZE,

            /// <summary>
            /// The minimum number of bits in the stencil buffer; defaults to 0.
            /// </summary>
            StencilSize = SDL_GL_STENCIL_SIZE,

            /// <summary>
            /// The minimum number of bits for the red channel of th
            /// accumulation buffer; defaults to 0.
            /// </summary>
            AccumRedSize = SDL_GL_ACCUM_RED_SIZE,

            /// <summary>
            /// The minimum number of bits for the green channel of the
            /// accumulation buffer; defaults to 0.
            /// </summary>
            AccumGreenSize = SDL_GL_ACCUM_GREEN_SIZE,

            /// <summary>
            /// The minimum number of bits for the blue channel of the
            /// accumulation buffer; defaults to 0.
            /// </summary>
            AccumBlueSize = SDL_GL_ACCUM_BLUE_SIZE,

            /// <summary>
            /// The minimum number of bits for the alpha channel of the
            /// accumulation buffer; defaults to 0.
            /// </summary>
            AccumAlphaSize = SDL_GL_ACCUM_ALPHA_SIZE,

            /// <summary>
            /// Whether the output is stereo 3D; defaults to off.
            /// </summary>
            Stereo = SDL_GL_STEREO,

            /// <summary>
            /// The number of buffers used for multisample anti-aliasing;
            /// defaults to 0.
            /// </summary>
            MultisampleBuffers = SDL_GL_MULTISAMPLEBUFFERS,

            /// <summary>
            /// The number of samples used around the current pixel used for
            /// multisample anti-aliasing; defaults to 0.
            /// </summary>
            MultisampleSamples = SDL_GL_MULTISAMPLESAMPLES,

            /// <summary>
            /// Set to 1 to require hardware acceleration, set to 0 to force
            /// software rendering; defaults to allow either.
            /// </summary>
            AcceleratedVisual = SDL_GL_ACCELERATED_VISUAL,

            /// <summary>
            /// OpenGL context major version.
            /// </summary>
            ContextMajorVersion = SDL_GL_CONTEXT_MAJOR_VERSION,

            /// <summary>
            /// OpenGL context minor version.
            /// </summary>
            ContextMinorVersion = SDL_GL_CONTEXT_MINOR_VERSION,

            /// <summary>
            /// Some combination of 0 or more of elements of the
            /// GLContextFlag enumeration; defaults to 0.
            /// </summary>
            ContextFlags = SDL_GL_CONTEXT_FLAGS,

            /// <summary>
            /// Type of GL context (Core, Compatibility, ES).
            /// </summary>
            ContextProfileMask = SDL_GL_CONTEXT_PROFILE_MASK,

            /// <summary>
            /// OpenGL context sharing; defaults to 0.
            /// </summary>
            ShareWithCurrentContext = SDL_GL_SHARE_WITH_CURRENT_CONTEXT,

            /// <summary>
            /// Requests sRGB capable visual; defaults to 0.
            /// </summary>
            FramebufferSRGBCapable = SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,

            /// <summary>
            /// Sets context the release behavior; defaults to 1.
            /// </summary>
            ContextReleaseBehavior = SDL_GL_CONTEXT_RELEASE_BEHAVIOR,
            ContextResetNotification = SDL_GL_CONTEXT_RESET_NOTIFICATION,
            ContextNoError = SDL_GL_CONTEXT_NO_ERROR,
            Floatbuffers = SDL_GL_FLOATBUFFERS,
		};

        /// <summary>
        /// An enumeration of OpenGL context configuration flags.
        /// </summary>
        [System::Flags]
        public enum class GLContextFlags : int
        {
            None = 0,

            /// <summary>
            /// This flag maps to GLX_CONTEXT_DEBUG_BIT_ARB in the
            /// GLX_ARB_create_context extension for X11 and
            /// WGL_CONTEXT_DEBUG_BIT_ARB in the WGL_ARB_create_context
            /// extension for Windows. This flag is currently ignored on
            /// other targets that don't support equivalent functionality.
            /// This flag is intended to put the GL into a "debug" mode which
            /// might offer better developer insights, possibly at a loss of
            /// performance (although a given GL implementation may or may not
            /// do anything differently in the presence of this flag).
            /// </summary>
            Debug = SDL_GL_CONTEXT_DEBUG_FLAG,

            /// <summary>
            /// This flag maps to GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB in the
            /// GLX_ARB_create_context extension for X11 and
            /// WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB in the
            /// WGL_ARB_create_context extension for Windows. This flag is
            /// currently ignored on other targets that don't support equivalent
            /// functionality. This flag is intended to put the GL into a
            /// "forward compatible" mode, which means that no deprecated
            /// functionality will be supported, possibly at a gain in
            /// performance, and only applies to GL 3.0 and later contexts.
            /// </summary>
            ForwardCompatible = SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG,

            /// <summary>
            /// This flag maps to GLX_CONTEXT_ROBUST_ACCESS_BIT_ARB in the
            /// GLX_ARB_create_context_robustness extension for X11 and
            /// WGL_CONTEXT_ROBUST_ACCESS_BIT_ARB in the
            /// WGL_ARB_create_context_robustness extension for Windows. This
            /// flag is currently ignored on other targets that don't support
            /// equivalent functionality. This flag is intended to require a GL
            /// context that supports the GL_ARB_robustness extension--a mode
            /// that offers a few APIs that are safer than the usual defaults.
            /// </summary>
            RobustAccess = SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG,

            /// <summary>
            /// This flag maps to GLX_CONTEXT_RESET_ISOLATION_BIT_ARB in the
            /// GLX_ARB_robustness_isolation extension for X11 and
            /// WGL_CONTEXT_RESET_ISOLATION_BIT_ARB in the
            /// WGL_ARB_robustness_isolation extension for Windows. This flag
            /// is currently ignored on other targets that don't support
            /// equivalent functionality. This flag is intended to require the
            /// GL to make promises about what to do in the face of driver or
            /// hardware failure.
            /// </summary>
            ResetIsolation = SDL_GL_CONTEXT_RESET_ISOLATION_FLAG,
        };

        /// <summary>
        /// An enumeration of OpenGL profiles.
        /// </summary>
        [System::Flags]
        public enum class GLProfile
        {
            None = 0,

            /// <summary>
            /// OpenGL core profile - deprecated functions are disabled.
            /// </summary>
            Core = SDL_GL_CONTEXT_PROFILE_CORE,

            /// <summary>
            /// OpenGL compatibility profile - deprecated functions are allowed.
            /// </summary>
            Compatibility = SDL_GL_CONTEXT_PROFILE_COMPATIBILITY,

            /// <summary>
            /// OpenGL ES profile - only a subset of the base OpenGL
            /// functionality is available.
            /// </summary>
            ES = SDL_GL_CONTEXT_PROFILE_ES,
        };
	}
}