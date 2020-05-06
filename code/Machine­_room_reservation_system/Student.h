#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "ComputerRoom.h"
#include "Identity.h"
#include "globalFile.h"
#include "OrderFile.h"

//ѧ����
class Student:public Identity
{
public:

	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id, string name, string pwd);

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//�˵�����
	virtual void operMenu();

	//ѧ��ѧ��
	int m_Id;

	vector<ComputerRoom> vCom;
};

