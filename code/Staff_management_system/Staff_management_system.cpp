#include<iostream>
#include "workerManager.h"
using namespace std;

int main()
{
	//ʵ���������߶���
	WorkerManager wm;
	int choice = 0;
	while (true)
	{
		//չʾ�˵�
		wm.show_Menu();
		cout << "���������ѡ��" << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:  //�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1:  //���ְ��
			wm.add_Emp();
			break;
		case 2:  //��ʾְ��
			wm.show_Emp();
			break;
		case 3:  //ɾ��ְ��
			wm.del_Emp();
			break;
		case 4:  //�޸�ְ��
			wm.mod_Emp();
			break;
		case 5:  //����ְ��
			wm.find_Emp();
			break;
		case 6:  //����ְ��
			wm.sort_Emp();
			break;
		case 7:  //����ļ�
			wm.clean_File();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");
	return 0;
}