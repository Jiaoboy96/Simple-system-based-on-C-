#include "SpeechManager.h"
#define FILENAME "speech.csv"

SpeechManager::SpeechManager()
{
	//��ʼ������������
	this->initSpeech();
	//����12��ѡ��
	this->create_Speaker();
	//���������¼
	this->loadRecord();
}


void SpeechManager::show_Menu()
{
	cout << "****************************************" << endl;
	cout << "*********** ��ӭ�μ��ݽ����� ***********" << endl;
	cout << "*********** 1����ʼ�ݽ����� ************" << endl;
	cout << "*********** 2���鿴�����¼ ************" << endl;
	cout << "*********** 3����ձ�����¼ ************" << endl;
	cout << "*********** 0���˳��������� ************" << endl;
	cout << "****************************************" << endl;

}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//�������ÿ�
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//����������ʼ��
	this->m_index = 1;
	//��ʼ����¼����
	this->m_Record.clear();
}

void SpeechManager::create_Speaker()
{
	string nameSeed = "ABCDEFGHIJKL";

	for (unsigned int i = 0; i < nameSeed.size(); i++)
	{
		string name = "ѡ��";
		name += nameSeed[i];
		
		Speaker	sp;
		sp.m_Name = name;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		//12��ѡ�ֱ��
		this->v1.push_back(i + 10001);

		//����Լ���Ӧѡ�� �ŵ�map������
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

void SpeechManager::startSpeech()
{
	//��һ�ֱ���
	//��ǩ
	speechDraw();
	//����
	speechContest();
	//��ʾ�������
	show_Score();
	//�ڶ��ֱ���
	this->m_index++;
	//��ǩ
	speechDraw();
	//����
	speechContest();
	//��ʾ���ս��
	show_Score();
	//�������
	saveRecord();

	//�������������¸��¼�¼
	this->initSpeech();
	this->create_Speaker();
	this->loadRecord();

	cout << "�������������" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "��" <<this->m_index<<"�ֱ������ڳ�ǩ��"<< endl;
	cout << "------------------------" << endl;
	cout << "��ǩ���˳�����£�" << endl;

	if (this->m_index == 1)
	{
		//��һ�ֱ���
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//�ڶ��ֱ���
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}

	cout << "----------------------" << endl;
	system("pause");
	cout << endl;

}

void SpeechManager::speechContest()
{
	cout << "----------------��" <<this->m_index<<"�ֱ�����ʽ��ʼ-----------------"<< endl;

	//׼����ʱ���� ���С��ɼ�
	//����Ϊkeyֵ
	multimap<double, int, greater<double>> groupScore;

	int num = 0;

	vector<int>v_Src; // ����ѡ������
	if (this->m_index ==1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//��������ѡ�ֽ��б���
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//��ί���
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double Score = (rand() % 401 + 600) / 10.0f; //600 ~1000
			//cout << Score << "  ";
			d.push_back(Score);
		}
		//cout << endl;
		
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();  //ȥ����߷ֺ���ͷ�
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);  //�ܷ�
		double avg = sum / (double)d.size();  //ƽ����
		
		//��ӡƽ����
		//cout << "ѡ�ֱ�ţ�" << *it << "  ѡ�����֣�" << this->m_Speaker[*it].m_Name << "  ѡ��ƽ���֣�" << avg << endl;;

		//��ƽ���ַŵ�map������
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//����ֵ������͵���ʱ������
		groupScore.insert(make_pair(avg, *it)); //key�ǵ÷֣�value��ѡ�ֱ��
		
		if (num % 6 == 0)  //ÿ�����˴�ӡһ�Σ���ӡ�����
		{
			cout << "��" << num / 6 << "С��������Σ�" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "��ţ�" << it->second << "  ������" << this->m_Speaker[it->second].m_Name << "  �ɼ���" <<it->first<< endl;
			}

			//ȡ��ǰ�����ŵ�v2��
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear();  //ÿ���������
		}
	}
	cout << "----------------��" << this->m_index << "�ֱ������-----------------" << endl;
	system("pause");
}

void SpeechManager::show_Score()
{
	cout << "------------��" << this->m_index << "�ֽ���ѡ����Ϣ���£�---------------" << endl;
	vector<int> v;
	if (this->m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}

	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "��ţ�" << *it << " ������" << m_Speaker[*it].m_Name << " �ɼ���" << m_Speaker[*it].m_Score[this->m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();

}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);  //�������ʽ���ļ�  --д�ļ�

	//��ÿ���˵�����д�뵽�ļ���
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//�ر��ļ�
	ofs.close();

	cout << "��¼�Ѿ����档" << endl;

	//�м�¼���ļ���Ϊ��
	this->fileIsEmpty = false;
	
}

void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //���ļ�

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//���ļ����
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ��" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;
	ifs.putback(ch);  //������Ķ�ȡ�ĵ����ַ�ȡ����

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string>v; // ���ÿ��ļ�¼
		int pos = -1;  //�鵽,��λ��
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//cout << "û���ҵ�" << endl;
				break;
			}
			string temp = data.substr(start, pos - start);
			v.push_back(temp);
			//cout << temp << endl;
			start = pos + 1;
		}
		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	/*for (map<int,vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	{
		cout << (it->first) + 1 << "��ھ���ţ�" << it->second[0] << "  ������" << it->second[1] << endl;
		cout << (it->first) + 1 << "���Ǿ���ţ�" << it->second[2] << "  ������" << it->second[3] << endl;
		cout << (it->first) + 1 << "�켾����ţ�" << it->second[4] << "  ������" << it->second[5] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
			{
				cout << "��"<<i + 1 << "��ھ���ţ�" << this->m_Record[i][0] << "  ������" << this->m_Record[i][1] << endl;
				cout << "��" << i + 1 << "���Ǿ���ţ�" << this->m_Record[i][2] << "  ������" << this->m_Record[i][3] << endl;
				cout << "��" << i + 1 << "�켾����ţ�" << this->m_Record[i][4] << "  ������" << this->m_Record[i][5] << endl;
				cout << endl;
			}
	}
	

	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "ȷ����գ�" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	
	int select  = 0;
	cin >> select;

	if (select == 1)
	{
		//ȷ�����
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeech();
		//����12��ѡ��
		this->create_Speaker();
		//���������¼
		this->loadRecord();

		cout << "��ճɹ�" << endl;
	}

	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}