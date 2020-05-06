#include "SpeechManager.h"
#define FILENAME "speech.csv"

SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();
	//创建12名选手
	this->create_Speaker();
	//加载往届记录
	this->loadRecord();
}


void SpeechManager::show_Menu()
{
	cout << "****************************************" << endl;
	cout << "*********** 欢迎参加演讲比赛 ***********" << endl;
	cout << "*********** 1、开始演讲比赛 ************" << endl;
	cout << "*********** 2、查看往届记录 ************" << endl;
	cout << "*********** 3、清空比赛记录 ************" << endl;
	cout << "*********** 0、退出比赛程序 ************" << endl;
	cout << "****************************************" << endl;

}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

void SpeechManager::initSpeech()
{
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//比赛轮数初始化
	this->m_index = 1;
	//初始化记录容器
	this->m_Record.clear();
}

void SpeechManager::create_Speaker()
{
	string nameSeed = "ABCDEFGHIJKL";

	for (unsigned int i = 0; i < nameSeed.size(); i++)
	{
		string name = "选手";
		name += nameSeed[i];
		
		Speaker	sp;
		sp.m_Name = name;
		sp.m_Score[0] = 0;
		sp.m_Score[1] = 0;

		//12名选手编号
		this->v1.push_back(i + 10001);

		//编号以及对应选手 放到map容器中
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}

}

void SpeechManager::startSpeech()
{
	//第一轮比赛
	//抽签
	speechDraw();
	//比赛
	speechContest();
	//显示晋级结果
	show_Score();
	//第二轮比赛
	this->m_index++;
	//抽签
	speechDraw();
	//比赛
	speechContest();
	//显示最终结果
	show_Score();
	//保存分数
	saveRecord();

	//比赛结束后，重新更新记录
	this->initSpeech();
	this->create_Speaker();
	this->loadRecord();

	cout << "本届比赛结束：" << endl;
	system("pause");
	system("cls");
}

void SpeechManager::speechDraw()
{
	cout << "第" <<this->m_index<<"轮比赛正在抽签："<< endl;
	cout << "------------------------" << endl;
	cout << "抽签结果顺序如下：" << endl;

	if (this->m_index == 1)
	{
		//第一轮比赛
		random_shuffle(v1.begin(),v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	else
	{
		//第二轮比赛
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
	cout << "----------------第" <<this->m_index<<"轮比赛正式开始-----------------"<< endl;

	//准备临时容器 存放小组成绩
	//分数为key值
	multimap<double, int, greater<double>> groupScore;

	int num = 0;

	vector<int>v_Src; // 比赛选手容器
	if (this->m_index ==1)
	{
		v_Src = v1;
	}
	else
	{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++)
	{
		num++;
		//评委打分
		deque<double>d;
		for (int i = 0; i < 10; i++)
		{
			double Score = (rand() % 401 + 600) / 10.0f; //600 ~1000
			//cout << Score << "  ";
			d.push_back(Score);
		}
		//cout << endl;
		
		sort(d.begin(), d.end(), greater<double>());
		d.pop_back();  //去掉最高分和最低分
		d.pop_front();

		double sum = accumulate(d.begin(), d.end(), 0.0f);  //总分
		double avg = sum / (double)d.size();  //平均分
		
		//打印平均分
		//cout << "选手编号：" << *it << "  选手名字：" << this->m_Speaker[*it].m_Name << "  选手平均分：" << avg << endl;;

		//将平均分放到map容器中
		this->m_Speaker[*it].m_Score[this->m_index - 1] = avg;

		//将打分的数据送到临时容器中
		groupScore.insert(make_pair(avg, *it)); //key是得分，value是选手编号
		
		if (num % 6 == 0)  //每六个人打印一次，打印完清空
		{
			cout << "第" << num / 6 << "小组比赛名次：" << endl;
			for (multimap<double,int,greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++)
			{
				cout << "编号：" << it->second << "  姓名：" << this->m_Speaker[it->second].m_Name << "  成绩：" <<it->first<< endl;
			}

			//取走前三名放到v2中
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

			groupScore.clear();  //每次清空容器
		}
	}
	cout << "----------------第" << this->m_index << "轮比赛完成-----------------" << endl;
	system("pause");
}

void SpeechManager::show_Score()
{
	cout << "------------第" << this->m_index << "轮晋级选手信息如下：---------------" << endl;
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
		cout << "编号：" << *it << " 姓名：" << m_Speaker[*it].m_Name << " 成绩：" << m_Speaker[*it].m_Score[this->m_index - 1] << endl;
	}
	cout << endl;
	system("pause");
	system("cls");
	this->show_Menu();

}

void SpeechManager::saveRecord()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out | ios::app);  //用输出方式打开文件  --写文件

	//将每个人的数据写入到文件中
	for (vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++)
	{
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << endl;

	//关闭文件
	ofs.close();

	cout << "记录已经保存。" << endl;

	//有记录，文件不为空
	this->fileIsEmpty = false;
	
}

void SpeechManager::loadRecord()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);  //读文件

	if (!ifs.is_open())
	{
		this->fileIsEmpty = true;
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//读文件情况
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;
	ifs.putback(ch);  //将上面的读取的单个字符取回来

	string data;
	int index = 0;
	while (ifs >> data)
	{
		//cout << data << endl;
		vector<string>v; // 存放每届的记录
		int pos = -1;  //查到,的位置
		int start = 0;

		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				//cout << "没有找到" << endl;
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
		cout << (it->first) + 1 << "届冠军编号：" << it->second[0] << "  分数：" << it->second[1] << endl;
		cout << (it->first) + 1 << "届亚军编号：" << it->second[2] << "  分数：" << it->second[3] << endl;
		cout << (it->first) + 1 << "届季军编号：" << it->second[4] << "  分数：" << it->second[5] << endl;
	}*/
}

void SpeechManager::showRecord()
{
	if (this->fileIsEmpty)
	{
		cout << "文件不存在或者记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Record.size(); i++)
			{
				cout << "第"<<i + 1 << "届冠军编号：" << this->m_Record[i][0] << "  分数：" << this->m_Record[i][1] << endl;
				cout << "第" << i + 1 << "届亚军编号：" << this->m_Record[i][2] << "  分数：" << this->m_Record[i][3] << endl;
				cout << "第" << i + 1 << "届季军编号：" << this->m_Record[i][4] << "  分数：" << this->m_Record[i][5] << endl;
				cout << endl;
			}
	}
	

	system("pause");
	system("cls");
}

void SpeechManager::clearRecord()
{
	cout << "确认清空？" << endl;
	cout << "1、确认" << endl;
	cout << "2、取消" << endl;
	
	int select  = 0;
	cin >> select;

	if (select == 1)
	{
		//确认清空
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeech();
		//创建12名选手
		this->create_Speaker();
		//加载往届记录
		this->loadRecord();

		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}