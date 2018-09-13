#include <stdio.h>
#include <windows.h>

void SetCurrentCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

COORD GetCurrentCursorPos(void)

{

	COORD curPoint;

	CONSOLE_SCREEN_BUFFER_INFO curInfo;



	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

	curPoint.X = curInfo.dwCursorPosition.X;

	curPoint.Y = curInfo.dwCursorPosition.Y;



	return curPoint;

}
void ShowBlock(int blockInfo[4][4])
{

	int x, y;

	COORD curPos = GetCurrentCursorPos();

	for (y = 0; y<4; y++)

	{

		for (x = 0; x<4; x++)

		{

			SetCurrentCursorPos(curPos.X + (x * 2), curPos.Y + y);
			if (blockInfo[y][x] == 1)

				printf("бс");

		}

	}

	SetCurrentCursorPos(curPos.X, curPos.Y);

}
void LoadBlockModel(int arr[4][4], int key) {

	int index = key * 26;
	char tmp[4][4];
	FILE * f = fopen("block.txt", "r");
	fseek(f, index, 0);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {

			fscanf(f, "%c", &tmp[i][j]);

			if (tmp[i][j] == '\n') {
				j--;
				continue;
			}
			arr[i][j] = tmp[i][j]-'0';
		}

	fclose(f);
}


int main()
{
	int blockModel[10][4][4];
	FILE * f = fopen("block.txt","r");
	
	LoadBlockModel(blockModel[0], 0);
	LoadBlockModel(blockModel[1], 1);
	LoadBlockModel(blockModel[2], 2);
	LoadBlockModel(blockModel[3], 3);


	SetCurrentCursorPos(0, 10);
	ShowBlock(blockModel[0]);

	SetCurrentCursorPos(10, 10);
	ShowBlock(blockModel[1]);

	SetCurrentCursorPos(20, 10);
	ShowBlock(blockModel[2]);

	SetCurrentCursorPos(30, 10);
	ShowBlock(blockModel[3]);

	getchar();
	return 0;




}