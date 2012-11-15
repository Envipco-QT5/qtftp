/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "qguifunctions_wince.h"
#include <shellapi.h>
#include <QtCore/qlibrary.h>

QT_USE_NAMESPACE

struct AygSHINITDLGINFO
{
    DWORD dwMask;
    HWND  hDlg;
    DWORD dwFlags;
};

struct AygSIPINFO
{
    DWORD   cbSize;
    DWORD   fdwFlags;
    RECT    rcVisibleDesktop;
    RECT    rcSipRect;
    DWORD   dwImDataSize;
    void   *pvImData;
};

#ifndef SHIDIF_CANCELBUTTON
#define SHIDIF_CANCELBUTTON 0x0080
#endif

#ifndef SHIDIM_FLAGS
#define SHIDIM_FLAGS 0x0001
#endif

#ifndef SHIDIF_DONEBUTTON
#define SHIDIF_DONEBUTTON 0x0001
#endif
#ifndef SHIDIF_SIZEDLGFULLSCREEN
#define SHIDIF_SIZEDLGFULLSCREEN 0x0004
#endif

#ifndef SHFS_SHOWTASKBAR
#define SHFS_SHOWTASKBAR 0x0001
#endif
#ifndef SHFS_HIDETASKBAR
#define SHFS_HIDETASKBAR 0x0002
#endif
#ifndef SHFS_SHOWSIPBUTTON
#define SHFS_SHOWSIPBUTTON 0x0004
#endif
#ifndef SHFS_HIDESIPBUTTON
#define SHFS_HIDESIPBUTTON 0x0008
#endif
#ifndef SHFS_SHOWSTARTICON
#define SHFS_SHOWSTARTICON 0x0010
#endif
#ifndef SHFS_HIDESTARTICON
#define SHFS_HIDESTARTICON 0x0020
#endif

#ifndef SIPF_OFF
#define SIPF_OFF 0x00000000
#endif
#ifndef SIPF_ON
#define SIPF_ON 0x00000001
#endif

#ifndef SPI_SETSIPINFO
#define SPI_SETSIPINFO 224
#endif
#ifndef SPI_GETSIPINFO
#define SPI_GETSIPINFO 225
#endif

typedef BOOL (*AygInitDialog)(AygSHINITDLGINFO*);
typedef BOOL (*AygFullScreen)(HWND, DWORD);
typedef BOOL (*AygSHSipInfo)(UINT, UINT, PVOID, UINT);

static AygInitDialog ptrAygInitDialog = 0;
static AygFullScreen ptrAygFullScreen = 0;
static AygSHSipInfo  ptrAygSHSipInfo  = 0;
static bool aygResolved = false;

static void resolveAygLibs()
{
    if (!aygResolved) {
        aygResolved = true;
        QLibrary ayglib(QLatin1String("aygshell"));
        if (!ayglib.load())
            return;
        ptrAygInitDialog = (AygInitDialog) ayglib.resolve("SHInitDialog");
        ptrAygFullScreen = (AygFullScreen) ayglib.resolve("SHFullScreen");
        ptrAygSHSipInfo  = (AygSHSipInfo)  ayglib.resolve("SHSipInfo");
    }
}

struct DIBINFO : public BITMAPINFO
{
    RGBQUAD arColors[255];

    operator LPBITMAPINFO() { return (LPBITMAPINFO) this; }
    operator LPBITMAPINFOHEADER() { return &bmiHeader; }
    RGBQUAD* ColorTable() { return bmiColors; }
};

int qt_wince_GetDIBits(HDC /*hdc*/ , HBITMAP hSourceBitmap, uint, uint, LPVOID lpvBits, LPBITMAPINFO, uint)
{
    if (!lpvBits) {
        qWarning("::GetDIBits(), lpvBits NULL");
        return 0;
    }
    BITMAP bm;
    GetObject(hSourceBitmap, sizeof(BITMAP), &bm);
    bm.bmHeight = qAbs(bm.bmHeight);

    HBITMAP hTargetBitmap;
    void *pixels;

    BITMAPINFO dibInfo;
    memset(&dibInfo, 0, sizeof(dibInfo));
    dibInfo.bmiHeader.biBitCount = 32;
    dibInfo.bmiHeader.biClrImportant = 0;
    dibInfo.bmiHeader.biClrUsed = 0;
    dibInfo.bmiHeader.biCompression = BI_RGB;;
    dibInfo.bmiHeader.biHeight = -bm.bmHeight;
    dibInfo.bmiHeader.biWidth = bm.bmWidth;
    dibInfo.bmiHeader.biPlanes = 1;
    dibInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    dibInfo.bmiHeader.biSizeImage = bm.bmWidth * bm.bmHeight * 4;

    HDC displayDC = GetDC(NULL);
    if (!displayDC) {
        qWarning("::GetDIBits(), failed to GetDC");
        return 0;
    }

    int ret = bm.bmHeight;

    hTargetBitmap = CreateDIBSection(displayDC, (const BITMAPINFO*) &dibInfo, DIB_RGB_COLORS,
                                    (void**)&pixels, NULL, 0);
    if (!hTargetBitmap) {
        qWarning("::GetDIBits(), failed to CreateDIBSection");
        return 0;
    }

    HDC hdcSrc = CreateCompatibleDC(displayDC);
    HDC hdcDst = CreateCompatibleDC(displayDC);

    if (!(hdcDst && hdcSrc)) {
        qWarning("::GetDIBits(), failed to CreateCompatibleDC");
        ret = 0;
    }

    HBITMAP hOldBitmap1 = (HBITMAP) SelectObject(hdcSrc, hSourceBitmap);
    HBITMAP hOldBitmap2 = (HBITMAP) SelectObject(hdcDst, hTargetBitmap);

    if (!(hOldBitmap1 && hOldBitmap2)) {
        qWarning("::GetDIBits(), failed to SelectObject for bitmaps");
        ret = 0;
    }

    if (!BitBlt(hdcDst, 0, 0, bm.bmWidth, bm.bmHeight, hdcSrc, 0, 0, SRCCOPY)) {
        qWarning("::GetDIBits(), BitBlt failed");
        ret = 0;
    }

    SelectObject(hdcSrc, hOldBitmap1);
    SelectObject(hdcDst, hOldBitmap2);

    DeleteDC(hdcSrc);
    DeleteDC(hdcDst);

    ReleaseDC(NULL, displayDC);

    memcpy(lpvBits, pixels, dibInfo.bmiHeader.biSizeImage);

    DeleteObject(hTargetBitmap);
    return ret;
}

bool qt_wince_TextOutW(HDC hdc, int x, int y, LPWSTR lpString, UINT c)
{
    return ExtTextOutW(hdc, x, y, 0, NULL, lpString, c, NULL);
}


HINSTANCE qt_wince_ShellExecute(HWND hwnd, LPCTSTR, LPCTSTR file, LPCTSTR params, LPCTSTR dir, int showCmd)
{
    SHELLEXECUTEINFO info;
    info.hwnd = hwnd;
    info.lpVerb = L"Open";
    info.lpFile = file;
    info.lpParameters = params;
    info.lpDirectory = dir;
    info.nShow = showCmd;
    info.cbSize = sizeof(info);
    ShellExecuteEx(&info);
    return info.hInstApp;
}

// Clipboard --------------------------------------------------------
BOOL qt_wince_ChangeClipboardChain( HWND /*hWndRemove*/, HWND /*hWndNewNext*/ )
{
    return FALSE;
}

HWND qt_wince_SetClipboardViewer( HWND /*hWndNewViewer*/ )
{
    return NULL;
}


// Graphics ---------------------------------------------------------
COLORREF qt_wince_PALETTEINDEX( WORD /*wPaletteIndex*/)
{
    return 0;
}

BOOL qt_wince_TextOut( HDC hdc, int nXStart, int nYStart, LPCTSTR lpString, int cbString )
{
    return ExtTextOut( hdc, nXStart, nYStart - 16, 0, NULL, lpString, cbString, NULL );
}

// Internal Qt -----------------------------------------------------
bool qt_wince_is_platform(const QString &platformString) {
    TCHAR tszPlatform[64];
    if (SystemParametersInfo(SPI_GETPLATFORMTYPE,
                             sizeof(tszPlatform)/sizeof(*tszPlatform),tszPlatform,0))
      if (0 == _tcsicmp(reinterpret_cast<const wchar_t *> (platformString.utf16()), tszPlatform))
            return true;
    return false;
}

bool qt_wince_is_pocket_pc() {
    return qt_wince_is_platform(QString::fromLatin1("PocketPC"));
}

bool qt_wince_is_smartphone() {
       return qt_wince_is_platform(QString::fromLatin1("Smartphone"));
}
bool qt_wince_is_mobile() {
     return (qt_wince_is_smartphone() || qt_wince_is_pocket_pc());
}

bool qt_wince_is_high_dpi() {
    if (!qt_wince_is_pocket_pc())
        return false;
    HDC deviceContext = GetDC(0);
    int dpi = GetDeviceCaps(deviceContext, LOGPIXELSX);
    ReleaseDC(0, deviceContext);
    if ((dpi < 1000) && (dpi > 0))
        return dpi > 96;
    else
        return false;
}

void qt_wince_maximize(QWidget *widget)
{
    HWND hwnd = widget->winId();
    if (qt_wince_is_mobile()) {
        AygSHINITDLGINFO shidi;
        shidi.dwMask = SHIDIM_FLAGS;
        shidi.hDlg = hwnd;
        shidi.dwFlags = SHIDIF_SIZEDLGFULLSCREEN;
        if (widget->windowFlags() & Qt::WindowCancelButtonHint)
            shidi.dwFlags |= SHIDIF_CANCELBUTTON;
        if (widget->windowFlags() & Qt::WindowOkButtonHint)
            shidi.dwFlags |= SHIDIF_DONEBUTTON;
        resolveAygLibs();
        if (ptrAygInitDialog)
            ptrAygInitDialog(&shidi);
    } else {
        RECT r;
        SystemParametersInfo(SPI_GETWORKAREA, 0, &r, 0);
        MoveWindow(hwnd, r.top, r.left, r.right - r.left, r.bottom - r.top, true);
        SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong (hwnd, GWL_EXSTYLE) | WS_EX_NODRAG);
    }
}

void qt_wince_minimize(HWND hwnd)
{
    uint exstyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    uint style = GetWindowLongW(hwnd, GWL_STYLE);
    RECT rect;
    RECT crect = {0,0,0,0};
    GetWindowRect(hwnd, &rect);
    AdjustWindowRectEx(&crect, style & ~WS_OVERLAPPED, FALSE, exstyle);
    MoveWindow(hwnd, rect.left - crect.left, rect.top - crect.top, 0, 0, true);
    SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong (hwnd, GWL_EXSTYLE) | WS_EX_NODRAG);
#ifdef Q_OS_WINCE_WM
    ShowWindow(hwnd, SW_HIDE);
#else
    ShowWindow(hwnd, SW_MINIMIZE);
#endif
}

void qt_wince_hide_taskbar(HWND hwnd) {
    if (ptrAygFullScreen)
        ptrAygFullScreen(hwnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON);
}

void qt_wince_full_screen(HWND hwnd, bool fullScreen, UINT swpf) {
    resolveAygLibs();
    if (fullScreen) {
        QRect r = qApp->desktop()->screenGeometry(QWidget::find(hwnd));
        SetWindowPos(hwnd, HWND_TOP, r.left(), r.top(), r.width(), r.height(), swpf);
        if (ptrAygFullScreen)
            ptrAygFullScreen(hwnd, SHFS_HIDETASKBAR | SHFS_HIDESIPBUTTON | SHFS_HIDESTARTICON);
        if (!qt_wince_is_mobile()) {
            HWND handle = FindWindow(L"HHTaskBar", L"");
            if (handle) {
                ShowWindow(handle, 0);
                EnableWindow(handle, false);
            }
        }
    } else {
        if (ptrAygFullScreen)
            ptrAygFullScreen(hwnd, SHFS_SHOWTASKBAR | SHFS_SHOWSIPBUTTON | SHFS_SHOWSTARTICON);
        SetWindowPos(hwnd, 0, 0, 0, 0, 0, swpf);
        if (!qt_wince_is_mobile()) {
            HWND handle = FindWindow(L"HHTaskBar", L"");
            if (handle) {
                ShowWindow(handle, 1);
                EnableWindow(handle, true);
            }
        }
    }
}

void qt_wince_show_SIP(bool show)
{
    resolveAygLibs();
    if (!ptrAygSHSipInfo)
        return;

    AygSIPINFO si;
    memset(&si, 0, sizeof(si));
    si.cbSize = sizeof(si);
    ptrAygSHSipInfo(SPI_GETSIPINFO, 0, &si, 0);
    si.cbSize = sizeof(si);
    si.fdwFlags = (show ? SIPF_ON : SIPF_OFF);
    ptrAygSHSipInfo(SPI_SETSIPINFO, 0, &si, 0);
}
