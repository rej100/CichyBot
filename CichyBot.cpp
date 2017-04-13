#include "CichyBot.h"

void CichyBot::Init()
{
	hdcSource = GetDC(NULL);
	hdcMemory = CreateCompatibleDC(hdcSource);
	capX = GetDeviceCaps(hdcSource, HORZRES);
	capY = GetDeviceCaps(hdcSource, VERTRES);
}

void CichyBot::UpdateBitmapDebugMoreCords(int x, int y, int w, int h)
{
	HDC hdcSource = GetDC(NULL);
	HDC hdcMemory = CreateCompatibleDC(hdcSource);

	int capX = GetDeviceCaps(hdcSource, HORZRES);
	int capY = GetDeviceCaps(hdcSource, VERTRES);

	theBitmap = CreateCompatibleBitmap(hdcSource, w, h);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, theBitmap);

	BitBlt(hdcMemory, 0, 0, w, h, hdcSource, x, y, SRCCOPY);
	theBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, theBitmap);
	CloseClipboard();

	DeleteDC(hdcSource);
	DeleteDC(hdcMemory);
}

void CichyBot::UpdateBitmap(int w, int h, bool debugFlag)
{

	theBitmap = CreateCompatibleBitmap(hdcSource, xPad + w, yPad + h);
	HBITMAP hBitmapOld = (HBITMAP)SelectObject(hdcMemory, theBitmap);

	BitBlt(hdcMemory, 0, 0, xPad + w, yPad + h, hdcSource, xPad + 1, yPad + 1, SRCCOPY);
	theBitmap = (HBITMAP)SelectObject(hdcMemory, hBitmapOld);

	if (debugFlag)
	{
		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_BITMAP, theBitmap);
		CloseClipboard();
	}

}

TdCords CichyBot::GetMousePos()
{
	POINT p;
	GetCursorPos(&p);
	p.x -= xPad;
	p.y -= yPad;
	return TdCords(p.x, p.y);
}

void CichyBot::SetMousePos(TdCords cords)
{
	int reX = cords.x + xPad, reY = cords.y + yPad;

	SetCursorPos(reX, reY);
}

Colors CichyBot::GetPixelRGB(TdCords cords, HDC hDC)
{
	COLORREF pix;
	pix = GetPixel(hDC, cords.x + xPad, cords.y + yPad);

	unsigned int r = GetRValue(pix);
	unsigned int g = GetGValue(pix);
	unsigned int b = GetBValue(pix);

	return Colors(r, g, b);
}

//==========

void CichyBot::LeftMbClick()
{
	//std::cout << "LeftMB Click" << std::endl;

	INPUT input;

	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;

	SendInput(1, &input, sizeof(INPUT));
}

void CichyBot::LeftMbDown()
{
	//std::cout << "LeftMB Down" << std::endl;

	INPUT input;

	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;

	SendInput(1, &input, sizeof(INPUT));
}

void CichyBot::LeftMbUp()
{
	//std::cout << "LeftMB Up" << std::endl;

	INPUT input;
	input.type = INPUT_MOUSE;
	input.mi.dx = 0;
	input.mi.dy = 0;
	input.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTUP);
	input.mi.mouseData = 0;
	input.mi.dwExtraInfo = NULL;
	input.mi.time = 0;

	SendInput(1, &input, sizeof(INPUT));
}