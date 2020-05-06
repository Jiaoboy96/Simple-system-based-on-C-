#pragma once
#include <vector>
#include <fstream>
#include <string>
#include "ComputerRoom.h"
#include "Identity.h"
#include "globalFile.h"
#include "OrderFile.h"

//学生类
class Student:public Identity
{
public:

	//默认构造
	Student();

	//有参构造
	Student(int id, string name, string pwd);

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//菜单界面
	virtual void operMenu();

	//学生学号
	int m_Id;

	vector<ComputerRoom> vCom;
};

