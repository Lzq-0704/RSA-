#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <conio.h>
#include <windows.h>
#include <math.h>
#include "rsa.h"
#include "ui.h"

int main()
{
	int i, event = 0;
	wchar_t s[200];
	short win_width, win_height;
	win_width = 480;
	win_height = 360;
	initgraph(win_width, win_height, NULL);
	for (i = 0; i < 256; i += 5)
	{
		setbkcolor(RGB(i, i, i));
		cleardevice();
		Sleep(8);
	}
	RECT TITLE = { title[0],title[1],title[2],title[3] };
	RECT R1 = { r[0][0],r[0][1],r[0][2],r[0][3] };
	RECT R2 = { r[1][0],r[1][1],r[1][2],r[1][3] };
	RECT R3 = { r[2][0],r[2][1],r[2][2],r[2][3] };
	RECT NAME = { name[0],name[1],name[2],name[3] };
	LOGFONT f;
	gettextstyle(&f);
	wcscpy(f.lfFaceName, L"宋体");
	f.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&f);
	settextcolor(BLACK);
	drawtext(L"RSA 加密算法计算器 version 11.4514.191.9810", &TITLE, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"计算公密钥", &R1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"加密", &R2, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"解密", &R3, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	drawtext(L"设计者：学生", &NAME, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	setlinecolor(BLACK);
	rectangle(r[0][0], r[0][1], r[0][2], r[0][3]);
	rectangle(r[1][0], r[1][1], r[1][2], r[1][3]);
	rectangle(r[2][0], r[2][1], r[2][2], r[2][3]);
	//初始化
	MOUSEMSG m;
	while (true)
	{
		m = GetMouseMsg();
		switch (m.uMsg)
		{
		case WM_MOUSEMOVE:
			setrop2(R2_XORPEN);
			setlinecolor(LIGHTCYAN);
			setlinestyle(PS_SOLID, 3);
			setfillcolor(WHITE);
			if (button_judge(m.x, m.y) != 0)
			{
				if (event != button_judge(m.x, m.y))
				{
					event = button_judge(m.x, m.y);
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
				}
			}
			else
			{
				if (event != 0)
				{
					fillrectangle(r[event - 1][0], r[event - 1][1], r[event - 1][2], r[event - 1][3]);
					event = 0;
				}
			}
			break;
		case WM_LBUTTONDOWN:
			switch (button_judge(m.x, m.y))
			{
			case 1:
			re:
				memset(text, 0, sizeof(text));
				memset(text1, 0, sizeof(text1));
				memset(out_text1, 0, sizeof(out_text1));
				memset(out_text, 0, sizeof(out_text));
				memset(s, 0, sizeof(s));
				//初始化
				InputBox(s, 30, L"请输入一个质数");
				swscanf(s, L"%llu", &p);
				while (sushu(p) == 0)
				{
					InputBox(s, 30, L"这不是质数，请重新输入");
					swscanf(s, L"%llu", &p);
				}
				InputBox(s, 30, L"请输入另一个质数");
				swscanf(s, L"%llu", &q);
				while (sushu(q) == 0)
				{
					InputBox(s, 30, L"这不是质数，请重新输入");
					swscanf(s, L"%llu", &q);
				}
				//输入并判断质数
				if (log2(p) + log2(q) > log2(LLONG_MAX))
				{
					MessageBox(NULL, L"数据过大,请重新输入", L"错误", MB_ICONHAND | MB_OK);
					goto re;
				}
				//若乘积超过longlong范围返回数字过大
				n = p * q;
				F_n = (p - 1) * (q - 1);
				for (e = 2; e < F_n; e++)
				{
					if (gcd(e, F_n) == 1)
					{
						break;
					}
				}
				//计算e
				if (e >= F_n)
				{
					MessageBox(NULL, L"参数不合理，请重新输入", L"错误", MB_ICONHAND | MB_OK);
					p = -1, q = -1, e = -1, d = -1, n = -1, F_n = -1;
					goto re;
				}
				//若不存在e返回参数不合理
				for (k = 1; k < e; k++) {
					if ((k * F_n + 1) % e == 0)
					{
						d = (k * F_n + 1) / e;
						break;
					}
				}
				//计算d
				if (k >= e)
				{
					MessageBox(NULL, L"参数不合理，请重新输入", L"问题", MB_ICONQUESTION | MB_OK);
					p = -1, q = -1, e = -1, d = -1, n = -1, F_n = -1;
					goto re;
				}
				//若不存在d返回参数不合理
				wchar_t str1[50];
				swprintf(str1, 50, L"公钥为(%llu,%llu)  私钥为(%llu,%llu)", e, n, d, n);
				wcscpy(out_text, str1);
				MessageBox(NULL, out_text, L"结果", MB_ICONINFORMATION | MB_OK);
				//输出公密钥
				FlushMouseMsgBuffer();
				break;
				//清空鼠标操作
			case 2:
				memset(text, 0, sizeof(text));
				memset(text1, 0, sizeof(text1));
				memset(out_text1, 0, sizeof(out_text1));
				memset(out_text, 0, sizeof(out_text));
				memset(fuzhi, 0, sizeof(fuzhi));
				memset(s, 0, sizeof(s));
				textlen = 0;
				//初始化
				if (e == -1 || n == -1)
				{
					InputBox(s, 60, L"未检测到公钥，请按此格式输入：(1,1)");
					while (swscanf(s, L"(%llu,%llu)%c", &e, &n, &w) != 2)
					{
						InputBox(s, 60, L"输入格式错误,请按此格式输入：(1,1)");
					}
				}
				//判断是否存在公钥
				else
				{
					ch = MessageBox(NULL, L"是否需要重新输入公钥", L"问题", MB_ICONQUESTION | MB_YESNO);
					if (ch == IDYES)
					{
						InputBox(s, 60, L"请按此格式输入公钥：(1,1)");
						while (swscanf(s, L"(%llu,%llu)%c", &e, &n, &w) != 2)
						{
							InputBox(s, 60, L"输入格式错误,请按此格式输入：(1,1)");
						}
					}
				}
				//询问是否重新输入
				InputBox(s, 200, L"请输入原文");
				swscanf(s, L"%[^\n]", text1);
				for (y = 0; y < 200; y++)
				{
					if (text1[y] != '\0')
					{
						text1[textlen] = text1[y];
						textlen++;
					}
				}
				text1[textlen] = '\0';
				//宽字符串转字符串处理
				for (x = 0; x < textlen; x++)
				{
					text[x] = mod((unsigned long long)text1[x], e, n);
					jd = (x + 1) / (2 * (float)textlen);
					jindu(jd);
				}
				//加密 C=(M^E)%N
				sprintf(out_text1, "加密结果为: ");
				for (x = 0; x < textlen; x++)
				{
					sprintf(out_text1 + strlen(out_text1), "%X ", text[x]);
					jd = 0.5 + (x + 1) / (2 * (float)textlen);
					jindu(jd);
				}
				//10进制数组转16进制字符串
				for (x = 12; out_text1[x] != '\0'; x++)
				{
					fuzhi[x - 12] = out_text1[x];
				}
				//复制内容去除前面文字
				SetClipboardText(fuzhi);
				sprintf(out_text1 + strlen(out_text1), "(已复制)");
				//复制
				MultiByteToWideChar(CP_ACP, 0, out_text1, -1, out_text, strlen(out_text1) + 1);
				MessageBox(NULL, out_text, L"结果", MB_ICONINFORMATION | MB_OK);
				//转格式并输出结果
				FlushMouseMsgBuffer();
				break;
				//清空鼠标操作
			case 3:
				memset(text, 0, sizeof(text));
				memset(text1, 0, sizeof(text1));
				memset(out_text1, 0, sizeof(out_text1));
				memset(out_text, 0, sizeof(out_text));
				memset(fuzhi, 0, sizeof(fuzhi));
				memset(s, 0, sizeof(s));
				textlen = 0;
				//初始化
				if (d == -1 || n == -1)
				{
					InputBox(s, 60, L"未检测到密钥，请按此格式输入：(1,1)");
					while (swscanf(s, L"(%llu,%llu)%c", &d, &n, &w) != 2)
					{
						InputBox(s, 60, L"输入格式错误,请按此格式输入：(1,1)");
					}
				}
				//判断是否存在密钥
				else
				{
					ch = MessageBox(NULL, L"是否需要重新输入密钥", L"问题", MB_ICONQUESTION | MB_YESNO);
					if (ch == IDYES)
					{
						InputBox(s, 60, L"请按此格式输入公钥：(1,1)");
						while (swscanf(s, L"(%llu,%llu)%c", &d, &n, &w) != 2)
						{
							InputBox(s, 60, L"输入格式错误,请按此格式输入：(1,1)");
						}
					}
				}
				//询问是否重新输入
				InputBox(s, 200, L"请输入密文");
				swscanf(s, L"%[^\n]", text1);
				for (y = 0; y < 200; y++)
				{
					if (text1[y] != '\0')
					{
						text1[textlen] = text1[y];
						textlen++;
					}
				}
				text1[textlen] = '\0';
				//宽字符串转字符串处理
				x = 0;
				endPtr = text1;
				for (x = 0; x < textlen; x++)
				{
					text[x] = strtol(endPtr, &endPtr, 16);
					text[x] = mod(text[x], d, n);
					jd = (x + 1) / (2 * (float)textlen);
					jindu(jd);
				}
				//读取16进制字符串转10进制数组并解密 M=(C^D)%N
				sprintf(out_text1, "解密结果为: ");
				for (x = 0; x < textlen; x++)
				{
					sprintf(out_text1 + strlen(out_text1), "%c", text[x]);
					jd = 0.5 + (x + 1) / (2 * (float)textlen);
					jindu(jd);
				}
				//数组转字符串
				for (x = 12; out_text1[x] != '\0'; x++)
				{
					fuzhi[x - 12] = out_text1[x];
				}
				//复制内容去除前面文字
				SetClipboardText(fuzhi);
				sprintf(out_text1 + strlen(out_text1), "(已复制)");
				//复制
				MultiByteToWideChar(CP_ACP, 0, out_text1, -1, out_text, strlen(out_text1) + 1);
				MessageBox(NULL, out_text, L"结果", MB_ICONINFORMATION | MB_OK);
				//转格式并输出结果
				FlushMouseMsgBuffer();
				break;
				//清空鼠标操作
			default:
				FlushMouseMsgBuffer();
				break;
				//清空鼠标操作
			}
			break;
			//点击按钮判断
		}
	}
	return 0;
}
