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
	//���캯��
	OrderFile();

	//����ԤԼ��¼
	void updataOrder();

	//��¼ԤԼ����
	int m_Size;

	//��¼����ԤԼ����Ϣ key��¼���� value��¼������Ϣ
	map<int, map<string, string>>m_OrderData;

	//��������
	~OrderFile();
};

