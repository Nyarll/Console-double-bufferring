#include "Console.h"
#include "ConsoleHandle.h"

#define EXIT { exit(-1);}

#define SCREEN_WIDTH	(640)
#define SCREEN_HEIGHT	(480)

typedef struct
{
	int x, y;
}Mouse;

// console game
// sport : running
int main(void)
{
	Mouse mouse;

	COORD coord = { 0,0 };
	
	int cnt = 0;

	getInstance()->createConsoleHandle(); //����������

	SetConsoleTitle(TEXT("console game"));
	//SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//SetBackColor(COLOR_RED);
	//SetTextColor(COLOR_BLUE);
	while (1)
	{

		GetCursorPosition(&mouse.x, &mouse.y);

		getInstance()->clearScreen(); //��ʂ̃N���A

		//ClearScreen();
		// ����ClearScreen
		//FillConsoleOutputCharacter(screen_data.hOutput, ' ', (screen_data.screenSize.X * screen_data.screenSize.Y), { 0,0 }, &word_num_buf);
		//FillConsoleOutputAttribute(screen_data.hOutput, screen_data.textAttributes, (screen_data.screenSize.X * screen_data.screenSize.Y), {0,0}, &word_num_buf);

		coord = { 0,25 };
		getInstance()->print("1", coord);		//�������o��

		getInstance()->swapConsoleHandle();		//�R���\�[���n���h�������ւ�

		//if (GetKeyInput() == KEY_LEFT)
		//{
		//	printf(":::::::\n");
		//	printf(":::::::\n");
		//	printf(":::::::\n");
		//}
		//else
		//{
		//	//SetCursorPosition(x, y);
		//	printf("�� �� ��\n");
		//	y += 1;
		//	//SetCursorPosition(x, y);
		//	printf("��   ��\n");
		//	y += 1;
		//	//SetCursorPosition(x, y);
		//	printf("�� �� ��\n");
		//}

		if (GetKeyInput() == KEY_ESC)
		{
			EXIT;
		}
		cnt++;

		Sleep(50);
	}

	getInstance()->deleteConsoleHandle();     //���

	return 0;
}

