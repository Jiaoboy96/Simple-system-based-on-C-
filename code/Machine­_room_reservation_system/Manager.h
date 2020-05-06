#pragma once
#include "Identity.h"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "globalFile.h"
#include "Student.h"
#include "Teacher.h"
#include "ComputerRoom.h"

//����Ա��
class Manager:public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void operMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴������Ϣ
	void showComputer();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ������
	void initVector();

	//����ظ� ����1 ���ѧ��/ְ���� ����2 �������
	bool checkRepeat(int id,int type);

	//ѧ������
	vector<Student>vStu;

	//��ʦ����
	vector<Teacher>vTea;

	//��������
	vector<ComputerRoom>vCom;
};

