#pragma once

#include <SDL.h>

using namespace System::Runtime::InteropServices;

namespace NETSDL2
{
	namespace Events
	{
		/// <summary>
		/// The SDL virtual key representation.
		/// </summary>
        public enum class Keycode : Sint32
		{
            Unknown = SDLK_UNKNOWN,

            Return = SDLK_RETURN,
            Escape = SDLK_ESCAPE,
            Backspace = SDLK_BACKSPACE,
            Tab = SDLK_TAB,
            Space = SDLK_SPACE,
            Exclaim = SDLK_EXCLAIM,
            QuoteDbl = SDLK_QUOTEDBL,
            Hash = SDLK_HASH,
            Percent = SDLK_PERCENT,
            Dollor = SDLK_DOLLAR,
            Ampersand = SDLK_AMPERSAND,
            Quote = SDLK_QUOTE,
            LeftParen = SDLK_LEFTPAREN,
            RightParen = SDLK_RIGHTPAREN,
            Asterisk = SDLK_ASTERISK,
            Plus = SDLK_PLUS,
            Comma = SDLK_COMMA,
            Minus = SDLK_MINUS,
            Period = SDLK_PERIOD,
            Slash = SDLK_SLASH,
            Num0 = SDLK_0,
            Num1 = SDLK_1,
            Num2 = SDLK_2,
            Num3 = SDLK_3,
            Num4 = SDLK_4,
            Num5 = SDLK_5,
            Num6 = SDLK_6,
            Num7 = SDLK_7,
            Num8 = SDLK_8,
            Num9 = SDLK_9,
            Colon = SDLK_COLON,
            Semicolon = SDLK_SEMICOLON,
            Less = SDLK_LESS,
            Equals = SDLK_EQUALS,
            Greater = SDLK_GREATER,
            Question = SDLK_QUESTION,
            At = SDLK_AT,

            LeftBracket = SDLK_LEFTBRACKET,
            Backslash = SDLK_BACKSLASH,
            RightBracket = SDLK_RIGHTBRACKET,
            Caret = SDLK_CARET,
            Underscore = SDLK_UNDERSCORE,
            BackQuote = SDLK_BACKQUOTE,
            a = SDLK_a,
            b = SDLK_b,
            c = SDLK_c,
            d = SDLK_d,
            e = SDLK_e,
            f = SDLK_f,
            g = SDLK_g,
            h = SDLK_h,
            i = SDLK_i,
            j = SDLK_j,
            k = SDLK_k,
            l = SDLK_l,
            m = SDLK_m,
            n = SDLK_n,
            o = SDLK_o,
            p = SDLK_p,
            q = SDLK_q,
            r = SDLK_r,
            s = SDLK_s,
            t = SDLK_t,
            u = SDLK_u,
            v = SDLK_v,
            w = SDLK_w,
            x = SDLK_x,
            y = SDLK_y,
            z = SDLK_z,

            CapsLock = SDLK_CAPSLOCK,

            F1 = SDLK_F1,
            F2 = SDLK_F2,
            F3 = SDLK_F3,
            F4 = SDLK_F4,
            F5 = SDLK_F5,
            F6 = SDLK_F6,
            F7 = SDLK_F7,
            F8 = SDLK_F8,
            F9 = SDLK_F9,
            F10 = SDLK_F10,
            F11 = SDLK_F11,
            F12 = SDLK_F12,

            PrintScreen = SDLK_PRINTSCREEN,
            ScrollLock = SDLK_SCROLLLOCK,
            Pause = SDLK_PAUSE,
            Insert = SDLK_INSERT,
            Home = SDLK_HOME,
            PageUp = SDLK_PAGEUP,
            Delete = SDLK_DELETE,
            End = SDLK_END,
            PageDown = SDLK_PAGEDOWN,
            Right = SDLK_RIGHT,
            Left = SDLK_LEFT,
            Down = SDLK_DOWN,
            Up = SDLK_UP,

            NumLockClear = SDLK_NUMLOCKCLEAR,
            KeypadDivice = SDLK_KP_DIVIDE,
            KeypadMultiply = SDLK_KP_MULTIPLY,
            KeypadMinus = SDLK_KP_MINUS,
            KeypadPlus = SDLK_KP_PLUS,
            KeypadEnter = SDLK_KP_ENTER,
            Keypad1 = SDLK_KP_1,
            Keypad2 = SDLK_KP_2,
            Keypad3 = SDLK_KP_3,
            Keypad4 = SDLK_KP_4,
            Keypad5 = SDLK_KP_5,
            Keypad6 = SDLK_KP_6,
            Keypad7 = SDLK_KP_7,
            Keypad8 = SDLK_KP_8,
            Keypad9 = SDLK_KP_9,
            Keypad0 = SDLK_KP_0,
            KeypadPeriod = SDLK_KP_PERIOD,

            Application = SDLK_APPLICATION,
            Power = SDLK_POWER,
            KeypadEquals = SDLK_KP_EQUALS,
            F13 = SDLK_F13,
            F14 = SDLK_F14,
            F15 = SDLK_F15,
            F16 = SDLK_F16,
            F17 = SDLK_F17,
            F18 = SDLK_F18,
            F19 = SDLK_F19,
            F20 = SDLK_F20,
            F21 = SDLK_F21,
            F22 = SDLK_F22,
            F23 = SDLK_F23,
            F24 = SDLK_F24,
            Execute = SDLK_EXECUTE,
            Help = SDLK_HELP,
            Menu = SDLK_MENU,
            Select = SDLK_SELECT,
            Stop = SDLK_STOP,
            Again = SDLK_AGAIN,
            Undo = SDLK_UNDO,
            Cut = SDLK_CUT,
            Copy = SDLK_COPY,
            Paste = SDLK_PASTE,
            Find = SDLK_FIND,
            Mute = SDLK_MUTE,
            VolumeUp = SDLK_VOLUMEUP,
            VolumeDown = SDLK_VOLUMEDOWN,
            KeypadComma = SDLK_KP_COMMA,
            KeypadEqualsAs400 = SDLK_KP_EQUALSAS400,

            AltErase = SDLK_ALTERASE,
            SysReq = SDLK_SYSREQ,
            Cancel = SDLK_CANCEL,
            Clear = SDLK_CLEAR,
            Prior = SDLK_PRIOR,
            Return2 = SDLK_RETURN2,
            Separator = SDLK_SEPARATOR,
            Out = SDLK_OUT,
            Oper = SDLK_OPER,
            ClearAgain = SDLK_CLEARAGAIN,
            CrSel = SDLK_CRSEL,
            ExSel = SDLK_EXSEL,

            Keypad00 = SDLK_KP_00,
            Keypad000 = SDLK_KP_000,
            KeypadThousandsSeparator = SDLK_THOUSANDSSEPARATOR,
            KeypadDecimalSeparator = SDLK_DECIMALSEPARATOR,
            KeypadCurrencyUnit = SDLK_CURRENCYUNIT,
            KeypadCurrencySubunit = SDLK_CURRENCYSUBUNIT,
            KeypadLeftParen = SDLK_KP_LEFTPAREN,
            KeypadRightParen = SDLK_KP_RIGHTPAREN,
            KeypadLeftBrace = SDLK_KP_LEFTBRACE,
            KeypadRightBrace = SDLK_KP_RIGHTBRACE,
            KeypadTab = SDLK_KP_TAB,
            KeypadBackspace = SDLK_KP_BACKSPACE,
            KeypadA = SDLK_KP_A,
            KeypadB = SDLK_KP_B,
            KeypadC = SDLK_KP_C,
            KeypadD = SDLK_KP_D,
            KeypadE = SDLK_KP_E,
            KeypadF = SDLK_KP_F,
            KeypadXor = SDLK_KP_XOR,
            KeypadPower = SDLK_KP_POWER,
            KeypadPercent = SDLK_KP_PERCENT,
            KeypadLess = SDLK_KP_LESS,
            KeypadGreater = SDLK_KP_GREATER,
            KeypadAmpersand = SDLK_KP_AMPERSAND,
            KeypadDoubldAmpersand = SDLK_KP_DBLAMPERSAND,
            KeypadVerticalBar = SDLK_KP_VERTICALBAR,
            KeypadDoubleVerticalBar = SDLK_KP_DBLVERTICALBAR,
            KeypadColon = SDLK_KP_COLON,
            KeypadHash = SDLK_KP_HASH,
            KeypadSpace = SDLK_KP_SPACE,
            KeypadAt = SDLK_KP_AT,
            KeypadExclam = SDLK_KP_EXCLAM,
            KeypadMemStore = SDLK_KP_MEMSTORE,
            KeypadMemRecall = SDLK_KP_MEMRECALL,
            KeypadMemClear = SDLK_KP_MEMCLEAR,
            KeypadMemAdd = SDLK_KP_MEMADD,
            KeypadMemSubtract = SDLK_KP_MEMSUBTRACT,
            KeypadMemMultiply = SDLK_KP_MEMMULTIPLY,
            KeypadMemDivide = SDLK_KP_MEMDIVIDE,
            KeypadPlusMinus = SDLK_KP_PLUSMINUS,
            KeypadClear = SDLK_KP_CLEAR,
            KeypadClearEntry = SDLK_KP_CLEARENTRY,
            KeypadBinary = SDLK_KP_BINARY,
            KeypadOctal = SDLK_KP_OCTAL,
            KeypadDecimal = SDLK_KP_DECIMAL,
            KeypadHexadecimal = SDLK_KP_HEXADECIMAL,

            LCtrl = SDLK_LCTRL,
            LShift = SDLK_LSHIFT,
            LAlt = SDLK_LALT,
            LGUI = SDLK_LGUI,
            RCtrl = SDLK_RCTRL,
            RShift = SDLK_RSHIFT,
            RAlt = SDLK_RALT,
            RGUI = SDLK_RGUI,

            Mode = SDLK_MODE,

            AudioNext = SDLK_AUDIONEXT,
            AudioPrev = SDLK_AUDIOPREV,
            AudioStop = SDLK_AUDIOSTOP,
            AudioPlay = SDLK_AUDIOPLAY,
            AudioMute = SDLK_AUDIOMUTE,
            MediaSelect = SDLK_MEDIASELECT,
            WWW = SDLK_WWW,
            Mail = SDLK_MAIL,
            Calculator = SDLK_CALCULATOR,
            Computer = SDLK_COMPUTER,
            ACSearch = SDLK_AC_SEARCH,
            ACHome = SDLK_AC_HOME,
            ACBack = SDLK_AC_BACK,
            ACForward = SDLK_AC_FORWARD,
            ACStop = SDLK_AC_STOP,
            ACRefresh = SDLK_AC_REFRESH,
            ACBookmarks = SDLK_AC_BOOKMARKS,

            BrightnessDown = SDLK_BRIGHTNESSDOWN,
            BrightnessUp = SDLK_BRIGHTNESSUP,
            DisplaySwitch = SDLK_DISPLAYSWITCH,
            KBDillumToggle = SDLK_KBDILLUMTOGGLE,
            KBDillumDown = SDLK_KBDILLUMDOWN,
            KBDillumUp = SDLK_KBDILLUMUP,
            Eject = SDLK_EJECT,
            Sleep = SDLK_SLEEP,
            App1 = SDLK_APP1,
            App2 = SDLK_APP2,

            AudioRewind = SDLK_AUDIOREWIND ,
            AudioFastForward = SDLK_AUDIOFASTFORWARD,

            SoftLeft = SDLK_SOFTLEFT,
            SoftRight = SDLK_SOFTRIGHT,
            Call = SDLK_CALL,
            EndCall = SDLK_ENDCALL,
		};

        /// <summary>
        /// Enumeration of valid key mods (possibly OR'd together).
        /// </summary>
        [System::Flags]
        public enum class Keymod : Uint16
        {
            None = KMOD_NONE,

            /// <summary>
            /// the left Shift key is down
            /// </summary>
            LShift = KMOD_LSHIFT,

            /// <summary>
            /// the right Shift key is down
            /// </summary>
            RShift = KMOD_RSHIFT,

            /// <summary>
            /// the left Ctrl(Control) key is down
            /// </summary>
            LCtrl = KMOD_LCTRL,

            /// <summary>
            /// the right Ctrl (Control) key is down
            /// </summary>
            RCtrl = KMOD_RCTRL,

            /// <summary>
            /// the left Alt key is down
            /// </summary>
            LAlt = KMOD_LALT,

            /// <summary>
            /// the right Alt key is down
            /// </summary>
            RAlt = KMOD_RALT,

            /// <summary>
            /// the left GUI key (often the Windows key) is down
            /// </summary>
            LGUI = KMOD_LGUI,

            /// <summary>
            /// the right GUI key (often the Windows key) is down
            /// </summary>
            RGUI = KMOD_RGUI,

            /// <summary>
            /// the Num Lock key (may be located on an extended keypad) is down
            /// </summary>
            Num = KMOD_NUM,

            /// <summary>
            /// the Caps Lock key is down
            /// </summary>
            Caps = KMOD_CAPS,

            /// <summary>
            /// the !AltGr key is down
            /// </summary>
            Mode = KMOD_MODE,

            /// <summary>
            /// the Scroll Lock key is down
            /// </summary>
            Scroll = KMOD_SCROLL,

            /// <summary>
            /// both ctrl key is down
            /// </summary>
            Ctrl = KMOD_CTRL,

            /// <summary>
            /// both shift key is down
            /// </summary>
            Shift = KMOD_SHIFT,

            /// <summary>
            /// both alt key is down
            /// </summary>
            Alt = KMOD_ALT,

            /// <summary>
            /// both GUI key is down
            /// </summary>
            GUI = KMOD_GUI,
        };
	}
}