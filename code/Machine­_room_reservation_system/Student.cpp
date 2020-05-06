#include "Student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//��ʼ������
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//��ʼ��������Ϣ
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxN)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

void Student::applyOrder()
{
	int data = 0; //���� ��һ~����
	int interval = 0; //ʱ��� ����~����
	int room = 0;  //������� 1~3

	cout << "��������ʱ������һ�����壡" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;


	while (true)
	{
		cin >> data;
		if (data >= 1 && data <= 5)
		{
			break;
		}
		cout << "��������������룺" << endl;
	}

	cout << "����������ԤԼ��ʱ��Σ�" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "��������������룺" << endl;
	}

	cout << "��ѡ�������" << endl;
	for (unsigned int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż�����������" << vCom[i].m_MaxN << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "��������������룺" << endl;
	}

	cout << "ԤԼ�ɹ�������У�" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "data:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomID:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");

}

void Student::showMyOrder()
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

		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			cout << "ԤԼ�����ڣ���" << of.m_OrderData[i]["data"]<<" ";
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

	system("pause");
	system("cls");
}

void Student::showAllOrder()
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

void Student::cancelOrder()
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
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
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

	cout << "������ȡ���ļ�¼��0������" << endl;
	unsigned int select = 0;
	
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
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updataOrder();

				cout << "�Ѿ�ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "��������" << endl;
	}

	system("pause");
	system("cls");

}

void Student::operMenu()
{
	cout << "\t-------��ӭѧ������" << this->m_Name << "��¼-------" << endl;
	cout << "\t------------------------------------\n";
	cout << "\t|                                  |\n";
	cout << "\t|          1������ԤԼ             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          2���鿴�ҵ�ԤԼ         |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          3���鿴��������ԤԼ     |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          4��ȡ��ԤԼ             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          0��ע����¼             |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	cout << "���������ѡ��" << endl;
}
