#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include<deque>
#include <string>
#include <algorithm>
#include <numeric>
#include "Speaker.h"
using namespace std;

//设计演讲比赛管理类
class SpeechManager
{
public:
	SpeechManager();

	//展示菜单
	void show_Menu();
	//退出系统
	void exitSystem();
	//初始化容器和属性
	void initSpeech();
	//创建12名选手
	void create_Speaker();
	//开始比赛
	void startSpeech();
	//抽签
	void speechDraw();
	//比赛
	void speechContest();
	//显示比赛分数
	void show_Score();
	//保存记录
	void saveRecord();
	//查看记录
	void loadRecord();
	//展示往届分数
	void showRecord();
	//清空记录
	void clearRecord();

	//比赛选手 容器 12人
	vector<int> v1;
	//第一轮晋级容器 6人
	vector<int> v2;
	//胜利前三名容器 3人
	vector<int> vVictory;
	//存放编号 对应选手 容器
	map<int, Speaker> m_Speaker;

	//记录比赛轮数
	int m_index;
	//判断文件是否问空
	bool fileIsEmpty;
	//存放往届记录的容器 int存放第几届
	map<int, vector<string>>m_Record;

	~SpeechManager();
};

