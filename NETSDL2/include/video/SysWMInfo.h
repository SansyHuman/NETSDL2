#pragma once

#include <SDL.h>
#include "SDL_syswm.h"
#include "../core/SDLVersion.h"

using namespace System::Runtime::InteropServices;
using namespace NETSDL2::Core;

namespace NETSDL2
{
	namespace Video
	{
		/// <summary>
		/// An enumeration of the various supported windowing subsystems.
		/// </summary>
		public enum class SysWMType
		{
            Unknown = SDL_SYSWM_UNKNOWN,

            /// <summary>
            /// Microsoft Windows.
            /// </summary>
            Windows = SDL_SYSWM_WINDOWS,

            /// <summary>
            /// X Window System.
            /// </summary>
            X11 = SDL_SYSWM_X11,

            /// <summary>
            /// DirectFB.
            /// </summary>
            DirectFB = SDL_SYSWM_DIRECTFB,

            /// <summary>
            /// Apple Mac OS X.
            /// </summary>
            Cocoa = SDL_SYSWM_COCOA,

            /// <summary>
            /// Apple iOS.
            /// </summary>
            UIKit = SDL_SYSWM_UIKIT,

            /// <summary>
            /// Wayland.
            /// </summary>
            Wayland = SDL_SYSWM_WAYLAND,

            /// <summary>
            /// WinRT.
            /// </summary>
            WinRT = SDL_SYSWM_WINRT,

            /// <summary>
            /// Android.
            /// </summary>
            Android = SDL_SYSWM_ANDROID,

            /// <summary>
            /// Vivante.
            /// </summary>
            Vivante = SDL_SYSWM_VIVANTE,

            /// <summary>
            /// OS/2
            /// </summary>
            OS2 = SDL_SYSWM_OS2,

            /// <summary>
            /// Haiku
            /// </summary>
            Haiku = SDL_SYSWM_HAIKU,

            /// <summary>
            /// KMS/DRM
            /// </summary>
            KMSDRM = SDL_SYSWM_KMSDRM,

            /// <summary>
            /// RiscOS
            /// </summary>
            RiscOS = SDL_SYSWM_RISCOS
		};

        [StructLayout(LayoutKind::Explicit, Size = 72)]
		/// <summary>
		/// A structure that contains system-dependent information about a window.
		/// </summary>
		public value struct SysWMInfo
		{
            [FieldOffset(0)]
            /// <summary>
            /// The current SDL version.
            /// </summary>
            SDLVersion Version;

            [FieldOffset(4)]
            /// <summary>
            /// The windowing system type
            /// </summary>
            SysWMType Subsystem;

            [StructLayout(LayoutKind::Sequential)]
            value struct Windows
            {
                /// <summary>
                /// The window handle.
                /// </summary>
                System::IntPtr Window;

                /// <summary>
                /// The window device context.
                /// </summary>
                System::IntPtr HDC;

                /// <summary>
                /// The window hinstance.
                /// </summary>
                System::IntPtr HInstance;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of Microsoft Windows system.
            /// </summary>
            Windows Win;

            [StructLayout(LayoutKind::Sequential)]
            value struct WindowsRT
            {
                /// <summary>
                /// The WinRT CoreWindow.
                /// </summary>
                System::IntPtr Window;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of WinRT.
            /// </summary>
            WindowsRT WinRT;

            [StructLayout(LayoutKind::Sequential)]
            value struct X11Window
            {
                /// <summary>
                /// The X11 display.
                /// </summary>
                System::IntPtr Display;

                /// <summary>
                /// The X11 window.
                /// </summary>
                System::IntPtr Window;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of X11.
            /// </summary>
            X11Window X11;

            [StructLayout(LayoutKind::Sequential)]
            value struct DirectFB
            {
                /// <summary>
                /// The directfb main interface.
                /// </summary>
                System::IntPtr DFB;

                /// <summary>
                /// The directfb window handle.
                /// </summary>
                System::IntPtr Window;

                /// <summary>
                /// The directfb client surface.
                /// </summary>
                System::IntPtr Surface;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of DirectFB.
            /// </summary>
            DirectFB DFB;

            [StructLayout(LayoutKind::Sequential)]
            value struct Cocoa_
            {
                /// <summary>
                /// The Cocoa window.
                /// </summary>
                System::IntPtr Window;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of Cocoa.
            /// </summary>
            Cocoa_ Cocoa;

            [StructLayout(LayoutKind::Sequential)]
            value struct UIKit_
            {
                /// <summary>
                /// The UIKit window.
                /// </summary>
                System::IntPtr Window;

                /// <summary>
                /// The GL view's Framebuffer Object; it must be bound when rendering to the screen using
                /// GL.
                /// </summary>
                Uint32 Framebuffer;

                /// <summary>
                /// The GL view's color Renderbuffer Object. It must be bound when SDL_GL_SwapWindow is
                /// called.
                /// </summary>
                Uint32 ColorBuffer;

                /// <summary>
                /// The Framebuffer Object which holds the resolve color Renderbuffer, when MSAA is used.
                /// </summary>
                Uint32 ResolveFramebuffer;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of UIKit.
            /// </summary>
            UIKit_ UIKit;

            [StructLayout(LayoutKind::Sequential)]
            value struct Wayland
            {
                /// <summary>
                /// Wayland display.
                /// </summary>
                System::IntPtr Display;

                /// <summary>
                /// Wayland surface.
                /// </summary>
                System::IntPtr Surface;

                /// <summary>
                /// Wayland shell_surface.
                /// </summary>
                System::IntPtr ShellSurface;

                /// <summary>
                /// Wayland EGL window.
                /// </summary>
                System::IntPtr EGLWindow;

                /// <summary>
                /// Wayland xdg surface.
                /// </summary>
                System::IntPtr XDGSurface;

                /// <summary>
                /// Wayland xdg toplevel role.
                /// </summary>
                System::IntPtr XDGTopLevel;

                /// <summary>
                /// Wayland xdg popup role.
                /// </summary>
                System::IntPtr XDGPopup;

                /// <summary>
                /// Wayland xdg positioner, for popup.
                /// </summary>
                System::IntPtr XDGPositioner;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of Wayland.
            /// </summary>
            Wayland WL;

            [StructLayout(LayoutKind::Sequential)]
            value struct Android_
            {
                /// <summary>
                /// The Android native window.
                /// </summary>
                System::IntPtr Window;

                /// <summary>
                /// The Android EGL surface.
                /// </summary>
                System::IntPtr Surface;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of Android.
            /// </summary>
            Android_ Android;

            [StructLayout(LayoutKind::Sequential)]
            value struct OS2_
            {
                /// <summary>
                /// The window handle.
                /// </summary>
                System::IntPtr Hwnd;

                /// <summary>
                /// The frame window handle.
                /// </summary>
                System::IntPtr HwndFrame;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of OS2.
            /// </summary>
            OS2_ OS2;

            [StructLayout(LayoutKind::Sequential)]
            value struct Vivante_
            {
                /// <summary>
                /// The Vivante EGL display type.
                /// </summary>
                System::IntPtr Display;

                /// <summary>
                /// The Vivante EGL window type.
                /// </summary>
                System::IntPtr Window;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of OS2.
            /// </summary>
            Vivante_ Vivante;

            [StructLayout(LayoutKind::Sequential)]
            value struct KMSDRM_
            {
                /// <summary>
                /// Device index.
                /// </summary>
                int DevIndex;

                /// <summary>
                /// DRM FD.
                /// </summary>
                int DRMFD;

                /// <summary>
                /// GBM device
                /// </summary>
                System::IntPtr GBMDev;
            };
            [FieldOffset(8)]
            /// <summary>
            /// Informations of OS2.
            /// </summary>
            KMSDRM_ KMSDRM;
		};
	}
}