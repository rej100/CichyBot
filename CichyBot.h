#pragma once

#include <iostream>
#include <windows.h>
#include <Gdiplus.h>
#include <vector>

struct vRGB
{
	vRGB()
		: R(0), G(0), B(0)
	{

	}

	vRGB(BYTE r, BYTE g, BYTE b)
		: R(r), G(b), B(b)
	{

	}
	

	BYTE R, G, B;
};

struct TdCords
{
	int x, y;
	TdCords(int x = 0, int y = 0)
		: x(x), y(y)
	{

	}

	TdCords operator- (TdCords& other)
	{
		int otX = x - other.x, otY = y - other.y;
		return TdCords(otX, otY);
	}

	TdCords operator+ (TdCords& other)
	{
		int otX = x + other.x, otY = y + other.y;
		return TdCords(otX, otY);
	}
};

struct Colors
{
	unsigned int r, g, b;
	Colors(int r = 0, int g = 0, int b = 0)
		: r(r), g(g), b(b)
	{

	}

	bool operator== (Colors other)
	{
		return r == other.r && g == other.g && b == other.b;
	}


	/*
	Colors operator- (Colors& other)
	{
	int otR = r - other.r, otG = g - other.g, otB = b - other.b;
	return Colors(otR, otG, otR);
	}

	Colors operator+ (Colors& other)
	{
	int otR = r + other.r, otG = g + other.g, otB = b + other.b;
	return Colors(otR, otG, otR);
	}
	*/
};

class CichyBot
{
public:
	int xPad = 0;
	int yPad = 0;

	int capX;
	int capY;
	BYTE* screenData = 0;

	HDC hdcSource;
	HDC hdcMemory;
	HBITMAP theBitmap;

	HWND dummyHWND = CreateWindowA("STATIC", "dummy", NIS_HIDDEN, 0, 0, 0, 0, NULL, NULL, NULL, NULL);

	void Init();

	void UpdateBitmapDebugMoreCords(int x, int y, int w, int h);
	void UpdateBitmap(int w, int h, bool debugFlag);

	HBITMAP CaptureToBitmap(TdCords upperLeft, TdCords lowerRight, bool debugFlag);

	Colors GetPixelRGBbitmap(TdCords cords, HBITMAP bitmap);
	//Colors GetPixelRGBb(TdCords cords, HBITMAP bitmap);
	Colors SumBitmapRGB(HBITMAP bitmap);

	TdCords GetMousePos();
	void SetMousePos(TdCords cords);

	Colors GetPixelRGB(TdCords cords, HDC hDC);

	void LeftMbClick();
	void LeftMbDown();
	void LeftMbUp();

};

