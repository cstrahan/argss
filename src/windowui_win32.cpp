/////////////////////////////////////////////////////////////////////////////
// ARGSS - Copyright (c) 2009 - 2010, Alejandro Marzini (vgvgf)
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//	* Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//	* Redistributions in binary form must reproduce the above copyright
//	notice, this list of conditions and the following disclaimer in the
//	documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "windowui_win32.h"
#include "output.h"
#include "windows.h"

////////////////////////////////////////////////////////////
/// Definitions
////////////////////////////////////////////////////////////
#ifdef UNICODE
	#ifndef _T
		#define _T(x) L ## x
	#endif
	static std::wstring s2ws(const std::string& s) {
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
#else
	#ifdef _T
		#undef _T
	#endif
	#define _T(x) x
	static std::string s2ws(const std::string& s) {
		return s;
	}
#endif
#ifndef WM_XBUTTONDOWN
	#define WM_XBUTTONDOWN 523
#endif
#ifndef WM_XBUTTONUP
	#define WM_XBUTTONUP 524
#endif
#ifndef XBUTTON1
	#define XBUTTON1 1
#endif
#ifndef XBUTTON2
	#define XBUTTON2 2
#endif

////////////////////////////////////////////////////////////
/// Event Process
////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	WindowUi* window = (WindowUi*) GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (!window->ProccesEvents(hWnd, uMsg, wParam, lParam)) {
		return 0;
	} else {
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}

////////////////////////////////////////////////////////////
/// Constructor
////////////////////////////////////////////////////////////
WindowUi::WindowUi(long iwidth, long iheight, std::string title, bool center, bool fs_flag) {
	keys.resize(Input::Keys::KEYS_COUNT, false);
	mouse_focus = false;
	mouse_wheel = 0;
	mouse_x = 0;
	mouse_y = 0;

	width = iwidth;
	height = iheight;

	fullscreen = fs_flag;

	hinstance = GetModuleHandle(NULL);

#ifdef UNICODE
	WNDCLASSEXW wc;
#else
	WNDCLASSEXA wc;
#endif
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc		= (WNDPROC) WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hinstance;
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= NULL;
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= _T("ARGSS Player");
	wc.hIconSm = NULL;

#ifdef UNICODE
	if (!RegisterClassExW(&wc)) {
#else
	if (!RegisterClassExA(&wc)) {
#endif
		Output::ErrorStr("Failed to register the window class.");
	}

	if (fullscreen) {
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = width;
		dmScreenSettings.dmPelsHeight = height;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			Output::WarningStr("Current fullscreen mode is not supported. Windowed mode will be used.");
		}
	}

	DWORD dwExStyle;
	DWORD dwStyle;
	if (fullscreen) {
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	} else {
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME;
	}

	long posx = 0;
	long posy = 0;
	if (!fullscreen && center) {
		RECT scrrect;
		if (SystemParametersInfo(SPI_GETWORKAREA, 0, &scrrect, SPIF_UPDATEINIFILE)) {
			int centerx = scrrect.right / 2;
			int centery = scrrect.bottom / 2;

			int edge = GetSystemMetrics(SM_CXEDGE);
			int capt = GetSystemMetrics(SM_CXFIXEDFRAME);

			posx = centerx - width / 2 - edge;
			posy = centery - height / 2 - capt;
		}
	}

	RECT windowRect = {posx, posy, posx + iwidth, posy + iheight};
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

	hwnd = CreateWindowEx(dwExStyle, _T("ARGSS Player"), s2ws(title).c_str(), dwStyle | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, windowRect.left, windowRect.top, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, NULL, NULL, hinstance, NULL);

	if (!hwnd) {
		Dispose();
		Output::ErrorStr("Failed to create the window.");
	}

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;

	hdc = GetDC(hwnd);
	if (!hdc) {
		Dispose();
		Output::ErrorStr("Failed to create opengl device context.");
	}
	unsigned int pixel_format = ChoosePixelFormat(hdc, &pfd);
	if (!pixel_format) {
		Dispose();
		Output::ErrorStr("Couldn't find a suitable pixel format.");
	}
	if (!SetPixelFormat(hdc, pixel_format, &pfd)) {
		Dispose();
		Output::ErrorStr("Can't set the pixel format.");
	}

	hrc = wglCreateContext(hdc);
	if (!hrc) {
		Dispose();
		Output::ErrorStr("Failed to create opengl rendering context.");
	}
	if (!wglMakeCurrent(hdc, hrc)) {
		Dispose();
		Output::ErrorStr("Can't activate opengl rendering context.");
	}

	SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
}

////////////////////////////////////////////////////////////
/// Destructor
////////////////////////////////////////////////////////////
WindowUi::~WindowUi() {

}

////////////////////////////////////////////////////////////
/// Swap Buffers
////////////////////////////////////////////////////////////
void WindowUi::SwapBuffers() {
	::SwapBuffers(hdc);
}

////////////////////////////////////////////////////////////
/// Dispose
////////////////////////////////////////////////////////////
void WindowUi::Dispose() {
	if (fullscreen) {
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(true);
	}
	if (hrc) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hrc);
		hrc = NULL;
	}
	if (hdc && !ReleaseDC(hwnd, hdc)) {
		hdc = NULL;
	}
	if (hwnd && !DestroyWindow(hwnd)) {
		hwnd = NULL;
	}
	if (!UnregisterClass(_T("ARGSS Player"), hinstance)) {
		hinstance = NULL;
	}
}

////////////////////////////////////////////////////////////
/// Resize
////////////////////////////////////////////////////////////
void WindowUi::Resize(long nwidth, long nheight) {
	if (width != nwidth && height != nheight) {
		width = nwidth;
		height = nheight;
	}
}

////////////////////////////////////////////////////////////
/// Set title
////////////////////////////////////////////////////////////
void WindowUi::SetTitle(std::string title) {
	SetWindowText(hwnd, s2ws(title).c_str());
}

////////////////////////////////////////////////////////////
/// Toggle fullscreen
////////////////////////////////////////////////////////////
void WindowUi::ToggleFullscreen() {
	if (fullscreen) {
		DEVMODE devmode;
		devmode.dmSize = sizeof(DEVMODE);
		devmode.dmPelsWidth = width;
		devmode.dmPelsHeight = height;
		devmode.dmBitsPerPel = 32;
		devmode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;

		if (ChangeDisplaySettings(&devmode, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL) {
			Output::Warning("Failed to toggle fullscreen mode");
			return;
		}

		SetWindowLong(hwnd, GWL_STYLE, WS_POPUP);
		SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_APPWINDOW);

		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_FRAMECHANGED);
		ShowWindow(hwnd, SW_SHOW);

		long Style = GetWindowLong(hwnd, GWL_STYLE);
		SetWindowLong(hwnd, GWL_STYLE, Style | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);

		fullscreen = true;
	} else {

	}
}

////////////////////////////////////////////////////////////
/// Get Width
////////////////////////////////////////////////////////////
long WindowUi::GetWidth() {
	return width;
}

////////////////////////////////////////////////////////////
/// Get Height
////////////////////////////////////////////////////////////
long WindowUi::GetHeight() {
	return height;
}

////////////////////////////////////////////////////////////
/// Get Event
////////////////////////////////////////////////////////////
bool WindowUi::GetEvent(Event& evnt) {
	if (hwnd && events.empty()) {
		MSG Message;
		while (PeekMessage(&Message, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	if (!events.empty()) {
		evnt = events.front();
		events.pop();

		return true;
	}

	return false;
}

////////////////////////////////////////////////////////////
/// Process events
////////////////////////////////////////////////////////////
int WindowUi::ProccesEvents(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Event evnt;
	long param1;
	switch (uMsg) {
	case WM_ACTIVATE:
		if (HIWORD(wParam)) {
			evnt.type = Event::LostFocus;
		} else {
			evnt.type = Event::GainFocus;
		}
		events.push(evnt);
		return 0;

	case WM_SETFOCUS:
		evnt.type = Event::GainFocus;
		events.push(evnt);
		return 0;

	case WM_KILLFOCUS:
		evnt.type = Event::LostFocus;
		events.push(evnt);
		return 0;

	case WM_SYSCOMMAND:
		switch (wParam) {
		case SC_SCREENSAVE:
		case SC_MONITORPOWER:
			return 0;
		}
		break;

	case WM_CLOSE:
		evnt.type = Event::Quit;
		events.push(evnt);
		return 0;

	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		evnt.type = Event::KeyDown;
		param1 = VK2IK(wParam);
		switch (param1) {
		case Input::Keys::LSHIFT:
		case Input::Keys::RSHIFT:
			evnt.param1 = Input::Keys::SHIFT;
			events.push(evnt);
		case Input::Keys::LCTRL:
		case Input::Keys::RCTRL:
			evnt.param1 = Input::Keys::CTRL;
			events.push(evnt);
		case Input::Keys::LALT:
		case Input::Keys::RALT:
			evnt.param1 = Input::Keys::ALT;
			events.push(evnt);
		}
		evnt.param1 = param1;
		events.push(evnt);
		keys[param1] = true;
		return 0;

	case WM_KEYUP:
	case WM_SYSKEYUP:
		evnt.type = Event::KeyUp;
		param1 = VK2IK(wParam);
		switch (param1) {
		case Input::Keys::LSHIFT:
		case Input::Keys::RSHIFT:
			evnt.param1 = Input::Keys::SHIFT;
			events.push(evnt);
		case Input::Keys::LCTRL:
		case Input::Keys::RCTRL:
			evnt.param1 = Input::Keys::CTRL;
			events.push(evnt);
		case Input::Keys::LALT:
		case Input::Keys::RALT:
			evnt.param1 = Input::Keys::ALT;
			events.push(evnt);
		}
		evnt.param1 = param1;
		events.push(evnt);
		keys[param1] = false;
		return 0;

	case WM_MOUSEWHEEL:
		mouse_wheel = GET_WHEEL_DELTA_WPARAM(wParam);
		return 0;

	case WM_LBUTTONDOWN:
		keys[Input::Keys::MOUSE_LEFT] = true;
		return 0;

	case WM_LBUTTONUP:
		keys[Input::Keys::MOUSE_LEFT] = false;
		return 0;

	case WM_RBUTTONDOWN:
		keys[Input::Keys::MOUSE_RIGHT] = true;
		return 0;

	case WM_RBUTTONUP:
		keys[Input::Keys::MOUSE_RIGHT] = false;
		return 0;

	case WM_MBUTTONDOWN:
		keys[Input::Keys::MOUSE_MIDDLE] = true;
		return 0;

	case WM_MBUTTONUP:
		keys[Input::Keys::MOUSE_MIDDLE] = false;
		return 0;

	case WM_XBUTTONDOWN:
		if (HIWORD(wParam) == XBUTTON1) {
			keys[Input::Keys::MOUSE_XBUTTON1] = true;
		} else {
			keys[Input::Keys::MOUSE_XBUTTON2] = true;
		}
		return 0;

	case WM_XBUTTONUP:
		if (HIWORD(wParam) == XBUTTON1) {
			keys[Input::Keys::MOUSE_XBUTTON1] = false;
		} else {
			keys[Input::Keys::MOUSE_XBUTTON2] = false;
		}
		return 0;

	case WM_MOUSEMOVE:
		mouse_focus = true;
		mouse_x = LOWORD(lParam);
		mouse_y = HIWORD(lParam);
		return 0;

	case WM_MOUSELEAVE:
		mouse_focus = false;
		return 0;
	}
	return 1;
}

////////////////////////////////////////////////////////////
/// Virtual Keys to InputKey
////////////////////////////////////////////////////////////
Input::Keys::InputKey WindowUi::VK2IK(int vk) {
	switch (vk) {
	case VK_BACK		: return Input::Keys::BACKSPACE;
	case VK_TAB			: return Input::Keys::TAB;
	case VK_CLEAR		: return Input::Keys::CLEAR;
	case VK_RETURN		: return Input::Keys::RETURN;
	case VK_PAUSE		: return Input::Keys::PAUSE;
	case VK_ESCAPE		: return Input::Keys::ESCAPE;
	case VK_SPACE		: return Input::Keys::SPACE;
	case VK_NEXT		: return Input::Keys::PGUP;
	case VK_PRIOR		: return Input::Keys::PGDN;
	case VK_END			: return Input::Keys::ENDS;
	case VK_HOME		: return Input::Keys::HOME;
	case VK_LEFT		: return Input::Keys::LEFT;
	case VK_UP			: return Input::Keys::UP;
	case VK_RIGHT		: return Input::Keys::RIGHT;
	case VK_DOWN		: return Input::Keys::DOWN;
	case VK_SNAPSHOT	: return Input::Keys::SNAPSHOT;
	case VK_INSERT		: return Input::Keys::INSERT;
	case VK_DELETE		: return Input::Keys::DEL;
	case VK_SHIFT		: return Input::Keys::SHIFT;
	case VK_LSHIFT		: return Input::Keys::LSHIFT;
	case VK_RSHIFT		: return Input::Keys::RSHIFT;
	case VK_CONTROL		: return Input::Keys::CTRL;
	case VK_LCONTROL	: return Input::Keys::LCTRL;
	case VK_RCONTROL	: return Input::Keys::RCTRL;
	case VK_MENU		: return Input::Keys::ALT;
	case VK_LMENU		: return Input::Keys::LALT;
	case VK_RMENU		: return Input::Keys::RALT;
	case '0'			: return Input::Keys::N0;
	case '1'			: return Input::Keys::N1;
	case '2'			: return Input::Keys::N2;
	case '3'			: return Input::Keys::N3;
	case '4'			: return Input::Keys::N4;
	case '5'			: return Input::Keys::N5;
	case '6'			: return Input::Keys::N6;
	case '7'			: return Input::Keys::N7;
	case '8'			: return Input::Keys::N8;
	case '9'			: return Input::Keys::N9;
	case 'A'			: return Input::Keys::A;
	case 'B'			: return Input::Keys::B;
	case 'C'			: return Input::Keys::C;
	case 'D'			: return Input::Keys::D;
	case 'E'			: return Input::Keys::E;
	case 'F'			: return Input::Keys::F;
	case 'G'			: return Input::Keys::G;
	case 'H'			: return Input::Keys::H;
	case 'I'			: return Input::Keys::I;
	case 'J'			: return Input::Keys::J;
	case 'K'			: return Input::Keys::K;
	case 'L'			: return Input::Keys::L;
	case 'M'			: return Input::Keys::M;
	case 'N'			: return Input::Keys::N;
	case 'O'			: return Input::Keys::O;
	case 'P'			: return Input::Keys::P;
	case 'Q'			: return Input::Keys::Q;
	case 'R'			: return Input::Keys::R;
	case 'S'			: return Input::Keys::S;
	case 'T'			: return Input::Keys::T;
	case 'U'			: return Input::Keys::U;
	case 'V'			: return Input::Keys::V;
	case 'W'			: return Input::Keys::W;
	case 'X'			: return Input::Keys::X;
	case 'Y'			: return Input::Keys::Y;
	case 'Z'			: return Input::Keys::Z;
	case VK_LWIN		: return Input::Keys::LOS;
	case VK_RWIN		: return Input::Keys::ROS;
	case VK_APPS		: return Input::Keys::APPS;
	case VK_NUMPAD0		: return Input::Keys::KP0;
	case VK_NUMPAD1		: return Input::Keys::KP1;
	case VK_NUMPAD2		: return Input::Keys::KP2;
	case VK_NUMPAD3		: return Input::Keys::KP3;
	case VK_NUMPAD4		: return Input::Keys::KP4;
	case VK_NUMPAD5		: return Input::Keys::KP5;
	case VK_NUMPAD6		: return Input::Keys::KP6;
	case VK_NUMPAD7		: return Input::Keys::KP7;
	case VK_NUMPAD8		: return Input::Keys::KP8;
	case VK_NUMPAD9		: return Input::Keys::KP9;
	case VK_MULTIPLY	: return Input::Keys::MULTIPLY;
	case VK_ADD			: return Input::Keys::ADD;
	case VK_SEPARATOR	: return Input::Keys::SEPARATOR;
	case VK_SUBTRACT	: return Input::Keys::SUBTRACT;
	case VK_DECIMAL		: return Input::Keys::DECIMAL;
	case VK_DIVIDE		: return Input::Keys::DIVIDE;
	case VK_F1			: return Input::Keys::F1;
	case VK_F2			: return Input::Keys::F2;
	case VK_F3			: return Input::Keys::F3;
	case VK_F4			: return Input::Keys::F4;
	case VK_F5			: return Input::Keys::F5;
	case VK_F6			: return Input::Keys::F6;
	case VK_F7			: return Input::Keys::F7;
	case VK_F8			: return Input::Keys::F8;
	case VK_F9			: return Input::Keys::F9;
	case VK_F10			: return Input::Keys::F10;
	case VK_F11			: return Input::Keys::F11;
	case VK_F12			: return Input::Keys::F12;
	case VK_CAPITAL		: return Input::Keys::CAPS_LOCK;
	case VK_NUMLOCK		: return Input::Keys::NUM_LOCK;
	case VK_SCROLL		: return Input::Keys::SCROLL_LOCK;
	}
	return Input::Keys::InputKey(0);
}

////////////////////////////////////////////////////////////
/// Properties
////////////////////////////////////////////////////////////
bool WindowUi::IsFullscreen() {
	return fullscreen;
}
std::vector<bool> WindowUi::GetKeyStates() {
	return keys;
}
bool WindowUi::GetMouseFocus() {
	return mouse_focus;
}
int WindowUi::GetMouseWheel() {
	return mouse_wheel;
}
int WindowUi::GetMousePosX() {
	return mouse_x;
}
int WindowUi::GetMousePosY() {
	return mouse_y;
}

#endif
