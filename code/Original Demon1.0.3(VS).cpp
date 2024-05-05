//#include<bits/stdc++.h>
#include <stdexcept>
#include<iostream>
#include<cstdio>
#include<conio.h>
#include<sstream>
#include<time.h>
#include<windows.h>
#include<sys/stat.h>
#include<io.h>
#include<thread>
#include<atomic>
#include <locale>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>

#define S(n) Sleep(n)
const int N = 5;
const std::string filePath1 = "C:\\Windows\\u006cu007au0068u0030u0030u0039.txt";
bool isRainRunning = true;
volatile bool stopBeep = false;
typedef LONG(NTAPI* _NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI* _NtResumeProcess)(IN HANDLE ProcessHandle);
HWND hwnd;

typedef struct
{
	int x, y;
	char ch;
}RAINDROP;
const int BUFFER_SIZE = 100;
int WIDTH = 80;
int HEIGHT = 30;
const int RAIN_LENGTH = 18;
RAINDROP raindropLine[BUFFER_SIZE];
HANDLE HOUT = GetStdHandle(STD_OUTPUT_HANDLE);

using namespace std;


//将窗口设为全屏————————————————————————————————————
void full_screen()//设置全屏
{
	HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi2;
	GetConsoleScreenBufferInfo(hConsole1, &csbi2);
	SMALL_RECT windowSize = csbi2.srWindow;
	SetConsoleWindowInfo(hConsole1, TRUE, &windowSize);
	if (!hwnd)
		hwnd = GetForegroundWindow();
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
	//	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION);
	//	HWND hwnd = GetConsoleWindow();
	//	if (hwnd)
	//	{
	//		LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);
	//		SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP) & ~WS_SIZEBOX); // 移除大小调整边框
	//		SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
	//	}
}
void keep_top()//设置置顶
{
	full_screen();
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);
	if (hwnd)
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, cx, cy, 0);
}

//获取管理员权限并以管理员身份运行———————————————————————————
bool IsProcessRunAsAdmin()//检查管理员身份
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;
	BOOL b = AllocateAndInitializeSid(
		&NtAuthority,
		2,
		SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&AdministratorsGroup);
	if (b)
	{
		CheckTokenMembership(NULL, AdministratorsGroup, &b);
		FreeSid(AdministratorsGroup);
	}
	return b == TRUE;
}
bool AdminOk;
short GetAdmin(LPCSTR Param, int Showcmd)//获取管理员身份
{
	if (IsProcessRunAsAdmin())
	{
		AdminOk = true;
		return 0;
	}
	TCHAR Path[MAX_PATH];
	ZeroMemory(Path, MAX_PATH);
	::GetModuleFileName(NULL, Path, MAX_PATH);
	HINSTANCE res;
	wchar_t wideParam[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, Param, -1, wideParam, MAX_PATH);
	res = ShellExecute(NULL, L"runas", Path, wideParam, NULL, Showcmd);
	if ((unsigned long long)res > 32)
		return 1;
	else
	{
		AdminOk = false;
		return 0;
	}
}


//跳跃动画————————————————————————————————————
void start()
{
	system("cls");
	int sssss = 2;
	while (sssss--) {
		system("cls");
		cout <<
			"■■■■■■■■" << endl <<
			"■      ■" << endl <<
			"■ ■  ■ ■" << endl <<
			"■      ■" << endl <<
			"■      ■" << endl <<
			"■      ■" << endl <<
			"■■■■■■■■" << endl;
		Sleep(300);
		system("cls");
		cout << endl;
		cout <<
			"■■■■■■■■" << endl <<
			"■      ■" << endl <<
			"■ ■  ■ ■" << endl <<
			"■      ■" << endl <<
			"■      ■" << endl <<
			"■      ■" << endl <<
			"■■■■■■■■" << endl;
		Sleep(300);
	}
	system("cls");
	cout <<
		"■■■■■■■■" << endl <<
		"■      ■" << endl <<
		"■ ^  ^ ■" << endl <<
		"■      ■" << endl <<
		"■      ■" << endl <<
		"■      ■" << endl <<
		"■■■■■■■■" << endl;
}

//文件—————————————————————————————————————————
bool folderExists(const std::string& folderPath)//文件夹检查
{
	DWORD attributes = GetFileAttributesA(folderPath.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}
bool fileExists(const std::string& filePath)//文件检查
{
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(filePath.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return true;
	}
	return false;
}
bool deleteFolder(const std::string& folderPath)//删除文件夹
{
	if (!RemoveDirectoryA(folderPath.c_str())) {
		DWORD error = GetLastError();
		if (error == ERROR_DIR_NOT_EMPTY) {
			std::cerr << "Error: The directory is not empty." << std::endl;
		}
		else {
			std::cerr << "Error: Failed to delete the directory. Error code: " << error << std::endl;
		}
		return false;
	}
	return true;
}
void filepath()//重要文件
{
	std::ofstream outputFile1;
	outputFile1.open(filePath1);
	outputFile1 << "\u005c\u0075\u0037\u0032\u0034\u0038\u005c\u0075\u0036\u0037\u0034\u0033\u005c\u0075\u0035\u0066\u0035\u0032\u005c\u0075\u0030\u0030\u0036\u0063\u005c\u0075\u0030\u0030\u0037\u0061\u005c\u0075\u0030\u0030\u0036\u0038\u005c\u0075\u0030\u0030\u0033\u0030\u005c\u0075\u0030\u0030\u0033\u0030\u005c\u0075\u0030\u0030\u0033\u0039\u005c\u0075\u0036\u0032\u0034\u0030\u005c\u0075\u0036\u0037\u0030\u0039\u005c\u0075\u0030\u0030\u0032\u0030\u005c\u0075\u0030\u0030\u0036\u0038\u005c\u0075\u0030\u0030\u0037\u0034\u005c\u0075\u0030\u0030\u0037\u0034\u005c\u0075\u0030\u0030\u0037\u0030\u005c\u0075\u0030\u0030\u0037\u0033\u005c\u0075\u0030\u0030\u0033\u0061\u005c\u0075\u0030\u0030\u0032\u0066\u005c\u0075\u0030\u0030\u0032\u0066\u005c\u0075\u0030\u0030\u0037\u0037\u005c\u0075\u0030\u0030\u0037\u0037\u005c\u0075\u0030\u0030\u0037\u0037\u005c\u0075\u0030\u0030\u0032\u0065\u005c\u0075\u0030\u0030\u0036\u0063\u005c\u0075\u0030\u0030\u0037\u0035\u005c\u0075\u0030\u0030\u0036\u0066\u005c\u0075\u0030\u0030\u0036\u0037\u005c\u0075\u0030\u0030\u0037\u0035\u005c\u0075\u0030\u0030\u0032\u0065\u005c\u0075\u0030\u0030\u0036\u0033\u005c\u0075\u0030\u0030\u0036\u0066\u005c\u0075\u0030\u0030\u0036\u0064\u005c\u0075\u0030\u0030\u0032\u0065\u005c\u0075\u0030\u0030\u0036\u0033\u005c\u0075\u0030\u0030\u0036\u0065\u005c\u0075\u0030\u0030\u0032\u0066\u005c\u0075\u0030\u0030\u0037\u0035\u005c\u0075\u0030\u0030\u0037\u0033\u005c\u0075\u0030\u0030\u0036\u0035\u005c\u0075\u0030\u0030\u0037\u0032\u005c\u0075\u0030\u0030\u0032\u0066\u005c\u0075\u0030\u0030\u0033\u0039\u005c\u0075\u0030\u0030\u0033\u0035\u005c\u0075\u0030\u0030\u0033\u0032\u005c\u0075\u0030\u0030\u0033\u0038\u005c\u0075\u0030\u0030\u0033\u0031\u005c\u0075\u0030\u0030\u0033\u0034";
	outputFile1.close();
}

//颜色—————————————————————————————————————————
void color(int ForgC, int BackC)//ForgC是文字颜色，BackC是背景颜色
{
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void color2(int foreground, int background)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), foreground + (background << 4));
}

//开场动画———————————————————————————————————————
void middle(); void gotoxy(HANDLE hOut, int x, int y);
void printGradientA()//文字渐变1
{
	int colors[] = { 7,15,8,0,8,15,7 }; // 白、浅灰、灰、深灰、黑
	for (int i = 0; i < 7; ++i) {
		color2(colors[i], 7);  // 设置黑色文字和对应颜色的背景
		system("cls");
		middle();
		if (i == 3)
			S(3200);
		else S(50);
	}
	S(300);
	color2(0, 7);  // 恢复默认颜色（黑色文字，白色背景）
	cout << endl;  // 换行
}
int cmdd()//获取屏幕大小
{
	RECT rectDlg;
	GetWindowRect(GetConsoleWindow(), &rectDlg); // 获得窗体在屏幕上的位置和大小
	//	printf("窗口位置大小: 左: %d, 上: %d, 右: %d, 底: %d, 宽: %d, 高: %d\r\n",
	//		rectDlg.left, rectDlg.top, rectDlg.right, rectDlg.bottom, rectDlg.right - rectDlg.left, rectDlg.bottom - rectDlg.top);
	return rectDlg.bottom - rectDlg.top + 4;
}
void gotoxy(HANDLE hOut, int x, int y)//移动光标 
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
void middle()//输出至屏幕中央1
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int x = dwSizeX / 2 - 18;
	gotoxy(hOutput, x, cmdd());
	cout << "╭━━━╮╱╱╱╱╱╱╱╱╱╱╱╱╭╮╱╭━━━╮" << endl;
	gotoxy(hOutput, x, cmdd() + 1);
	cout << "┃╭━╮┃╱╱╱╱╱╱╱╱╱╱╱╱┃┃╱╰╮╭╮┃" << endl;
	gotoxy(hOutput, x, cmdd() + 2);
	cout << "┃┃╱┃┣━┳┳━━┳┳━╮╭━━┫┃╱╱┃┃┃┣━━┳╮╭┳━━┳━╮" << endl;
	gotoxy(hOutput, x, cmdd() + 3);
	cout << "┃┃╱┃┃╭╋┫╭╮┣┫╭╮┫╭╮┃┃╱╱┃┃┃┃┃━┫╰╯┃╭╮┃╭╮╮" << endl;
	gotoxy(hOutput, x, cmdd() + 4);
	cout << "┃╰━╯┃┃┃┃╰╯┃┃┃┃┃╭╮┃╰╮╭╯╰╯┃┃━┫┃┃┃╰╯┃┃┃┃" << endl;
	gotoxy(hOutput, x, cmdd() + 5);
	cout << "	╰━━━┻╯╰┻━╮┣┻╯╰┻╯╰┻━╯╰━━━┻━━┻┻┻┻━━┻╯╰╯" << endl;
	gotoxy(hOutput, x, cmdd() + 6);
	cout << "╱╱╱╱╱╱╱╭━╯┃" << endl;
	gotoxy(hOutput, x, cmdd() + 7);
	cout << "╱╱╱╱╱╱╱╰━━" << endl;
}
void middle2()//输出至屏幕中央2
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int x = dwSizeX / 2 - 11;
	gotoxy(hOutput, x, cmdd());
	cout << "╭╮╱╱╱╱╭╮╱╭━━━┳━━━┳━━━╮" << endl;
	gotoxy(hOutput, x, cmdd() + 1);
	cout << "┃┃╱╱╱╱┃┃╱┃╭━╮┃╭━╮┃╭━╮┃" << endl;
	gotoxy(hOutput, x, cmdd() + 2);
	cout << "┃┃╭━━━┫╰━┫┃┃┃┃┃┃┃┃╰━╯┃" << endl;
	gotoxy(hOutput, x, cmdd() + 3);
	cout << "┃┃┣━━┃┃╭╮┃┃┃┃┃┃┃┃┣━━╮┃" << endl;
	gotoxy(hOutput, x, cmdd() + 4);
	cout << "┃╰┫┃━━┫┃┃┃╰━╯┃╰━╯┣━━╯┃" << endl;
	gotoxy(hOutput, x, cmdd() + 5);
	cout << "╰━┻━━━┻╯╰┻━━━┻━━━┻━━━╯" << endl;
}
void printGradientB()//文字渐变2
{
	int colors[] = { 7,15,8,0,8,15,7 }; // 白、浅灰、灰、深灰、黑
	for (int i = 0; i < 7; ++i) {
		color2(colors[i], 7);  // 设置黑色文字和对应颜色的背景
		system("cls");
		middle2();
		if (i == 3)
			S(3200);
		else S(50);
	}
	S(300);
	color2(0, 7);  // 恢复默认颜色（黑色文字，白色背景）
	cout << endl;  // 换行
}
void middle0()//提示
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int x;
	int n = 116;
	x = dwSizeX / 2 - 58;
	gotoxy(hOutput, x, cmdd() - 1);
	while (n--) {
		cout << "-";
	}n = 116;
	x = dwSizeX / 2 - 49;
	gotoxy(hOutput, x, cmdd() + 1);
	cout << "有极少数的人在观看一些视觉影像时可能会突然癫痫发作，这些影响包括电玩游戏中出现的闪光或图形。" << endl;
	x = dwSizeX / 2 - 52;
	gotoxy(hOutput, x, cmdd() + 2);
	cout << "甚至连没有突然发病或癫痫史的人也可能具有些可能会在观看视频游戏时导致“光敏性癫痫发作”的未确诊症状。" << endl;
	x = dwSizeX / 2 - 52;
	gotoxy(hOutput, x, cmdd() + 3);
	cout << "癫痫症发作时可能有多种症状，包括头晕目眩、眼睛或面部抽搐、四肢痉挛或发抖、神志不清、混乱或暂时失去意识。" << endl;
	x = dwSizeX / 2 - 41;
	gotoxy(hOutput, x, cmdd() + 4);
	cout << "癫痫发作也可能导致意识丧失或痉挛，进而可能导致患者因跌倒或撞击到旁边的物体而受伤。" << endl;
	x = dwSizeX / 2 - 26;
	gotoxy(hOutput, x, cmdd() + 5);
	cout << "若出现以上所述任何症状，请立即停止该游戏并送医诊断。" << endl;
	x = dwSizeX / 2 - 58;
	gotoxy(hOutput, x, cmdd() + 7);
	while (n--) {
		cout << "-";
	}
	x = dwSizeX / 2 - 20;
	gotoxy(hOutput, x, cmdd() + 8); color(8, 7);
	cout << "请按任意键继续 Please press any key to continue" << endl;
	color(0, 7);
	_getch();
	system("cls");
	S(900);
}
void printGradient()//开始动画
{
	middle0();
	printGradientB();
	S(3000);
	printGradientA();
}

//随机数
double average_distance(const vector<int>& permutation)//打乱函数
{
	double distance_sum = 0;
	for (int i = 0; i < N; i++)
		distance_sum += abs(permutation[i] - i);
	return distance_sum / N;
}
int Random_numbers()//随机数生成函数
{
	std::random_device rd;
	std::mt19937 rng(rd());

	int N = 10; // 假设 N 是某个已定义的值

	// 第一种方法：使用 shuffle 函数
	std::vector<int> permutation(N);
	for (int i = 0; i < N; i++)
		permutation[i] = i;
	std::shuffle(permutation.begin(), permutation.end(), rng);
	int ans1 = average_distance(permutation);

	// 第二种方法：使用 uniform_int_distribution 和 swap 函数
	for (int i = 0; i < N; i++)
		permutation[i] = i;
	for (int i = 1; i < N; i++) {
		std::uniform_int_distribution<int> dist(0, i);
		int random_index = dist(rng);
		std::swap(permutation[i], permutation[random_index]);
	}
	int ans2 = average_distance(permutation);

	bool num1 = rand() % 2;
	ans2 = average_distance(permutation);
	return num1 ? ans1 : ans2;
}

//主要内容
void capital(); void rain(); void Gstart(bool pd);
void gotoxy2(HANDLE hConsole, int x, int y)//主菜单附加1-附加1
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(hConsole, coord);
}
void setCursorPosition(int x, int y) //主菜单附加1-附加2
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
enum Notes//音符定义
{
	qdo = 262, qre = 294, qmi = 330, qfa = 349, qso = 392, qla = 440, qsi = 494,
	do_ = 523, re = 578, mi = 659, fa = 698, so = 784, la = 880, si = 988,
	do1 = 1046, re1 = 1175, mi1 = 1318, fa1 = 1480, so1 = 1568, la1 = 1760, si1 = 1976,
	sqdo = 277, sqre = 311, sqfa = 370, sqso = 415, sqla = 466,
	sdo = 554, sre = 622, sfa = 740, sso = 831, sla = 932,
	sdo1 = 1046, sre1 = 1245, sfa1 = 1480, sso1 = 1661, sla1 = 1865
};
void background_music()//背景音乐
{
	int pai = 400, ban = 200;
	int ting = 128;
	while (!stopBeep)
	{
		Sleep(1000); Beep(la, ban); Beep(si, ban); Sleep(ting); Beep(do1, pai + ban); Beep(si, ban); Sleep(ting); Beep(do1, pai);
		Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(si, 3 * pai); Sleep(ting); Beep(mi, ban); Beep(mi, ban); Beep(la, ban + pai);
		Beep(so, ban); Sleep(ting); Beep(la, pai); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(so, 2 * pai); Sleep(ting); Sleep(pai);
		Beep(mi, ban); Sleep(ting / 2); Beep(mi, ban); Sleep(ting / 2); Beep(fa, pai + ban); Beep(mi, ban); Sleep(ting); Beep(fa, ban);
		Beep(do1, ban + pai); Sleep(ting); Beep(mi, 2 * pai); Sleep(ting); Sleep(ban); Beep(do1, ban); Sleep(ting / 2); Beep(do1, ban);
		Sleep(ting / 2); Beep(do1, ban); Sleep(ting / 2); Beep(si, ban + pai); Beep(sfa, ban); Sleep(ting); Beep(sfa, pai); Beep(si, pai);
		Sleep(ting); Beep(si, 2 * pai); Sleep(ting); Sleep(pai); Beep(la, ban); Beep(si, ban); Sleep(ting); Beep(do1, pai + ban); Beep(si, ban);
		Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(si, 2 * pai); Sleep(ting); Sleep(pai); Beep(mi, ban);
		Sleep(20); Beep(mi, ban); Sleep(ting); Beep(la, pai + ban); Beep(so, ban); Sleep(ting); Beep(la, pai); Sleep(ting); Beep(do1, pai);
		Sleep(ting); Beep(so, 3 * pai); Sleep(ting + ban); Beep(mi, ban); Sleep(ting / 2); Beep(fa, pai); Sleep(ting); Beep(do1, ban); Beep(si, ban);
		Sleep(20); Beep(si, pai); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(re1, ban); Sleep(20); Beep(re1, ban); Sleep(20); Beep(mi1, ban);
		Sleep(ting / 2); Beep(do1, pai); Sleep(ting + pai); Beep(do1, pai); Beep(si, ban); Sleep(ting); Beep(la, ban); Sleep(20); Beep(la, ban); Sleep(ting);
		Beep(si, pai); Sleep(ting); Beep(sso, pai); Sleep(ting); Beep(sso, 2 * pai); Sleep(ting + pai); Beep(do1, ban); Beep(re1, ban); Sleep(ting);
		Beep(mi1, pai + ban); Beep(re1, ban); Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(fa1, pai); Sleep(ting); Beep(re1, 2 * pai); Sleep(pai + ting);
		Beep(so, ban); Sleep(20); Beep(so, ban); Sleep(ting); Beep(do1, ban); Beep(si, ban); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(mi1, pai);
		Sleep(ting); Beep(mi1, 2 * pai); Sleep(ting + 2 * pai); Beep(la, ban); Beep(si, ban); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(si, pai);
		Sleep(ting); Beep(re1, ban); Sleep(20); Beep(re1, ban); Sleep(ting); Beep(do1, pai + ban); Beep(so, ban); Sleep(20); Beep(so, pai); Sleep(pai + ting);
		Beep(fa1, pai); Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(re1, pai); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(mi1, 4 * pai);
		Beep(mi1, pai * 2); Sleep(pai + ting); Beep(mi1, pai); Sleep(ting); Beep(la1, 2 * pai); Sleep(ting); Beep(so1, pai); Sleep(ting); Beep(so1, pai);
		Sleep(ting); Beep(mi1, ban); Sleep(ting / 2); Beep(re1, ban); Sleep(ting); Beep(do1, pai); Sleep(ting + ban); Beep(do1, ban); Sleep(ting);
		Beep(re1, pai); Sleep(ting); Beep(do1, ban); Beep(re1, ban); Sleep(20); Beep(re1, ban); Sleep(ting); Beep(so1, pai); Sleep(ting); Beep(mi1, 2 * pai);
		Sleep(ting + pai); Beep(mi, pai); Sleep(ting); Beep(la1, 2 * pai); Sleep(ting); Beep(so1, 2 * pai); Sleep(ting); Beep(mi1, ban); Beep(re1, ban);
		Sleep(ting); Beep(do1, 2 * pai); Sleep(ting + ban); Beep(do1, ban); Sleep(ting); Beep(re1, pai); Sleep(ting); Beep(do1, ban); Beep(re1, ban);
		Sleep(20); Beep(re1, ban); Sleep(ting); Beep(si, pai); Sleep(ting); Beep(la, 2 * pai); Sleep(ting); Beep(la, ban); Beep(si, ban); Beep(do1, pai + ban);
		Beep(si, ban); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(si, 3 * pai); Sleep(ting); Beep(mi, ban); Beep(mi, ban);
		Beep(la, ban + pai); Beep(so, ban); Sleep(ting); Beep(la, pai); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(so, 2 * pai); Sleep(ting); Sleep(pai);
		Beep(mi, ban); Sleep(ting / 2); Beep(mi, ban); Sleep(ting / 2); Beep(fa, pai + ban); Beep(mi, ban); Sleep(ting); Beep(fa, ban); Beep(do1, ban + pai);
		Sleep(ting); Beep(mi, 2 * pai); Sleep(ting); Sleep(ban); Beep(do1, ban); Sleep(ting / 2); Beep(do1, ban); Sleep(ting / 2); Beep(do1, ban); Sleep(ting / 2);
		Beep(si, ban + pai); Beep(sfa, ban); Sleep(ting); Beep(sfa, pai); Beep(si, pai); Sleep(ting); Beep(si, 2 * pai); Sleep(ting); Sleep(pai); Beep(la, ban);
		Beep(si, ban); Sleep(ting); Beep(do1, pai + ban); Beep(si, ban); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(mi1, pai); Sleep(ting); Beep(si, 2 * pai);
		Sleep(ting); Sleep(pai); Beep(mi, ban); Sleep(20); Beep(mi, ban); Sleep(ting); Beep(la, pai + ban); Beep(so, ban); Sleep(ting); Beep(la, pai);
		Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(so, 3 * pai); Sleep(ting + ban); Beep(mi, ban); Sleep(ting / 2); Beep(fa, pai); Sleep(ting); Beep(do1, ban);
		Beep(si, ban); Sleep(20); Beep(si, pai); Sleep(ting); Beep(do1, pai); Sleep(ting); Beep(re1, ban); Sleep(20); Beep(re1, ban); Sleep(20);
		Beep(mi1, ban); Sleep(ting / 2); Beep(do1, pai); Sleep(ting + pai); Beep(la, 4 * pai); Sleep(1000);
	}
}
void mainmenu()//主菜单
{
	system("cls");
	cout << "???" << endl;
	//	printGradient();
}
void capital()//主菜单附加1
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	int consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	gotoxy2(hConsole, 0, consoleHeight - 1);
	std::ifstream file(filePath1);
	std::string things;
	std::getline(file, things);
	file.close();
	cout << things << " ";
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	gotoxy(hOutput, 0, 0);
}
void title()//主菜单附加2
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	RECT rectDlg;
	GetWindowRect(GetConsoleWindow(), &rectDlg);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	gotoxy(hOutput, 0, 0);
	cout << "  ╔═╗─╔╗─╔╗────────╔══╗            ║";
	cout << "                               " << endl;
	gotoxy(hOutput, 0, 1);
	cout << "  ║║╠╦╬╬═╬╬═╦╦═╗╔╗─╚╗╗╠═╦══╦═╦═╦╗  ║" << endl;
	gotoxy(hOutput, 0, 2);
	cout << "  ║║║╔╣║╬║║║║║╬╚╣╚╗╔╩╝║╩╣║║║╬║║║║  ║" << endl;
	gotoxy(hOutput, 0, 3);
	cout << "  ╚═╩╝╚╬╗╠╩╩═╩══╩═╝╚══╩═╩╩╩╩═╩╩═╝  ║" << endl;
	gotoxy(hOutput, 0, 4);
	cout << "  ─────╚═╝                         ║" << endl;
	//	gotoxy(hOutput,0,5);
	//	cout<<"                                  ║"<<endl;
	gotoxy(hOutput, 0, 5);
	cout << "═══════════════════════════════════╝";
}
void gotoxy3(int x, int y)//主菜单附加3-附加3
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(HOUT, pos);
}
void show_cursor(BOOL hide)//主菜单附加3-附加1
{
	CONSOLE_CURSOR_INFO cciCursor;
	if (GetConsoleCursorInfo(HOUT, &cciCursor))
	{
		cciCursor.bVisible = hide;
		SetConsoleCursorInfo(HOUT, &cciCursor);
	}
}
void set_color(int color2)//主菜单附加3-附加2
{
	SetConsoleTextAttribute(HOUT, color2);
}
void rain()//主菜单附加3
{
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(HOUT, &info);
	HEIGHT = info.srWindow.Bottom - 1;
	WIDTH = info.srWindow.Right;

	show_cursor(FALSE);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		raindropLine[i].x = rand() % WIDTH;
		raindropLine[i].y = rand() % (HEIGHT);
		raindropLine[i].ch = rand() % 2 + 48;
	}

	while (isRainRunning)
	{
		//		capital();
		GetConsoleScreenBufferInfo(HOUT, &info);
		HEIGHT = info.srWindow.Bottom;
		WIDTH = info.srWindow.Right;
		for (int i = 0; i < BUFFER_SIZE; ++i)
		{
			title();
			capital();
			Gstart(false);
			if (raindropLine[i].y <= HEIGHT)
			{
				gotoxy3(raindropLine[i].x, raindropLine[i].y);
				set_color(0x70);
				putchar(raindropLine[i].ch);
			}
			gotoxy3(raindropLine[i].x, raindropLine[i].y - RAIN_LENGTH);
			putchar(' ');
			raindropLine[i].y++;
			raindropLine[i].ch = rand() % 2 + 48;
			if (raindropLine[i].y > HEIGHT + RAIN_LENGTH)
			{
				raindropLine[i].x = rand() % WIDTH;
				raindropLine[i].y = rand() % HEIGHT;
			}
			if (raindropLine[i].y <= HEIGHT)
			{
				gotoxy3(raindropLine[i].x, raindropLine[i].y);
				set_color(0x70);
				putchar(raindropLine[i].ch);
			}
		}
		Sleep(50);
	}
	//	getchar();
}
int lll1, lll2;
void Gstart(bool pd)//主菜单附加4
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int dwSizeY = bInfo.dwSize.Y;
	// 计算第4/5行的中间位置
	int y = dwSizeY * 4 / 5;
	int x = dwSizeX / 2 - 13;
	if (pd == true)
	{
		lll1 = x;
		lll2 = y;
	}
	gotoxy(hOutput, x, y - 2);
	cout << "                           " << endl;
	color(15, 0);
	gotoxy(hOutput, x, y - 1);
	cout << "  -----------------------  " << endl;
	gotoxy(hOutput, x, y);
	cout << "           START           " << endl;
	gotoxy(hOutput, x, y + 1);
	cout << "  -----------------------  " << endl;
	color(0, 7);
	gotoxy(hOutput, x, y + 2);
	cout << "                           " << endl;
}
void SetCursorHand()//主菜单附加5-附加1
{
	SetCursor(LoadCursor(NULL, IDC_HAND));
}
void SetCursorArrow()//主菜单附加5-附加2
{
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}
void Gstart2()//主菜单附加5
{
	INPUT_RECORD mouseRec;
	DWORD numEvents;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hInput, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	while (true) {
		/*
		if (mouseRec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED) {
		// 获取鼠标移动的位置
		COORD mousePos = mouseRec.Event.MouseEvent.dwMousePosition;
		// 处理鼠标移动事件
		if (mousePos.X >= lll1 && mousePos.X <= lll1 + 27  && mousePos.Y >= lll2-1 && mousePos.Y <= lll2 + 1) {
//				SetCursorHand(); // 鼠标移动到文字区域内，设置为小手
		}
		else{
		}
		}
		*/
		ReadConsoleInput(hInput, &mouseRec, 1, &numEvents);
		if (mouseRec.EventType == MOUSE_EVENT && mouseRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			// 获取鼠标点击的位置
			COORD mousePos = mouseRec.Event.MouseEvent.dwMousePosition;
			// 判断点击位置是否在文字区域内
			if (mousePos.X >= lll1 && mousePos.X <= lll1 + 27 && mousePos.Y == lll2) { // 这里假设文字的位置是(0, 0)到(9, 0)
				isRainRunning = false;
				system("cls");
				cout << "Text clicked!" << endl;
				break;
				goto code;
			}
		}
	}
code:;
	system("cls");
}

//剧情
void out(std::string s, int tim)//剧情文字输出
{
	tim *= 200;
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	int dwSizeX = bInfo.dwSize.X;
	int l = s.size();
	int x = dwSizeX / 2 - l / 2;
	int colors[] = { 7,8,0,8,7 }; // 白、浅灰、灰、深灰、黑
	for (int i = 0; i < 5; ++i) {
		gotoxy(hOutput, x, cmdd() + 3);
		color2(colors[i], 7);  // 设置黑色文字和对应颜色的背景
		cout << s << endl;
		if (i == 2)
			S(tim);
		else S(100);
	}
	S(300);
	color2(0, 7);  // 恢复默认颜色（黑色文字，白色背景）
	cout << endl;
}
void yinzi()//引子
{
	system("cls");
	S(900);
	std::string s[] = { "呜，是远处的号角声，","伴着风与雨的怒吼，透过簇簇秋菊传至这看似豪华的房屋","”明月千里共，宫囚一窗隔“，电闪下看见这一行字","白纸衬着浓墨，将使人倦怠的阴风送至这作诗者的心中","他不禁打了个寒颤","他悄悄地放下笔，掀开铺子，露出了一条隧道","......","大雨如倾盆般落下，伴着刀割似的狂风","十年的软囚，十年的丧兄之痛，十年的忍声吞气，十年的悲愤！","雨渐渐地大了，身后的火光却不见减弱","路是看不清的，也没有房屋，他走着，他只是走着，走在这泥泞的荒原里，走在这复仇的道路上，由着被囚禁过十年的心引领着......","“呜”，又是一声号角......" };
	for (int i = 0; i < 12; i++) {
		out(s[i], s[i].size());
		system("cls");
		S(450);
	}
}
void namec()
{
	cout << "请输入您的名字:";
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	GetConsoleScreenBufferInfo(hOutput, &bInfo);
	bool i = true;
	/*
	while(getch()){
	gotoxy(hOutput,8,0);
	if(i==true) cout<<"|"<<endl,i=false;
	else cout<<" "<<endl,i=true;
	}
	*/
	std::string s;
	cin >> s;
}
int main() {
	if (!fileExists(filePath1.c_str())) {
		filepath();
	}
	HWND hwnd2 = GetConsoleWindow();
	GetAdmin("", 1);
	full_screen();
	ShowWindow(hwnd2, SW_HIDE);
	keep_top();
	system("title 原魔(Original Demon)1.0.3");
	system("color 70");
	//	start();
	S(300);
	//	Gstart();
	printGradient();
	capital();
	//	thread beepThread(background_music);
	//	thread otherThread(mainmenu);
	//	otherThread.join();
	//	beepThread.join();
	Gstart(true);
	thread rain_thread(rain);
	Gstart2();
	rain_thread.join();
	system("cls");
	mainmenu();
	namec();
	yinzi();
	return 0;
}
