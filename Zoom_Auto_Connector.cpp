#define _CRT_SECURE_NO_WARNINGS //윈도우, 초~고등학교 전용
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <Windows.h>
using namespace std;
unordered_map<string, string> lm;
char weak[7][10] = { {"일요일"},{"월요일"},{"화요일"},{"수요일"},{"목요일"},{"금요일"},{"토요일"} };
vector<string> split(string s, string di)
{
	vector<string> v;
	int start = 0, d = s.find(di);
	while (d != string::npos)
	{
		v.push_back(s.substr(start, d - start));
		start = d + 1;
		d = s.find(di, start);
	}
	v.push_back(s.substr(start, d - start));
	for (int i = 0; i < v.size(); ++i)
		v[i].erase(remove(v[i].begin(), v[i].end(), ' '), v[i].end()); //공백 제거
	return v;
}
vector<vector<string>> extV(string a) //월요일 : 기하, 미적, 이산수학
{
	vector<vector<string>> v(7);
	vector<string> vt = split(a, "\n");
	int i, j, p1;
	for (i = 0; i < 7; ++i)
	{
		string we = weak[i];
		for (j = 0; j < vt.size(); ++j)
		{
			p1 = vt[j].find(we);
			if (p1 == string::npos)	continue;
			vt[j] = vt[j].substr(vt[j].find(":") + 1);
			v[i] = split(vt[j], ",");
		}
	}
	return v;
}
void extL(string a) //기하 : https://www.GIHA.com/
{
	int i, p1;
	vector<string> vt = split(a, "\n");
	for (i = 0; i < vt.size(); ++i)
	{
		p1 = vt[i].find(":");
		if (p1 == string::npos)	continue;
		string h = vt[i].substr(0, p1);
		vt[i] = vt[i].substr(p1 + 1);
		lm[h] = vt[i];
	}
}
bool veri(string &a)
{
	for (int i = 0; i < a.length(); ++i)
		if (!('0' <= a[i] && a[i] <= '9'))
			return 0;
	return 1;
}
vector<int> extT(string a) //시간 특성
{
	vector<string> vt = split(a, "\n");
	vector<int> v;
	int i, j, p1;
	for (i = 0; i < vt.size(); ++i)
	{
		p1 = vt[i].find(":");
		if (p1 == string::npos)	continue;
		string r = vt[i].substr(p1 + 1);
		if (!i)
		{
			if (r.find(":") == string::npos)
			{
				cout << "\n\n수업 시작 시간이 제대로 입력되지 않았습니다. 수업 시작 시간을 다시 입력하세요.\n\n예) 수업 시작 : 9:10\n\n(시간 사이에 ':'가 반드시 있어야 함)\n\n현재 상태 --> 수업 시작 : " << vt[0] << "\n\n\n\n";
				exit(1);
			}
			vector<string> fz = split(r, ":");
			if (veri(fz[0]) && veri(fz[1]))
			{
				v.push_back(stoi(fz[0]));
				v.push_back(stoi(fz[1]));
			}
			else
			{
				cout << "\n\n수업 시작 시간이 제대로 입력되지 않았습니다. 수업 시간에는 숫자만 써야 합니다. (가운데 ':'제외)\n\n현재 상태 --> " << vt[0] << "\n\n\n\n";
				exit(1);
			}
		}
		else
		{
			if (veri(r))
				v.push_back(stoi(r));
			else
			{
				cout << "\n\n수업 시간들이 제대로 입력되지 않았습니다. 수업 시간에는 숫자만 써야 합니다.\n\n현재 상태 --> " << vt[i] << "\n\n\n\n";
				exit(1);
			}
		}
	}
	return v;
}
int main()
{
	ifstream file("For_Zoom_Connector.txt");
	string dac;
	if (file.is_open())
	{
		printf("-------------------------------줌 자동 연결기-------------------------------\n|                                                                          |\n|   이 프로그램은 시간에 맞게 자동으로 줌에 들어가지는 프로그램 입니다.    |\n|                                                                          |\n|               줌에 들어가신 후 출석체크는 본인의 몫입니다.               |\n|                                                                          |\n|            프로그램에 오류가 생겼을 경우 껏다 켜주시면 됩니다.           |\n|                                                                          |\n|      코드를 수정하실 필요없고, For_Zoom_Connector.txt를 수정하세요.      |\n|                                                                          |\n----------------------------------------------------------By 조형래---------\n");
		printf("\n만약 다른 요일의 수업을 진행해야 한다면 그 요일의 숫자를 눌러주세요.\n\n(일 : 0, 월 : 1, 화 : 2, 수 : 3, 목 : 4, 금 : 5, 토 : 6\n\n\n정상 수업한다면 그냥 엔터를 눌러주세요.\n");
		getline(cin, dac);
	}
	else
	{
		ofstream WriteFile("For_Zoom_Connector.txt");
		WriteFile << "<<((예시))>>\n//시간표는 요일만 가능, ':' 문자 반드시 써야됨, 공백 무시됨, 오타 주의\n//주소에 (&),(\")이 있으면 앞에 \\ 붙힐 것.\n\n>>시간표\n월요일 : 기하, 미적, 이산수학, 선형 대수학\n화요일 : 글쓰기, 영화 감상 및 비평A, English\n*****\n\n>>과목 링크\n기하 : https://www.GIHA.com/\n미적 : https://www.MIJUK.com/\n(등등 전부 링크 달기)\n*****\n\n>>수업 시간\n수업 시작 : 9:10\n수업 시간 : 50\n쉬는 시간 : 10\n점심 시간 : 50\n점심 교시 : 4 //(4교시 후 점심이란 뜻)\n\n\n\n########## 이제부터 본문 작성 --------------------------------------------------\n>>시간표\n\n*****\n\n>>과목 링크\n\n*****\n\n>>수업 시간\n수업 시작 : \n수업 시간 : \n쉬는 시간 : \n점심 시간 : \n점심 교시 : \n*****";
		cout << "################\n#\n# 이 프로그램이 있는 위치에 For_Zoom_Connector 이라는 텍스트 파일이 생성되었습니다.\n#\n# 예시처럼 과목과 링크를 입력해주세요.\n#\n################\n\n\n\n";
		return 0;
	}

	time_t now;
	struct tm TIME;
	now = time(NULL);
	TIME = *localtime(&now);  //시간 동기화

	int p1, p2, p3, i, j, tt, cut;
	vector<string> dacf(7);
	dacf[0] = "0"; dacf[1] = "1"; dacf[2] = "2"; dacf[3] = "3"; dacf[4] = "4"; dacf[5] = "5"; dacf[6] = "6";
	for (i = 0; i < 7; ++i)
		if (dac.find(dacf[i]) != string::npos)    TIME.tm_wday = i;		//다른 요일 수업할 때 인식하는 프로그램

	stringstream ss;
	ss << file.rdbuf();
	string t = ss.str();
	t = t.substr(t.find("##########") + 90); //이러면 t는 본문 내용만 // 딱 >>시간표\n뒤부터

	p1 = t.find("*****");
	string a = t.substr(0, p1); //a는 시간표 내용
	vector<vector<string>> v = extV(a);

	p2 = t.find(">>과목 링크\n");;
	p3 = t.find("*****", p2 + 12);
	string b = t.substr(p2 + 12, p3 - p2 - 13); //b는 링크 내용
	extL(b);

	p2 = t.find(">>수업 시간\n");;
	p3 = t.find("*****", p2 + 12);
	string c = t.substr(p2 + 12, p3 - p2 - 13); //c는 시간 특성 내용
	vector<int> td = extT(c);
	tt = 3600 * td[0] + 60 * td[1]; //sec 스케일
	vector<pair<int, int>> ct(1, { 0,0 }); //ct[1]=1교시 시작, 끝 //2는2
	pair<int, int> tep;
	for (i = 0; i < v[TIME.tm_wday].size(); ++i) //시간표 작성
	{
		tep.first = tt;
		tt += td[2] * 60;
		tep.second = tt;
		ct.push_back(tep);
		if (i != td[5] - 1)	tt += td[3] * 60;
		else  tt += td[4] * 60;
	}

	if (v[TIME.tm_wday].empty())
	{
		printf("\n\n오늘은 수업이 없는 날 입니다. 축하드립니다.\n\n\n\n");
		return 0;   //바로 프로그램 끝남
	}

	while (1) //    1초 루프 시작///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		now = time(NULL);
		TIME = *localtime(&now); //시간 동기화

		system("cls");
		printf("-------------------------------줌 자동 연결기-------------------------------\n|                                                                          |\n|   이 프로그램은 시간에 맞게 자동으로 줌에 들어가지는 프로그램 입니다.    |\n|                                                                          |\n|               줌에 들어가신 후 출석체크는 본인의 몫입니다.               |\n|                                                                          |\n|            프로그램에 오류가 생겼을 경우 껏다 켜주시면 됩니다.           |\n|                                                                          |\n|      코드를 수정하실 필요없고, For_Zoom_Connector.txt를 수정하세요.      |\n|                                                                          |\n----------------------------------------------------------By 조형래---------\n");
		cout << "\n오늘은 " << TIME.tm_year + 1900 << "년 " << TIME.tm_mon << "월 " << TIME.tm_mday << "일 " << weak[TIME.tm_wday] << " 입니다.";

		int c = 1;
		for (i = 0; i < 7; ++i)
			if (dac.find(dacf[i]) != string::npos)
			{
				TIME.tm_wday = i;
				cout << "  " << weak[i] << " 시간표가 진행됩니다.  ";
				c = 0;
			}
		if (c)
			printf("                               "); //다른 요일 수업할 때 인식하는 프로그램

		printf(" %02d:%02d:%02d\n\n", TIME.tm_hour, TIME.tm_min, TIME.tm_sec);
		cut = TIME.tm_hour * 3600 + TIME.tm_min * 60 + TIME.tm_sec; //현재 시간 sec 스케일

		for (int classN = 1; classN <= v[TIME.tm_wday].size(); ++classN)
		{
			if (ct[classN].first <= cut && cut < ct[classN].second)	printf("--------------------------------->>  ");
			printf("%d교시 : %02d:%02d ~ %02d:%02d    ", classN, ct[classN].first / 3600, (ct[classN].first % 3600) / 60, ct[classN].second / 3600, (ct[classN].second % 3600) / 60);
			cout << v[TIME.tm_wday][classN - 1]; //v[]의 내용은 제로 스케일

			if (cut == ct[classN].first) //줌 링크 실행
			{
				if (!lm.count(v[TIME.tm_wday][classN - 1]))
				{
					printf("\n오류!!! <- 해당 과목에 대한 링크가 없음\n#######################################\n");
					int alarm = 10;
					while (alarm--)
					{
						cout << '\a';
						Sleep(200);
					}
				}
				else
				{
					string sys = "start " + lm[v[TIME.tm_wday][classN - 1]];
					char tchar[1000] = { "" };
					strcpy(tchar, sys.c_str());
					system(tchar);
					cout << "   --" << classN << "교시 " << v[TIME.tm_wday][classN - 1] << " 열리는 중--" << '\a';
					cout << '\a';
				}
			}

			printf("\n");
			if (classN != v[TIME.tm_wday].size())
			{
				if (ct[classN].second <= cut && cut < ct[classN + 1].first) //휴식 시간 출력
					printf("--------------------------------->>  ");
				if (classN != td[5])
					cout << "------쉬는시간-------\n";
				else
					cout << "------점심시간-------\n";
			}
		}
		if (cut > ct[v[TIME.tm_wday].size()].second)
		{
			printf("\n\n수업이 모두 종료되었습니다! 수고하셨습니다.\n\n\n");
			return 0;
		}
		Sleep(900);
	}
}
