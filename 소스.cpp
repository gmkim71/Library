#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Book {
private:
	string  name; // 책 이름
	string  company; // 출판사
	string  date; // 입고일
	unsigned int price;// 가격
public:
	Book() {
		name = "";
		company = "";
		date = "";
		price = 0;
	}
	Book(string n, string c, string d, unsigned p)
		: name(n), company(c), date(d), price(p) {
	}

	string getName() { return name; }
	string getCompany() { return company; }
	string getDate() { return date; }
	void setName(string n) { name = n; }
	void setCompany(string c) { company = c; }
	void setDate(string d) { date = d; }
	void setPrice(unsigned p) { price = p; }

	unsigned getPrice() { return price; }
};

Book *p[10];
int count = 0;
void insert() {
	string blank, name, company, date;
	unsigned price;
	int n = ::count;
	p[n] = new Book;
	getline(cin, blank);
	cout << "도서명 : >>";
	getline(cin, name);
	cout << "출판사명 : >>";
	getline(cin, company);
	cout << "입고일 : >>";
	getline(cin, date);
	cout << "가격 : ";
	cin >> price;
	p[n]->setName(name);
	p[n]->setCompany(company);
	p[n]->setDate(date);
	p[n]->setPrice(price);
	::count++;
}

void list() {
	if (::count == 0) {
		cout << "표시할 데이터가 없습니다." << endl;
		return;
	}
	for (int i = 0; i < ::count; i++) {
		cout << i + 1 << "Record  "
			<< p[i]->getName() << " "
			<< p[i]->getCompany() << " "
			<< p[i]->getDate() << " "
			<< p[i]->getPrice() << endl;
	}
}

int get_record(int sel_record) {
	int target_record = 0;
	while (1) {
		cout << "대상 레코드 선택 (나가기: 0)";
		cin >> target_record;
		if (target_record == 0) return -1;
		if (target_record < 0 || target_record > ::count + 1) {
			cout << "범위 내가 아닙니다. 레코드 번호를 다시 선택하세요." << endl;
		}
		else {
			return target_record - 1;
		}
	}
}

void update_data() {
	int select = 0;
	string blank, name, company, date;
	unsigned price;
	int update_record;
	while (1) {
		cout << "도서명:1, 출판사명:2, 입고일:3, 가격:4, 나가기:5 >>";
		cin >> select;
		getline(cin, blank);
		switch (select)
		{
		case 1:
			cout << "도서명 :";
			getline(cin, name);
			break;
		case 2:
			cout << "출판사명 :";
			getline(cin, company);
			break;
		case 3:
			cout << "입고일 :";
			getline(cin, date);
			break;
		case 4:
			cout << "가격 :";
			cin >> price;
			break;
		default:
			break;
		}
		if (select == 5) return;
		if (select < 1 || select  > 5) {
			cout << " 다시 입력하세요(범위 초과)...!" << endl;
			continue;
		}
		else {
			update_record = get_record(select);
			if (update_record == -1) continue;
			if (select == 1)  p[update_record]->setName(name);
			if (select == 2)  p[update_record]->setCompany(company);
			if (select == 3)  p[update_record]->setDate(date);
			if (select == 4)  p[update_record]->setPrice(price);
			cout << "수정되었습니다..!" << endl;
			list();
		}
	}
}

void point_mem(int target) {
	for (int i = target; i <= ::count; i++) {
		p[i - 1] = p[i];
	}
	cout << target << "번 Record가 삭제되었습니다. 결과는..." << endl;
	delete p[::count];
	::count--;
}

void delete_record() {
	int select = 0;
	if (::count == 0) {
		cout << "레코드가 없습니다.";
		return;
	}

	while (1) {
		list();
		cout << "삭제할 레코드를 선택하세요..! (나가기: 0) >> ";
		cin >> select;
		if (select == 0) return;
		if (select < 0 || select > ::count + 1) {
			cout << "다시 입력하세요(범위 초과)..!" << endl;
			continue;
		}
		point_mem(select);
		if (::count == 0) return;
	}
}

void mem_free() {
	if (::count == 0) return;
	for (int i = 0; i < ::count; i++) {
		delete p[i];
	}
}  // 메모리 다 지우기 (반납)

void file_save() {
	if (::count == 0) {
		cout << "저장할 레코드가 없습니다." << endl;
	}
	ofstream fs;  // 출력
	fs.open("bookdb.txt");
	for (int i = 0; i < ::count; i++) {
		fs << p[i]->getName() << "," << p[i]->getCompany() << ","
			<< p[i]->getDate() << "," << p[i]->getPrice() << endl;   // 기록
	}
	cout << ::count << "개의 record를 저장하였습니다." << endl;
	fs.close();
}

void init() {
	ifstream fs;
	string linedata;
	string temp[4];
	int j = 0;
	fs.open("bookdb.txt");
	if (fs) {    // cout << "bookdb.txt 오픈 성공!!" << endl;
		while (getline(fs, linedata)) {   // cout << linedata << endl;
			for (int i = 0; i < linedata.size(); i++) {
				if (linedata[i] != ',') temp[j] += linedata[i];
				else {
					++j;
				}
			}
			p[::count] = new Book;
			p[::count]->setName(temp[0]);
			p[::count]->setCompany(temp[1]);
			p[::count]->setDate(temp[2]);
			unsigned price = stoi(temp[3]);
			p[::count]->setPrice(price);
			::count++;
			for (int i = 0; i <= j; i++) {
				temp[i] = "";
			}
			j = 0;
		}
		cout << ::count << "개 의 레코드를 읽어들였습니다.." << endl;
		// list();
		fs.close();
	}
}

int main() {
	init(); // 초기화
	int select = 0;
	cout << "*** 도서관리 시스템에 오신 것을 환영합니다." << endl;
	while (1) {
		cout << "등록:1, 수정:2, 보기:3, 레코드삭제:4, 종료:5";
		cout << ">>";
		cin >> select;
		if (select == 5) {
			file_save();
			mem_free();
			break; // 5는 프로그램 종료
		}
		switch (select)
		{
		case 1:
			insert();
			break;
		case 2:
			update_data();
			break;
		case 3:
			list();
			break;
		case 4:
			delete_record();
			break;
		default:
			break;
		}
		cout << endl;
	}
	cout << "시스템을 종료합니다!" << endl;
	return 0;
}
