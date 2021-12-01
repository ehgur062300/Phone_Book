#include <iostream>
#include "DLL.h"

using namespace std;

int main() {
	int num = 0;
	string data;
	string data_name, data_num;
	struct DLL dll;

	dll.Print_data();
	while (1) {
		cout << "---------------------------------------------------------\n";
		cout << "<< 1. 검색 >>  << 2. 수정 >>  << 3. 삭제 >>  << 4. 추가 >>\n";
		cout << "---------------------------------------------------------\n";

		switch (dll.get_int()) {
		case 1:
			system("cls");
			dll.Search_Node();
			dll.Print_data();
			break;

		case 2:
			system("cls");
			dll.Modify_Node();
			dll.Print_data();
			break;

		case 3:
			system("cls");
			dll.Delete_Node();
			dll.Print_data();
			break;

		case 4:
			system("cls");
			dll.Insert_Node();
			dll.Print_data();
			break;
		}
	}
	return 0;
}
