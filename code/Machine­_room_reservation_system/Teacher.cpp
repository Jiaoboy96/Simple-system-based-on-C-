#include "Teacher.h"

Teacher::Teacher()
{
}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "\t-------��ӭ��ʦ��" << this->m_Name << "��¼-------" << endl;
	cout << "\t------------------------------------\n";
	cout << "\t|                                  |\n";
	cout << "\t|          1���鿴����ԤԼ         |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          2�����ԤԼ             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          0��ע����¼             |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	cout << "���������ѡ��" << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "û��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		// stringתint
		// string����.c_str() תconst char *
		//����atoi ( const char *)תint

		cout << i + 1 << "��";
		cout << "ԤԼ�����ڣ���" << of.m_OrderData[i]["data"] << " ";
		cout << "ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����") << " ";
		cout << "�����ţ�" << of.m_OrderData[i]["roomID"] << " ";
		cout << "ѧ�ţ�" << of.m_OrderData[i]["stuId"] << " ";
		cout << "������" << of.m_OrderData[i]["stuName"] << " ";

		string status = "״̬��";
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_OrderData[i]["status"] == "-1")
		{
			status += "ԤԼʧ�ܣ����δͨ��";
		}
		else
		{
			status += "ԤԼȡ��";
		}
		cout << status << endl;

	}

	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "û��ԤԼ��¼" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "����л���ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼��" << endl;

	int index = 1;
	vector<int>v; // ���������������±���
	for (int i = 0; i < of.m_Size; i++)
	{
		//���ж�������ѧ��
		if (this->m_EmpId == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			//����ɸѡ ����л���ԤԼ�ɹ�
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "��";
				cout << "ԤԼ�����ڣ���" << of.m_OrderData[i]["data"] << " ";
				cout << "ʱ��Σ�" << (of.m_OrderData[i]["interval"] == "1" ? "����" : "����") << " ";
				cout << "�����ţ�" << of.m_OrderData[i]["roomID"] << " ";

				string status = "״̬��";
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				else if (of.m_OrderData[i]["status"] == "-1")
				{
					status += "ԤԼʧ�ܣ����δͨ��";
				}
				else
				{
					status += "ԤԼȡ��";
				}
				cout << status << endl;

			}
		}
	}

	cout << "��������˵�ԤԼ��¼��0������" << endl;
	unsigned int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "��������˽����" << endl;
				cout << "1��ͨ��" << endl;
				cout << "2����ͨ��" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
				}
				
				of.updataOrder();

				cout << "������" << endl;
				break;
			}
		}
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");

}
