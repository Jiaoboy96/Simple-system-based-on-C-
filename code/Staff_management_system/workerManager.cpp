#include "workerManager.h"

WorkerManager::WorkerManager()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//文件不存在
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，并且没有数据
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空" << endl;
		//初始化属性
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并且记录数据
	int num = this->get_EmpNum();
	cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker*[this->m_EmpNum];
	//将文件中的数据，存到数组中
	this->init_Emp();
	
}
void WorkerManager::show_Menu()
{
	cout << "****************************************" << endl;
	cout << "******** 欢迎使用职工管理系统！ ********" << endl;
	cout << "*********** 0、退出管理程序 ************" << endl;
	cout << "*********** 1、增加职工信息 ************" << endl;
	cout << "*********** 2、显示职工信息 ************" << endl;
	cout << "*********** 3、删除离职职工 ************" << endl;
	cout << "*********** 4、修改职工信息 ************" << endl;
	cout << "*********** 5、查找职工信息 ************" << endl;
	cout << "*********** 6、按照编号排序 ************" << endl;
	cout << "*********** 7、清空所有文档 ************" << endl;
	cout << "****************************************" << endl;
}
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}
void WorkerManager::add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;

	int addNum = 0;//保存用户的输入数量
	cin >> addNum;

	if (addNum <= 0)
	{
		cout << "输入有误" << endl;
	}
	else
	{
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker ** newSpace = new Worker*[newSize];

		//将原来的数据放到新空间
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;

			cout << "请输入第"<< i+1 << "个新职工的编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
			cin >> name;

			cout << "请选择该职工的岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;
			cin >> dSelect;

			Worker * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}

			//将创建的职工保存到数组中
			newSpace[this->m_EmpNum + i] = worker;

		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间指向
		this->m_EmpArray = newSpace;

		//更新职工人数
		this->m_EmpNum = newSize;

		//提示添加职工
		cout << "成功添加"<<addNum<<"名新职工" << endl;
	}

	//将职工信息保存到文件
	this->save();

	system("pause");
	system("cls");
}
void WorkerManager::show_Emp()
{
	//判断文件是否为空
	if (this->get_EmpNum() <= 0)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}
void WorkerManager::del_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "文件不存在或记录为空" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "输入你要删除的职工id：" << endl;
		int id = 0;
		cin >> id;

		int index = this->isExist(id);
		
		if (index != -1)  //找到职工，进行删除操作
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i+1];
			}
			this->m_EmpNum--; //更新数组中记录的人员个数

			this->save();

			cout << "删除成功" << endl;
		}
		else
		{
			cout << "未删除成功，职工不存在" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkerManager::isExist(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			//找到职工
			index = i;
			break;
		}
	}
	return 0;
}
void WorkerManager::mod_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "文件为空，修改失败" << endl;
	}
	else
	{
		cout << "请输入要修改的职工id："<<endl;
		int id;
		cin >> id;

		int index = this->isExist(id);
		if (index != -1)
		{
			//查找到该职工
			delete this->m_EmpArray[index];

			int newId = 0;
			string newName;
			int dSelect = 0;

			cout << "查找到" <<id <<"号职工，请输入新的职工号："<< endl;
			cin >> newId;

			cout << "请输入新姓名：" << endl;
			cin >> newName;

			cout << "请输入新岗位：" << endl;
			cout << "1、普通职工：" << endl;
			cout << "2、经理：" << endl;
			cout << "3、老板：" << endl;
			cin >> dSelect;

			Worker *worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId,newName,dSelect);
				break;
			case 2:
				worker = new Manager(newId, newName, dSelect);
				break;
			case 3:
				worker = new Boss(newId, newName, dSelect);
				break;
			default:
				break;
			}

			//更新数据到数组中
			this->m_EmpArray[index] = worker;

			cout << "修改成功" << endl;

			this->save();  //更新数据到文件中

		}
		else
		{
			cout << "修改失败，未找到此职工" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::find_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "文件为空，修改失败" << endl;
	}
	else
	{
		cout << "请输入查找的方式：" << endl;
		cout << "1、按照职工编号查找：" << endl;
		cout << "2、按照职工姓名查找：" << endl;
	

		int select = 0;
		cin >> select;
		if (select ==1)
		{
			//按照编号查
			int id;
			cout << "请输入要查找的职工编号：" << endl;
			cin >> id;

			int index = this->isExist(id);
			if (index != -1)
			{
				//找到职工
				cout << "找到职工，信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else
			{
				cout << "未查到职工信息" << endl;
			}
		}
		else if(select ==2)
		{
			//按照姓名查
			string name;
			cout << "请输入要查找的职工姓名：" << endl;
			cin >> name;
			//加入判断是否查到的标志
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					cout << "查找成功，职工编号为：" << this->m_EmpArray[i]->m_Id
						<<"的信息如下："<< endl;

					flag = true;
					//显示找到的职工信息
					this->m_EmpArray[i]->showInfo();
				}

			}
			if (flag == false)
			{
				cout << "未找到职工信息" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}
void WorkerManager::sort_Emp()
{
	if (this->get_EmpNum() <= 0)
	{
		cout << "文件为空，修改失败" << endl;
	}
	else
	{
		cout << "请输入排序的方式：" << endl;
		cout << "1、按照职工编号升序：" << endl;
		cout << "2、按照职工编号降序：" << endl;

		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minOrMax = i; //声明最小值或者最大值下标
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  //升序
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
				else  //降序
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minOrMax = j;
					}
				}
			}

			//判断一开始认定的最小值或者最大值是不是最小值或者最大值，不是的话交换
			if (i != minOrMax)
			{
				Worker *temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
			
		}
		this->save();
		cout << "排序成功：" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::clean_File()
{
	cout << "确认清空？" << endl;
	cout << "1、确认：" << endl;
	cout << "2、返回：" << endl;

	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//打开模式 ios::trunc 如果存在删除文件并重新创建
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i] != NULL)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = NULL;
				}
			}
			this->m_EmpNum = 0;
			delete[] m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_FileIsEmpty = true;
		}

		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "  " << this->m_EmpArray[i]->m_Name
			<< "  " << this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数
		num++;
	}
	ifs.close();

	return num;
}
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker *worker = NULL;
		//根据不同的部门ID创建不同对象
		if (dId == 1)  //普通员工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //经理
		{
			worker = new Manager(id, name, dId);
		}
		else //总裁
		{
			worker = new Boss(id, name, dId);
		}

		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}

