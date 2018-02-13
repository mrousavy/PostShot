#ifndef WINDOWHELPER_H
#define WINDOWHELPER_H

#include <QtCore>
#include <QDebug>

// Ignore hidden windows
#define IGNORE_HIDDEN
// Ignore windows with {0,0,0,0} coords
//#define IGNORE_NULLS
// Ignore windows without titles
#define IGNORE_NOTITLE

namespace WindowHelper
{
	struct WindowSpec
	{
	public:
		WindowSpec(QRect rect, int z, char* title)
			: dimensions(rect), zIndex(z), name(title) {}

		QRect dimensions;
		int zIndex;
		char* name;
	};

#ifdef Q_WS_WIN
#include <Windows.h>

	// Z Index counter
	static int currz;

	inline BOOL CALLBACK enumWindowsProc(
			__in  HWND hWnd,
			__in  LPARAM lParam)
	{
#ifdef IGNORE_HIDDEN
		if (!IsWindowVisible(hWnd))
			return TRUE;
#endif
#ifdef IGNORE_NOTITLE
		if (GetWindowTextLength(hWnd) == 0)
			return TRUE;
#endif

		auto windows = reinterpret_cast<QList<Window>*>(lParam);
		RECT rect;
		GetWindowRect(hWnd, &rect);

#ifdef IGNORE_NULLS
		if (rect.left == 0  && rect.top == 0 &&
			rect.right == 0 && rect.bottom == 0)
			return TRUE;
#endif

		Window window;
		window.rect = QRect(rect.left, rect.top, rect.right, rect.bottom);
		window.z = currz++;
		GetWindowText(hWnd, window.name, sizeof(window.name));
		windows->append(window);

		return TRUE;
	}

	inline QList<Window> getAllWindows()
	{
		currz = 0;
		QList<Window> windows;
		BOOL success = EnumWindows(enumWindowsProc, reinterpret_cast<LPARAM>(&windows));
		if (!success) throw std::runtime_error("Could not enumerate windows!");
		return windows;
	}

#elif defined(Q_OS_LINUX)
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>

	static Display* display;

	inline QList<WindowSpec> getAllWindows()
	{
		if (display == nullptr) display = XOpenDisplay(NULL);

		Atom clients = XInternAtom(display, "_NET_CLIENT_LIST" , true);
		Atom actualType;
		int format;
		unsigned long numItems, bytesAfter;
		unsigned char* data = 0;
		int status = XGetWindowProperty(display, DefaultRootWindow(display),
										clients, 0L, (~0L), false, AnyPropertyType,
										&actualType, &format, &numItems,
										&bytesAfter, &data);
		QList<WindowSpec> windows;
		if (status >= Success && numItems) {
			Q_ASSERT(format == 32);
			quint32* array = (quint32*) data;
			for (quint32 k = 0; k < numItems; k++) {
				Window wId = (Window) array[k];
				Window* root = nullptr;
				int x, y;
				unsigned int w, h, bw, d;
				XGetGeometry(display, wId, root, &x, &y, &w, &h, &bw, &d);
				WindowSpec window(QRect(x, y, w, h), 5, "TEST");
				windows.append(window); // TODO: Build QRect
			}
			XFree(data);
		}
		return windows;
	}
#endif

}

#endif // WINDOWHELPER_H
