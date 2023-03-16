//
// Created by xzl on 2023/3/9.
//

#ifndef PROJECTDATABASE__INTERFACES_H_
#define PROJECTDATABASE__INTERFACES_H_
#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
#define BYNAME 1
#define BYSCORE 2
#define BYID 3
class students
{
 public:
	int64_t ID{0};
	double_t sum{0},average{0};
	std::string name;
	std::vector<double_t> score;
	void Calc_Score();
	students(int64_t ,const std::string&);
};
class Database
{
 private:
	int32_t n,m;
	std::list<students> data;
	std::vector<std::list<students>::iterator> sorted_list;
	std::unordered_map<int64_t ,std::list<students>::iterator> ID_MAP;
	std::unordered_multimap<std::string ,std::list<students>::iterator> name_MAP;
 public:
		std::list<students>::iterator NULLDATA();
		int32_t get_classes();
		void Read_STU(students&);
		void Init(int32_t,int32_t);
		void Delete_STU(std::list<students>::iterator);
		std::list<students>::iterator Find_Student_ID(int64_t);
	    std::pair<std::unordered_multimap<std::string,std::list<students>::iterator>::iterator,
		std::unordered_multimap<std::string,std::list<students>::iterator>::iterator>
			Find_Student_name(const std::string&);
		const std::vector<std::list<students>::iterator>& Print_Data();
		void Sort_Data(int16_t ,bool );
		void Save_To_File(std::ofstream&);
		void Read_From_File(std::ifstream&);
		bool empty();
};
void Set_Position(int32_t,int32_t);
int32_t Menu();
void Find_Student_BY_Fuking_Name_Implementation(Database& );
void Find_Student_BY_Fuking_ID_Implementation(Database& );
void init_Read(Database& );
void Add_Students(Database& );
void Print_Data(Database&);
void Delete_Students(Database&);
void Read_File(Database&);
void Save_File(Database&);
void Modify_Students(Database&);
#endif //PROJECTDATABASE__INTERFACES_H_
