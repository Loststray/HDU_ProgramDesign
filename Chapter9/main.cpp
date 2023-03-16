#include "Functions.h"

int main()
{
	system("mode con cols=130 lines=60");
	system("color 0E");
	Database db;
	while(1)
	{
		system("cls");
		int32_t op = Menu();
		bool empty = db.empty();
		switch (op)
		{
			case 1:
				if (empty)
					init_Read(db);
				else
				{
					std::cout << "Initlized";
					char tmp = _getch();
				}
				break;
			case 2:
				Add_Students(db);
				break;
			case 3:
				if (!empty)
				Delete_Students(db);
				break;
			case 4 :
				if (!empty)
				Find_Student_BY_Fuking_ID_Implementation(db);
				break;
			case 5:
				if (!empty)
				Find_Student_BY_Fuking_Name_Implementation(db);
				break;
			case 6:
				if (!empty)
				Modify_Students(db);
				break;
			case 7:
				//
				break;
			case 8:
				break;
			case 9:
				if (!empty)
				db.Sort_Data(BYID, false);
				break;
			case 10:
				if (!empty)
				db.Sort_Data(BYNAME, false);
				break;
			case 11:
				if (!empty)
				db.Sort_Data(BYSCORE, true);
				break;
			case 12:
				if (!empty)
				db.Sort_Data(BYSCORE, false);
				break;
			case 13:
				//
				break;
			case 14:
				if (!empty)
				Print_Data(db);
				break;
			case 15:
				if (!empty)
				Save_File(db);
				break;
			case 16: Read_File(db);
			default: break;
		}
	}
}
