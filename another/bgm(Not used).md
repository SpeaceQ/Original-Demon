```c
#include <cstdio>
#include <windows.h>
enum Notes {
	qdo = 262, qre = 294, qmi = 330, qfa = 349, qso = 392, qla = 440, qsi = 494,
	do_ = 523, re = 578, mi = 659, fa = 698, so = 784, la = 880, si = 988,
	do1 = 1046, re1 = 1175, mi1 = 1318, fa1 = 1480, so1 = 1568, la1 = 1760, si1 = 1976,
	sqdo = 277, sqre = 311, sqfa = 370, sqso = 415, sqla = 466,
	sdo = 554, sre = 622, sfa = 740, sso = 831, sla = 932,
	sdo1 = 1046, sre1 = 1245, sfa1 = 1480, sso1 = 1661, sla1 = 1865
};
void background_music(){
	int pai=400,ban=200;
	int ting=128;
	Sleep(1000);Beep(la,ban);Beep(si,ban);Sleep(ting);Beep(do1,pai+ban);Beep(si,ban);Sleep(ting);Beep(do1,pai);
	Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(si,3*pai);Sleep(ting);Beep(mi,ban);Beep(mi,ban);Beep(la,ban+pai);
	Beep(so,ban);Sleep(ting);Beep(la,pai);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(so,2*pai);Sleep(ting);Sleep(pai);
	Beep(mi,ban);Sleep(ting/2);Beep(mi,ban);Sleep(ting/2);Beep(fa,pai+ban);Beep(mi,ban);Sleep(ting);Beep(fa,ban);
	Beep(do1,ban+pai);Sleep(ting);Beep(mi,2*pai);Sleep(ting);Sleep(ban);Beep(do1,ban);Sleep(ting/2);Beep(do1,ban);
	Sleep(ting/2);Beep(do1,ban);Sleep(ting/2);Beep(si,ban+pai);Beep(sfa,ban);Sleep(ting);Beep(sfa,pai);Beep(si,pai);
	Sleep(ting);Beep(si,2*pai);Sleep(ting);Sleep(pai);Beep(la,ban);Beep(si,ban);Sleep(ting);Beep(do1,pai+ban);Beep(si,ban);
	Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(si,2*pai);Sleep(ting);Sleep(pai);Beep(mi,ban);
	Sleep(20);Beep(mi,ban);Sleep(ting);Beep(la,pai+ban);Beep(so,ban);Sleep(ting);Beep(la,pai);Sleep(ting);Beep(do1,pai);
	Sleep(ting);Beep(so,3*pai);Sleep(ting+ban);Beep(mi,ban);Sleep(ting/2);Beep(fa,pai);Sleep(ting);Beep(do1,ban);Beep(si,ban);
	Sleep(20);Beep(si,pai);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(re1,ban);Sleep(20);Beep(re1,ban);Sleep(20);Beep(mi1,ban);
	Sleep(ting/2);Beep(do1,pai);Sleep(ting+pai);Beep(do1,pai);Beep(si,ban);Sleep(ting);Beep(la,ban);Sleep(20);Beep(la,ban);Sleep(ting);
	Beep(si,pai);Sleep(ting);Beep(sso,pai);Sleep(ting);Beep(sso,2*pai);Sleep(ting+pai);Beep(do1,ban);Beep(re1,ban);Sleep(ting);
	Beep(mi1,pai+ban);Beep(re1,ban);Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(fa1,pai);Sleep(ting);Beep(re1,2*pai);Sleep(pai+ting);
	Beep(so,ban);Sleep(20);Beep(so,ban);Sleep(ting);Beep(do1,ban);Beep(si,ban);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(mi1,pai);
	Sleep(ting);Beep(mi1,2*pai);Sleep(ting+2*pai);Beep(la,ban);Beep(si,ban);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(si,pai);
	Sleep(ting);Beep(re1,ban);Sleep(20);Beep(re1,ban);Sleep(ting);Beep(do1,pai+ban);Beep(so,ban);Sleep(20);Beep(so,pai);Sleep(pai+ting);
	Beep(fa1,pai);Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(re1,pai);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(mi1,4*pai);
	Beep(mi1,pai*2);Sleep(pai+ting);Beep(mi1,pai);Sleep(ting);Beep(la1,2*pai);Sleep(ting);Beep(so1,pai);Sleep(ting);Beep(so1,pai);
	Sleep(ting);Beep(mi1,ban);Sleep(ting/2);Beep(re1,ban);Sleep(ting);Beep(do1,pai);Sleep(ting+ban);Beep(do1,ban);Sleep(ting);
	Beep(re1,pai);Sleep(ting);Beep(do1,ban);Beep(re1,ban);Sleep(20);Beep(re1,ban);Sleep(ting);Beep(so1,pai);Sleep(ting);Beep(mi1,2*pai);
	Sleep(ting+pai);Beep(mi,pai);Sleep(ting);Beep(la1,2*pai);Sleep(ting);Beep(so1,2*pai);Sleep(ting);Beep(mi1,ban);Beep(re1,ban);
	Sleep(ting);Beep(do1,2*pai);Sleep(ting+ban);Beep(do1,ban);Sleep(ting);Beep(re1,pai);Sleep(ting);Beep(do1,ban);Beep(re1,ban);
	Sleep(20);Beep(re1,ban);Sleep(ting);Beep(si,pai);Sleep(ting);Beep(la,2*pai);Sleep(ting);Beep(la,ban);Beep(si,ban);Beep(do1,pai+ban);
	Beep(si,ban);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(si,3*pai);Sleep(ting);Beep(mi,ban);Beep(mi,ban);
	Beep(la,ban+pai);Beep(so,ban);Sleep(ting);Beep(la,pai);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(so,2*pai);Sleep(ting);Sleep(pai);
	Beep(mi,ban);Sleep(ting/2);Beep(mi,ban);Sleep(ting/2);Beep(fa,pai+ban);Beep(mi,ban);Sleep(ting);Beep(fa,ban);Beep(do1,ban+pai);
	Sleep(ting);Beep(mi,2*pai);Sleep(ting);Sleep(ban);Beep(do1,ban);Sleep(ting/2);Beep(do1,ban);Sleep(ting/2);Beep(do1,ban);Sleep(ting/2);
	Beep(si,ban+pai);Beep(sfa,ban);Sleep(ting);Beep(sfa,pai);Beep(si,pai);Sleep(ting);Beep(si,2*pai);Sleep(ting);Sleep(pai);Beep(la,ban);
	Beep(si,ban);Sleep(ting);Beep(do1,pai+ban);Beep(si,ban);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(mi1,pai);Sleep(ting);Beep(si,2*pai);
	Sleep(ting);Sleep(pai);Beep(mi,ban);Sleep(20);Beep(mi,ban);Sleep(ting);Beep(la,pai+ban);Beep(so,ban);Sleep(ting);Beep(la,pai);
	Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(so,3*pai);Sleep(ting+ban);Beep(mi,ban);Sleep(ting/2);Beep(fa,pai);Sleep(ting);Beep(do1,ban);
	Beep(si,ban);Sleep(20);Beep(si,pai);Sleep(ting);Beep(do1,pai);Sleep(ting);Beep(re1,ban);Sleep(20);Beep(re1,ban);Sleep(20);
	Beep(mi1,ban);Sleep(ting/2);Beep(do1,pai);Sleep(ting+pai);Beep(la,4*pai);Sleep(1000);
	background_music();
}
int main()
{
	background_music();
}
```
