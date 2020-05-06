#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
#include"Boss.h"
#include"Manager.h"
#include"Employee.h"
#include<fstream>
using namespace std;

#define FILENAME "empFlie.txt"

class WorkerManager
{
public:
	//构造函数
	WorkerManager();
	
	//展示菜单
	void show_Menu();
	//退出系统
	void exitSystem();
	//添加职工
	void add_Emp();
	//显示员工
	void show_Emp();
	//删除职工
	void del_Emp();
	//判断职工是否存在，存在返回职工位置，不存在返回-1
	int isExist(int id);
	//修改职工
	void mod_Emp();
	//查找职工
	void find_Emp();
	//将职工排序
	void sort_Emp();
	//清空文件
	void clean_File();
	//保存文件
	void save();
	//统计人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();

	//记录职工人数
	int m_EmpNum;
	//职工数组指针
	Worker ** m_EmpArray;
	//标志文件是否为空
	bool m_FileIsEmpty;

	//析构函数
	~WorkerManager();
};

