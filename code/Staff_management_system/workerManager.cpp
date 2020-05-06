#include "workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//�ļ�������
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ�����û������
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		//��ʼ������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	cout << "ְ������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//���ļ��е����ݣ��浽������
	this->init_Emp();
	
}
void WorkerManager::show_Menu()
{
	cout << "****************************************" << endl;
	cout << "******** ��ӭʹ��ְ������ϵͳ�� ********" << endl;
	cout << "*********** 0���˳�������� ************" << endl;
	cout << "*********** 1������ְ����Ϣ ************" << endl;
	cout << "*********** 2����ʾְ����Ϣ ************" << endl;
	cout << "*********** 3��ɾ����ְְ�� ************" << endl;
	cout << "*********** 4���޸�ְ����Ϣ ************" << endl;
	cout << "*********** 5������ְ����Ϣ ************" << endl;
	cout << "*********** 6�����ձ������ ************" << endl;
	cout << "*********** 7����������ĵ� ************" << endl;
	cout << "****************************************" << endl;
}
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::add_Emp()
{
	cout << "���������ְ����������" << endl;

	int addNum = 0;//�����û�����������
	cin >> addNum;

	if (addNum <= 0)
	{
		cout << "��������" << endl;
	}
	else
	{
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker ** newSpace = new Worker*[newSize];

		//��ԭ�������ݷŵ��¿ռ�
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//���������
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "�������"<< i+1 << "����ְ���ı��" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//��������ְ�����浽������
			newSpace[this->m_EmpNum + i] = worker;

		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ�ָ��
		this->m_EmpArray = newSpace;

		//����ְ������
		this->m_EmpNum = newSize;

		//��ʾ���ְ��
		cout << "�ɹ����"<<addNum<<"����ְ��" << endl;
	}

	//��ְ����Ϣ���浽�ļ�
	this->save();

	system("pause");
	system("cls");
}
void WorkerManager::show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->get_EmpNum() <= 0)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}
void WorkerManager::del_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "������Ҫɾ����ְ��id��" << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);
		
		if (index != -1)  //�ҵ�ְ��������ɾ������
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--; //���������м�¼����Ա����

			this->save();

			cout << "ɾ���ɹ�" << endl;
		}
		else
		{
			cout << "δɾ���ɹ���ְ��������" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return 0;
}
void WorkerManager::mod_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "�ļ�Ϊ�գ��޸�ʧ��" << endl;
	}
	else
	{
		cout << "������Ҫ�޸ĵ�ְ��id��"<<endl;
		int id;
		cin >> id;

		int index = this->isExist(id);
		if (index != -1)
		{
			//���ҵ���ְ��
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "���ҵ�" <<id <<"��ְ�����������µ�ְ���ţ�"<< endl;
			cin >> newId;

			cout << "��������������" << endl;
			cin >> newName;

			cout << "�������¸�λ��" << endl;
			cout << "1����ְͨ����" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ壺" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId,newName,dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//�������ݵ�������
			this->m_EmpArray[index] = worker;

			cout << "�޸ĳɹ�" << endl;

			this->save();  //�������ݵ��ļ���

		}
		else
		{
			cout << "�޸�ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::find_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "�ļ�Ϊ�գ��޸�ʧ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1������ְ����Ų��ң�" << endl;
		cout << "2������ְ���������ң�" << endl;
	

		int select = 0;
		cin >> select;
		if (select ==1)
		{
			//���ձ�Ų�
			int id;
			cout << "������Ҫ���ҵ�ְ����ţ�" << endl;
			cin >> id;

			int index = this->isExist(id);
			if (index != -1)
			{
				//�ҵ�ְ��
				cout << "�ҵ�ְ������Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "δ�鵽ְ����Ϣ" << endl;
			}
		}
		else if(select ==2)
		{
			//����������
			string name;
			cout << "������Ҫ���ҵ�ְ��������" << endl;
			cin >> name;
			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "���ҳɹ���ְ�����Ϊ��" << this->m_EmpArray[i]->m_Id
						<<"����Ϣ���£�"<< endl;

					flag = true;
					//��ʾ�ҵ���ְ����Ϣ
					this->m_EmpArray[i]->showInfo();
				}

			}
			if (flag == false)
			{
				cout << "δ�ҵ�ְ����Ϣ" << endl;
			}
		}
		else
		{
			cout << "��������" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::sort_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "�ļ�Ϊ�գ��޸�ʧ��" << endl;
	}
	else
	{
		cout << "����������ķ�ʽ��" << endl;
		cout << "1������ְ���������" << endl;
		cout << "2������ְ����Ž���" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i; //������Сֵ�������ֵ�±�
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  //����
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//�ж�һ��ʼ�϶�����Сֵ�������ֵ�ǲ�����Сֵ�������ֵ�����ǵĻ�����
			if (i != minOrMax)
			{
				Worker *temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
			
		}
		this->save();
		cout << "����ɹ���" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::clean_File()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ�ϣ�" << endl;
	cout << "2�����أ�" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//��ģʽ ios::trunc �������ɾ���ļ������´���
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			this->m_EmpNum = 0;
			delete[] m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}

		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "  " << this->m_EmpArray[i]->m_Name
			<< "  " << this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ������
		num++;
	}
	ifs.close();

	return num;
}
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker *worker = NULL;
		//���ݲ�ͬ�Ĳ���ID������ͬ����
		if (dId == 1)  //��ͨԱ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //����
		{
			worker = new Manager(id, name, dId);
		}
		else //�ܲ�
		{
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

