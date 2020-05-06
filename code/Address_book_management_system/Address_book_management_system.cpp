#include<iostream>
#include<string>
using namespace std;

#define MAX 1000

//�����ϵ�˽ṹ��
struct Person
{
	//����
	string m_Name;
	//�Ա� 1-�� 2-Ů
	int m_Sex;
	//����
	int m_Age;
	//�绰
	string m_Phone;
	//סַ
	string m_Addr;
};

//���ͨѶ¼�ṹ��
struct Addressbooks
{
	//ͨѶ¼�б������ϵ������
	struct Person personArray[MAX];
	//ͨѶ¼�е�ǰ��¼��ϵ�˸���
	int m_Size;
};

//�˵�����
void showMenu()
{
	cout << "***************************" << endl;
	cout << "*****  1�������ϵ��  *****" << endl;
	cout << "*****  2����ʾ��ϵ��  *****" << endl;
	cout << "*****  3��ɾ����ϵ��  *****" << endl;
	cout << "*****  4��������ϵ��  *****" << endl;
	cout << "*****  5���޸���ϵ��  *****" << endl;
	cout << "*****  6�������ϵ��  *****" << endl;
	cout << "*****  0���˳�ͨѶ¼  *****" << endl;
	cout << "***************************" << endl;
}

//1�������ϵ��
void addPerson(struct Addressbooks * abs)
{
	//�ж�ͨѶ¼�Ƿ���Ա
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼����" << endl;
		return;
	}
	else
	{
		//�����ϵ��
		//����
		string name;
		cout << "���������֣�" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;
		//�Ա�
		cout << "�������Ա�1-�� 2-Ů" << endl;
		int sex = 0;
		while (true)
		{
			//���������ȷ����ֵ���˳������������������
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "����������������" << endl;
		}
		//����
		cout << "���������䣺" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;
		//�绰
		cout << "��������ϵ�˵绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;
		//��ַ
		cout << "�������ͥסַ��" << endl;
		string Address;
		cin >> Address;
		abs->personArray[abs->m_Size].m_Addr= Address;

		//����ͨѶ¼����
		abs->m_Size++;

		cout << "��ӳɹ�" << endl;
		system("pause");  //�밴���������
		system("cls");  //��������
	}
}
//2����ʾ��ϵ��
void showPerson(Addressbooks * abs)
{
	//�ж�ͨѶ¼�����Ƿ�Ϊ0��Ϊ0����ʾ��¼Ϊ��
	//�����Ϊ0����ʾ��¼����ϵ����Ϣ
	if (abs->m_Size==0)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < abs->m_Size; i++)
		{
			cout << "������" <<abs->personArray[i].m_Name<< "\t";
			cout << "�Ա�" << (abs->personArray[i].m_Sex == 1 ? "��":"Ů") << "\t";
			cout << "���䣺" << abs->personArray[i].m_Age << "\t";
			cout << "�绰��" << abs->personArray[i].m_Phone << "\t";
			cout << "��ַ��" << abs->personArray[i].m_Addr << endl;
		}
	}
	system("pause");  //�밴���������
	system("cls");  //��������
}

//�����ϵ���Ƿ���ڣ�������ڣ�������ϵ���������λ�ã������ڷ���-1
int isExist(Addressbooks *abs,string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		if (abs->personArray[i].m_Name == name)
		{
			return i;//������ϵ�˵��±�
		}
	}
	return -1;

}

//3��ɾ����ϵ��
void deletePerson(Addressbooks * abs)
{
	cout << "������Ҫɾ������ϵ�����֣�" << endl;
	string name;
	cin >> name;
	//�ж�ͨѶ¼�Ƿ��д���
	int ret = isExist(abs, name);
	if (ret != -1)
	{
		//�鵽���ˣ�����ɾ������
		for (int i = ret; i < abs->m_Size; i++)
		{
			//����ǰ��
			abs->personArray[i] = abs->personArray[i + 1];
			abs->m_Size--;//��������
		}
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "���޴���" << endl;
	}
	system("pause");  //�밴���������
	system("cls");  //��������
}

//4������ָ����ϵ����Ϣ
void findPerson(Addressbooks *abs)
{

	cout << "��������Ҫ���ҵ���ϵ����Ϣ��" << endl;
	string name;
	cin >> name;

	//�ж���ϵ���Ƿ����ͨѶ¼��
	int ret = isExist(abs, name);

	if (ret != -1) //�ҵ���ϵ��
	{
		cout << "������" << abs->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t";
		cout << "���䣺" << abs->personArray[ret].m_Age << "\t";
		cout << "�绰��" << abs->personArray[ret].m_Phone << "\t";
		cout << "��ַ��" << abs->personArray[ret].m_Addr << endl;
	}
	else
	{
		cout << "δ�ҵ�ָ����ϵ��" << endl;
	}
	system("pause");  //�밴���������
	system("cls");  //��������
}

//5���޸�ָ����ϵ��
void modifyPerson(Addressbooks *abs) 
{
	cout << "��������Ҫ�޸ĵ���ϵ��������" << endl;
	string name;
	cin >> name;

	//�ж���ϵ���Ƿ����ͨѶ¼��
	int ret = isExist(abs, name);

	if (ret != -1) //�ҵ���ϵ��
	{
		//����
		abs->personArray[ret].m_Name = name;
		//�Ա�
		cout << "��������Ҫ�޸ĵ���ϵ���Ա�" << endl;
		int sex = 0;
		while (true)
		{
			cin >> sex;
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			else
			{
				cout << "����������������" << endl;
			}
		}
		//����
		cout << "��������Ҫ�޸ĵ���ϵ�����䣺" << endl;
		int age = 0;
		cin >> age;
		abs->personArray[ret].m_Age = age;
		//�绰
		cout << "��������Ҫ�޸ĵ���ϵ�˵绰��" << endl;
		string phone;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;
		//סַ
		cout << "��������Ҫ�޸ĵ���ϵ��סַ��" << endl;
		string address;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else
	{
		cout << "δ�ҵ�ָ����ϵ��" << endl;
	}
	system("pause");  //�밴���������
	system("cls");  //��������
}

//6�������ϵ��
void cleanPerson(Addressbooks * abs)
{
	abs->m_Size = 0;
	cout << "ͨѶ¼�Ѿ����" << endl;
	system("pause");  //�밴���������
	system("cls");  //��������
}

int main()
{
	//����ͨѶ¼�ṹ��ı���
	struct Addressbooks abs;
	abs.m_Size = 0;

	int select = 0;

	while (true)
	{
		showMenu();
		cin >> select;
		switch (select)
		{
		case 1://1�������ϵ��
			addPerson(&abs);
			break;
		case 2://2����ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3://3��ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4://4��������ϵ��
			findPerson(&abs);
			break;
		case 5://5���޸���ϵ��
			modifyPerson(&abs);
			break;
		case 6://6�������ϵ��
			cleanPerson(&abs);
			break;
		case 0://0���˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
}