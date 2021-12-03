#include <iostream>
#include "DLL.h"

using namespace std;
int main() {
	int num = 0;
	string data;
	string data_name, data_num;
	struct DLL dll;
	system(" mode  con lines=30   cols=60 ");
	ifstream R_File("Phone_Data_List");
	ofstream W_File;

	R_File;
	while (1) {
		cout << "---------------------------------------------------------\n";
		cout << "< 1. 검색 > < 2. 수정 > < 3. 삭제 > < 4. 추가 > <5. 목록>\n";
		cout << "---------------------------------------------------------\n";

		switch (dll.get_int()) {
		case 1:
			system("cls");
			dll.Search_Node();
			break;

		case 2:
			system("cls");
			dll.Modify_Node();
			break;

		case 3:
			system("cls");
			dll.Delete_Node();
			break;

		case 4:
			dll.Insert_Node();
			dll.Print_data();
			break;

		case 5:
			system("cls");
			dll.Print_data();
			break;

		default:
			cout << "잘못입력하셨습니다.\n";
			break;
		}

	}
	return 0;
}
