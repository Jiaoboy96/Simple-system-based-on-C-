//自己通用的数组类
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

	//拷贝函数
	MyArray(const MyArray& arr)
	{
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;
		//this->pAddress = arr.pAddress;  //浅拷贝

		//深拷贝
		this->pAddress = new T[arr.m_Size];
		//将arr中的数据拷贝过来
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
	}

	//operator=  防止浅拷贝
	MyArray& operator=(const MyArray& arr)
	{
		//先判断原来堆区是否有数据，如果有先释放,将自己的数据清零，接受arr的数据
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this->pAddress = NULL;
			this->m_Capacity = 0;
			this->m_Size = 0;
		}

		//深拷贝
		this->m_Capacity = arr.m_Capacity;
		this->m_Size = arr.m_Size;

		//深拷贝
		this->pAddress = new T[arr.m_Size];
		//将arr中的数据拷贝过来
		for (int i = 0; i < this->m_Size; i++)
		{
			this->pAddress[i] = arr.pAddress[i];
		}
		return *this;
	}

	//尾插法
	void Push_Back(const T& val)
	{
		//判断容量是否满载
		if (this -> m_Capacity == this->m_Size)
		{
			cout << "容量满载" << endl;
			return;
		}
		this->pAddress[this->m_Size] = val; //在数组末尾加入数据
		this->m_Size++; //更新数组大小
	}

	//尾删
	void Pop_Back()
	{
		//让用户访问不到最后一个元素，即为删除--逻辑删除
		if (this->m_Size == 0)
		{
			cout << "空数组" << endl;
			return;
		}
		this->m_Size--;
	}

	//通过下标方式访问数组数据
	T& operator[](int index)
	{
		return this->pAddress[index];
	}

	//返回数组的容量
	int getCapacity()
	{
		return this->m_Capacity;
	}

	//返回数组大小
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
	T * pAddress; //指针指向堆区开辟的真实数组
	int m_Capacity; //数组容量
	int m_Size; //数组大小
};


