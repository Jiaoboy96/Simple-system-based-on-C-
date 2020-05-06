#include <iostream>
#include <ctime>
#include "SpeechManager.h"
using namespace std;

int main()
{
	//���������
	srand((unsigned int)time(NULL));
	SpeechManager speechManager;
	
	//for (map<int,Speaker>::iterator it = speechManager.m_Speaker.begin(); it!= speechManager.m_Speaker.end();it++)
	//{
	//	cout << it->first << "   " << it->second.m_Name << "   " << it->second.m_Score[0] << endl;
	//}

	int choice = 0;  //��������û���ѡ��

	while (true)
	{
		speechManager.show_Menu();

		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			speechManager.exitSystem();
			break;
		case 1:  //��ʼ����
			speechManager.startSpeech();
			break;
		case 2:  //�鿴��¼
			speechManager.showRecord();
			break;
		case 3: //��ռ�¼
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