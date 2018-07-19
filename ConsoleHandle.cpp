#include "ConsoleHandle.h"


const SHORT BLACK = 0;
const SHORT WHITE = 15;
const int COLORS = 16;

static CONSOLE Console;
static HANDLE consoleHandle1;
static HANDLE consoleHandle2;
static bool isSwap;
static CONSOLE_CURSOR_INFO cursorInfo;
static CONSOLE_SCREEN_BUFFER_INFO screenInfo;
static CHAR_INFO* buffer;

static void _swapConsoleHandle(void);
static void _createConsoleHandle(void);
static void _deleteConsoleHandle(void);
static void _print(const char str[], COORD coord, COORD size);
static void _clearScreen(void);
static HANDLE getHandle(void);


CONSOLE getInstance(void) 
{
	if (!Console) {
		Console = (CONSOLE)malloc(sizeof(*Console));
		Console->swapConsoleHandle = _swapConsoleHandle;
		Console->createConsoleHandle = _createConsoleHandle;
		Console->deleteConsoleHandle = _deleteConsoleHandle;
		Console->print = _print;
		Console->clearScreen = _clearScreen;
		Console->getHandle = getHandle;
	}
	return Console;
}
static void _swapConsoleHandle(void)
{
	SetConsoleActiveScreenBuffer(getHandle());
	isSwap = !isSwap;
}
static void _createConsoleHandle(void)
{
	//コンソールハンドルを作る
	consoleHandle1 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	consoleHandle2 = CreateConsoleScreenBuffer(
		GENERIC_READ | GENERIC_WRITE,
		0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle1, &cursorInfo);
	SetConsoleCursorInfo(consoleHandle2, &cursorInfo);

	GetConsoleScreenBufferInfo(getHandle(), &screenInfo);

	isSwap = false;         //取り敢えずfalseで初期化


	buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * screenInfo.dwSize.Y * screenInfo.dwSize.X); //バッファーを確保
																								//バッファーを初期化
	for (int y = 0; y < screenInfo.dwSize.Y; ++y)
	{
		for (int x = 0; x < screenInfo.dwSize.X; ++x)
		{
			buffer[y * (int)screenInfo.dwSize.X + x].Attributes = WHITE + (BLACK << 4);
			buffer[y * (int)screenInfo.dwSize.X + x].Char.UnicodeChar = ' ';
		}
	}
}
static void _deleteConsoleHandle(void) 
{

	free(buffer);
	CloseHandle(consoleHandle2);
	CloseHandle(consoleHandle1);
	free(Console);
}
static HANDLE getHandle(void) 
{

	return isSwap ? consoleHandle1 : consoleHandle2;
}

static void _print(const char str[],COORD coord, COORD size) 
{

	//COORD coord = { 0, 0 };                                                             //書き込みを開始する位置 x:0y:0に設定
	//COORD size = { screenInfo.dwSize.X,screenInfo.dwSize.Y };                           //サイズ
	SMALL_RECT rect = { coord.X, coord.Y, size.X, size.Y };   //書き込む箇所を矩形で指定
	int length = strlen(str);                                                           //文字の長さ
	for (int y = 0; y < screenInfo.dwSize.Y; ++y)
	{
		for (int x = 0; x < screenInfo.dwSize.X; ++x) 
		{
			buffer[y * (int)size.X + x].Char.UnicodeChar = str[x % (rand() % length + 1)];
			buffer[y * (int)size.X + x].Attributes = WHITE;/*rand() % COLORS + (rand() % COLORS << 4);*/
		}
	}

	WriteConsoleOutputA(getHandle(), buffer, size, coord, &rect);
}

void _clearScreen(void)
{
	DWORD   dwNumberOfCharsWritten; // 書き込まれたセル数
	COORD   coord = { 0, 0 };       //書き込みを開始する位置 x:0y:0に設定
	GetConsoleScreenBufferInfo(getHandle(), &screenInfo);
	// バッファ内の指定した座標から指定した数の文字セル分だけ、前景色と背景色を設定
	FillConsoleOutputAttribute(getHandle(),
		WHITE + (BLACK << 4),
		screenInfo.dwSize.X * screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
	// バッファ内の指定した座標から、指定した文字を指定した数だけ書き込む
	FillConsoleOutputCharacter(
		getHandle(),
		' ',
		screenInfo.dwSize.X * screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
}
