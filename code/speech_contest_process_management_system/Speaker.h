#pragma once
#include <iostream>
using namespace std;

//选手类
class Speaker
{
public:
	Speaker();
	~Speaker();

	string m_Name;  //选手名字
	double m_Score[2];  //选手分数-两轮
};
