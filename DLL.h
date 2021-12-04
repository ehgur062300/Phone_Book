#include <iostream>
#include <fstream>

struct Phone_data {
	std::string name;
	std::string num;
};

struct Node {
	Phone_data data; //전화번호부의 이름과 번호 접근
	Node* prev; // 이전 노드 접근
	Node* next; // 다음 노드 접근
	Node() {
		data = { "","" };
		prev = next = NULL;
	}

	Node(std::string _name, std::string _num, Node* p = NULL, Node* n = NULL) {
		data.name = _name;
		data.num = _num;
		prev = p;
		next = n;
	}
};

struct DLL {
	Node* head;

	DLL() {
		head = NULL;
	}
	~DLL() {
		Node* h;
		while (head->next != NULL) {
			h = head->next;
			delete head;
			head = h;
		}
	}

	void ReadFile() { //파일 읽어오기
		std::string name, num;
		std::ifstream readFile;
		readFile.open("Phone_Data_List.txt");
		if (readFile.fail()) {
			std::cerr << "<< error : 파일을 찾을수 없습니다. >>\n";
			return;
		}
		while (!readFile.eof()) {
			if (readFile >> name >> num) { Insert_Node(name, num); }
			else { break; }
		}
		readFile.close();
	}

	void WriteFile() { //파일에 쓰기
		Node* node = head;
		std::ofstream writeFile;
		writeFile.open("Phone_Data_List.txt");
		if (writeFile.fail()) {
			std::cerr << "<< error >>" << std::endl;
			return;
		}
		while (1) {
			if (node == NULL) { break; }
			writeFile << node->data.name;
			writeFile.width(15);
			writeFile << node->data.num << "\n";
			node = node->next;
		}
		writeFile.close();
	}

	//문자 입력 예외처리 함수
	int get_int() {
		int num = 0;
		std::cout << "선택 : ";
		std::cin >> num;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(10, '\n');
			std::cout << " << error : 올바른 형식으로 입력해 주세요. >>\n";
		}
		else { return num; }
	}

	//전화번호부 출력 함수
	bool Print_data() {
		int cnt = 0;
		bool io = false;
		Node* ptr = head;
		Node* temp = ptr;
		std::cout << "_________________________________________________________\n";
		std::cout << "<<                         목록                        >>\n";
		std::cout << "\n";
		while (1) {//노드가 비어있으면 io = true를 반환
			if (temp == NULL) {
				io = true;
				break;
			}

			std::cout << "[" << cnt << "] " << temp->data.name;
			std::cout.width(15);
			std::cout << temp->data.num << "\n";

			if (temp->next == NULL) { break; }
			temp = temp->next;
			cnt++;
		}// 노드가 비어있지 않으면 io = false를 반환
		std::cout << "_________________________________________________________\n";
		return io;
	}

	//추가 함수
	void Insert_Node(std::string name = "", std::string num = "") {
		std::string data_name = name, data_num = num;
		Node* ptr = head;

		Print_data();
		system("cls");

		// 파일에 저장된 정보를 불러오는게 아닌 메인에서 추가를 선택했을 경우
		if (name == "") {
			std::cout << "---------------------------------------------------------\n\n";
			std::cout << "추가할 정보 (이름 and 번호) : ";
			std::cin >> data_name >> data_num;
		}

		Node* New_Node = new Node(data_name, data_num, NULL, NULL);

		while (1) {
			if (head == NULL) { //전화번호부가 비어있을때
				head = New_Node;
				break;
			}
			else {
				if (ptr->data.name > New_Node->data.name) {
					if (ptr == head) { // 새로운 노드가 첫번째 노드보다 작을 때
						ptr->prev = New_Node;
						New_Node->next = ptr;
						head = New_Node;
						break;
					}

					else { // 중간에 값 삽입
						New_Node->prev = ptr->prev;
						New_Node->prev->next = New_Node;
						ptr->prev = New_Node;
						New_Node->next = ptr;
						break;

					}
				}
				else if (ptr->next == NULL) // 마지막값 일 때
				{
					New_Node->prev = ptr;
					ptr->next = New_Node;
					break;
				}
				ptr = ptr->next;
			}
		}
		system("cls");
		WriteFile();
	}

	void Delete_Node() {
		int cnt = 0;
		bool io = false;
		std::string data = "";
		Node* ptr = head;
		Node* temp = ptr;

		if (Print_data()) {
			std::cout << "삭제할 정보가 존재하지 않습니다.\n";
			return;
		}

		else {
			std::cout << "---------------------------------------------------------\n\n";
			std::cout << "삭제할 정보(이름 or 번호) : ";
			std::cin >> data;

			while (temp != NULL) {
				if (temp->data.name == data) { cnt++; }
				temp = temp->next;
			}

			if (cnt > 1) {
				temp = ptr;
				cnt = 0;
				system("cls");
				std::cout << "_________________________________________________________\n";
				std::cout << "<<                     중복된 정보                     >>\n";
				while (temp != NULL) {
					if (temp->data.name == data) {
						std::cout << "[" << cnt << "] " << temp->data.name << "     " << temp->data.num << "\n";
						cnt++;
					}
					temp = temp->next;
				}

				std::cout << "---------------------------------------------------------\n\n";
				std::cout << "삭제할 정보(전화번호) : ";
				std::cin >> data;

			}
			temp = ptr;
			while (ptr != NULL) {
				if (ptr->data.name == data || ptr->data.num == data) { io = true; break; }
				else {
					temp = ptr;
					ptr = ptr->next;
				}
			}

			if (io == false) { std::cout << "입력하신 정보는 존재하지 않습니다.\n"; return; }

			else if (temp == ptr) {
				temp->prev = NULL;
				temp = temp->next;
				head = temp;
				delete ptr;
				std::cout << "정보가 삭제되었습니다. \n";
			}
			else if (ptr->next == NULL && temp != ptr) { temp->next = NULL; delete ptr; }

			else {
				temp = ptr->prev;
				ptr->next->prev = temp;
				temp->next = ptr->next;
				delete ptr;
				std::cout << "정보가 삭제되었습니다. \n";
			}
		}
		WriteFile();
	}


	//수정된 연락처 정렬
	void Modify_sort(Node* target) {
		Node* Cur_Node = target;

		while (1) {
			if (Cur_Node->next != NULL && target->data.name > Cur_Node->next->data.name) {
				Cur_Node = Cur_Node->next;
				if (Cur_Node->next == NULL) { break; }
			}
			else if (Cur_Node->prev != NULL && target->data.name < Cur_Node->prev->data.name) {
				Cur_Node = Cur_Node->prev;
				if (Cur_Node->prev == NULL) { break; }
			}
			else { break; }
		}

		if (target == head) {//수정할 정보가 헤드일때
			if (Cur_Node->data.name < target->data.name && Cur_Node->next != NULL) {
				head = target->next;
				target->next = Cur_Node->next;
				Cur_Node->next->prev = target;
				target->prev = Cur_Node;
				Cur_Node->next = target;
			}
			else if (Cur_Node->data.name < target->data.name && Cur_Node->next == NULL) {
				head = target->next;
				target->next = NULL;
				target->prev = Cur_Node;
				Cur_Node->next = target;
			}
		}
		else if (target->next == NULL) {//수정할 정보가 tail일때
			if (Cur_Node->data.name > target->data.name && Cur_Node->prev != NULL) {
				target->prev->next = NULL;
				Cur_Node->prev->next = target;
				target->prev = Cur_Node->prev;
				target->next = Cur_Node;
				Cur_Node->prev = target;
			}

			else if (Cur_Node->data.name > target->data.name && Cur_Node->prev == NULL) {
				target->prev->next = NULL;
				target->next = Cur_Node;
				Cur_Node->prev = target;
				head = target;
			}
		}
		//수정할 정보가 헤드가 아니고 tail도 아닐때
		else if (target->prev != NULL && target->next != NULL) {
			if (Cur_Node->data.name > target->data.name && Cur_Node->prev == NULL) {
				target->prev->next = target->next;
				target->next->prev = target->prev;
				head = target;
				head->next = Cur_Node;
				Cur_Node->prev = head;
			}
			else if (Cur_Node->data.name > target->data.name && Cur_Node->prev != NULL) {
				target->prev->next = target->next;
				target->next->prev = target->prev;
				Cur_Node->prev->next = target;
				target->prev = Cur_Node->prev;
				target->next = Cur_Node;
				Cur_Node->prev = target;
			}
			else if (Cur_Node->data.name < target->data.name) {
				if (Cur_Node->next != NULL) {
					target->next->prev = target->prev;
					target->prev->next = target->next;
					target->next = Cur_Node->next;
					target->prev = Cur_Node;
					Cur_Node->next->prev = target;
					Cur_Node->next = target;
				}
				else {
					target->next->prev = target->prev;
					target->prev->next = target->next;
					target->next = NULL;
					target->prev = Cur_Node;
					Cur_Node->next = target;
				}
			}
		}
		else { return; }
	}

	//수정 함수
	void Modify_Node() {
		int data_idx = 0;
		std::string data_name, data_num;
		Node* ptr = head;
		Node* temp = ptr;

		if (Print_data()) {
			std::cout << "수정할 정보가 존재하지 않습니다.\n";
			return;
		}

		else {
			std::cout << "---------------------------------------------------------\n\n";
			std::cout << "수정할 정보(index num) : ";
			std::cin >> data_idx;


			std::cout << "변경을 원하지 않으시는 정보는 no를 입력해주세요\n";
			std::cout << "수정할 정보(이름) : ";
			std::cin >> data_name;

			std::cout << "수정할 정보(번호) : ";
			std::cin >> data_num;

			while (1) {
				if (data_idx == 0) { break; }
				temp = temp->next;
				if (data_idx != 0 && temp == NULL) {
					std::cout << "존재하지 않는 idx 번호입니다.";
					return;
				}
				data_idx--;
			}

			if (data_name == "no" && data_num != "no") {
				temp->data.num = data_num;
				WriteFile();
			}

			else if (temp->next == NULL && temp->prev == NULL) {
				if (data_num == "no" && data_name != "no") {
					temp->data.name = data_name;
					WriteFile();
				}

				else if (data_num != "no" && data_name != "no") {
					temp->data.name = data_name;
					temp->data.num = data_num;
					WriteFile();
				}

				else { return; }
			}

			else {
				if (data_num == "no" && data_name != "no") {
					temp->data.name = data_name;
					Modify_sort(temp);
					WriteFile();
				}

				else if (data_num != "no" && data_name != "no") {
					temp->data.name = data_name;
					temp->data.num = data_num;
					Modify_sort(temp);
					WriteFile();
				}
				else { return; }
			}
		}
	}

	//검색 함수
	void Search_Node() {
		int cnt = 0;
		std::string data = "";
		Node* ptr = head;
		Node* temp = ptr;
		if (Print_data()) { std::cout << "연락처에 정보가 없습니다.\n"; return; }
		else {
			std::cout << "검색할 정보(이름 or 번호) : ";
			std::cin >> data;

			system("cls");
			std::cout << "_________________________________________________________\n";
			std::cout << "<<                     검색된 정보                     >>\n";
			while (temp != NULL) {
				if (temp->data.name == data || temp->data.num == data) {

					std::cout << "[" << cnt << "] " << temp->data.name << "     " << temp->data.num << "\n";
					cnt++;
				}
				temp = temp->next;
			}
			if (cnt == 0) { std::cout << "검색하신 정보는 존재하지 않는 정보입니다.\n"; }
			std::cout << "\n";
		}
	}
};
