//�Լ�ͨ�õ�������
#pragma once
#include<iostream>
#include<string>
using namespace std;

template<class T>
class MyArray
{
public:
	MyArray(int capacity)
	{
		this->m_Capacity = capacity;
		this->m_Size = 0;
		this->pAddress = new T[this->m_Capacity];
	}

	//��������
	MyArray(const MyArray& arr)
	{
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//this->pAddress = arr.pAddress;  //ǳ����

		//���
		this->pAddress = new T[arr.m_Size];
		//��arr�е����ݿ�������
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//operator=  ��ֹǳ����
	MyArray& operator=(const MyArray& arr)
	{
		//���ж�ԭ�������Ƿ������ݣ���������ͷ�,���Լ����������㣬����arr������
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}

		//���
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;

		//���
		this->pAddress = new T[arr.m_Size];
		//��arr�е����ݿ�������
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//β�巨
	void Push_Back(const T& val)
	{
		//�ж������Ƿ�����
		if (this -> m_Capacity == this->m_Size)
		{
			cout << "��������" << endl;
			return;
		}
		this->pAddress[this->m_Size] = val; //������ĩβ��������
		this->m_Size++; //���������С
	}

	//βɾ
	void Pop_Back()
	{
		//���û����ʲ������һ��Ԫ�أ���Ϊɾ��--�߼�ɾ��
		if (this->m_Size == 0)
		{
			cout << "������" << endl;
			return;
		}
		this->m_Size--;
	}

	//ͨ���±귽ʽ������������
	T& operator[](int index)
	{
		return this->pAddress[index];
	}

	//�������������
	int getCapacity()
	{
		return this->m_Capacity;
	}

	//���������С
	int getSize()
	{
		return this->m_Size;
	}

	~MyArray()
	{
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
		}
	}
private:
	T * pAddress; //ָ��ָ��������ٵ���ʵ����
	int m_Capacity; //��������
	int m_Size; //�����С
};

