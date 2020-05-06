#include<iostream>
using namespace std;
#include"MyArray.hpp"

void PrintIntArray(MyArray	<int>& arr)
{
	for (int i = 0; i < 5; i++)
	{
		cout << arr[i] << endl;
	}
}
void test1()
{
	MyArray	<int> arr1(5);

	for (int i = 0; i < 5; i++)
	{
		//利用尾插法插入数据
		arr1.Push_Back(i);
	}
	cout << "arr1打印输出：" << endl;
	PrintIntArray(arr1);
	cout << "容量大小：" << arr1.getCapacity() << endl;
	cout << "数组大小：" << arr1.getSize() << endl;

	MyArray <int> arr2(arr1);
	cout << "arr2的打印输出：" << endl;
	PrintIntArray(arr2);

	//尾删
	arr2.Pop_Back();
	cout << "arr2尾删的打印输出：" << endl;
	cout << "容量大小：" << arr2.getCapacity() << endl;
	cout << "数组大小：" << arr2.getSize() << endl;

}

class Person
{
public:
	Person() {};
	Person(string name, int age)
	{
		this->m_Age = age;
		this->m_Name = name;
	}
	string m_Name;
	int m_Age;
};

void printPersonArray(MyArray<Person>& arr)
{
	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << "姓名：\t" << arr[i].m_Name << endl;
		cout << "年龄：\t" << arr[i].m_Age << endl;
	}
}

void test2()
{
	MyArray<Person> arr3(10);
	Person p1("孙悟空", 12);
	Person p2("猪八戒", 34);
	Person p3("嫦娥", 3);
	Person p4("安其拉", 243);
	Person p5("露娜", 432);

	arr3.Push_Back(p1);
	arr3.Push_Back(p2);
	arr3.Push_Back(p3);
	arr3.Push_Back(p4);
	arr3.Push_Back(p5);

	printPersonArray(arr3);

	cout << arr3.getCapacity() << endl;
	cout << arr3.getSize() << endl;
}

int main()
{
	//test1();
	test2();
	system("pause");

	return 0;
}