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
	COORD size = { 0,0 };

	SHORT x = 3, y = 22;

	int cnt = 0;

	BOOL j_flag = FALSE;

	SHORT vy = 0, ay = 0;

	getInstance()->createConsoleHandle(); //初期化処理
	SetCursorVisibility(CURSOR_INVISIBLE);

	SetConsoleTitle(TEXT("console game"));
	//SetScreenSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//SetBackColor(COLOR_RED);
	//SetTextColor(COLOR_BLUE);
	while (1)
	{

		//GetCursorPosition(&mouse.x, &mouse.y);

		getInstance()->clearScreen(); //画面のクリア
		SetCursorPosition(0, 0);
		//ClearScreen();
		// 実質ClearScreen
		//FillConsoleOutputCharacter(screen_data.hOutput, ' ', (screen_data.screenSize.X * screen_data.screenSize.Y), { 0,0 }, &word_num_buf);
		//FillConsoleOutputAttribute(screen_data.hOutput, screen_data.textAttributes, (screen_data.screenSize.X * screen_data.screenSize.Y), {0,0}, &word_num_buf);

		// 左右の移動
		if (GetKeyInput() == KEY_LEFT)
		{
			x -= 1;
		}
		if (GetKeyInput() == KEY_RIGHT)
		{
			x += 1;
		}
		
		/*if ((GetKeyInput() == KEY_SPACE) && (!j_flag))
		{
			j_flag = TRUE;
		}*/
		
		if (j_flag)
		{
			if (y > 18)
			{
				vy = -1;
			}
			else
			{
				j_flag = FALSE;
				vy = 1;
			}
		}

		if (GetKeyInput() == KEY_UP)
		{
			vy -= 1;
		}

		//vy += ay;
		//y += vy;

		//if(y)

		if ((y + 3) < 25)
		{
			y = 22;
			vy = 0;
		}

		//x -= 1;

		// 画面外に出たら反対側から出てくる
		if (x > 119)
		{
			x = 0;
		}
		if (x < 0)
		{
			x = 119;
		}

		if (y > 30)
		{
			x = 0;
		}
		if (x < 0)
		{
			y = 30;
		}


		if (GetKeyInput() == KEY_ESC)
		{
			EXIT;
		}
		cnt++;

		// Render

		coord = { x,y };
		size = { x + 1,y + 3 };
		getInstance()->print("|", coord, size);

		/*coord = { x + 1,y };
		size = 
		getInstance()->print(" ", coord);*/

		/*coord = { x,y + 3 };
		getInstance()->print(" ", coord);*/

		coord = { 0,25 };
		size = { 120,30 };
		getInstance()->print("1", coord, size);		//文字を出力

		// Flip
		getInstance()->swapConsoleHandle();		//コンソールハンドルを入れ替え

		//Sleep(50);
	}

	getInstance()->deleteConsoleHandle();     //解放

	return 0;
}

