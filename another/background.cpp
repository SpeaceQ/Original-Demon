

#include <time.h>
#include <Windows.h>
#include <stdio.h>
#include<bits/stdc++.h>

using namespace std;

typedef struct		//记录雨滴的结构体
{
	int x, y;
	char ch;
}RAINDROP;

const int BUFFER_SIZE = 100;
int WIDTH = 80;
int HEIGHT = 30;
const int RAIN_LENGTH = 18;

RAINDROP raindropLine[BUFFER_SIZE];
HANDLE HOUT=GetStdHandle(STD_OUTPUT_HANDLE);//获得标准输出的句柄

void gotoxy(int x, int y)			
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(HOUT, pos);
}

void show_cursor(BOOL hide)
{
	CONSOLE_CURSOR_INFO cciCursor;
	if (GetConsoleCursorInfo(HOUT,&cciCursor))//获得光标信息
	{
		cciCursor.bVisible=hide;
		SetConsoleCursorInfo(HOUT,&cciCursor);
	}
}

void set_color(int color2)
{
	SetConsoleTextAttribute(HOUT, color2);
}
void gotoxy(HANDLE hOut,int x,int y)//移动光标 
{
	COORD pos;
	pos.X=x;
	pos.Y=y;
	SetConsoleCursorPosition(hOut, pos);
}
void capital()//主菜单附加1
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleHeight=csbi.srWindow.Bottom-csbi.srWindow.Top+1;
	gotoxy(hConsole,0,consoleHeight-1);
	cout<<"66666666"<<endl;
}
void rain(){
	capital();
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(HOUT, &info);	//获得控制台窗体信息
	HEIGHT=info.srWindow.Bottom-1;			//根据控制台的宽高设置显示的宽高
	WIDTH=info.srWindow.Right;
	
	show_cursor(FALSE);
	srand((unsigned int)time(NULL));
	for (int i=0; i<BUFFER_SIZE; i++)			//随机设置雨滴下落的位置
	{
		raindropLine[i].x=rand()%WIDTH;
		raindropLine[i].y=rand()%HEIGHT;
		raindropLine[i].ch=rand()%2+48;				//设置雨滴内容0或1
	}
	
	while(true)				
	{
		GetConsoleScreenBufferInfo(HOUT, &info);	//当窗体大小变化时，重新设置宽高信息
		HEIGHT=info.srWindow.Bottom;
		WIDTH=info.srWindow.Right;
		for(int i=0;i<BUFFER_SIZE;++i)
		{
			if(raindropLine[i].y<=HEIGHT)
			{
				gotoxy(raindropLine[i].x, raindropLine[i].y);
//				set_color(FOREGROUND_GREEN);	//设置雨滴颜色
				set_color(8);
				putchar(raindropLine[i].ch);
			}
			gotoxy(raindropLine[i].x,raindropLine[i].y-RAIN_LENGTH);	//擦除过长的雨滴
			putchar(' ');
			raindropLine[i].y++;
			raindropLine[i].ch = rand() % 2 + 48;
			if(raindropLine[i].y>HEIGHT+RAIN_LENGTH)		
			{
				raindropLine[i].x=rand()%WIDTH;
				raindropLine[i].y=rand()%HEIGHT;
			}
			if(raindropLine[i].y<=HEIGHT)
			{
				gotoxy(raindropLine[i].x,raindropLine[i].y);
//				set_color(FOREGROUND_GREEN|FOREGROUND_INTENSITY);	//高亮最下方的雨滴
				set_color(15);
				putchar(raindropLine[i].ch);
			}
		}
		Sleep(50);
	}
	getchar();
}
int main()
{
	rain();
	return 0;
}
