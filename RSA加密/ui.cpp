#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "ui.h"

#define PI 3.1416

int r[3][4] = { {30,70,130,110},{170,70,220,110},{260,70,310,110} };
int title[] = { 0,10,480,50 };
int name[] = { 0,310,480,350 };
char text1[400] = { 0 };
unsigned long long text[400] = { 0 };
char out_text1[1000] = { 0 };
char fuzhi[1000];
wchar_t out_text[1000] = { 0 };
wchar_t out[10];
float jd;
char* endPtr;
int ch = 0;

int button_judge(int x, int y)
{
	if (x > r[0][0] && x<r[0][2] && y>r[0][1] && y < r[0][3])return 1;
	if (x > r[1][0] && x<r[1][2] && y>r[1][1] && y < r[1][3])return 2;
	if (x > r[2][0] && x<r[2][2] && y>r[2][1] && y < r[2][3])return 3;
	return 0;
}

void jindu(float a)
{
	wchar_t t[10];
	RECT r = { 370,85,400,115 };
	BeginBatchDraw();
	setrop2(R2_COPYPEN);
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	fillrectangle(354, 69, 411, 131);
	setlinestyle(PS_NULL);
	setbkmode(TRANSPARENT);
	setfillcolor(BLUE);
	setlinestyle(PS_NULL);
	fillpie(355, 70, 415, 130, 0, a * 2 * PI);
	setfillcolor(WHITE);
	fillcircle(385, 100, 20);
	swprintf(t, 10, L"%d%%", (int)(a * 100.0));
	wcscpy(out, t);
	drawtext(out, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	FlushBatchDraw();
}

void SetClipboardText(char* text) {
	if (OpenClipboard(NULL)) {
		EmptyClipboard();
		HGLOBAL hglbCopy = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
		char* lptstrCopy = (char*)GlobalLock(hglbCopy);
		strcpy(lptstrCopy, text);
		GlobalUnlock(hglbCopy);
		SetClipboardData(CF_TEXT, hglbCopy);
		CloseClipboard();
	}
}
