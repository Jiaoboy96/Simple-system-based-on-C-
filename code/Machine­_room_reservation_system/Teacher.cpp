#include "Teacher.h"

Teacher::Teacher()
{
}

Teacher::Teacher(int empId, string name, string pwd)
{
	this->m_EmpId = empId;
	this->m_Name = name;
	this->m_Pwd = pwd;
}

void Teacher::operMenu()
{
	cout << "\t-------欢迎老师：" << this->m_Name << "登录-------" << endl;
	cout << "\t------------------------------------\n";
	cout << "\t|                                  |\n";
	cout << "\t|          1、查看所有预约         |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          2、审核预约             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          0、注销登录             |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	cout << "请输入你的选择：" << endl;
}

void Teacher::showAllOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_Size; i++)
	{
		// string转int
		// string利用.c_str() 转const char *
		//利用atoi ( const char *)转int

		cout << i + 1 << "、";
		cout << "预约的日期：周" << of.m_OrderData[i]["data"] << " ";
		cout << "时间段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
		cout << "机房号：" << of.m_OrderData[i]["roomID"] << " ";
		cout << "学号：" << of.m_OrderData[i]["stuId"] << " ";
		cout << "姓名：" << of.m_OrderData[i]["stuName"] << " ";

		string status = "状态：";
		if (of.m_OrderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_OrderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_OrderData[i]["status"] == "-1")
		{
			status += "预约失败，审核未通过";
		}
		else
		{
			status += "预约取消";
		}
		cout << status << endl;

	}

	system("pause");
	system("cls");
}

void Teacher::validOrder()
{
	OrderFile of;

	if (of.m_Size == 0)
	{
		cout << "没有预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或者预约成功的记录可以取消，请输入取消的记录：" << endl;

	int index = 1;
	vector<int>v; // 存放在最大容器的下标编号
	for (int i = 0; i < of.m_Size; i++)
	{
		//先判断是自身学号
		if (this->m_EmpId == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			//再做筛选 审核中或者预约成功
			if (of.m_OrderData[i]["status"] == "1" || of.m_OrderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约的日期：周" << of.m_OrderData[i]["data"] << " ";
				cout << "时间段：" << (of.m_OrderData[i]["interval"] == "1" ? "上午" : "下午") << " ";
				cout << "机房号：" << of.m_OrderData[i]["roomID"] << " ";

				string status = "状态：";
				if (of.m_OrderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_OrderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				else if (of.m_OrderData[i]["status"] == "-1")
				{
					status += "预约失败，审核未通过";
				}
				else
				{
					status += "预约取消";
				}
				cout << status << endl;

			}
		}
	}

	cout << "请输入审核的预约记录，0代表返回" << endl;
	unsigned int select = 0;
	int ret = 0;

	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "请输入审核结果：" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;

				if (ret == 1)
				{
					of.m_OrderData[v[select - 1]]["status"] = "2";
				}
				else
				{
					of.m_OrderData[v[select - 1]]["status"] = "-1";
				}
				
				of.updataOrder();

				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");

}
