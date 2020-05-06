#include <iostream>
#include <ctime>
#include "SpeechManager.h"
using namespace std;

int main()
{
	//随机数种子
	srand((unsigned int)time(NULL));
	SpeechManager speechManager;
	
	//for (map<int,Speaker>::iterator it = speechManager.m_Speaker.begin(); it!= speechManager.m_Speaker.end();it++)
	//{
	//	cout << it->first << "   " << it->second.m_Name << "   " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;  //用来存放用户的选择

	while (true)
	{
		speechManager.show_Menu();

		cout << "请输入你的选择：" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:  //退出系统
			speechManager.exitSystem();
			break;
		case 1:  //开始比赛
			speechManager.startSpeech();
			break;
		case 2:  //查看记录
			speechManager.showRecord();
			break;
		case 3: //清空记录
			speechManager.clearRecord();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");

	return 0;
}