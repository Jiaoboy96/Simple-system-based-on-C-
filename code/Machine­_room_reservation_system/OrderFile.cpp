#include "OrderFile.h"

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	string data;  //日期
	string interval; //时间段
	string stuId; //学生ID
	string stuName;  //学生姓名
	string roomId;  //机房ID
	string status;  //预约状态

	this->m_Size = 0;  //记录的条数

	while (ifs >> data && ifs >> interval && ifs >> stuId && ifs >> stuName
		&& ifs >> roomId && ifs >> status)
	{
		/*cout << data << endl;
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomID << endl;
		cout << status << endl;
		cout << endl;*/


		string key;
		string value;

		map<string, string>m;
		//截取日期
		int pos = data.find(":");
		if (pos != -1)
		{
			key = data.substr(0, pos);
			value = data.substr(pos + 1, data.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		//截取时间段
		pos = interval.find(":");
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		//截取学生ID
		pos = stuId.find(":");
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		//截取学生名字
		pos = stuName.find(":");
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		//截取机房号
		pos = roomId.find(":");
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		//截取预约状态
		pos = status.find(":");
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);

			m.insert(make_pair(key, value));
		}
		
		//将小容器放大大容器中
		this->m_OrderData.insert(make_pair(this->m_Size, m));
		this->m_Size++;
		
	}

	ifs.close();
}

void OrderFile::updataOrder()
{

	if (this->m_Size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);

	for (int  i = 0; i < this->m_Size; i++)
	{
		ofs << "data:" << this->m_OrderData[i]["data"] << " ";
		ofs << "interval:" << this->m_OrderData[i]["interval"] << " ";
		ofs << "stuId:" << this->m_OrderData[i]["stuId"] << " ";
		ofs << "stuName:" << this->m_OrderData[i]["stuName"] << " ";
		ofs << "roomID:" << this->m_OrderData[i]["roomID"] << " ";
		ofs << "status:" << this->m_OrderData[i]["status"] << " " << endl;;
		
	}
	ofs.close();

}

OrderFile::~OrderFile()
{
}
