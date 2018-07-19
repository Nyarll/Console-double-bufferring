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
	//�R���\�[���n���h�������
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

	isSwap = false;         //��芸����false�ŏ�����


	buffer = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * screenInfo.dwSize.Y * screenInfo.dwSize.X); //�o�b�t�@�[���m��
																								//�o�b�t�@�[��������
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

	//COORD coord = { 0, 0 };                                                             //�������݂��J�n����ʒu x:0y:0�ɐݒ�
	//COORD size = { screenInfo.dwSize.X,screenInfo.dwSize.Y };                           //�T�C�Y
	SMALL_RECT rect = { coord.X, coord.Y, size.X, size.Y };   //�������މӏ�����`�Ŏw��
	int length = strlen(str);                                                           //�����̒���
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
	DWORD   dwNumberOfCharsWritten; // �������܂ꂽ�Z����
	COORD   coord = { 0, 0 };       //�������݂��J�n����ʒu x:0y:0�ɐݒ�
	GetConsoleScreenBufferInfo(getHandle(), &screenInfo);
	// �o�b�t�@���̎w�肵�����W����w�肵�����̕����Z���������A�O�i�F�Ɣw�i�F��ݒ�
	FillConsoleOutputAttribute(getHandle(),
		WHITE + (BLACK << 4),
		screenInfo.dwSize.X * screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
	// �o�b�t�@���̎w�肵�����W����A�w�肵���������w�肵����������������
	FillConsoleOutputCharacter(
		getHandle(),
		' ',
		screenInfo.dwSize.X * screenInfo.dwSize.Y,
		coord,
		&dwNumberOfCharsWritten
	);
}
