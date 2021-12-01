#include <iostream>
#include <string>

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
		return num;
	}

	//전화번호부 출력 함수
	bool Print_data() {
		int cnt = 0;
		bool io = false;
		Node* ptr = head;
		Node* temp = ptr;
		while (1) {
			if (ptr == NULL) { 
				std::cout << "정보가 존재하지 않습니다. 추가해주세요\n";
				io = true;
				break;
			}
			std::cout << "---------------------------------------------------------\n";
			std::cout << "[" << cnt << "] " << temp->data.name << "     " << temp->data.num << "\n";
			if (temp->next == NULL) { break; }
			temp = temp->next;
			cnt++;
		}
		return io;
	}

	//추가 함수
	void Insert_Node() {
		std::string data_name = "", data_num = "";
		Node* ptr = head;
		Node* next_Node = ptr;

		Print_data();
		std::cout << "---------------------------------------------------------\n\n";
		std::cout << "추가할 정보 (이름 and 번호) : ";
		std::cin >> data_name >> data_num;
		
		Node* New_Node = new Node(data_name, data_num, NULL, NULL);
		
		while (1) {
			if (head == NULL) { //전화번호부가 비어있을때
				head = New_Node;
				break;
			}
			else {
				if (ptr->data.name > New_Node->data.name) {
					if (ptr == head) { // 새로운 노드가 첫번째 노드보다 작을 때
						Node* New_Node = new Node(data_name, data_num, NULL, NULL);
						ptr->prev = New_Node;
						New_Node->next = ptr;
						head = New_Node;
						break;
					}

					else { // 중간에 값 삽입
						Node* New_Node = new Node(data_name, data_num, NULL, NULL);
						New_Node->prev = ptr->prev;
						New_Node->prev->next = New_Node;
						ptr->prev = New_Node;
						New_Node->next = ptr;
						break;

					}
				}
				else if (ptr->next == NULL) // 마지막값 일 때
				{
					Node* New_Node = new Node(data_name, data_num, NULL, NULL);
					New_Node->prev = ptr;
					ptr->next = New_Node;
					break;
				}
				ptr = ptr->next;
			}
		}	
	}

	void Delete_Node() {
		std::string data = "";
		Node* ptr = head;
		Node* temp = ptr;

		if (Print_data()) { return; }

		else {
			std::cout << "---------------------------------------------------------\n\n";
			std::cout << "삭제할 정보(이름 or 번호) : ";
			std::getline(std::cin, data);
			

			while (ptr != NULL) {
				if (ptr->data.name == data || ptr->data.num == data) { break; }
				else {
					temp = ptr;
					ptr = ptr->next;
				}
			}

			if (ptr == NULL) { std::cout << "삭제할 정보가 존재하지 않습니다.\n"; }

			else if (temp == ptr) {
				temp->prev = NULL;
				temp = temp->next;
				head = temp;
				delete ptr;
				std::cout << "정보가 삭제되었습니다. \n";
			}
			else if (ptr->next == NULL && temp != ptr) { delete ptr; }

			else {
				temp = ptr->prev;
				ptr->next->prev = temp;
				temp->next = ptr->next;
				delete ptr;
				std::cout << "정보가 삭제되었습니다. \n";
			}
		}
		system("cls");
	}

	void Next_Node_Check(Node* next_Node, Node* ptr) { //수정되기 전 노드의 next와 수정된 노드의 비교함수
		next_Node->next->prev = ptr;
		ptr->next = next_Node->next;
		next_Node->prev = ptr->prev;
		ptr->prev->next = next_Node;
		ptr->prev = next_Node;
		next_Node->next = ptr;

		ptr = ptr->next;
	}

	void Prev_Node_Check(Node* prev_Node, Node* ptr) {//수정되기 전 노드의 prev와 수정된 노드의 비교함수
		ptr->next->prev = prev_Node;
		prev_Node->next = ptr->next;
		prev_Node->prev->next = ptr;
		ptr->prev = prev_Node->prev;
		ptr->next = prev_Node;

		ptr = ptr->prev;

	}
	//수정 함수
	void Modify_Node() {
		int num = 0;
		std::string data_name = "", data_num = "";
		Node* ptr = head;
		Node* temp = ptr;
		Node* prev_Node = ptr;
		Node* next_Node = ptr;

		if (Print_data()) { return; }

		else {
			std::cout << "---------------------------------------------------------\n\n";
			num = get_int();
			std::cout << "변경을 원하지 않으시는 정보는 no를 입력해주세요\n";
			std::cout << "수정할 정보(이름) : ";
			std::cin >> data_name;

			if (head == NULL) { std::cout << "수정할 정보가 존재하지 않습니다.\n";  return; }
			while (num == 0) {
				temp = temp->next;
				next_Node = temp->next;
				prev_Node = temp->prev;
				num--;
			}

			if (data_name == "no") { 
				std::cin >> data_num;
				temp->data.num = data_num;
			}

			else if (data_num == "no") {
				temp->data.name = data_name;
				while (1) {
					if (prev_Node == NULL) {
						if (next_Node->data.name < temp->data.name) { Next_Node_Check(next_Node, temp); }
						else { break; }
					}

					else if (next_Node == NULL) {
						if (prev_Node->data.name > temp->data.name) { Prev_Node_Check(prev_Node, temp); }
						else { break; }
					}

					else {
						if (prev_Node->data.name > temp->data.name) { Prev_Node_Check(prev_Node, temp); }
						else if (next_Node->data.name < temp->data.name) { Next_Node_Check(next_Node, temp); }
					}
				}
			}
			else {
				temp->data.name = data_name;
				temp->data.num = data_num;
				while (1) {
					prev_Node = temp->prev;
					next_Node = temp->next;
					if (prev_Node == NULL) {
						if (next_Node->data.name < temp->data.name) { Next_Node_Check(next_Node, temp); }
						else { break; }
					}

					else if (next_Node == NULL) {
						if (prev_Node->data.name > temp->data.name) { Prev_Node_Check(prev_Node, temp); }
						else { break; }
					}

					else {
						if (prev_Node->data.name > temp->data.name) { Prev_Node_Check(prev_Node, temp); }
						else if (next_Node->data.name < temp->data.name) { Next_Node_Check(next_Node, temp); }
					}
				}

			}
		}
	}

	//검색 함수
	void Search_Node() {
		std::string data = "";
		Node* ptr = head;
		Node* temp = ptr;
		if (Print_data()) { return; }
		else {
			std::cout << "검색할 정보(이름 or 번호 or 한 단어) : ";
			std::cin >> data;

			while (temp != NULL) {
				if (temp->data.name == data || temp->data.num == data || temp->data.name.find(data) != std::string::npos) {
					std::cout << "---------------------------------------------------------\n";
					std::cout << temp->data.name << "     " << temp->data.num << "\n";
					temp = temp->next;
				}
			}
		}
	}
	
};
