#pragma once

#ifndef _CONSOLE_HANDLE_H_
#define _CONSOLE_HANDLE_H_
#include <Windows.h>
#include<string.h>
#include<stdio.h>

typedef struct __CONSOLE 
{
	void(*swapConsoleHandle)(void); //����ւ�
	void(*createConsoleHandle)(void);   //������
	void(*deleteConsoleHandle)(void);   //��n��
	void(*print)(const char str[], COORD coord); //�������o��
	void(*clearScreen)(void);           //��ʂ��N���A
	HANDLE(*getHandle)(void);			//�n���h���擾
} *CONSOLE;

CONSOLE getInstance(void);

#endif //_CONSOLE_HANDLE_H_