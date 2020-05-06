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

//����ݽ�����������
class SpeechManager
{
public:
	SpeechManager();

	//չʾ�˵�
	void show_Menu();
	//�˳�ϵͳ
	void exitSystem();
	//��ʼ������������
	void initSpeech();
	//����12��ѡ��
	void create_Speaker();
	//��ʼ����
	void startSpeech();
	//��ǩ
	void speechDraw();
	//����
	void speechContest();
	//��ʾ��������
	void show_Score();
	//�����¼
	void saveRecord();
	//�鿴��¼
	void loadRecord();
	//չʾ�������
	void showRecord();
	//��ռ�¼
	void clearRecord();

	//����ѡ�� ���� 12��
	vector<int> v1;
	//��һ�ֽ������� 6��
	vector<int> v2;
	//ʤ��ǰ�������� 3��
	vector<int> vVictory;
	//��ű�� ��Ӧѡ�� ����
	map<int, Speaker> m_Speaker;

	//��¼��������
	int m_index;
	//�ж��ļ��Ƿ��ʿ�
	bool fileIsEmpty;
	//��������¼������ int��ŵڼ���
	map<int, vector<string>>m_Record;

	~SpeechManager();
};

