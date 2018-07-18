#pragma once

#ifndef _CONSOLE_HANDLE_H_
#define _CONSOLE_HANDLE_H_
#include <Windows.h>
#include<string.h>
#include<stdio.h>

typedef struct __CONSOLE 
{
	void(*swapConsoleHandle)(void); //入れ替え
	void(*createConsoleHandle)(void);   //初期化
	void(*deleteConsoleHandle)(void);   //後始末
	void(*print)(const char str[], COORD coord); //文字を出力
	void(*clearScreen)(void);           //画面をクリア
	HANDLE(*getHandle)(void);			//ハンドル取得
} *CONSOLE;

CONSOLE getInstance(void);

#endif //_CONSOLE_HANDLE_H_