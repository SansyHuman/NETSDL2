using NETSDL2.Core;
using NETSDL2.Video;

using System.Diagnostics;
using System.Runtime.InteropServices;

Hint.ClearHints();

Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHint(SDLHint.H_RENDER_SCALE_QUALITY, "linear"));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHintWithPriority(SDLHint.H_RENDER_SCALE_QUALITY, "best", HintPriority.Default));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHintWithPriority(SDLHint.H_RENDER_SCALE_QUALITY, "best", HintPriority.Override));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));

var result = SDL.Init(SubSystems.Video);
if(result.ResultType == Result<None, int>.Type.Failed)
{
    Console.WriteLine("Failed to initialize SDL.");
    return;
}

result = Video.Init(null);
Console.WriteLine("Video init: {0}", result);

Error.SetError("호무호무");
string errorMessage = Error.GetError();
Logging.LogInfo(LogCategory.Application, "Hello, {0}!", Error.GetError());

Logging.LogInfo(LogCategory.Application, "Hello, {0}!", "Subo");

Logging.SetOutputFunction((IntPtr userData, LogCategory category, LogPriority priority, string message) =>
{
    Debug.Assert(userData == new IntPtr(10000));

    Console.WriteLine("[{0}] ({1}): {2}", priority, category, message);
}, new IntPtr(10000));

Logging.LogWarn(LogCategory.Application, "Hello, {0}!", "Subo");

var outputFunc = Logging.GetOutputFunction(out IntPtr userData);
Debug.Assert(userData == new IntPtr(10000));

var revision = NETSDL2.Core.Version.Revision;
var version = NETSDL2.Core.Version.LibraryVersion;

Logging.LogInfo(LogCategory.Application, "SDL version: {0}", version);

Logging.LogInfo(LogCategory.Application, "GL load: {0}", GL.LoadLibrary(null));

Logging.LogInfo(LogCategory.Application, "MajorVersion: {0}", GL.GetAttribute(GLAttr.ContextMajorVersion));
Logging.LogInfo(LogCategory.Application, "MajorVersion: {0}", GL.GetAttribute(GLAttr.ContextMinorVersion));
Logging.LogInfo(LogCategory.Application, "Profile: {0}", GL.GetAttribute(GLAttr.ContextProfileMask));
Logging.LogInfo(LogCategory.Application, "SetAttribute: {0}", GL.SetAttribute(GLAttr.ContextProfileMask, (int)GLProfile.Compatibility));
Logging.LogInfo(LogCategory.Application, "Profile: {0}", GL.GetAttribute(GLAttr.ContextProfileMask));
Logging.LogInfo(LogCategory.Application, "Multisample: {0}", GL.GetAttribute(GLAttr.MultisampleBuffers));
Logging.LogInfo(LogCategory.Application, "SetAttribute: {0}", GL.SetAttribute(GLAttr.MultisampleBuffers, 1));
Logging.LogInfo(LogCategory.Application, "SetAttribute: {0}", GL.SetAttribute(GLAttr.MultisampleSamples, 4));
Logging.LogInfo(LogCategory.Application, "SetAttribute: {0}", GL.SetAttribute(GLAttr.ContextFlags, (int)GLContextFlags.Debug));

var window = new Window("Hello", Window.WINDOWPOS_UNDEFINED, Window.WINDOWPOS_UNDEFINED, 800, 600, WindowFlags.AllowHighDPI | WindowFlags.OpenGL | WindowFlags.Resizable);
window.OnHidden += (Window window, uint timestamp) =>
{
    Logging.LogInfo(LogCategory.Application, "Window hidden on {0}", timestamp);
};
window.OnMoved += (Window window, uint timestamp, int x, int y) =>
{
    Logging.LogInfo(LogCategory.Application, "Main window moved on {0} to {1}, {2}", timestamp, x, y);
};

window.SetWindowHitTest((Window window, Point point, IntPtr data) =>
{
    window.GetWindowSize(out int w, out int h);
    if (point.X > w / 2)
        return HitTestResult.Draggable;

    return HitTestResult.Normal;
}, new IntPtr(50000));

MessageBoxColorScheme scheme = new MessageBoxColorScheme();
scheme[MessageBoxColorType.Text] = new MessageBoxColor(0, 0, 35);
scheme[MessageBoxColorType.Background] = new MessageBoxColor(230, 230, 230);
scheme[MessageBoxColorType.ButtonBackground] = new MessageBoxColor(255, 232, 0);
scheme[MessageBoxColorType.ButtonBorder] = new MessageBoxColor(255, 255, 255);
scheme[MessageBoxColorType.ButtonSelected] = new MessageBoxColor(0, 23, 255);

var messageBoxResult = Window.ShowMessageBox(
    new MessageBoxData()
    {
        Flags = MessageBoxFlags.Information,
        Window = null,
        Title = "Warning",
        Message = "This is test.",
        Buttons = new MessageBoxButtonData[]
        {
            new MessageBoxButtonData()
            {
                Flags = MessageBoxButtonFlags.None,
                ButtonID = 0,
                Text = "네"
            },
            new MessageBoxButtonData()
            {
                Flags = MessageBoxButtonFlags.ReturnkeyDefault,
                ButtonID = 1,
                Text = "아니오"
            }
        },
        ColorScheme = scheme
    });

Logging.LogInfo(LogCategory.Application, "Pressed button: {0}", messageBoxResult);

var simpleBoxResult = Window.ShowSimpleMessageBox(MessageBoxFlags.Error, "에러", "테스트용", window);
Logging.LogInfo(LogCategory.Application, "Simple message box: {0}", simpleBoxResult);

_ = window.GetWindowBordersSize(out int top, out int left, out int bottom, out int right);
Logging.LogInfo(LogCategory.Application, "Window border: {0}, {1}, {2}, {3}", top, left, bottom, right);
Logging.LogInfo(LogCategory.Application, "Window display mode: {0}", window.GetWindowDisplayMode());
ushort[] redGamma = new ushort[256];
ushort[] greenGamma = new ushort[256];
ushort[] blueGamma = new ushort[256];
_ = window.GetWindowGammaRamp(redGamma, null, blueGamma);
for(int i = 0; i < 256; i++)
{
    redGamma[i] = (ushort)((float)redGamma[i] / 2.0f);
}
window.SetWindowGammaRamp(redGamma, null, blueGamma);
var windowByID = Window.GetWindowFromID(window.ID).ResultValue;
window.GetWindowMaximumSize(out int w, out int h);
Logging.LogInfo(LogCategory.Application, "Window max size: {0}, {1}", w, h);
window.GetWindowMinimumSize(out w, out h);
Logging.LogInfo(LogCategory.Application, "Window min size: {0}, {1}", w, h);
window.SetWindowMaximumSize(1920, 1080);
window.SetWindowMinimumSize(300, 300);
window.GetWindowMaximumSize(out w, out h);
Logging.LogInfo(LogCategory.Application, "Window max size: {0}, {1}", w, h);
window.GetWindowMinimumSize(out w, out h);
Logging.LogInfo(LogCategory.Application, "Window min size: {0}, {1}", w, h);
Logging.LogInfo(LogCategory.Application, "Window opacity: {0}", window.GetWindowOpacity());
window.GetWindowPosition(out int x, out int y);
Logging.LogInfo(LogCategory.Application, "Window position: {0}, {1}", x, y);
window.GetWindowSize(out w, out h);
Logging.LogInfo(LogCategory.Application, "Window size: {0}, {1}", w, h);
GL.GetDrawableSize(window, out w, out h);
Logging.LogInfo(LogCategory.Application, "Window drawable size: {0}, {1}", w, h);
Logging.LogInfo(LogCategory.Application, "현재 GL window: {0}", GL.GetCurrentWindow());
window.Title = "안녕 world!";

SysWMInfo info = new SysWMInfo();
info.Version = NETSDL2.Core.Version.CompiledVersion;

bool sysInfoAcquired = window.GetWindowWMInfo(ref info);
if (!sysInfoAcquired)
{
    Logging.LogInfo(LogCategory.Application, Error.GetError());
}

var context = GL.CreateContext(window);
Logging.LogInfo(LogCategory.Application, "GLContext: {0}", context);
Logging.LogInfo(LogCategory.Application, "Current GL window: {0}", GL.GetCurrentWindow());

Logging.LogInfo(LogCategory.Application, "Multisample: {0}", GL.GetAttribute(GLAttr.MultisampleBuffers));
Logging.LogInfo(LogCategory.Application, "Multisample: {0}", GL.GetAttribute(GLAttr.MultisampleSamples));

Logging.LogInfo(LogCategory.Application, "GL_EXT_framebuffer_blit: {0}", GL.ExtensionSupported("GL_EXT_framebuffer_blit"));
Logging.LogInfo(LogCategory.Application, "Current context: {0}", GL.GetCurrentContext());

unsafe
{
    delegate* unmanaged[Stdcall]<uint, void> glActiveTextureARB_ptr = null;
    glActiveTextureARB_ptr = (delegate* unmanaged[Stdcall]<uint, void>)GL.GetProcAddress("glActiveTextureARB").ToPointer();
    Logging.LogInfo(LogCategory.Application, "glActiveTextureARB: 0x{0:x}", (int)glActiveTextureARB_ptr);
}

Logging.LogInfo(LogCategory.Application, "Swap interval: {0}", GL.GetSwapInterval());
Logging.LogInfo(LogCategory.Application, "Set swap interval: {0}", GL.SetSwapInterval(-1));
Logging.LogInfo(LogCategory.Application, "Swap interval: {0}", GL.GetSwapInterval());
Logging.LogInfo(LogCategory.Application, "Make current: {0}", GL.MakeCurrent(window, context.ResultValue));

GL.SwapWindow(window);

if (context.IsSuccess)
    GLContext.DeleteContext(context.ResultValue);

Logging.LogInfo(LogCategory.Application, "Flash window: {0}", window.FlashWindow(FlashOperation.Briefly));
window.RaiseWindow();
window.MinimizeWindow();
window.MaximizeWindow();
window.RestoreWindow();
window.SetWindowBordered(false);
window.SetWindowBordered(true);
var brightResult = window.SetWindowBrightness(0.5f);
errorMessage = Error.GetError();
brightResult = window.SetWindowBrightness(1.0f);

IntPtr prev = window.SetWindowData("안녕", new IntPtr(5000));
prev = window.SetWindowData("안녕", new IntPtr(10000));
prev = window.SetWindowData("Aver", new IntPtr(20000));
prev = window.GetWindowData("안녕");
prev = window.GetWindowData("Aver");
prev = window.GetWindowData("erer");

window.SetWindowDisplayMode(Display.GetDisplayModes(0)[Display.GetNumDisplayModes(0) - 1]);
window.SetWindowFullscreen(WindowFlags.FullscreenDesktop);
window.SetWindowFullscreen(WindowFlags.None);

window.IsGrabbed = true;
window.IsGrabbed = false;

Logging.LogInfo(LogCategory.Application, "InputFocus: {0}", window.SetWindowInputFocus());
Logging.LogInfo(LogCategory.Application, "InputFocus: {0}", Error.GetError());

Window modal = new Window("Modal", Window.WINDOWPOS_CENTERED, Window.WINDOWPOS_CENTERED, 500, 300, WindowFlags.None);
modal.SetWindowResizable(true);
modal.OnMoved += (Window window, uint timestamp, int x, int y) =>
{
    Logging.LogInfo(LogCategory.Application, "Modal window moved on {0} to {1}, {2}", timestamp, x, y);
};
Logging.LogInfo(LogCategory.Application, "Modal: {0}", modal.SetWindowModalFor(window));
Logging.LogInfo(LogCategory.Application, "Modal: {0}", Error.GetError());

Window.ShowMessageBox(
    new MessageBoxData()
    {
        Flags = MessageBoxFlags.Information,
        Window = null,
        Title = "Warning",
        Message = "This is test.",
        Buttons = new MessageBoxButtonData[]
        {
            new MessageBoxButtonData()
            {
                Flags = MessageBoxButtonFlags.None,
                ButtonID = 0,
                Text = "네"
            },
            new MessageBoxButtonData()
            {
                Flags = MessageBoxButtonFlags.ReturnkeyDefault,
                ButtonID = 1,
                Text = "아니오"
            }
        },
        ColorScheme = scheme
    });

Logging.LogInfo(LogCategory.Application, "Opacity: {0}", window.SetWindowOpacity(0.5f));

window.SetWindowPosition(100, 100);

window.SetWindowResizable(true);
window.SetWindowResizable(false);
window.SetWindowSize(500, 500);

window.HideWindow();
window.ShowWindow();

window.Dispose();
modal.Dispose();

DisplayMode desired = new DisplayMode()
{
    Format = PixelFormatEnum.Unknown,
    W = 1920,
    H = 1080,
    RefreshRate = 60
};
Result<DisplayMode, None> displayMode = Display.GetClosestDisplayMode(1, desired);
Logging.LogInfo(LogCategory.Application, "{0}", displayMode);

Result<DisplayMode, int> currentMode = Display.GetCurrentDisplayMode(0);
Logging.LogInfo(LogCategory.Application, "{0}", currentMode);

currentMode = Display.GetDesktopDisplayMode(0);
Logging.LogInfo(LogCategory.Application, "{0}", currentMode);

PixelFormatEnum currentModeValue = currentMode.ResultValue.Format;
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetPixelType(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetBitsPerPixel(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetBytesPerPixel(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetPackedLayout(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetPackedOrder(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetArrayOrder(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.GetBitmapOrder(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.IsPixelFormatFourCC(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.IsPixelFormatAlpha(currentModeValue));
Logging.LogInfo(LogCategory.Application, "{0}", PixelFormatInfo.IsPixelFormatIndexed(currentModeValue));

Logging.LogInfo(LogCategory.Application, "Video driver: {0}", Display.GetCurrentVideoDriver());
Logging.LogInfo(LogCategory.Application, "Display bounds: {0}", Display.GetDisplayBounds(0));
_ = Display.GetDisplayDPI(0, out float ddpi, out float hdpi, out float vdpi);
Logging.LogInfo(LogCategory.Application, "DPI: {0}, {1}, {2}", ddpi, hdpi, vdpi);

Logging.LogInfo(LogCategory.Application, "{0}", Display.GetDisplayMode(0, 0));
var availableModes = Display.GetDisplayModes(0);
foreach(var mode in availableModes)
{
    Logging.LogInfo(LogCategory.Application, "{0}", mode);
}
Logging.LogInfo(LogCategory.Application, "{0}", Display.GetDisplayName(0));
Logging.LogInfo(LogCategory.Application, "Display usable bounds: {0}", Display.GetDisplayUsableBounds(0));
Logging.LogInfo(LogCategory.Application, "Grabbed window: {0}", Window.GrabbedWindow);
Logging.LogInfo(LogCategory.Application, "Number of display modes: {0}", Display.GetNumDisplayModes(0));
Logging.LogInfo(LogCategory.Application, "Number of displays: {0}", Display.NumVideoDisplays);
Logging.LogInfo(LogCategory.Application, "Number of drivers: {0}", Display.NumVideoDrivers);
Logging.LogInfo(LogCategory.Application, "Driver: {0}", Display.GetVideoDriver(0));
Logging.LogInfo(LogCategory.Application, "Driver: {0}", Display.GetVideoDriver(1));
Logging.LogInfo(LogCategory.Application, "Screen saver: {0}", Display.IsScreenSaverEnabled);
Display.EnableScreenSaver();
Logging.LogInfo(LogCategory.Application, "Screen saver: {0}", Display.IsScreenSaverEnabled);
Display.DisableScreenSaver();
Logging.LogInfo(LogCategory.Application, "Screen saver: {0}", Display.IsScreenSaverEnabled);
unsafe
{
    PixelFormat* format = Pixels.AllocFormat(PixelFormatEnum.RGBA8888);
    Palette* palette = Pixels.AllocPalette(3);

    Logging.LogInfo(LogCategory.Application, "Set palete color: {0}", Pixels.SetPaletteColors(palette, 1, new Color(100, 20, 20, 50)));
    Logging.LogInfo(LogCategory.Application, "{0}", (*palette)[1]);

    Logging.LogInfo(LogCategory.Application, "Set pixel palette: {0}", Pixels.SetPixelFormatPalette(format, palette));
    Logging.LogInfo(LogCategory.Application, "{0}", Error.GetError());
}

Video.Quit();
SDL.Quit();
