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
	std::queue<std::string> queue;				// очередь за посадку за столы
	std::set<std::string> in_club;				// ники человек внутри клуба
	std::map<int, mytime> pc_start_session;		// связь компа и врмеени начала текущео члеовека
	std::map<std::string, int> visiter_pc;		// связь человека и номером пк 
	std::vector<bool> busy_pc;					// отображает свободен ли пк
	std::vector<int> revenue_pc;				// сколько дененег принес и-тый пк
	std::vector<mytime> time_work_pc;			// сколько времени проработал и-тый пк
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

	// открыть входной файл
	if (argv[1] == NULL) {
		std::cout << "File not entered";
		return -1;
	}
	std::ifstream file_in(argv[1]);
	std::ofstream file_out("out.txt");
	std::string line;
	if (!file_in) { // открылся файл не открылся?
		std::cout << "Error 1 - no open file\n";
		return -1;
	}

	// считать заголовок про кол-во компов, врем работы, цену
	// считать кол-во компов
	getline(file_in, line);
	for (char c : line) // проверка формата первой строки
		if (!isdigit(c)) {
			std::cout << line << std::endl;
			return -2;
		}
	club.num_pc = stoi(line);

	// считать врем открытия и закрытия
	getline(file_in, line);
	// раделяем на 2 врменини по пробелу
	std::vector<std::string> time_pc = myfuncline(line, ' ');
	if (time_pc.size() > 2) { // проверка формата второй строки
		std::cout << line << std::endl;
		return -3;
	}
	std::vector<std::string> timet = myfuncline(time_pc[0], ':');
	if (!(isdigit(time_pc[0][0]) and isdigit(time_pc[0][1]) and time_pc[0][2] == ':' and isdigit(time_pc[0][3]) and isdigit(time_pc[0][4]) and time_pc[0].size() < 6)) {// проверка формата второй строки
		std::cout << line << std::endl;
		return -3;
	}
	mytime time_start(stoi(timet[0]), stoi(timet[1]));
	if (!time_start.right_time()) { // провека на время
		std::cout << line << std::endl;
		return -3;
	}
	timet = myfuncline(time_pc[1], ':');
	if (!(isdigit(time_pc[1][0]) and isdigit(time_pc[1][1]) and time_pc[1][2] == ':' and isdigit(time_pc[1][3]) and isdigit(time_pc[1][4]) and time_pc[1].size() < 6)) {// проверка формата второй строки
		std::cout << line << std::endl;
		return -3;
	}
	mytime time_end(stoi(timet[0]), stoi(timet[1]));
	mytime t_pref(0,0);
	if (!time_end.right_time()) { // провека на время
		std::cout << line << std::endl;
		return -3;
	}
	//считать цену часа
	getline(file_in, line);
	for (char c : line) // проверка формата третьей строки
		if (!isdigit(c)) {
			std::cout << line << std::endl;
			return -4;
		}
	club.price = stoi(line);

	// заполнение массивов данных
	for (int i = 0; i < club.num_pc; ++i) {
		mytime tmp(0, 0);
		club.time_work_pc.push_back(tmp);
		club.revenue_pc.push_back(0);
		club.busy_pc.push_back(true);
	}

	// запись в файл времени начала работы
	file_out << time_start.tostring() << std::endl;

	while (getline(file_in, line)) { // считываем построчно сообытия
		std::vector<std::string> buff = myfuncline(line, ' ');
		std::vector<std::string> buff_time = myfuncline(buff[0], ':');
		if (!(isdigit(buff_time[0][0]) and isdigit(buff_time[0][1]) and isdigit(buff_time[1][0]) and isdigit(buff_time[1][1]) and buff_time.size() < 3)) {// проверка формата второй строки
			std::cout << line << std::endl;
			return -5;
		}
		
		mytime time_event(stoi(buff_time[0]), stoi(buff_time[1]));
		if (!time_event.right_time()) { // провека на время
			std::cout << line << std::endl;
			return -5;
		}

		// првоерка что след событие больше или равно по времени
		if (t_pref.hour > time_event.hour or (t_pref.hour == time_event.hour and t_pref.min > time_event.min)) {
			std::cout << line;
			return -5;
		}
		// проверка формата на id события
		if (buff.size() > 1 and !(isdigit(buff[1][0]))) {
			std::cout << line << std::endl;
			return -5;
		}
		int id = stoi(buff[1]);
			
		for (char c : buff[2]) { // проверка формата на ник
			if (!(isdigit(c) or c != '_' or c != '-' or !(islower(c)))) {
				std::cout << line << std::endl;
				return -5;
			}
		}
		std::string name = buff[2];
		
		// запись события в выходной файл
		file_out << line << std::endl;

		// пременная bool рашьне открытия
		bool start = (time_start.hour > time_event.hour or (time_start.hour == time_event.hour and time_start.min > time_event.min));
		// переменная bool позже закрытия
		bool end = (time_end.hour < time_event.hour or (time_end.hour == time_event.hour and time_end.min < time_event.min));
		if (start or end)  // проверка на время - открыт ли клуб?
			file_out << buff[0] << " 13 " << "NotOpenYet" << std::endl;
		else {
			switch (id) { // определяем номер события 
			case 1: {// обработка события 1  - человек зашел в клуб
				if (club.in_club.find(name) != club.in_club.end()) // находится человек в клубе ?
					file_out << buff[0] << " 13 " << "YouShallNotPass" << std::endl;
				else
					club.in_club.insert(name);
			}
			break;
			case 2: {// обработка события 2 - клиент сел за стол
				if (buff.size() == 4) {
					for (char c : buff[3]) // проверка формата id компьютера 
						if (!isdigit(c)) {
							std::cout << line << std::endl;
							return -5;
						}
					int id_pc = stoi(buff[3]);
					if (id_pc > club.num_pc and id_pc != 0) { // проверка что такой пк есть
						std::cout << line << std::endl;
						return -5;
					}
					if (club.in_club.find(name) != club.in_club.end()) { // находится человек в клубе ?
						if (club.busy_pc[id_pc - 1] == false) // место занято ?
							file_out << buff[0] << " 13 " << "PlaceIsBusy" << std::endl;
						else {
							if (club.visiter_pc.find(name) != club.visiter_pc.end())  // если он сидел за другим пк
								club.remove_session(name, club.revenue_and_time(name, time_event));
							club.create_session(id_pc, time_event, name);
						}
					}
					else
						file_out << buff[0] << " 13 " << "ClientUnknown" << std::endl;
				}
			}
			break;
			case 3: { // обработка события 3 - клиент ожидает
				if (club.in_club.find(name) != club.in_club.end()) { // находится человек в клубе ?
					if (free_pc(club.busy_pc)) // есть свободные столы ?
						file_out << buff[0] << " 13 " << "ICanWaitNoLonger" << std::endl;
					else if (club.queue.size() == club.num_pc) { // если очередь заполнена ?
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
			case 4: { // обработка события 4 - клиент ушел
				if (club.in_club.find(name) != club.in_club.end()) { // находится человек в клубе ?
					if (club.visiter_pc.find(name) != club.visiter_pc.end()) { // сидел ли человек за пк?
						int pc_id = club.revenue_and_time(name, time_event);
						club.remove_session(name, pc_id);
						if (club.queue.size() > 0) { // проверка на очередь
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
	// Проверка на неушедших после закрытия
	for (; club.in_club.size() > 0;) {
		if (club.visiter_pc.find(*(club.in_club.begin())) != club.visiter_pc.end()) // сидел ли человек за пк?
			club.revenue_and_time(*(club.in_club.begin()), time_end);
		file_out << time_end.tostring() << " 11 " << *(club.in_club.begin()) << std::endl;
		club.in_club.erase(club.in_club.begin());
	}

	// вывод времени окончания работы клуба
	file_out << time_end.tostring() << std::endl;
	// вывод прибыли и врмени использования каждого пк
	for (int i = 0; i < club.num_pc; ++i)
		file_out << (i + 1) << ' ' << club.revenue_pc[i] << ' ' << club.time_work_pc[i].tostring() << std::endl;

	file_out.close();
	file_in.close();
	return 0;
}
