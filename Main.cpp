#include "Console.h"
#include "ConsoleHandle.h"

#define EXIT { exit(-1);}

#define SCREEN_WIDTH	(640)
#define SCREEN_HEIGHT	(480)

typedef struct
{
	int x, y;
}Mouse;

const SHORT WHITE = 15;

CHAR_INFO* buffer;

// console game
// sport : running
int main(void)
{
	Mouse mouse;

	COORD coord = { 0,0 };

	SHORT x = 3, y = 22;

	int cnt = 0;

	getInstance()->createConsoleHandle(); //����������

	SetConsoleTitle(TEXT("console game"));
	//SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//SetBackColor(COLOR_RED);
	//SetTextColor(COLOR_BLUE);
	while (1)
	{

		//GetCursorPosition(&mouse.x, &mouse.y);

		getInstance()->clearScreen(); //��ʂ̃N���A

		//ClearScreen();
		// ����ClearScreen
		//FillConsoleOutputCharacter(screen_data.hOutput, ' ', (screen_data.screenSize.X * screen_data.screenSize.Y), { 0,0 }, &word_num_buf);
		//FillConsoleOutputAttribute(screen_data.hOutput, screen_data.textAttributes, (screen_data.screenSize.X * screen_data.screenSize.Y), {0,0}, &word_num_buf);

		coord = { x,y };
		getInstance()->print("|", coord);

		coord = { x + 1,y };
		getInstance()->print(" ", coord);

		coord = { x,y + 3 };
		getInstance()->print(" ", coord);

		coord = { 0,25 };
		getInstance()->print("1", coord);		//�������o��

		// ���E�̈ړ�
		if (GetKeyInput() == KEY_LEFT)
		{
			x -= 1;
		}
		if (GetKeyInput() == KEY_RIGHT)
		{
			x += 1;
		}
		
		// �㉺�ړ��H
		if (GetKeyInput() == KEY_UP)
		{
			y -= 1;
		}
		if (GetKeyInput() == KEY_DOWN)
		{
			y += 1;
		}

		// ��ʊO�ɏo���甽�Α�����o�Ă���
		if (x > 119)
		{
			x = 0;
		}
		if (x < 0)
		{
			x = 119;
		}

		if (GetKeyInput() == KEY_ESC)
		{
			EXIT;
		}
		cnt++;

		getInstance()->swapConsoleHandle();		//�R���\�[���n���h�������ւ�

		//Sleep(50);
	}

	getInstance()->deleteConsoleHandle();     //���

	return 0;
}

