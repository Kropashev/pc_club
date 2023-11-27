#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <set>

std::vector<std::string> myfuncline(std::string s, char d) {
	std::stringstream stm(s);
	std::string str;
	std::vector<std::string> buff;
	while (getline(stm, str, d)) {
		buff.push_back(str);
	}
	return buff;
}

bool free_pc(std::vector<bool> x) {
	for (auto i : x)
		if (x[i])
			return x[i];
	return false;
}

struct mytime {
	int hour;
	int min;

	mytime();
	mytime(int h, int m);

	bool right_time();
	mytime int_time(int x);
	int time_int(mytime x);
	std::string tostring();
};
mytime::mytime() {
	 hour = 0;
	 min = 0;
 }
mytime::mytime(int h, int m) {
	hour = h;
	min = m;
}
bool  mytime::right_time() {
	if (hour <= 24 and min <= 60)
		return true;
	return false;
}
mytime mytime::int_time(int x) {
	mytime t;
	t.hour = x / 60;
	t.min = x % 60;
	return t;
}
int time_int(mytime x) {
	return x.hour + (x.min * 60);
}
std::string mytime::tostring() {
	 std::string str;
	 if (hour > 9)
		 str+= std::to_string(hour);
	 else {
		 str.push_back('0');
		 str+= std::to_string(hour);
	 }
	 str.push_back(':');
	 if (min > 9)
		 str += std::to_string(min);
	 else {
		 str.push_back('0');
		 str += std::to_string(min);
	 }
	 return str;
 }

int time_work(mytime tmp, mytime s) {
	int inttime_end = tmp.hour * 60 + tmp.min;
	int inttime_start = s.hour * 60 + s.min;
	return inttime_end - inttime_start;
}
mytime plus_time_work(mytime time_work_pc, int time_int) {
	time_work_pc.hour += time_int / 60;
	time_work_pc.min += time_int % 60;
	return time_work_pc;
}
int plus_revenue_pc(int price, int inttime_res) {
	int res = 0;
	res += price * (inttime_res / 60);
	if (inttime_res % 60 > 0)
		res += price;
	return res;
}

struct Pc_club {
	std::queue<std::string> queue;				// ������� �� ������� �� �����
	std::set<std::string> in_club;				// ���� ������� ������ �����
	std::map<int, mytime> pc_start_session;		// ����� ����� � ������� ������ ������� ��������
	std::map<std::string, int> visiter_pc;		// ����� �������� � ������� �� 
	std::vector<bool> busy_pc;					// ���������� �������� �� ��
	std::vector<int> revenue_pc;				// ������� ������� ������ �-��� ��
	std::vector<mytime> time_work_pc;			// ������� ������� ���������� �-��� ��
	int price;
	int num_pc;

	int revenue_and_time(std::string name, mytime time_event);
	void remove_session(std::string name, int pc_id);
	void create_session(int id_pc, mytime time_event, std::string name);
};

int  Pc_club::revenue_and_time(std::string name, mytime time_event) {
	
	int pc_id = visiter_pc[name];
	int inttime_res = time_work(time_event, pc_start_session[pc_id]);
	time_work_pc[pc_id - 1] = plus_time_work(time_work_pc[pc_id - 1], inttime_res);
	revenue_pc[pc_id - 1] += plus_revenue_pc(price, inttime_res);
	return pc_id;
}
void Pc_club::remove_session(std::string name, int pc_id) {
	busy_pc[pc_id - 1] = true;
	pc_start_session.erase(pc_id);
	visiter_pc.erase(name);
}
void Pc_club::create_session(int id_pc, mytime time_event, std::string name) {
	busy_pc[id_pc - 1] = false;
	pc_start_session.insert({ id_pc,time_event });
	visiter_pc.insert({ name, id_pc });
}

int main(int argc, char* argv[]) {

	Pc_club club {};

	// ������� ������� ����
	if (argv[1] == NULL) {
		std::cout << "File not entered";
		return -1;
	}
	std::ifstream file_in(argv[1]);
	std::ofstream file_out("out.txt");
	std::string line;
	if (!file_in) { // �������� ���� �� ��������?
		std::cout << "Error 1 - no open file\n";
		return -1;
	}

	// ������� ��������� ��� ���-�� ������, ���� ������, ����
	// ������� ���-�� ������
	getline(file_in, line);
	for (char c : line) // �������� ������� ������ ������
		if (!isdigit(c)) {
			std::cout << line << std::endl;
			return -2;
		}
	club.num_pc = stoi(line);

	// ������� ���� �������� � ��������
	getline(file_in, line);
	// �������� �� 2 �������� �� �������
	std::vector<std::string> time_pc = myfuncline(line, ' ');
	if (time_pc.size() > 2) { // �������� ������� ������ ������
		std::cout << line << std::endl;
		return -3;
	}
	std::vector<std::string> timet = myfuncline(time_pc[0], ':');
	if (!(isdigit(time_pc[0][0]) and isdigit(time_pc[0][1]) and time_pc[0][2] == ':' and isdigit(time_pc[0][3]) and isdigit(time_pc[0][4]) and time_pc[0].size() < 6)) {// �������� ������� ������ ������
		std::cout << line << std::endl;
		return -3;
	}
	mytime time_start(stoi(timet[0]), stoi(timet[1]));
	if (!time_start.right_time()) { // ������� �� �����
		std::cout << line << std::endl;
		return -3;
	}
	timet = myfuncline(time_pc[1], ':');
	if (!(isdigit(time_pc[1][0]) and isdigit(time_pc[1][1]) and time_pc[1][2] == ':' and isdigit(time_pc[1][3]) and isdigit(time_pc[1][4]) and time_pc[1].size() < 6)) {// �������� ������� ������ ������
		std::cout << line << std::endl;
		return -3;
	}
	mytime time_end(stoi(timet[0]), stoi(timet[1]));
	mytime t_pref(0,0);
	if (!time_end.right_time()) { // ������� �� �����
		std::cout << line << std::endl;
		return -3;
	}
	//������� ���� ����
	getline(file_in, line);
	for (char c : line) // �������� ������� ������� ������
		if (!isdigit(c)) {
			std::cout << line << std::endl;
			return -4;
		}
	club.price = stoi(line);

	// ���������� �������� ������
	for (int i = 0; i < club.num_pc; ++i) {
		mytime tmp(0, 0);
		club.time_work_pc.push_back(tmp);
		club.revenue_pc.push_back(0);
		club.busy_pc.push_back(true);
	}

	// ������ � ���� ������� ������ ������
	file_out << time_start.tostring() << std::endl;

	while (getline(file_in, line)) { // ��������� ��������� ��������
		std::vector<std::string> buff = myfuncline(line, ' ');
		std::vector<std::string> buff_time = myfuncline(buff[0], ':');
		if (!(isdigit(buff_time[0][0]) and isdigit(buff_time[0][1]) and isdigit(buff_time[1][0]) and isdigit(buff_time[1][1]) and buff_time.size() < 3)) {// �������� ������� ������ ������
			std::cout << line << std::endl;
			return -5;
		}
		
		mytime time_event(stoi(buff_time[0]), stoi(buff_time[1]));
		if (!time_event.right_time()) { // ������� �� �����
			std::cout << line << std::endl;
			return -5;
		}

		// �������� ��� ���� ������� ������ ��� ����� �� �������
		if (t_pref.hour > time_event.hour or (t_pref.hour == time_event.hour and t_pref.min > time_event.min)) {
			std::cout << line;
			return -5;
		}
		// �������� ������� �� id �������
		if (buff.size() > 1 and !(isdigit(buff[1][0]))) {
			std::cout << line << std::endl;
			return -5;
		}
		int id = stoi(buff[1]);
			
		for (char c : buff[2]) { // �������� ������� �� ���
			if (!(isdigit(c) or c != '_' or c != '-' or !(islower(c)))) {
				std::cout << line << std::endl;
				return -5;
			}
		}
		std::string name = buff[2];
		
		// ������ ������� � �������� ����
		file_out << line << std::endl;

		// ��������� bool ������ ��������
		bool start = (time_start.hour > time_event.hour or (time_start.hour == time_event.hour and time_start.min > time_event.min));
		// ���������� bool ����� ��������
		bool end = (time_end.hour < time_event.hour or (time_end.hour == time_event.hour and time_end.min < time_event.min));
		if (start or end)  // �������� �� ����� - ������ �� ����?
			file_out << buff[0] << " 13 " << "NotOpenYet" << std::endl;
		else {
			switch (id) { // ���������� ����� ������� 
			case 1: {// ��������� ������� 1  - ������� ����� � ����
				if (club.in_club.find(name) != club.in_club.end()) // ��������� ������� � ����� ?
					file_out << buff[0] << " 13 " << "YouShallNotPass" << std::endl;
				else
					club.in_club.insert(name);
			}
			break;
			case 2: {// ��������� ������� 2 - ������ ��� �� ����
				if (buff.size() == 4) {
					for (char c : buff[3]) // �������� ������� id ���������� 
						if (!isdigit(c)) {
							std::cout << line << std::endl;
							return -5;
						}
					int id_pc = stoi(buff[3]);
					if (id_pc > club.num_pc and id_pc != 0) { // �������� ��� ����� �� ����
						std::cout << line << std::endl;
						return -5;
					}
					if (club.in_club.find(name) != club.in_club.end()) { // ��������� ������� � ����� ?
						if (club.busy_pc[id_pc - 1] == false) // ����� ������ ?
							file_out << buff[0] << " 13 " << "PlaceIsBusy" << std::endl;
						else {
							if (club.visiter_pc.find(name) != club.visiter_pc.end())  // ���� �� ����� �� ������ ��
								club.remove_session(name, club.revenue_and_time(name, time_event));
							club.create_session(id_pc, time_event, name);
						}
					}
					else
						file_out << buff[0] << " 13 " << "ClientUnknown" << std::endl;
				}
			}
			break;
			case 3: { // ��������� ������� 3 - ������ �������
				if (club.in_club.find(name) != club.in_club.end()) { // ��������� ������� � ����� ?
					if (free_pc(club.busy_pc)) // ���� ��������� ����� ?
						file_out << buff[0] << " 13 " << "ICanWaitNoLonger" << std::endl;
					else if (club.queue.size() == club.num_pc) { // ���� ������� ��������� ?
						file_out << buff[0] << " 11 " << name << std::endl;
						club.in_club.erase(club.in_club.find(name));
					}
					else 
						club.queue.push(name);
				}
				else 
					file_out << buff[0] << " 13 " << "ClientUnknown" << std::endl;
			}
			break;
			case 4: { // ��������� ������� 4 - ������ ����
				if (club.in_club.find(name) != club.in_club.end()) { // ��������� ������� � ����� ?
					if (club.visiter_pc.find(name) != club.visiter_pc.end()) { // ����� �� ������� �� ��?
						int pc_id = club.revenue_and_time(name, time_event);
						club.remove_session(name, pc_id);
						if (club.queue.size() > 0) { // �������� �� �������
							club.create_session(pc_id, time_event, club.queue.front());
							file_out << buff[0] << " 12 " << club.queue.front() << ' ' << pc_id << std::endl;
							club.queue.pop();
						}
					}
					file_out << buff[0] << " 11 " << *club.in_club.find(name) << std::endl;
					club.in_club.erase(club.in_club.find(name));
				}
				else
					file_out << buff[0] << " 13 " << "ClientUnknown" << std::endl;
			}
			break;
			default: {
				std::cout << line << std::endl;
				return -5;
				}	
			}
		}
		t_pref = time_event;
	}
	// �������� �� ��������� ����� ��������
	for (; club.in_club.size() > 0;) {
		if (club.visiter_pc.find(*(club.in_club.begin())) != club.visiter_pc.end()) // ����� �� ������� �� ��?
			club.revenue_and_time(*(club.in_club.begin()), time_end);
		file_out << time_end.tostring() << " 11 " << *(club.in_club.begin()) << std::endl;
		club.in_club.erase(club.in_club.begin());
	}

	// ����� ������� ��������� ������ �����
	file_out << time_end.tostring() << std::endl;
	// ����� ������� � ������ ������������� ������� ��
	for (int i = 0; i < club.num_pc; ++i)
		file_out << (i + 1) << ' ' << club.revenue_pc[i] << ' ' << club.time_work_pc[i].tostring() << std::endl;

	file_out.close();
	file_in.close();
	return 0;
}
