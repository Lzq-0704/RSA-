#pragma once

extern int r[3][4];
extern int title[];
extern int name[];

extern char text1[400];
extern unsigned long long text[400];
extern char out_text1[1000];
extern char fuzhi[1000];
extern wchar_t out_text[1000];
extern wchar_t out[10];
extern float jd;
extern char* endPtr;
extern int ch;

int button_judge(int x, int y);
void jindu(float a);
void SetClipboardText(char* text);
