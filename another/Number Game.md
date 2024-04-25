### [This](https://www.cnblogs.com/spaceq/category/2376381.html)
### 介绍
这是一个双人数字游戏，这个程序刚开始会让你输入一个数，表示序列的长度，然后摁下`Enter`，接着第一个人在序列中输入1 ~ 2个`1`，第二个人在序列中输入1 ~ 2个`0`，直到序列无空间为止，最后一个输入的人算输。
### 更新说明
1. 这份代码在原来的基础上加入了和电脑对战(话说电脑确实有些恶心，不过毕竟你赢的概率为2/3)，在一个人无聊的时候可以打打。
2. 如果你想查看还剩多少个字符的话，请摁下回车。
####[上一版本](https://www.cnblogs.com/spaceq/articles/18001025)
### 代码

```
/*
C++ number game
*/
#include<bits/stdc++.h>
//#include<windows.h>
#include <conio.h>
#include <sstream>
#define ll long long
using namespace std;

char PrN , o ;
int PrNN[2] ;
string s , n2 ;
ll n , vn , m , ne ;
char c;
bool chooseai ,pdinput ;
void output1()
{
	cout << "Roules:" << endl 
	<< "1. You can choose the first or second to enter;" << endl
	<< "2. Player 1 enters 1 and player 2 enters 0;" << endl 
	<< "3. You can choose to enter one or two at a time;" << endl 
	<< "4. The last person to enter will lose the game." << endl 
	<< "5. If you want to know how many characters are left, press enter." << endl ;
	cout << "Please tell me how long you want the string to be for typing" << ":" ;
}
void output2()
{
	cout << vn <<endl ;
	cout << "There is " << n << " character left" << endl ;
}
void outputai()
{
	aipd:;
	cout << "Do you want to play with report?" << endl ;
	cout << "Y.yes/N.no" << endl ;
	char choosess = getchar() ;
	if (choosess == 'y' || choosess == 'Y')
	{
		system("cls") ;
		chooseai = true ;
	}
	else if (choosess == 'n' || choosess == 'N')
	{
		system("cls") ;
		chooseai = false ;
	}
	else 
	{
		system("cls") ;
		goto aipd ;
	}
}
int main()
{
	cout << "Before begin the game , it is recommended that the length of the string be limited to one line." << endl ;
	cout << "Plese enter 'o' to next: " ;
	nback:;
	o = getchar() ;
	if(o == 'o')
	{
		system("cls") ;
	}
	else 
	{
		goto nback ;
	}
	brk:;
	outputai() ;
	pd:;
	s = "" ;
	n = 0 ;
	PrNN[1] = 0 ;
	PrNN[2] = 0 ;
	output1() ;
	cin >> n2 ;
	c = n2[0] ;
	if( isdigit(c) )
	{
		stringstream geek(n2) ;
		geek >> n ;
	}
	else 
	{
		system("cls") ;
		goto pd ;
	}
	if (n == 0)
	{
		n = 0 ;
		system("cls") ;
		goto pd ;
	}
	ne += 4 ;
	if (n != ne)
	{
		ne = 0 ;
	}
	cout << "There is " << n << " character left" << endl ;
	vn = n ;
	while (n)
	{ 
//		m = n % 3 ;
		code:;
//		pdinput = false ;
		PrN = getch() ;
		if (PrN != '1' and PrN != '0' and PrN != 13)
		{
			system("cls") ;
			output1() ; output2() ;
			cout << s ;
			goto code;
		}
		if (PrN == 13 && chooseai == false)
		{
			system("cls") ;
			output1() ; output2() ;
			cout << s ;
			goto code;
		}
		if (PrN == '1')
		{
			pdinput = true ;
			PrNN[0] = 0 ;
			PrNN[1] ++ ;
			if (PrNN[1] > 2)
			{
				system("cls") ;
				output1() ; output2() ;
				cout << s ;
				goto code;
			}
			else{
				n -- ;
				s += PrN ;
				cout << PrN ;
			}
		}
		else if (PrN == '0' && chooseai == false)
		{    
			PrNN[1] = 0 ;
			PrNN[0] ++ ;
			if (PrNN[0] > 2)
			{
				system("cls") ;
				output1() ; output2() ;
				cout << s ;
				goto code;
			}
			else{
				n -- ;
				s += PrN ;
				cout << PrN ;
			}
		}
		if (PrN == 13 && pdinput)
		{
			pdinput = false ;
			m = n % 3 ;
//			if (n == 2)
//			{
//				cout << "0" ;
//				s += "0" ;
//				n -= 1 ;
//			}
			if (n == 1)
			{
				cout << "0" ;
				s += "0" ;
				n -= 1 ;
				goto endd ;
			}
			else if (m == 0)
			{
				if (PrNN[1] == 1)
				{
					cout << "00" ;
					s += "00" ;
					n -= 2 ;
				}
				else 
				{
					cout << "0" ;
					s += "0" ;
					n -= 1 ;
				}
			}
			else if (m == 1)
			{
				if (PrNN[1] == 1)
				{
					cout << "00" ;
					s += "00" ;
					n -= 2;
				}
				else 
				{
					cout << "0" ;
					s += "0" ;
					n -= 1 ;
				}
			}
			else if (m == 2)
			{
				cout << "0" ;
				s += "0" ;
				n -= 1 ;
			}
			PrNN[1] = 0 ;
			goto code ;
		}
//		if (pdinput == false)
//		{
//			goto code ;
//		}
	}
	endd:;
	if (PrN == '1')
	{
		cout << endl ;
		if (chooseai == false)
		{
			cout << "Player 2 win!" << endl ;	
		}
		else 
		{
			cout << "Computer win!" << endl ;
			if (ne != 0 && chooseai == true)
			{
				cout << "Haha, you're nothing more than that!" << endl ;
			}
		}
	}
	else 
	{
		cout << endl ;
		if (chooseai == false)
		{
			cout << "Player 1 win!" << endl ;
		}
		else 
		{
			cout << "Player win!" << endl ;
			ne = vn/3 ;
			ne *= 3 ;
			cout << "Oh , I know you will win , do you have to try enter " << ne + 4 <<" ?" << endl ;
		}
	}
	cout << "Plese press the o to next , or press the q to quit:" ;
	back:;
	o = getchar() ;
	if (o == 'o')
	{
		cout << 'o' << endl ;
		system("cls");
		goto brk ;
	}
	else if (o == 'q') 
	{
		goto en ;
	}
	else 
	{
		goto back ;
	}
	en:;
	return 0;
}
```
##### 友情链接:<https://jasonxing.eu.org/>
