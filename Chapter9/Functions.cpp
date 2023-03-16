//
// Created by xzl on 2023/3/9.
//

#ifndef PROJECTDATABASE__FUNCTIONS_H_
#define PROJECTDATABASE__FUNCTIONS_H_
#include <utility>
#include "Interfaces.h"
const int32_t POS_X[4] = {35, 40, 50, 65};
students::students(int64_t id, const std::string &n)
{
	ID = id;
	name = n;
}
void students::Calc_Score()
{
	sum = 0;
	for (auto i : score)
		sum += i;
	average = sum / (double_t)score.size();
}
void Database::Read_STU(students &NewSTU)
{
	data.push_back(NewSTU);
	ID_MAP[NewSTU.ID] = --data.end();
	name_MAP.emplace(NewSTU.name, --data.end());
	sorted_list.emplace_back(--data.end());
}
void Database::Init(int32_t nout, int32_t mout)
{
	this->n = nout, this->m = mout;
	ID_MAP.clear();
	name_MAP.clear();
	data.clear();
	sorted_list.clear();
	ID_MAP.reserve(nout << 1);
	name_MAP.reserve(nout << 1);
}
void Database::Delete_STU(std::list<students>::iterator pos)
{
	ID_MAP.erase(pos->ID);
	name_MAP.erase(pos->name);
	data.erase(pos);
	sorted_list.clear();
	n = data.size();
}
std::list<students>::iterator Database::Find_Student_ID(int64_t Target_ID)
{
	if (ID_MAP.count(Target_ID))
		return ID_MAP[Target_ID];
	else
		return data.end();
}
std::pair<std::unordered_multimap<std::string, std::list<students>::iterator>::iterator,
		  std::unordered_multimap<std::string, std::list<students>::iterator>::iterator> Database::Find_Student_name(
	const std::string &Target_name)
{
	if (name_MAP.count(Target_name))
		return name_MAP.equal_range(Target_name);
	else
		return {name_MAP.end(), name_MAP.end()};
}
const std::vector<std::list<students>::iterator>& Database::Print_Data()
{
	if (sorted_list.empty())
		for(auto it = data.begin();it != data.end();it++)
			sorted_list.emplace_back(it);
	return sorted_list;
}
void Database::Sort_Data(const int16_t types, const bool Is_Decending)
{
	if (types == BYNAME)
	{
		auto cmp = [&](const std::list<students>::iterator &a, const std::list<students>::iterator &b)
		{
			return Is_Decending ^ (a->name > b->name);
		};
		std::sort(sorted_list.begin(), sorted_list.end(), cmp);
	}
	if (types == BYID)
	{
		auto cmp = [&](const std::list<students>::iterator &a, const std::list<students>::iterator &b)
		{
			return Is_Decending ^ (a->ID > b->ID);
		};
		std::sort(sorted_list.begin(), sorted_list.end(), cmp);
	}
	if (types == BYSCORE)
	{
		auto cmp = [&](const std::list<students>::iterator &a, const std::list<students>::iterator &b)
		{
			return Is_Decending ^ (a->sum > b->sum);
		};
		std::sort(sorted_list.begin(), sorted_list.end(), cmp);
	}
	std::cout << "排序完毕";
}
void Database::Save_To_File(std::ofstream& fout)
{
	fout << std::fixed << std::setprecision(2);
	fout << n << ' ' << m << '\n';
	for (const auto &rec : data)
	{
		fout << rec.ID << ' ' << rec.name << '\n';
		for (const auto &S : rec.score)
			fout << S << ' ';
		fout << '\n';
		fout << rec.sum << ' ' << rec.average << '\n';
	}
	fout.close();
}
void Database::Read_From_File(std::ifstream &fin)
{
	fin >> n >> m;
	sorted_list.clear();
	data.clear();
	ID_MAP.clear();
	name_MAP.clear();
	for (int i = 0; i < n; i++)
	{
		int64_t NID;
		std::string Ntmp;
		fin >> NID >> Ntmp;
		students tmp(NID, Ntmp);
		for (int j = 0; j < m; j++)
		{
			double_t t;
			fin >> t;
			tmp.score.push_back(t);
		}
		tmp.Calc_Score();
		Read_STU(tmp);
	}
	fin.close();
}
bool Database::empty()
{
	return data.empty();
}
std::list<students>::iterator Database::NULLDATA()
{
	return data.end();
}
int32_t Database::get_classes()
{
	return m;
}
void Set_Position(const int32_t x, const int32_t y)
{
	HANDLE HandleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {static_cast<SHORT>(x), static_cast<SHORT>(y)};
	SetConsoleCursorPosition(HandleOut, pos);
}
int32_t Menu()
{
	int32_t y = 5, x = 0;
	Set_Position(POS_X[2], y);
	std::cout << "学生成绩管理系统\n";
	for (int i = 0; i < 2; i++)
	{
		Set_Position(POS_X[0], ++y);
		for (int j = 0; j < 55; j++)
			std::cout << '-';
	}
	Set_Position(POS_X[0], ++y);
	std::cout << "1.输入学生信息"; // O(n)
	Set_Position(POS_X[3], y);
	std::cout << "2.增加学生信息";// O(1 * len)
	Set_Position(POS_X[0], y += 2);
	std::cout << "3.删除学生信息";// O(1 * len)
	Set_Position(POS_X[3], y);
	std::cout << "4.按学号查找信息"; // O(1)
	Set_Position(POS_X[0], y += 2);
	std::cout << "5.按姓名查找信息";// O (1)
	Set_Position(POS_X[3], y);
	std::cout << "6.修改学生信息"; //O(1)
	Set_Position(POS_X[0], y += 2);
	std::cout << "7.计算学生成绩"; //O(1)
	Set_Position(POS_X[3], y);
	std::cout << "8.计算课程成绩";// O(1)
	Set_Position(POS_X[0], y += 2);
	std::cout << "9.按照学号排序";// O(nlogn)
	Set_Position(POS_X[3], y);
	std::cout << "10.按照姓名排序";// O(nlogn)
	Set_Position(POS_X[0], y += 2);
	std::cout << "11.总成绩升序";// O(nlogn)
	Set_Position(POS_X[3], y);
	std::cout << "12.总成绩降序";// O(nlogn)
	Set_Position(POS_X[0], y += 2);
	std::cout << "13.学生成绩统计";
	Set_Position(POS_X[3], y);
	std::cout << "14.打印学生成绩"; // O(n)
	Set_Position(POS_X[0], y += 2);
	std::cout << "15.学生记录存盘";
	Set_Position(POS_X[3], y);
	std::cout << "16.学生记录读取";
	for (int i = 0; i < 2; i++)
	{
		Set_Position(POS_X[0], ++y);
		for (int j = 0; j < 55; j++)
			std::cout << '-';
	}
	Set_Position(POS_X[0], ++y);
	std::cout << "请输入你想要进行的功能 [  ]\b\b\b";
	std::cin >> x;
	return x;
}
void Find_Student_BY_Fuking_Name_Implementation(Database &db)
{
	system("cls");
	std::cout << "你的名字?????\n";
	std::string fuckers;
	std::cin >> fuckers;
	auto range = db.Find_Student_name(fuckers);
	std::vector<students> tmpstu;
	for (auto it = range.first; it != range.second; it++)
		tmpstu.push_back(*(it->second));
	std::cout << tmpstu.size() << '\n';
	for (auto &it : tmpstu)
		std::cout << it.name << ' ' << it.ID << '\n';
	_getch();
}
void init_Read(Database &db)
{
	system("cls");
	int32_t y = 6;
	Set_Position(POS_X[1], y);
	std::cout << "请输入 学生人数 和 课程数量";
	int32_t n, m;
	std::cin >> n >> m;
	db.Init(n,m);
	for (int i = 0; i < n; i++)
	{
		int64_t ID;
		std::string tmp;
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入 学号 与 姓名:\t";
		std::cin >> ID >> tmp;
		students NewSTU(ID, tmp);
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入" << m << "门课程成绩:";
		for (int32_t j = 0; j < m; j++)
		{
			double_t t;
			std::cin >> t;
			NewSTU.score.push_back(t);
		}
		NewSTU.Calc_Score();
		db.Read_STU(NewSTU);
	}
}
void Read_File(Database &db)
{
	system("cls");
	std::string filename;
	//std::cout << "请输入文件路径";
	//std::cin >> filename;
	if (filename.empty())
		filename = R"(C:\Users\20774\CLionProjects\ProjectDatabase\student.txt)";
	std::ifstream fin(filename.c_str());
	if (!fin.is_open())
	{
		system("cls");
		std::cout << "无法打开指定文件";
		_getch();
		return;
	}
	db.Read_From_File(fin);
	std::cout << "读入完成";
	_getch();
}
void Delete_Students(Database &db)
{
	system("cls");
	int64_t ID;
	std::cout << "请输入ID";
	std::cin >> ID;
	auto pos = db.Find_Student_ID(ID);
	if (pos == db.NULLDATA())
	{
		std::cout << "没有找到";
		_getch();
		return;
	}
	std::cout << std::setw(15) << pos->ID << std::setw(15) << pos->name;
	for (auto &i : pos->score)
		std::cout << i;
	std::cout << pos->sum << ' ' << pos->average;
	std::cout << "是否删除记录（Y/N）?";
	char opt;
	std::cin >> opt;
	if (tolower(opt) == 'y')
	{
		db.Delete_STU(pos);
		std::cout << "删除完毕";
	} else if (tolower(opt) == 'n')
		std::cout << "不删除";
	else
		std::cout << "非法操作";
	_getch();
}
void Print_Data(Database &db)
{
	system("cls");
	auto sorted_list = db.Print_Data();
	Set_Position(20, 10);
	std::cout << "学号\t姓名\t\t";
	for (int i = 1; i <=(**sorted_list.begin()).score.size(); i++)
		std::cout << "课程" << i << "\t\t";
	std::cout << "总分\t\t平均分";
	int32_t y = 10;
	for (const auto &rec : sorted_list)
	{
		Set_Position(12, y += 2);
		std::cout << std::right << std::setw(15) << rec->ID << std::right << std::setw(15) << rec->name;
		for (const auto &S : rec->score)
			std::cout << std::fixed << std::setw(15) << std::setprecision(2) << S;
		std::cout << std::fixed << std::setw(15) << std::setprecision(2) << rec->sum << std::right << std::setw(15)
				  << rec->average;
	}
	_getch();
}
void Save_File(Database &db)
{
	system("cls");
	std::string filename;
	//std::cout << "请输入文件路径";
	//std::cin >> filename;
	if (filename.empty())
		filename = R"(C:\Users\20774\CLionProjects\ProjectDatabase\fucker.txt)";
	std::ofstream fout(filename.c_str());
	if (!fout.is_open())
	{
		system("cls");
		std::cout << "无法打开指定文件";
		_getch();
		return;
	}
	db.Save_To_File(fout);
	std::cout << "存盘完成";
	_getch();
}
void Modify_Students(Database &db)
{
	system("cls");
	int64_t ID;
	std::cout << "输入ID:\n";
	std::cin >> ID;
	auto pos = db.Find_Student_ID(ID);
	if (pos == db.NULLDATA())
	{
		std::cout << "非法ID";
		return;
	}
	std::cout << pos->ID << ' ' << pos->name << '\n';
	for (auto &i : pos->score)
		std::cout << i << ' ';
	std::cout << '\n';
	std::cout << pos->sum << ' ' << pos->average << '\n';
	std::cout << "是否修改记录（Y/N）?";
	char opt;
	std::cin >> opt;
	int32_t y = 6;
	if (tolower(opt) == 'y')
	{
		int64_t New_ID,m = db.get_classes();
		std::string name;
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入 学号 与 姓名:\t";
		std::cin >> New_ID >> name;
		pos->ID = New_ID;
		pos->name = name;
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入" << m << "门课程成绩:";
		for (int32_t j = 0; j < m; j++)
		{
			double_t t;
			std::cin >> t;
			pos->score[j] = t;
		}
		pos->Calc_Score();
		std::cout << "修改完毕";
	}
	else if (tolower(opt) == 'n')
		std::cout << "不修改";
	else
		std::cout << "非法操作";
	_getch();
}
void Add_Students(Database &db)
{
	system("cls");
	int32_t y = 6;
	Set_Position(POS_X[1], y);
	std::cout << "请输入增加学生人数";
	int32_t n, m = db.get_classes();
	std::cin >> n;
	for (int i = 0; i < n; i++)
	{
		int64_t ID;
		std::string tmp;
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入 学号 与 姓名:\t";
		std::cin >> ID >> tmp;
		students NewSTU(ID, tmp);
		Set_Position(POS_X[0], ++y);
		std::cout << "请输入" << m << "门课程成绩:";
		for (int32_t j = 0; j < m; j++)
		{
			double_t t;
			std::cin >> t;
			NewSTU.score.push_back(t);
		}
		NewSTU.Calc_Score();
		db.Read_STU(NewSTU);
	}
	std::cout << "读入完成";
	_getch();
}
void Find_Student_BY_Fuking_ID_Implementation(Database &db)
{
	system("cls");
	std::cout << "你的ID?????\n";
	int64_t ID;
	std::cin >> ID;
	auto pos = db.Find_Student_ID(ID);
	if (pos == db.NULLDATA())
	{
		std::cout << "没有记录";
		_getch();
		return;
	}
	std::cout << std::right << std::setw(15) << pos->ID << std::right << std::setw(15) << pos->name;
	for (const auto &S : pos->score)
		std::cout << std::fixed << std::setw(15) << std::setprecision(2) << S;
	std::cout << std::fixed << std::setw(15) << std::setprecision(2) << pos->sum << std::right << std::setw(15)
			  << pos->average;
	std::cout << "找到了";
	_getch();
}
#endif //PROJECTDATABASE__FUNCTIONS_H_
