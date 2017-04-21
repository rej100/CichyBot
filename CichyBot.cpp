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

/*

Colors CichyBot::GetPixelRGBb(TdCords cords, HBITMAP bitmap)
{
	capX = GetDeviceCaps(hdcSource, HORZRES);
	capY = GetDeviceCaps(hdcSource, VERTRES);

	BITMAP bm;
	GetObject(bitmap, sizeof(bm), &bm);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = ;
	bmi.biWidth = capX;
	bmi.biHeight = -capY;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;

	if (screenData)
		free(screenData);
	screenData = (BYTE*)malloc(4 * capX * capY);

	GetDIBits(hdcMemory, bitmap, 0, capY, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	unsigned int r = screenData[4 * ( ( (cords.y + xPad) * yPad ) + (cords.x + xPad) ) + 2];
	unsigned int g = screenData[4 * ( ( (cords.y + xPad) * yPad ) + (cords.x + xPad) ) + 1];
	unsigned int b = screenData[4 * ( ( (cords.y + xPad) * yPad ) + (cords.x + xPad) )];

	return Colors(r, g, b);
}

*/

/*
Colors CichyBot::GetPixelRGBb(TdCords cords, HBITMAP bitmap)
{
	BITMAP bm;
	GetObject(bitmap, sizeof(bm), &bm);

	BITMAPINFOHEADER bmi = { 0 };
	bmi.biSize = sizeof(BITMAPINFOHEADER);
	bmi.biPlanes = 1;
	bmi.biBitCount = 24;
	bmi.biWidth = bm.bmWidth;
	bmi.biHeight = -bm.bmHeight;
	bmi.biCompression = BI_RGB;
	bmi.biSizeImage = 0;

	if (screenData)
		free(screenData);
	screenData = (BYTE*)malloc(4 * bm.bmWidth * bm.bmHeight);
	
	GetDIBits(hdcMemory, bitmap, 0, bm.bmHeight, screenData, (BITMAPINFO*)&bmi, DIB_RGB_COLORS);

	unsigned int r = screenData[4 * ((cords.y * bm.bmWidth) + cords.x) + 2];
	unsigned int g = screenData[4 * ((cords.y * bm.bmWidth) + cords.x) + 1];
	unsigned int b = screenData[4 * ((cords.y * bm.bmWidth) + cords.x)];
	
	return Colors(r, g, b);
}
*/




Colors CichyBot::GetPixelRGBbitmap(TdCords cords, HBITMAP bitmap)
{
	
	BITMAP bi;

	//Get the Height and Width
	GetObject(bitmap, sizeof(bi), &bi);
	int Width = bi.bmWidth; int Height = bi.bmHeight;

	//Allocate and Initialize enough memory for external (Y-dimension) array
	//pixel.resize(Height);

	//Create a memory device context and place your bitmap
	HDC hDC = GetDC(dummyHWND);
	HDC hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, bitmap);

	COLORREF pix;

	pix = GetPixel(hMemDC, cords.x, cords.y);
	unsigned int r = GetRValue(pix);
	unsigned int g = GetGValue(pix);
	unsigned int b = GetBValue(pix);

	//Cleanup device contexts
	DeleteDC(hMemDC);
	ReleaseDC(dummyHWND, hDC);

	return Colors(r, g, b);
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



