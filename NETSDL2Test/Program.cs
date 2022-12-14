using NETSDL2.Core;
using NETSDL2.Video;
using NETSDL2.Events;
using NETSDL2.IO;
using NETSDL2.Audio;
using NETSDL2.Haptic;
using NETSDL2.Image;

using System.Diagnostics;
using System.Runtime.InteropServices;
using NETSDL2.Systems;
using System.Runtime.CompilerServices;

Hint.ClearHints();

Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHint(SDLHint.H_RENDER_SCALE_QUALITY, "linear"));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHintWithPriority(SDLHint.H_RENDER_SCALE_QUALITY, "best", HintPriority.Default));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));
Console.WriteLine("{0}", Hint.SetHintWithPriority(SDLHint.H_RENDER_SCALE_QUALITY, "best", HintPriority.Override));
Console.WriteLine("{0}", Hint.GetHint(SDLHint.H_RENDER_SCALE_QUALITY));

var result = SDL.Init(SubSystems.Everything);
if(result.ResultType == Result<None, int>.Type.Failed)
{
    Console.WriteLine("Failed to initialize SDL.");
    return;
}

ImageInitFlags imageFlags = Image.Init(ImageInitFlags.Jpg | ImageInitFlags.Png | ImageInitFlags.Webp);
SDLVersion imageLinkedVersion = Image.LinkedVersion;
SDLVersion imageVersion = Image.Version;

MixerInitFlags mixerFlags = Mixer.Init(
    MixerInitFlags.Flac | MixerInitFlags.Mod | MixerInitFlags.Mp3 |
    MixerInitFlags.Ogg | MixerInitFlags.Mid | MixerInitFlags.Opus
    );

SharedObject user32 = new SharedObject("user32.dll");
IntPtr getcursor = user32.LoadFunction("GetCursor");

unsafe
{
    delegate* unmanaged[Stdcall]<void*> GetCursor = (delegate* unmanaged[Stdcall]<void*>)getcursor.ToPointer();
    void* cursorHandle = GetCursor();
}

FunctionPointer<WindowsMessageHook> messageHook = new FunctionPointer<WindowsMessageHook>(
    (userdata, hwnd, msg, wparam, lparam) =>
    {
        Logging.LogInfo(LogCategory.Application, "Message hook {0} {1} {2} {3} {4}", userdata, hwnd, msg, wparam, lparam);
    });
Platform.SetWindowsMessageHook(messageHook, new IntPtr(5421));

IntPtr allocMem = Stdinc.Calloc(128 + 2, 4);
unsafe
{
    int* m = (int*)allocMem.ToPointer();
    m[0] = 128 * 4; // memory byte size
    m[1] = 0; // current pos;
}
RWops memRW = new RWops();
memRW.Type = RWopsType.Memory;
memRW.Data1 = allocMem;

memRW.SizeFn = (RWops op) =>
{
    return 128 * 4;
};
memRW.SeekFn = (RWops context, long offset, SeekFrom whence) =>
{
    unsafe
    {
        int* memory = (int*)context.Data1.ToPointer();
        int byteSize = memory[0];
        int currentPos = memory[1];

        switch (whence)
        {
            case SeekFrom.Set:
                if (offset < 0 || offset >= byteSize)
                    return -1;
                memory[1] = (int)offset;
                return memory[1];
            case SeekFrom.Cur:
                {
                    int newPos = currentPos + (int)offset;
                    if (newPos < 0 || newPos >= byteSize)
                        return -1;
                    memory[1] = newPos;
                    return memory[1];
                }
            case SeekFrom.End:
                {
                    int newPos = byteSize - 1 + (int)offset;
                    if (newPos < 0 || newPos >= byteSize)
                        return -1;
                    memory[1] = newPos;
                    return memory[1];
                }
        }

        return -1;
    }
};
memRW.ReadFn = (RWops context, IntPtr ptr, ulong size, ulong maxnum) =>
{
    unsafe
    {
        int* memory = (int*)context.Data1.ToPointer();
        int byteSize = memory[0];
        int currentPos = memory[1];

        int readByte = (int)(size * maxnum);
        if (readByte + currentPos > byteSize)
            readByte = byteSize - currentPos;
        readByte = (readByte / (int)size) * (int)size;

        byte* memByte = (byte*)memory;
        Stdinc.Memcpy(ptr, new IntPtr(&memByte[currentPos + 8]), (ulong)readByte);

        memory[1] = currentPos + readByte;

        return (ulong)(readByte / (int)size);
    }
};
memRW.WriteFn = (RWops context, IntPtr ptr, ulong size, ulong num) =>
{
    unsafe
    {
        int* memory = (int*)context.Data1.ToPointer();
        int byteSize = memory[0];
        int currentPos = memory[1];

        int writeByte = (int)(size * num);
        if (writeByte + currentPos > byteSize)
            writeByte = byteSize - currentPos;
        writeByte = (writeByte / (int)size) * (int)size;

        byte* memByte = (byte*)memory;
        Stdinc.Memcpy(new IntPtr(&memByte[currentPos + 8]), ptr, (ulong)writeByte);

        memory[1] = currentPos + writeByte;

        return (ulong)(writeByte / (int)size);
    }
};
memRW.CloseFn = (RWops op) =>
{
    Stdinc.Free(op.Data1);
    return 0;
};

memRW.WriteLE64(254362);
memRW.Seek(0, SeekFrom.Set);
ulong ulongn = memRW.ReadLE64();
memRW.Write(new int[] { 1, 3, 5, 4, 6, 8 }, 0, 6);
memRW.Seek(-4 * 6, SeekFrom.Cur);
int[] intns = new int[8];
memRW.Read(intns, 1, 6);

memRW.Close();

RWops bmpFile = new RWops("./테스트.bmp", NETSDL2.IO.FileMode.Read);
bool isBmp = bmpFile.IsBMP();
isBmp = bmpFile.IsAVIF();
isBmp = bmpFile.IsCUR();
isBmp = bmpFile.IsGIF();
isBmp = bmpFile.IsICO();
isBmp = bmpFile.IsJPG();
isBmp = bmpFile.IsJXL();
isBmp = bmpFile.IsLBM();
isBmp = bmpFile.IsPCX();
isBmp = bmpFile.IsPNG();
isBmp = bmpFile.IsPNM();
isBmp = bmpFile.IsQOI();
isBmp = bmpFile.IsSVG();
isBmp = bmpFile.IsTIF();
isBmp = bmpFile.IsWEBP();
isBmp = bmpFile.IsXCF();
isBmp = bmpFile.IsXPM();
isBmp = bmpFile.IsXV();

Surface bmpSurface = Image.Load("./테스트.bmp");
bmpSurface.Dispose();

bmpSurface = Image.Load(bmpFile, false);
bmpSurface.Dispose();
bmpFile.Seek(0, SeekFrom.Set);
bmpSurface = Image.Load(bmpFile, true);

bmpSurface.SaveJPG("./테스트10.jpg", 10);
bmpSurface.SaveJPG("./테스트50.jpg", 50);
bmpSurface.SaveJPG("./테스트100.jpg", 100);
bmpSurface.SavePNG("./테스트.png");

bmpSurface.Dispose();

string[] xpmData =
{
    "48 4 2 1",
    "a c #ffffff",
    "b c #000000",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab",
    "abaabaababaaabaabababaabaabaababaabaaababaabaaab"
};

Surface xpmSurface = Image.ReadXPMFromArrayToRGB888(xpmData);

xpmSurface.SaveJPG("./XPMTest.jpg", 50);
xpmSurface.SavePNG("./XPMTest.png");

unsafe
{
    var keystates = Keyboard.GetKeyboardState(out int numkeys);
}

None resultVarer = result;

string controllerMap = GameController.MappingForIndex(0);

result = Video.Init(null);
Console.WriteLine("Video init: {0}", result);

Console.WriteLine("Base path: {0}", Filesystem.GetBasePath());
Console.WriteLine("Pref path: {0}", Filesystem.GetPrefPath("Haje", "Test"));

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

Logging.LogInfo(LogCategory.Application, "OS: {0}", Platform.GetPlatform());

Locale[] locales = Locale.GetPreferredLocales();
foreach(var locale in locales)
{
    Logging.LogInfo(LogCategory.Application, "Locale: {0}", locale);
}

Logging.LogInfo(LogCategory.Application, "Cores: {0}", CPUInfo.CPUCount);
Logging.LogInfo(LogCategory.Application, "Cache line: {0}", CPUInfo.CPUCacheLineSize);
Logging.LogInfo(LogCategory.Application, "System RAM: {0}", CPUInfo.SystemRAM);
Logging.LogInfo(LogCategory.Application, "SIMD alignment: {0}", CPUInfo.SIMDAlignment);

Logging.LogInfo(LogCategory.Application, "HasSSE42: {0}", CPUInfo.HasSSE42);
Logging.LogInfo(LogCategory.Application, "HasSSE41: {0}", CPUInfo.HasSSE41);
Logging.LogInfo(LogCategory.Application, "HasSSE3: {0}", CPUInfo.HasSSE3);
Logging.LogInfo(LogCategory.Application, "HasSSE2: {0}", CPUInfo.HasSSE2);
Logging.LogInfo(LogCategory.Application, "HasSSE: {0}", CPUInfo.HasSSE);
Logging.LogInfo(LogCategory.Application, "HasRDTSC: {0}", CPUInfo.HasRDTSC);
Logging.LogInfo(LogCategory.Application, "HasMMX: {0}", CPUInfo.HasMMX);
Logging.LogInfo(LogCategory.Application, "HasLASX: {0}", CPUInfo.HasLASX);
Logging.LogInfo(LogCategory.Application, "HasLSX: {0}", CPUInfo.HasLSX);
Logging.LogInfo(LogCategory.Application, "HasNEON: {0}", CPUInfo.HasNEON);
Logging.LogInfo(LogCategory.Application, "HasARMSIMD: {0}", CPUInfo.HasARMSIMD);
Logging.LogInfo(LogCategory.Application, "HasAVX512F: {0}", CPUInfo.HasAVX512F);
Logging.LogInfo(LogCategory.Application, "HasAVX2: {0}", CPUInfo.HasAVX2);
Logging.LogInfo(LogCategory.Application, "HasAVX: {0}", CPUInfo.HasAVX);
Logging.LogInfo(LogCategory.Application, "HasAltiVec: {0}", CPUInfo.HasAltiVec);
Logging.LogInfo(LogCategory.Application, "Has3DNow: {0}", CPUInfo.Has3DNow);

Misc.OpenURL("https://www.youtube.com/");

IntPtr simdMem = CPUInfo.SIMDAlloc(128);
simdMem = CPUInfo.SIMDRealloc(simdMem, 256);
CPUInfo.SIMDFree(simdMem);

float ave = Endian.SwapFloat(1.51f);
int ainer = Bits.MostSignificantBitIndex32(545123);
bool exrerh = Bits.HasExactlyOneBitSet32(5);

Platform.GetDXGIOutputInfo(0, out int adapter, out int output);

int numSensors = Sensor.NumSensors;

PowerState powerState = Power.GetPowerInfo(out int secs, out int percetns);

int numAudioDriver = Audio.GetNumAudioDrivers();
for(int i = 0; i < numAudioDriver; i++)
{
    Logging.LogInfo(LogCategory.Application, "Audio driver: {0}", Audio.GetAudioDriver(i));
}
Logging.LogInfo(LogCategory.Application, "Current audio driver: {0}", Audio.GetCurrentAudioDriver());

int numAudioOutput = Audio.GetNumAudioDevices(false);
int numAudioInput = Audio.GetNumAudioDevices(true);

for (int i = 0; i < numAudioOutput; i++)
{
    Logging.LogInfo(LogCategory.Application, "Audio output: {0}", Audio.GetAudioDeviceName(i, false));
}

for (int i = 0; i < numAudioInput; i++)
{
    Logging.LogInfo(LogCategory.Application, "Audio input: {0}", Audio.GetAudioDeviceName(i, true));
}

Audio.BuildAudioCVT(out AudioCVT cvt, AudioFormat.U16, 2, 44000, AudioFormat.F32, 2, 48000);

Logging.LogInfo(LogCategory.Application, "Default input: {0}", Audio.GetDefaultAudioInfo(out string audioName, out AudioSpec audioSpec, true));
Logging.LogInfo(LogCategory.Application, "Default input: {0} {1}", audioName, audioSpec);

Logging.LogInfo(LogCategory.Application, "Default output: {0}", Audio.GetDefaultAudioInfo(out audioName, out audioSpec, false));
Logging.LogInfo(LogCategory.Application, "Default output: {0} {1}", audioName, audioSpec);

for (int i = 0; i < numAudioInput; i++)
{
    Logging.LogInfo(LogCategory.Application, "Audio input: {0}", Audio.GetAudioDeviceSpec(i, true, out audioSpec));
    Logging.LogInfo(LogCategory.Application, "Audio input: {0}", audioSpec);
}

for (int i = 0; i < numAudioOutput; i++)
{
    Logging.LogInfo(LogCategory.Application, "Audio output: {0}", Audio.GetAudioDeviceSpec(i, false, out audioSpec));
    Logging.LogInfo(LogCategory.Application, "Audio output: {0}", audioSpec);
}

NETSDL2.Concurrent.Thread thread = new NETSDL2.Concurrent.Thread((data) =>
{
    unsafe
    {
        int count = data.ToInt32();
        for (int i = 0; i < count; i++)
            Logging.LogInfo(LogCategory.Application, "Thread id {0} running {1}", NETSDL2.Concurrent.Thread.CurrentThreadID, i);

        return count;
    }
}, "Testing thread", new IntPtr(10));
thread.Detach();
thread = new NETSDL2.Concurrent.Thread((data) =>
{
    unsafe
    {
        int count = data.ToInt32();
        for (int i = 0; i < count; i++)
            Logging.LogInfo(LogCategory.Application, "Thread id {0} running {1}", NETSDL2.Concurrent.Thread.CurrentThreadID, i);

        return count;
    }
}, "Testing thread", new IntPtr(10));
thread.Detach();
uint mainThreadID = NETSDL2.Concurrent.Thread.CurrentThreadID;

NETSDL2.Systems.Timer timer = new NETSDL2.Systems.Timer(
    1000,
    (interval, data) =>
    {
        Logging.LogInfo(LogCategory.Application, "Timer: {0}", data.ToInt64());
        return interval;
    }, new IntPtr(1234));

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
bool isShaped = window.IsShapedWindow;

window.OnHidden += (Window window, uint timestamp) =>
{
    Logging.LogInfo(LogCategory.Application, "Window hidden on {0}", timestamp);
};
window.OnMoved += (Window window, uint timestamp, int x, int y) =>
{
    Logging.LogInfo(LogCategory.Application, "Main window moved on {0} to {1}, {2}", timestamp, x, y);
};
window.OnKeyPressed += (Window window, uint timestamp, Scancode physicalKey, Keycode virtualKey, Keymod modifiers) =>
{
    Logging.LogInfo(LogCategory.Application, "Main window key pressed on {0} {1} ({2}) with {3}", timestamp, physicalKey, virtualKey, modifiers & (~Keymod.Num));
};
window.OnKeyPressing += (Window window, uint timestamp, Scancode physicalKey, Keycode virtualKey, Keymod modifiers) =>
{
    Logging.LogInfo(LogCategory.Application, "Main window key pressing on {0} {1} ({2}) with {3}", timestamp, physicalKey, virtualKey, modifiers & (~Keymod.Num));
};
window.OnKeyReleased += (Window window, uint timestamp, Scancode physicalKey, Keycode virtualKey, Keymod modifiers) =>
{
    Logging.LogInfo(LogCategory.Application, "Main window key released on {0} {1} ({2}) with {3}", timestamp, physicalKey, virtualKey, modifiers & (~Keymod.Num));
};

window.SetWindowHitTest((Window window, Point point, IntPtr data) =>
{
    window.GetWindowSize(out int w, out int h);
    if (point.X > w / 2)
        return HitTestResult.ResizeRight;

    return HitTestResult.Normal;
}, new IntPtr(50000));

ICCProfile profile = window.GetWindowICCProfile().ResultValue;

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
Logging.LogInfo(LogCategory.Application, "Opacity: {0}", window.SetWindowOpacity(1.0f));

window.SetWindowPosition(100, 100);

window.SetWindowResizable(true);
window.SetWindowResizable(false);
window.SetWindowResizable(true);
window.SetWindowSize(500, 500);

window.HideWindow();
window.ShowWindow();

modal.Dispose();

ushort[] pixels = new ushort[16 * 16] {
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
    0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
    0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
    0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
    0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
    0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
    0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
    0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
    0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
    0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
    0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
    0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
    0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
    0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
    0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
    0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
    0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
    0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
    0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
    0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
    0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
    0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff
};
unsafe
{
    fixed (ushort* pPixels = &pixels[0])
    {
        using (Surface surface = new Surface((void*)pPixels, 16, 16, 16, 16 * 2, 0x0f00, 0x00f0, 0x000f, 0xf000))
        {
            SDL.ThrowOnFailure = true;
            surface.FillRects(new Rect[]
            {
                new Rect(0, 0, 4, 4),
                new Rect(4, 4, 4, 4)
            }, 0x7fff);
            Surface surfaceConv = surface.ConvertSurfaceFormat(PixelFormatEnum.BGRA4444);
            surfaceConv.SetSurfaceRLE(true);
            surfaceConv.SetColorKey(true, 0x0fff);
            uint colorKey = surfaceConv.GetColorKey();
            surfaceConv.SetColorKey(false, 0);
            surfaceConv.GetSurfaceColorMod(out byte red, out byte green, out byte blue);
            surfaceConv.SetSurfaceColorMod(128, 120, 60);
            surfaceConv.GetSurfaceColorMod(out red, out green, out blue);
            Surface surfaceConvCopy = new Surface(surfaceConv);
            Surface blitSurf = new Surface(16, 16, 32, PixelFormatEnum.BGRA8888);
            Surface.BlitSurface(surfaceConvCopy, new Rect(0, 0, 16, 8), blitSurf, new Rect(0, 8, 16, 8));
            window.SetWindowIcon(blitSurf);
            SDL.ThrowOnFailure = false;
        }
    }
}

Surface bmpImage = new Surface("테스트.bmp");
None areiahre = bmpImage.SaveBMP("테스트저장.bmp");

Renderer renderer;
Window winWithRenderer = new Window(1920, 1080, WindowFlags.AllowHighDPI, out renderer);
winWithRenderer.SetWindowAlwaysOnTop(true);
Surface windowSurface = winWithRenderer.GetWindowSurface().ResultValue;
windowSurface = winWithRenderer.GetWindowSurface().ResultValue;
PixelFormat windowSurfaceFormat = windowSurface.Format;

Texture bmpTexture = renderer.LoadTexture("테스트.bmp");

Texture texture = new Texture(renderer, PixelFormatEnum.RGBA8888, TextureAccess.Target, 200, 200);
Texture texture2 = new Texture(renderer, windowSurface);
Texture texture3 = new Texture(renderer, Pixels.MasksToPixelFormatEnum(16, 0x0f00, 0x00f0, 0x000f, 0xf000), TextureAccess.Streaming, 200, 200);

Logging.LogInfo(LogCategory.Application, "Texture alpha: {0}", texture.GetTextureAlphaMod());
Logging.LogInfo(LogCategory.Application, "Texture blend: {0}", texture.GetTextureBlendMode());
Logging.LogInfo(LogCategory.Application, "Texture color: {0}", texture.GetTextureColorMod(out byte r, out byte g, out byte b));
Logging.LogInfo(LogCategory.Application, "Texture color: {0}, {1}, {2}", r, g, b);

Logging.LogInfo(LogCategory.Application, "Make current: {0}", GL.MakeCurrent(window, context.ResultValue));
Logging.LogInfo(LogCategory.Application, "Bind: {0}, {1}", GL.BindTexture(texture2, out float texw, out float texh), Error.GetError());
Logging.LogInfo(LogCategory.Application, "Unbind: {0}, {1}", GL.UnbindTexture(texture2), Error.GetError());

Logging.LogInfo(LogCategory.Application, "Lock texture: {0}", texture3.LockTexture(null, out IntPtr px, out int pt));
Logging.LogInfo(LogCategory.Application, "Lock texture: {0}, {1}", px, pt);
Logging.LogInfo(LogCategory.Application, "Lock texture: {0}", texture3.LockTexture(new Rect(100, 100, 50, 50), out px, out pt));
Logging.LogInfo(LogCategory.Application, "Lock texture: {0}, {1}", px, pt);
texture3.UnlockTexture();
Logging.LogInfo(LogCategory.Application, "Query texture: {0}", texture2.QueryTexture(out PixelFormatEnum pixelFormat, out TextureAccess texAccess, out w, out h));
Logging.LogInfo(LogCategory.Application, "Query texture: {0}, {1}, {2}, {3}", pixelFormat, texAccess, w, h);

Logging.LogInfo(LogCategory.Application, "Renderer blend: {0}", renderer.GetDrawBlendMode());
Logging.LogInfo(LogCategory.Application, "Set renderer blend: {0}", renderer.SetDrawBlendMode(BlendMode.Blend));
Logging.LogInfo(LogCategory.Application, "Renderer blend: {0}", renderer.GetDrawBlendMode());

Logging.LogInfo(LogCategory.Application, "Renderer draw color: {0}", renderer.GetDrawColor(out r, out g, out b, out byte a));
Logging.LogInfo(LogCategory.Application, "Renderer draw color: {0}, {1}, {2}, {3}", r, g, b, a);
Logging.LogInfo(LogCategory.Application, "Set renderer draw color: {0}", renderer.SetDrawColor(255, 0, 0, 128));
Logging.LogInfo(LogCategory.Application, "Renderer draw color: {0}", renderer.GetDrawColor(out r, out g, out b, out a));
Logging.LogInfo(LogCategory.Application, "Renderer draw color: {0}, {1}, {2}, {3}", r, g, b, a);

Logging.LogInfo(LogCategory.Application, "Renderer info: {0}", renderer.GetRendererInfo());

Logging.LogInfo(LogCategory.Application, "Renderer output size: {0}", renderer.GetRendererOutputSize(out w, out h));
Logging.LogInfo(LogCategory.Application, "Renderer output size: {0}, {1}", w, h);

Logging.LogInfo(LogCategory.Application, "Render target: {0}", renderer.GetRenderTarget());
Logging.LogInfo(LogCategory.Application, "Set render target: {0}", renderer.SetRenderTarget(texture));
Logging.LogInfo(LogCategory.Application, "Render target: {0}", renderer.GetRenderTarget());

renderer.SetVSync(1);

renderer.SetRenderTarget(null);
renderer.SetDrawColor(255, 255, 255, 255);
Logging.LogInfo(LogCategory.Application, "Clear: {0}", renderer.Clear());
renderer.Present();

unsafe
{
    fixed (ushort* pPixels = &pixels[0])
    {
        texture3.UpdateTexture(new Rect(0, 0, 16, 16), new IntPtr(pPixels), 16 * 2);
    }
}

texture3.SetTextureScaleMode(ScaleMode.Nearest);

renderer.SetRenderTarget(texture);
renderer.SetDrawColor(255, 0, 0, 128);
renderer.DrawLine(0, 0, 200, 100);
renderer.Present();

renderer.SetRenderTarget(null);
renderer.Copy(texture3, new Rect(0, 0, 16, 16), new Rect(250, 150, 200, 200));
renderer.Present();

renderer.CopyEx(texture, new Rect(50, 50, 100, 100), new Rect(250, 150, 200, 200), 40, new Point(0, 0), RendererFlip.None);
renderer.Present();

renderer.CopyEx(texture, null, new Rect(250, 150, 200, 200), 40, new Point(0, 0), RendererFlip.Horizontal);
renderer.Present();

renderer.CopyEx(texture, new Rect(50, 50, 100, 100), null, 40, new Point(0, 0), RendererFlip.Vertical);
renderer.Present();

renderer.CopyExF(texture, new Rect(50, 50, 100, 100), new FRect(250, 150, 200, 200), 40, new FPoint(0, 0), RendererFlip.None);
renderer.Present();

renderer.CopyExF(texture, null, new FRect(250, 150, 200, 200), 40, new FPoint(0, 0), RendererFlip.Horizontal);
renderer.Present();

renderer.CopyExF(texture, new Rect(50, 50, 100, 100), null, 40, new FPoint(0, 0), RendererFlip.Vertical);
renderer.Present();

renderer.DrawLines(new Point(0, 0), new Point(200, 300), new Point(600, 500), new Point(700, 100));
renderer.Present();

renderer.DrawLinesF(new FPoint(0, 0), new FPoint(100.5f, 200.2f), new FPoint(800, 400), new FPoint(200, 300));
renderer.Present();

renderer.RenderGeometry(null, new Vertex[]
{
    new Vertex(new FPoint(500, 100), new Color(255, 0, 0, 127), new FPoint()),
    new Vertex(new FPoint(300, 300), new Color(0, 255, 0, 127), new FPoint()),
    new Vertex(new FPoint(700, 300), new Color(0, 0, 255, 127), new FPoint())
}, null);
renderer.Present();

renderer.RenderGeometry(null, new Vertex[]
{
    new Vertex(new FPoint(100, 100), new Color(255, 0, 0, 127), new FPoint(0, 0)),
    new Vertex(new FPoint(100, 500), new Color(0, 255, 0, 127), new FPoint(0, 1)),
    new Vertex(new FPoint(500, 500), new Color(0, 0, 255, 127), new FPoint(1, 1)),
    new Vertex(new FPoint(500, 100), new Color(255, 255, 255, 255), new FPoint(1, 0))
}, new int[] { 0, 1, 2, 0, 2, 3 });
renderer.Present();

Surface webpSurf = Image.Load("webpim.webp");
Texture webpTex = new Texture(renderer, webpSurf);
renderer.RenderGeometry(webpTex, new Vertex[]
{
    new Vertex(new FPoint(100, 100), new Color(255, 255, 255, 255), new FPoint(0, 0)),
    new Vertex(new FPoint(100, 500), new Color(255, 255, 255, 255), new FPoint(0, 1)),
    new Vertex(new FPoint(500, 500), new Color(255, 255, 255, 255), new FPoint(1, 1)),
    new Vertex(new FPoint(500, 100), new Color(255, 255, 255, 255), new FPoint(1, 0))
}, new int[] { 0, 1, 2, 0, 2, 3 });
renderer.Present();

Animation gifAnim = new Animation("img.gif");
for(int i = 0; i < gifAnim.Count; i++)
{
    Logging.LogInfo(LogCategory.Application, "GIF {0} frame delay: {1}", i, gifAnim.GetDelay(i));
    Texture gifTex = new Texture(renderer, gifAnim[i]);
    renderer.RenderGeometry(gifTex, new Vertex[]
    {
        new Vertex(new FPoint(100, 100), new Color(255, 255, 255, 255), new FPoint(0, 0)),
        new Vertex(new FPoint(100, 500), new Color(255, 255, 255, 255), new FPoint(0, 1)),
        new Vertex(new FPoint(500, 500), new Color(255, 255, 255, 255), new FPoint(1, 1)),
        new Vertex(new FPoint(500, 100), new Color(255, 255, 255, 255), new FPoint(1, 0))
    }, new int[] { 0, 1, 2, 0, 2, 3 });
    renderer.Present();

    NETSDL2.Systems.Timer.Delay((uint)gifAnim.GetDelay(i));
}

Logging.LogInfo(LogCategory.Application, "Render driver num: {0}", Render.GetNumRenderDrivers());

RendererInfo[] renderers = Render.GetRenderDriverInfos();
foreach (RendererInfo re in renderers)
{
    Logging.LogInfo(LogCategory.Application, "Render driver: {0}", re);
}

renderer.Dispose();
winWithRenderer.Dispose();
windowSurface.Dispose();
texture.Dispose();
texture2.Dispose();

window.IsMouseGrabbed = false;
bool mainLoop = true;

FunctionPointer<EventFilter> watch = new FunctionPointer<EventFilter>(
    (IntPtr data, ref Event e) =>
    {
        if (e.Type == EventType.MouseButtonDown)
        {
            Logging.LogInfo(LogCategory.Application, "Mouse pos: {0}, {1}", e.Button.X, e.Button.Y);
        }
        return 1;
    }
    );
Events.AddEventWatch(watch, IntPtr.Zero);

int channels = Mixer.AllocateChannels(-1);
channels = Mixer.AllocateChannels(channels == 0 ? 8 : channels * 2);

_ = Mixer.OpenAudio(44000, AudioFormat.F32, 2, 4096).ResultValue;
Chunk nyanCatMusic = new Chunk("nyancat.mp3");
nyanCatMusic.Volume(64);
_ = Mixer.FadeInChannel(0, nyanCatMusic, -1, 1000);

Event @event = new Event();
while (mainLoop)
{
    while (Events.PollEvent(out @event).IsSuccess)
    {
        if (@event.Type == EventType.Quit)
        {
            mainLoop = false;
            Mixer.FadeOutChannel(0, 1000);
            NETSDL2.Systems.Timer.Delay(1000);
            break;
        }
    }
}

window.Dispose();

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
    using (PixelFormatWrapper format = new PixelFormatWrapper(Pixels.AllocFormat(PixelFormatEnum.RGBA8888)))
    {
        using (PaletteWrapper palette = new PaletteWrapper(Pixels.AllocPalette(3)))
        {
            Logging.LogInfo(LogCategory.Application, "Calc gamma: {0}", Pixels.CalculateGammaRamp(0.3f, redGamma));

            uint rgb = Pixels.MapRGB(format, 250, 120, 128);
            uint rgba = Pixels.MapRGBA(format, 102, 25, 59, 128);
            Pixels.GetRGB(rgb, format, out r, out g, out b);
            Pixels.GetRGBA(rgba, format, out r, out g, out b, out a);

            bool converted = Pixels.PixelFormatEnumToMasks(PixelFormatEnum.BGRA5551, out int bpp, out uint rmask, out uint gmask, out uint bmask, out uint amask);
            PixelFormatEnum formatEnum = Pixels.MasksToPixelFormatEnum(bpp, rmask, gmask, bmask, amask);

            Logging.LogInfo(LogCategory.Application, "Set palete color: {0}", Pixels.SetPaletteColors(palette, 1, new Color(100, 20, 20, 50)));
            Logging.LogInfo(LogCategory.Application, "{0}", (*palette.Palette)[1]);

            Logging.LogInfo(LogCategory.Application, "Set pixel palette: {0}", Pixels.SetPixelFormatPalette(format, palette));
            Logging.LogInfo(LogCategory.Application, "{0}", Error.GetError());

            Surface blitSurf = new Surface(16, 16, 32, PixelFormatEnum.BGRA8888);
            blitSurf.SetSurfacePalette(palette);
        }
    }
}

FPoint[] fpoints = new FPoint[]
{
    new FPoint(1.0f, 2.0f),
    new FPoint(5.0f, -4.0f),
    new FPoint(2.0f, 3.0f),
    new FPoint(-3.0f, -2.0f)
};

bool enclose = RectOps.EncloseFPoints(fpoints, null, out FRect encloseRectF);
enclose = RectOps.EncloseFPoints(fpoints, new FRect(0.0f, 0.0f, 7.0f, 6.0f), out encloseRectF);

bool hasIntersection = RectOps.HasIntersectionF(new FRect(0.0f, 0.0f, 7.0f, 6.0f), new FRect(-5.0f, -4.0f, 2.0f, 3.0f));
hasIntersection = RectOps.HasIntersectionF(new FRect(0.0f, 0.0f, 7.0f, 6.0f), new FRect(-5.0f, -4.0f, 9.0f, 8.0f));
hasIntersection = RectOps.IntersectFRect(new FRect(0.0f, 0.0f, 7.0f, 6.0f), new FRect(-5.0f, -4.0f, 9.0f, 8.0f), out FRect intersectF);
hasIntersection = RectOps.IntersectFRect(new FRect(0.0f, 0.0f, 7.0f, 6.0f), new FRect(-5.0f, -4.0f, 2.0f, 3.0f), out intersectF);
hasIntersection = RectOps.IntersectFRectAndLine(new FRect(0.0f, 0.0f, 5.0f, 5.0f), -1.0f, -1.0f, 0.0f, 6.0f);
hasIntersection = RectOps.IntersectFRectAndLine(new FRect(0.0f, 0.0f, 5.0f, 5.0f), -1.0f, -1.0f, 3.0f, 6.0f);

bool pointIn = RectOps.PointInFRect(new FPoint(0.0f, 2.0f), new FRect(2.0f, 3.0f, 5.0f, 6.0f));
pointIn = RectOps.PointInFRect(new FPoint(3.0f, 5.0f), new FRect(2.0f, 3.0f, 5.0f, 6.0f));

RectOps.UnionFRect(new FRect(0.0f, 0.0f, 7.0f, 6.0f), new FRect(-5.0f, -4.0f, 9.0f, 8.0f), out FRect unionF);

Point[] points = new Point[]
{
    new Point(1, 2),
    new Point(5, -4),
    new Point(2, 3),
    new Point(-3, -2)
};

enclose = RectOps.EnclosePoints(points, null, out Rect encloseRect);
enclose = RectOps.EnclosePoints(points, new Rect(0, 0, 7, 6), out encloseRect);

hasIntersection = RectOps.HasIntersection(new Rect(0, 0, 7, 6), new Rect(-5, -4, 2, 3));
hasIntersection = RectOps.HasIntersection(new Rect(0, 0, 7, 6), new Rect(-5, -4, 9, 8));
hasIntersection = RectOps.IntersectRect(new Rect(0, 0, 7, 6), new Rect(-5, -4, 9, 8), out Rect intersect);
hasIntersection = RectOps.IntersectRect(new Rect(0, 0, 7, 6), new Rect(-5, -4, 2, 3), out intersect);
hasIntersection = RectOps.IntersectRectAndLine(new Rect(0, 0, 5, 5), -1, -1, 0, 6);
hasIntersection = RectOps.IntersectRectAndLine(new Rect(0, 0, 5, 5), -1, -1, 3, 6);

pointIn = RectOps.PointInRect(new Point(0, 2), new Rect(2, 3, 5, 6));
pointIn = RectOps.PointInRect(new Point(3, 5), new Rect(2, 3, 5, 6));

RectOps.UnionRect(new Rect(0, 0, 7, 6), new Rect(-5, -4, 9, 8), out Rect union);

Logging.LogInfo(LogCategory.Application, "Has clipboard: {0}", Clipboard.HasClipboardText);
Logging.LogInfo(LogCategory.Application, "Get clipboard: {0}", Clipboard.GetClipboardText());
Logging.LogInfo(LogCategory.Application, "Set clipboard: {0}", Clipboard.SetClipboardText("치노쨩"));
Logging.LogInfo(LogCategory.Application, "Has clipboard: {0}", Clipboard.HasClipboardText);
Logging.LogInfo(LogCategory.Application, "Get clipboard: {0}", Clipboard.GetClipboardText());

unsafe
{
    Logging.LogInfo(LogCategory.Application, "Vulkan load: {0}", Vulkan.LoadLibrary(null));
    Window vulkanWindow = new Window("Vulkan", 100, 100, 800, 600, WindowFlags.Vulkan | WindowFlags.AllowHighDPI);
    Vulkan.GetDrawableSize(vulkanWindow, out int width, out int height);
    Logging.LogInfo(LogCategory.Application, "Size: {0}, {1}", width, height);
    string[] extensions = Vulkan.GetInstanceExtensions(vulkanWindow).ResultValue;
    foreach(string extension in extensions)
    {
        Logging.LogInfo(LogCategory.Application, "Extension: {0}", extension);
    }
    void* vkGetInstanceProcAddr = Vulkan.GetVkGetInstanceProcAddr();
    Logging.LogInfo(LogCategory.Application, "vkGetInstanceProcAddr: 0x{0:x}", (ulong)vkGetInstanceProcAddr);

    vulkanWindow.Dispose();

    Vulkan.UnloadLibrary();
}

Image.Quit();
Mixer.Quit();

Video.Quit();
SDL.Quit();
