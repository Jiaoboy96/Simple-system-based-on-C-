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
	//���캯��
	WorkerManager();
	
	//չʾ�˵�
	void show_Menu();
	//�˳�ϵͳ
	void exitSystem();
	//���ְ��
	void add_Emp();
	//��ʾԱ��
	void show_Emp();
	//ɾ��ְ��
	void del_Emp();
	//�ж�ְ���Ƿ���ڣ����ڷ���ְ��λ�ã������ڷ���-1
	int isExist(int id);
	//�޸�ְ��
	void mod_Emp();
	//����ְ��
	void find_Emp();
	//��ְ������
	void sort_Emp();
	//����ļ�
	void clean_File();
	//�����ļ�
	void save();
	//ͳ������
	int get_EmpNum();
	//��ʼ��Ա��
	void init_Emp();

	//��¼ְ������
	int m_EmpNum;
	//ְ������ָ��
	Worker ** m_EmpArray;
	//��־�ļ��Ƿ�Ϊ��
	bool m_FileIsEmpty;

	//��������
	~WorkerManager();
};

