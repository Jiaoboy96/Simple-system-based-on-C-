#include "Student.h"

Student::Student()
{
}

Student::Student(int id, string name, string pwd)
{
	//初始化属性
	this->m_Id = id;
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxN)
	{
		vCom.push_back(com);
	}
	ifs.close();
}

void Student::applyOrder()
{
	int data = 0; //日期 周一~周五
	int interval = 0; //时间段 上午~下午
	int room = 0;  //机房编号 1~3

	cout << "机房开放时间是周一到周五！" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	cout << "请输入申请预约的时间：" << endl;


	while (true)
	{
		cin >> data;
		if (data >= 1 && data <= 5)
		{
			break;
		}
		cout << "输入错误，重新输入：" << endl;
	}

	cout << "请输入申请预约的时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;

	while (true)
	{
		cin >> interval;
		if (interval >= 1 && interval <= 2)
		{
			break;
		}
		cout << "输入错误，重新输入：" << endl;
	}

	cout << "请选择机房：" << endl;
	for (unsigned int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "号机房的容量：" << vCom[i].m_MaxN << endl;
	}
	while (true)
	{
		cin >> room;
		if (room >= 1 && room <= 3)
		{
			break;
		}
		cout << "输入错误，重新输入：" << endl;
	}

	cout << "预约成功，审核中！" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "data:" << data << " ";
	ofs << "interval:" << interval << " ";
	ofs << "stuId:" << this->m_Id << " ";
	ofs << "stuName:" << this->m_Name << " ";
	ofs << "roomID:" << room << " ";
	ofs << "status:" << 1 << endl;

	ofs.close();

	system("pause");
	system("cls");

}

void Student::showMyOrder()
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

		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
		{
			cout << "预约的日期：周" << of.m_OrderData[i]["data"]<<" ";
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

	system("pause");
	system("cls");
}

void Student::showAllOrder()
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

void Student::cancelOrder()
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
		if (this->m_Id == atoi(of.m_OrderData[i]["stuId"].c_str()))
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

	cout << "请输入取消的记录，0代表返回" << endl;
	unsigned int select = 0;
	
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
				of.m_OrderData[v[select - 1]]["status"] = "0";
				of.updataOrder();

				cout << "已经取消预约" << endl;
				break;
			}
		}
		cout << "输入有误" << endl;
	}

	system("pause");
	system("cls");

}

void Student::operMenu()
{
	cout << "\t-------欢迎学生代表：" << this->m_Name << "登录-------" << endl;
	cout << "\t------------------------------------\n";
	cout << "\t|                                  |\n";
	cout << "\t|          1、申请预约             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          2、查看我的预约         |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          3、查看机房所有预约     |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          4、取消预约             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          0、注销登录             |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	cout << "请输入你的选择：" << endl;
}
