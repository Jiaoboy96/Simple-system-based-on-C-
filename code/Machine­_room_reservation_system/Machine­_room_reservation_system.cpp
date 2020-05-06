#include<iostream>
#include<fstream>
#include <string>
#include "globalFile.h"
#include"Identity.h"
#include "Manager.h"
#include "Student.h"
#include "Teacher.h"
using namespace std;

//进入管理员的子菜单
void managerMenu(Identity* &manager)
{
	while (true)
	{
		//调用管理员子类菜单
		manager->operMenu();

		//将父类指针转为子类指针，调用子类的其他接口
		Manager * man = (Manager*)manager;

		int select;
		cin >> select;

		if (select == 1) //添加账号
		{
			//cout << "添加账号" << endl;
			man->addPerson();
		}
		else if (select == 2) //查看账号
		{
			//cout << "查看账号" << endl;
			man->showPerson();
		}
		else if (select == 3)  //查看机房
		{
			//cout << "查看机房" << endl;
			man->showComputer();
		}
		else if (select == 4) // 清空预约
		{
			//cout << "清空预约" << endl;
			man->cleanFile();
		}
		else
		{
			delete manager;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入学生的子菜单
void studentMenu(Identity* &student)
{
	while (true)
	{
		//调用管理员子类菜单
		student->operMenu();

		//将父类指针转为子类指针，调用子类的其他接口
		Student * stu = (Student*)student;

		int select;
		cin >> select;

		if (select == 1) //申请预约
		{
			//cout << "申请预约" << endl;
			stu->applyOrder();
		}
		else if (select == 2) //查看预约
		{
			//cout << "查看预约" << endl;
			stu->showMyOrder();
		}
		else if (select == 3)  //查看所有预约
		{
			//cout << "查看所有预约" << endl;
			stu->showAllOrder();
		}
		else if (select == 4) // 取消预约
		{
			//cout << "取消预约" << endl;
			stu->cancelOrder();
		}
		else
		{
			delete student;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//进入老师的子菜单
void TeacherMenu(Identity* &teacher)
{
	while (true)
	{
		//调用管理员子类菜单
		teacher->operMenu();

		//将父类指针转为子类指针，调用子类的其他接口
		Teacher * tea = (Teacher*)teacher;

		int select;
		cin >> select;

		if (select == 1) //查看所有预约
		{
			//cout << "查看所有预约" << endl;
			tea->showAllOrder();
		}
		else if (select == 2) //审核预约
		{
			//cout << "审核预约" << endl;
			tea->validOrder();
		}
		else
		{
			delete teacher;
			cout << "注销成功" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
}

//登录功能  文件名 操作身份类型
void LoginIn(string filename, int type)
{
	//父类指针 用于指向子类对象
	Identity* person = NULL;

	//读文件
	ifstream ifs;
	ifs.open(filename, ios::in);

	//判断文件是否存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//准备信息 接受用户的信息
	int id = 0;
	string name;
	string pwd;

	//判断身份
	if (type == 1)  //学生身份
	{
		cout << "请输入你的学号" << endl;
		cin >> id;
	}
	else if (type == 2)  //老师身份
	{
		cout << "请输入你的职工号" << endl;
		cin >> id;
	}

	cout << "请输入用户名" << endl;
	cin >> name;

	cout << "请输入密码" << endl;
	cin >> pwd;

	if (type == 1)
	{
		//学生身份
		int fId;  //从文件读取的ID号
		string fName; //从文件读取的名字
		string fPwd; //从文件读取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "学生验证成功" << endl;
				system("pause");
				system("cls");
				//创建学生对象
				person = new Student(id,name,pwd);
				studentMenu(person);
				return;

			}
		}
	}
	else if (type == 2)
	{
		//老师身份
		int fId;  //从文件读取的ID号
		string fName; //从文件读取的名字
		string fPwd; //从文件读取的密码

		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息对比
			if (fId == id && fName == name && fPwd == pwd)
			{
				cout << "老师验证成功" << endl;
				system("pause");
				system("cls");
				//创建老师对象
				person = new Teacher(id, name, pwd);
				TeacherMenu(person);
				return;
			}
		}
	}
	else if (type == 3)
	{
		//管理员身份
		string fName; //从文件读取的名字
		string fPwd; //从文件读取的密码

		while (ifs >> fName && ifs >> fPwd)
		{
			//与用户输入的信息对比
			if (fName == name && fPwd == pwd)
			{
				cout << "管理员验证成功" << endl;
				system("pause");
				system("cls");
				//创建管理员对象
				person = new Manager(name, pwd);
				
				managerMenu(person);
				return;
			}
		}
	}

	cout << "验证失败" << endl;
	system("pause");
	system("cls");
}

int main()
{
	int select = 0;

	while (true)
	{
		cout << "----------------欢迎来的机房预约系统-------------" << endl;
		cout << endl;
		cout << "\t------------------------------------\n";
		cout << "\t|                                  |\n";
		cout << "\t|          1、学生代表             |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          2、老 师                |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          3、管理员               |\n";
		cout << "\t|                                  |\n";
		cout << "\t|          0、退  出               |\n";
		cout << "\t|                                  |\n";
		cout << "\t------------------------------------\n";
		cout << "请输入你的身份：" << endl;


		cin >> select;  //接受用户的选择

		switch (select)
		{
		case 1:  //学生身份
			LoginIn(STUDENT_FILE, 1);
			break;
		case 2:  //老师身份
			LoginIn(TEACHER_FILE, 2);
			break;
		case 3:  //管理员身份
			LoginIn(ADMIN_FILE, 3);
			break;
		case 0: //退出
		{
			cout << "欢迎下一次使用！" << endl;
			system("pause");
			return 0;
		}
		break;
		default:
			cout << "输入有误，重新输入：" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}