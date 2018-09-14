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

void OpeningScene() {

	system("mode con cols=100 lines=24");
	FILE * f = fopen("opening.txt", "r");
	char a[10000];
	int i = 0;
	while (!feof(f)) {
		fgets(a, 1024, f);
		printf("%s", a);
		Sleep(2);
	}
	fclose(f);

	printf("\n");
	FILE * f2 = fopen("art.txt", "r");
	while (!feof(f2)) {
		a[i] = fgetc(f2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i % 2 == 1 ? 8 : 7);
		printf("%c", a[i++]);
		Sleep(1);
	}
	fclose(f2);

	printf("PRESS ANY KEY TO CONTINUE");
	getchar();
	//Sleep(4000);
	system("cls");

}


int main()
{
	int blockModel[10][4][4];

	LoadBlockModel(blockModel[0], 0);
	LoadBlockModel(blockModel[1], 1);
	LoadBlockModel(blockModel[2], 2);
	LoadBlockModel(blockModel[3], 3);

	OpeningScene();
	/*SetCurrentCursorPos(0, 10);
	ShowBlock(blockModel[0]);

	SetCurrentCursorPos(10, 10);
	ShowBlock(blockModel[1]);

	SetCurrentCursorPos(20, 10);
	ShowBlock(blockModel[2]);

	SetCurrentCursorPos(30, 10);
	ShowBlock(blockModel[3]);*/

	getchar();
	return 0;




}