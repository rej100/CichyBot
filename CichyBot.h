#pragma once

#include <iostream>
#include <windows.h>

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

	HDC hdcSource;
	HDC hdcMemory;
	HBITMAP theBitmap;

	void Init();

	void UpdateBitmapDebugMoreCords(int x, int y, int w, int h);
	void UpdateBitmap(int w, int h, bool debugFlag);

	TdCords GetMousePos();
	void SetMousePos(TdCords cords);

	Colors GetPixelRGB(TdCords cords, HDC hDC);

	void LeftMbClick();
	void LeftMbDown();
	void LeftMbUp();

};

