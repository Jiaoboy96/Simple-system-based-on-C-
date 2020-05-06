#include "Manager.h"

Manager::Manager()
{
}

Manager::Manager(string name, string pwd)
{
	//初始化管理员信息
	this->m_Name = name;
	this->m_Pwd = pwd;

	//初始化容器 获取到文件的学生老师信息
	this->initVector();

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_MaxN)
	{
		vCom.push_back(com);
	}
	ifs.close();
	cout << "机房数量：" << vCom.size() << endl;
}

void Manager::operMenu()
{
	cout << "\t-------欢迎管理员："<<this->m_Name<<"登录-------"<< endl;
	cout << "\t------------------------------------\n";
	cout << "\t|                                  |\n";
	cout << "\t|          1、添加账号             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          2、查看账号             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          3、查看机房             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          4、清空预约             |\n";
	cout << "\t|                                  |\n";
	cout << "\t|          0、注销登录             |\n";
	cout << "\t|                                  |\n";
	cout << "\t------------------------------------\n";
	cout << "请输入你的选择：" << endl;
}

void Manager::addPerson()
{
	cout << "请输入添加的账号类型：" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName; //操作文件名
	string tip;  //提示id号
	string errorTip; //重复错误提示

	//文件操作对象
	ofstream ofs;

	int select = 0; //接受用户的选择
	cin >> select;

	if (select == 1)
	{
		fileName = STUDENT_FILE;
		tip = "请输入学号：";
		errorTip = "学号重复，请重新输入";
	}
	else
	{
		fileName = TEACHER_FILE;
		tip = "请输入职工编号：";
		errorTip = "职工号重复，请重新输入";
	}

	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	cout << tip << endl;

	while (true)
	{
		cin >> id;
		bool ret = checkRepeat(id, select);

		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}

	cout << "请输入姓名：" << endl;
	cin >> name;

	cout << "请输入密码：" << endl;
	cin >> pwd;

	//向文件添加数据
	ofs << id << " " << name << " " << pwd << " " << endl;

	system("pause");
	system("cls");

	ofs.close();

	//调用初始化的接口，重新更新文件数据
	this->initVector();
}


void printStudent(Student & s)
{
	cout << "学号：" << s.m_Id << " 姓名：" << s.m_Name << " 密码：" << s.m_Pwd << endl;
}
void printTeacher(Teacher & t)
{
	cout << "职工号：" << t.m_EmpId << " 姓名：" << t.m_Name << " 密码：" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "请选择查看内容" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;
	cin >> select;

	if (select == 1)
	{
		//查看学生
		cout << "所有学生信息如下：" << endl;
		for_each(vStu.begin(), vStu.end(), printStudent);
	}
	else
	{
		//查看老师
		cout << "所有老师信息如下：" << endl;
		for_each(vTea.begin(), vTea.end(), printTeacher);

	}

	system("pause");
	system("cls");
}

void Manager::showComputer()
{
	cout << "机房信息如下：" << endl;

	for (vector<ComputerRoom>::iterator it = vCom.begin(); it != vCom.end(); it++)
	{
		cout << "机房编号：" << it->m_ComId << " 机房容量：" << it->m_MaxN << endl;
	}

	system("pause");
	system("cls");
}

void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);

	if (!ofs.is_open())
	{
		cout << "未打开文件" << endl;
	}
	else
	{
		ofs.close();
		cout << "清空成功" << endl;
	}

	system("pause");
	system("cls");
}

void Manager::initVector()
{
	//清空容器
	vStu.clear();
	vTea.clear();

	//读取信息 学生
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}

	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	cout << "当前学生数量为：" << vStu.size() << endl;
	ifs.close();

	//读取信息 老师
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
		return;
	}

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	cout << "当前老师数量为：" << vTea.size() << endl;
	ifs.close();
}

bool Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		//检测学生
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (id == it->m_Id)
			{
				return true;
			}
		}
	}
	else
	{
		//检测老师
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (id == it->m_EmpId)
			{
				return true;
			}
		}
	}
	return false;
}
