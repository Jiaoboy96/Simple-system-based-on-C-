#include<iostream>
#include<fstream>
#include <string>
#include "globalFile.h"
#include"Identity.h"
#include "Manager.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

//�������Ա���Ӳ˵�
void managerMenu(Identity* &manager)
{
	while (true)
	{
		//���ù���Ա����˵�
		manager->operMenu();

		//������ָ��תΪ����ָ�룬��������������ӿ�
		Manager * man = (Manager*)manager;

		int select;
		cin >> select;

		if (select == 1) //����˺�
		{
			//cout << "����˺�" << endl;
			man->addPerson();
		}
		else if (select == 2) //�鿴�˺�
		{
			//cout << "�鿴�˺�" << endl;
			man->showPerson();
		}
		else if (select == 3)  //�鿴����
		{
			//cout << "�鿴����" << endl;
			man->showComputer();
		}
		else if (select == 4) // ���ԤԼ
		{
			//cout << "���ԤԼ" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//����ѧ�����Ӳ˵�
void studentMenu(Identity* &student)
{
	while (true)
	{
		//���ù���Ա����˵�
		student->operMenu();

		//������ָ��תΪ����ָ�룬��������������ӿ�
		Student * stu = (Student*)student;

		int select;
		cin >> select;

		if (select == 1) //����ԤԼ
		{
			//cout << "����ԤԼ" << endl;
			stu->applyOrder();
		}
		else if (select == 2) //�鿴ԤԼ
		{
			//cout << "�鿴ԤԼ" << endl;
			stu->showMyOrder();
		}
		else if (select == 3)  //�鿴����ԤԼ
		{
			//cout << "�鿴����ԤԼ" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) // ȡ��ԤԼ
		{
			//cout << "ȡ��ԤԼ" << endl;
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//������ʦ���Ӳ˵�
void TeacherMenu(Identity* &teacher)
{
	while (true)
	{
		//���ù���Ա����˵�
		teacher->operMenu();

		//������ָ��תΪ����ָ�룬��������������ӿ�
		Teacher * tea = (Teacher*)teacher;

		int select;
		cin >> select;

		if (select == 1) //�鿴����ԤԼ
		{
			//cout << "�鿴����ԤԼ" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) //���ԤԼ
		{
			//cout << "���ԤԼ" << endl;
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "ע���ɹ�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//��¼����  �ļ��� �����������
void LoginIn(string filename, int type)
{
	//����ָ�� ����ָ���������
	Identity* person = NULL;

	//���ļ�
	ifstream ifs;
	ifs.open(filename, ios::in);

	//�ж��ļ��Ƿ����
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//׼����Ϣ �����û�����Ϣ
	int id = 0;
	string name;
	string pwd;

	//�ж����
	if (type == 1)  //ѧ�����
	{
		cout << "���������ѧ��" << endl;
		cin >> id;
	}
	else if (type == 2)  //��ʦ���
	{
		cout << "���������ְ����" << endl;
		cin >> id;
	}

	cout << "�������û���" << endl;
	cin >> name;

	cout << "����������" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//ѧ�����
		int fId;  //���ļ���ȡ��ID��
		string fName; //���ļ���ȡ������
		string fPwd; //���ļ���ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ�Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "ѧ����֤�ɹ�" << endl;
				system("pause");
				system("cls");
				//����ѧ������
				person = new Student(id,name,pwd);
				studentMenu(person);
				return;

			}
		}
	}
	else if (type == 2)
	{
		//��ʦ���
		int fId;  //���ļ���ȡ��ID��
		string fName; //���ļ���ȡ������
		string fPwd; //���ļ���ȡ������

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ�Ա�
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "��ʦ��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				//������ʦ����
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//����Ա���
		string fName; //���ļ���ȡ������
		string fPwd; //���ļ���ȡ������

		while (ifs >> fName && ifs >> fPwd)
		{
			//���û��������Ϣ�Ա�
			if (fName == name && fPwd == pwd)
			{
				cout << "����Ա��֤�ɹ�" << endl;
				system("pause");
				system("cls");
				//��������Ա����
				person = new Manager(name, pwd);
				
				managerMenu(person);
				return;
			}
		}
	}

	cout << "��֤ʧ��" << endl;
	system("pause");
	system("cls");
}

int main()
{
	int select = 0;

	while (true)
	{
		cout << "----------------��ӭ���Ļ���ԤԼϵͳ-------------" << endl;
		cout << endl;
		cout << "\t------------------------------------\n";
		cout << "\t|                                  |\n";
		cout << "\t|          1��ѧ������             |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          2���� ʦ                |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          3������Ա               |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          0����  ��               |\n";
		cout << "\t|                                  |\n";
		cout << "\t------------------------------------\n";
		cout << "�����������ݣ�" << endl;


		cin >> select;  //�����û���ѡ��

		switch (select)
		{
		case 1:  //ѧ�����
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //��ʦ���
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //����Ա���
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //�˳�
		{
			cout << "��ӭ��һ��ʹ�ã�" << endl;
			system("pause");
			return 0;
		}
		break;
		default:
			cout << "���������������룺" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}