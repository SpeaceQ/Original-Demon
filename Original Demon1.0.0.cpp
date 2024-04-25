```c
#include<bits/stdc++.h>
#include<conio.h>
#include<sstream>
#include<time.h>
#include<windows.h>
#include<sys/stat.h>
#include<io.h>

#define S(n) Sleep(n)
const int N=5;
typedef LONG(NTAPI *_NtSuspendProcess)(IN HANDLE ProcessHandle);
typedef LONG(NTAPI *_NtResumeProcess)(IN HANDLE ProcessHandle);
HWND hwnd;

std::string filee="C:\\GenSen";
std::string fileee[10],cundang[10];
using namespace std;

char choose;
std::string name;
std::string Juese[N][4],Wuqi[10][3];//1jian,2qiang,3gong
bool Juese2[N];

bool IsProcessRunAsAdmin()
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
short GetAdmin(LPCSTR Param, int Showcmd)
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
	res = ShellExecute(NULL, "runas", Path, Param, NULL, Showcmd);
	if ((unsigned long long)res > 32)
		return 1;
	else
	{
		AdminOk = false;
		return 0;
	}
}
bool folderExists(const std::string& folderPath) {
	DWORD attributes = GetFileAttributesA(folderPath.c_str());
	return (attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY));
}
bool fileExists(const std::string& filePath) {
	WIN32_FIND_DATAA findFileData;
	HANDLE hFind = FindFirstFileA(filePath.c_str(), &findFileData);
	if (hFind != INVALID_HANDLE_VALUE) {
		FindClose(hFind);
		return true;
	}
	return false;
}
bool deleteFolder(const std::string& folderPath) {
	if (!RemoveDirectoryA(folderPath.c_str())) {
		DWORD error = GetLastError();
		if (error == ERROR_DIR_NOT_EMPTY) {
			std::cerr << "Error: The directory is not empty." << std::endl;
		} else {
			std::cerr << "Error: Failed to delete the directory. Error code: " << error << std::endl;
		}
		return false;
	}
	return true;
}

void start();void mainmenu();
void cundang1(bool pd);void cundang3(std::string s,int n);
void gameimage(int n);
void color(int ForgC, int BackC) {
	WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void wenjianjia(int n){
	std::string s1=filee+to_string(n);
	if(deleteFolder(s1)){
		cout<<"文件夹初始化成功"<<endl;
	}
	else{
		cout<<"文件夹初始化失败"<<endl;
	}
	const char* path=s1.c_str();
	int result = mkdir(path);
	if (!result) {
		std::cout << "文件夹创建成功！" << std::endl;
	} else {
		std::cerr << "无法创建文件夹。" << std::endl;
	}
	std::string filePath1=s1+"\\Jinbi.txt";
	std::string filePath2=s1+"\\Juese.txt";
	std::string filePath3=s1+"\\Jindu.txt";
	std::ofstream outputFile1;
	outputFile1.open(filePath1);
	outputFile1<<"9900";
	std::ofstream outputFile2;
	outputFile2.open(filePath2);
	outputFile2<<"1 0 0 0 0 0";
	std::ofstream outputFile3;
	outputFile3.open(filePath3);
	outputFile3<<"0 0 0 0 0 0 1";
}
void anot(){
	Juese[1][0]="1";Juese[1][1]="9950";Juese[1][2]="8500";Juese[1][3]="大伟丘";Juese[1][4]="90";
	Juese[2][0]="1";Juese[2][1]="9930";Juese[2][2]="8500";Juese[2][3]="阿萨姆";Juese[2][4]="85";
	Juese[3][0]="2";Juese[3][1]="9850";Juese[3][2]="9000";Juese[3][3]="狂徒";Juese[3][4]="95";
	Juese[4][0]="2";Juese[4][1]="9970";Juese[4][2]="8000";Juese[4][3]="国王";Juese[4][4]="80";
	Juese[5][0]="3";Juese[5][1]="9940";Juese[5][2]="8700";Juese[5][3]="醉将";Juese[5][4]="50";
	Juese[6][0]="3";Juese[6][1]="9900";Juese[6][2]="8700";Juese[6][3]="彼得番";Juese[6][4]="95";
	
//	Wuqi[1][0]='1';
}
void optxt(){
	start();
	Sleep(750);
	cout<<"欢";S(300);
	cout<<"迎";S(300);
	cout<<"来";S(300);
	cout<<"到";S(300);
	cout<<"原";S(300);
	cout<<"魔";S(300);
	getch();
	system("cls");
}
void loading(int n){
	int m=5-n,s=n;
	cout<<"正在加载数据"<<endl;
	while(n--){cout<<"■■";}
	while(m--){cout<<"□□";}
	S(s*100+500-10*s);
	system("cls");
}
void opan(){
	optxt();
	cout<<"正在加载数据"<<endl;
	cout<<"□□□□□□□□□□";
	system("cls");
	anot();
	cundang1(false);
	cundang1(true);
}
bool fileExists1(const std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}
void cundang1(bool pd){
	int n=5;
	std::string cunnn="存档";
	while(n--){
//		cout<<(5-n)<<endl;
		std::string numb=to_string(5-n);
		fileee[5-n]=filee+numb;
//		cout<<fileee[5-n]<<endl;
		if (folderExists(fileee[5-n])){
			cundang[5-n]=cunnn+numb;
//			cout<<cundang[5-n];
			if(pd==true){
				cundang3(fileee[5-n],5-n);
			}
		}
		else {
			cundang[5-n]="+";
		}
		if(pd==false) loading(5-n);
	}
}
void cundang2(int n){
	std::string wenben="请问您确定要创建存档"+to_string(n)+"?";
	int msboxID1=MessageBoxA(NULL,wenben.c_str(),("提示"),MB_YESNO);
	if(msboxID1==IDYES){
		
//		cout<<fileee[n]<<endl;
//		bool flag=CreateDirectory(fileee[n].c_str(),NULL);
//		std::ofstream file1(fileee[n]+"\\Jinbi");
//		file1<<"0";
//		std::ofstream file2(fileee[n]+"\\Juese");
//		file2<<"Player";
		
		wenjianjia(n);
		cundang1(true);
		system("cls");
		mainmenu();
	}
}
void cundang3(std::string s,int n){
	std::string s1=s+"\\Jinbi.txt",s2=s+"\\Juese.txt",s3=s+"\\Jindu.txt";
	if(fileExists(s1)&&fileExists(s2)&&fileExists(s3)) ;
	else cundang[n]="!";
}
void cundang4(int n){
	int msboxID=MessageBoxA(NULL,("此存档已损坏!\n请问是否要使其成为一个新的存档"),("提示"),MB_YESNO|MB_ICONWARNING);
	if(msboxID==IDYES){
//		std::ofstream file1(fileee[n]+"\\Jinbi");
//		file1<<"0";
//		std::ofstream file2(fileee[n]+"\\Juese");
//		file2<<"Player";
		wenjianjia(n);
	}
}

void mijing1(int n){
	int i=2;
	int fff;
	int ffff=1200;
	std::istringstream(Juese[n][2])>>fff;
	cout<<"你的血量: "<<(10000-fff)<<"		"<<"怪物血量: "<<ffff<<endl;
	mijing1g:;
	if(ffff<=0){
		cout<<"你赢了!"<<endl;
		S(300);
		gameimage(1);
	}
//	cout<<"你的血量: "<<(10000-fff)<<"		"<<"怪物血量: "<<ffff;
	if(2>1){
		int num1=rand()%100;
		cout<<num1<<endl;
		if(num1==10){
			cout<<endl<<"怪物造成了暴击!"<<endl;
			fff+=20;
			i++;
			cout<<"您还剩:"<<(10000-fff)<<"点血"<<endl;
//			goto mijing1g;
		}
		else {
			cout<<endl<<"怪物对您造成了"<<10<<"点伤害!"<<endl;
			fff+=10;
			cout<<"您还剩"<<(10000-fff)<<"点血"<<endl;
//			goto mijing1g;
		}
	}
	if(4>3){
		cout<<"请问您是:"<<endl<<
		"1. 攻击"<<"	"<<"2. 逃跑";
		char chooses=getch();
		if(chooses>'2'||chooses<'1'){
			cout<<'\r'<<"1. 攻击"<<"	"<<"2. 逃跑";
		}
		else {
			cout<<endl;
			if(chooses=='1'){
				int l;
				std::istringstream(Juese[n][4])>>l;
				int num1=rand()%(100-l);
				cout<<num1<<endl;
				if(num1==1){
					cout<<"您对怪物造成了暴击!"<<endl;
					ffff-=1000;
				}
				else {
					ffff-=50;
					cout<<"怪物还剩:"<<ffff<<"点血"<<endl;
				}
				goto mijing1g;
			}
			else {
				cout<<"你逃跑了!"<<endl;
				S(300);
				gameimage(1);
			}
		}
	}
}
void gameimage(int n){
	if(n==1){
		m1:;
		system("cls");
		cout<<"1. 经验秘境"<<"		"<<"2. 金币秘境"<<endl;
		cout<<"---------------------------"<<endl;
		char chooses=getch();
		if(chooses>'2'||chooses<'1'){
			if(chooses>'9'||chooses<'1'){
				goto m1;
			}
			else {
				cout<<"没有这个选项!"<<endl;
				S(400);
				goto m1;
			}
		}
		else {
			m11 :;
			system("cls");
			cout<<"请选择您的角色:"<<endl;
			std::string str=filee+to_string(n)+"\\Juese.txt";
			std::ifstream file(str);
			int jus[N];
			for(int i=1;i<=N;i++){
				file>>jus[i];
				Juese2[jus[i]]=true;
			}
			for(int i=1;i<=N;i++){
				if(Juese2[i]==true)
					cout<<i<<". "<<Juese[i][3]<<endl;
				else {
					cout<<i<<". ";
					color(8,23);
					cout<<Juese[i][3]<<endl;
					color(0,7);
				}
			}
			chooses=getch();
			char nn=N+'0';
			if(chooses>nn||chooses<'1'){
				if(chooses>'9'||chooses<'0')
					goto m11;
				else {
					cout<<"没有这个角色！"<<endl;
					S(300);
					goto m11;
				}
			}
			else {
				int nu=chooses-'0';
				if(Juese2[nu]==false){
					cout<<"您还没有获得这个角色！"<<endl;
				}
				else {
					mijing1(nu);
				}
			}
		}
	}
}
void gamemenuimage(std::string strl){
	system("cls");
	std::string title="title 原魔(Original Demon)1.0.0 欢迎"+strl;
	system(title.c_str());
	cout<<
	" Ｍ　Ｍ　　　　　　ｉ　　　　　　Ｍ　Ｍ"<<endl<<
	" ＭＭＭ　　　　　　　　　　　　　ＭＭＭ"<<endl<<
	" ＭＭＭ　　ａａ　ｉｉ　　ｎｎ　　ＭＭＭ　　ｅ　　ｕ　ｕ　ｎｎ"<<endl<<
	" Ｍ　Ｍ　ａ　ａ　　ｉ　　ｎ　ｎ　Ｍ　Ｍ　ｅ　ｅ　ｕ　ｕ　ｎ　ｎ"<<endl<<
	" Ｍ　Ｍ　ａ　ａ　　ｉ　　ｎ　ｎ　Ｍ　Ｍ　ｅｅ　　ｕ　ｕ　ｎ　ｎ"<<endl<<
	" Ｍ　Ｍ　　ａａ　ｉｉｉ　ｎ　ｎ　Ｍ　Ｍ　　ｅｅ　　ｕｕ　ｎ　ｎ"<<endl;
	cout<<
	"---------------------------------------------------------------"<<endl;
	cout<<
	"---------------------------------------------------------------"<<endl;
	cout<<"名字: "<<strl<<endl;
	cout<<"等级: "<<" "<<endl;
	cout<<
	"---------------------------------------------------------------"<<endl;
	cout<<"1. 秘境"<<"		"<<"2. 人物"<<"		"<<"3. 任务"<<"		"<<"4. 设置"<<endl;
	cout<<"5. 商店"<<"		"<<"6. 背包"<<"		"<<endl;
	cout<<
	"---------------------------------------------------------------"<<endl;
	
}
void gamemenu(bool pd,int n){
//	int originalStdinFD=dup(fileno(stdin));
//	int old=_dup(1);
	system("cls");
	bool a[5];
	std::string strl;
	std::string str=filee+to_string(n)+"\\Jindu.txt";
//	freopen(str.c_str(),"r",stdin);
	std::ifstream file(str);
	for(int i=1;i<=5;i++){
//		cin>>a[i];
		file>>a[i];
	}
	file>>strl;
//	cout<<a[1]<<endl<<a[2]<<endl<<a[3]<<endl<<a[4]<<endl<<a[5]<<endl<<strl<<endl;
//	fclose(stdin);
	file.close();
//	cin.clear();
//	freopen("CON","r",stdin);
	if(a[1]==false){
		codee:;
		cout<<"请输入您的名字:";
//		Sleep(300);
//		std::getline(std::cin,name);
		cin>>name;
		if(name=="Fuck"||name=="China"){
			cout<<"名字不合法!"<<endl;
			S(300);
			system("cls");
			goto codee;
		}
		else{
			a[1]=true;
			system("cls");
			cout<<"欢迎"<<name<<"!"<<endl;
			std::string dataToWrite="1 0 0 0 0 "+name+" 1";
			std::string filePath3=filee+to_string(n)+"\\Jindu.txt";
			std::ofstream outputFile3;
			outputFile3.open(filePath3);
			outputFile3<<dataToWrite;
			S(600);
		}
	}
	else{
		cout<<"欢迎"<<strl<<"!"<<endl;
		S(600);
	}
//	cout<<name<<endl;
//	S(300);
	idm:;
	gamemenuimage(strl);
	char chooses;
	chooses=getch();
	char nn=N+'0';
	if(chooses>nn||chooses<'1'){
		if(chooses>'9'||chooses<'0'){
			goto idm;
		}
		else {
			cout<<"没有这个选项!"<<endl;
			S(400);
			goto idm;
		}
	}
	int nm=chooses-'0';
	gameimage(nm);
}
void mainmenu(){
//	system("color 07");
	code:;
	system("cls");
	cout<<"存档数据"<<endl;
	cundang1(true);
	for(int i=1;i<=5;i++){
		cout<<"  "<<i<<'.'<<' '<<cundang[i]<<endl;
	}
	cout<<"请选择你要游玩的存档"<<':';
	choose=getch();
	char nn=N+'0';
//	nn=static_cast<char>(N);
//	cout<<nn<<endl;
	if(choose>nn||choose<'1') {
		if(choose>'9'||choose<'0')
			goto code;
		else {
			cout<<"没有这个存档，请输入1~"<<N<<"之间任意数字!"<<endl;
			Sleep(250);
			goto code;
		}
	}
	int n=choose-'0';
	if(cundang[n]!="+"&&cundang[n]!="!"){
		gamemenu(true,n);
	}
	else if(cundang[n]=="+"){
		cundang2(n);
		gamemenu(false,n);
	}
	else if(cundang[n]=="!"){
		cundang4(n);
		cundang1(true);
		goto code;
	}
}

int main(){
	system("title 原魔(Original Demon)1.0.0");
	system("color 70");
	srand((unsigned int)time(NULL));
	opan();
	mainmenu();
//	cundang2(1);
	
	return 0;
}
void start(){
	system("cls");
	int sssss=2;
	while(sssss--){
		system("cls");
		cout<<
		"■■■■■■■■"<<endl<<
		"■      ■"<<endl<<
		"■ ■  ■ ■"<<endl<<
		"■      ■"<<endl<<
		"■      ■"<<endl<<
		"■      ■"<<endl<<
		"■■■■■■■■"<<endl;
		Sleep(300);
		system("cls");
		cout<<endl;
		cout<<
		"■■■■■■■■"<<endl<<
		"■      ■"<<endl<<
		"■ ■  ■ ■"<<endl<<
		"■      ■"<<endl<<
		"■      ■"<<endl<<
		"■      ■"<<endl<<
		"■■■■■■■■"<<endl;
		Sleep(300);
	}
	system("cls");
	cout<<
	"■■■■■■■■"<<endl<<
	"■      ■"<<endl<<
	"■ ^  ^ ■"<<endl<<
	"■      ■"<<endl<<
	"■      ■"<<endl<<
	"■      ■"<<endl<<
	"■■■■■■■■"<<endl;
}
```
