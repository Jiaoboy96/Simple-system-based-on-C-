#pragma once
#include <iostream>
#include "globalFile.h"
#include <fstream>
#include <string>
#include <map>
using namespace std;


class OrderFile
{
public:
	//构造函数
	OrderFile();

	//更新预约记录
	void updataOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约的信息 key记录条数 value记录具体信息
	map<int, map<string, string>>m_OrderData;

	//析构函数
	~OrderFile();
};

