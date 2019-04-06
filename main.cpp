#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>
#include <locale>
#include <iomanip>
#include <exception>

using namespace std;

class Date {
public:
	Date() {
		year = 1900;
		month = 1;
		day = 1;
	};
	Date(const int& new_year, const int& new_month, const int& new_day) {
		year = new_year;
		month = new_month;
		day = new_day;
	}
	int GetYear() const {
		return year;
	};
	int GetMonth() const {
		return month;
	};
	int GetDay() const {
		return day;
	};
private:
	int year;
	int month;
	int day;
};
struct Events {
	Date date;
	string event;
};

bool operator == (const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() == rhs.GetYear() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetDay() == rhs.GetDay()) {
		return 1;
	}
	else {
		return 0;
	}
}

bool operator == (const Events& lhs, const Events& rhs) {
	if (lhs.date.GetYear() == rhs.date.GetYear() && lhs.date.GetMonth() == rhs.date.GetMonth() && lhs.date.GetDay() == rhs.date.GetDay() && lhs.event == rhs.event) {
		return 1;
	}
	else {
		return 0;
	}
}

const bool operator<(const Date& lhs, const Date& rhs) {
	int lhs_sum = lhs.GetYear() * 365 + lhs.GetMonth() * 31 + lhs.GetDay();
	int rhs_sum = rhs.GetYear() * 365 + rhs.GetMonth() * 31 + rhs.GetDay();
	return (lhs_sum < rhs_sum);
}

const bool operator<(const Events& lhs, const Events& rhs) {
	if (lhs.date == rhs.date) {
		return(lhs.event < rhs.event);
	}
	else {
		int lhs_sum = lhs.date.GetYear() * 365 + lhs.date.GetMonth() * 31 + lhs.date.GetDay();
		int rhs_sum = rhs.date.GetYear() * 365 + rhs.date.GetMonth() * 31 + rhs.date.GetDay();
		return (lhs_sum < rhs_sum);
	}
}

ostream& operator << (ostream& stream, Date& date) {
	stream << setw(4) << setfill('0') << date.GetYear() << '-';
	stream << setw(2) << setfill('0') << date.GetMonth() << '-';
	stream << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

ostream& operator << (ostream& stream, Events& events) {
	stream << setw(4) << setfill('0') << events.date.GetYear() << '-';
	stream << setw(2) << setfill('0') << events.date.GetMonth() << '-';
	stream << setw(2) << setfill('0') << events.date.GetDay() << ' ';
	stream << events.event;
	return stream;
}

istream& operator>>(istream& stream, Date& date) {
	int y, m, d;
	if (stream >> y && '-' && stream >> m && '-' && stream >> d) {
		date = { y, m, d };
	}
	return stream;
}


class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		Events tmp;
		tmp.date = date;
		tmp.event = event;
		db.insert(tmp);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		Events tmp;
		tmp.date = date;
		tmp.event = event;
		if (db.count(tmp) == 0) {
			cout << "Event not found" << endl;
			return 0;
		}
		else {
			db.erase(tmp);
			cout << "Deleted successfully" << endl;
			return 1;
		}
	}

	int DeleteDate(const Date& date) {
		set<Events> tmp_set;
		int n = 0;
		for (auto& d : db) {
			Events tmp_event;
			if (d.date == date) {
				n++;
			}
			else {
				tmp_event.date = d.date;
				tmp_event.event = d.event;
				tmp_set.insert(tmp_event);
			}
		}
		db = tmp_set;
		cout << "Deleted " << n << " events" << endl;
		return n;
	}

	bool Find(const Date& date) const {
		vector<string> tmp;
		for (auto& d : db) {
			if (d.date == date) tmp.push_back(d.event);
		}
		if (tmp.size() != 0) {
			sort(begin(tmp), end(tmp));
			for (auto& s : tmp) {
				cout << s << endl;
			}
			return 1;
		}
		else {
			return 0;
		}
	}

	void Print() const {
		for (auto d : db) {
			cout << d << endl;
		}
	}

private:
	set<Events> db;
};

//Checks if NextSymbol is "-" and skips it
void CheckDelimiter(stringstream& stream) {
	if (stream.peek() != '-') {
		stringstream ss;
		ss << "Wrong date format: " << stream.str();
		throw runtime_error(ss.str());
	}
	stream.ignore(1);
}

//Checks if string a number
bool is_number(const std::string& s) {
	return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

//Checks if string a number(skipping sign)
bool is_number_znak(const std::string& s) {
	return !s.empty() && find_if(s.begin() + 1, s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

//Throws Wrong Date exception
void CallWrongDate(stringstream& stream) {
	stringstream ss;
	ss << "Wrong date format: " << stream.str();
	throw runtime_error(ss.str());
}

bool isEnd(stringstream& stream) {
	return (stream.peek() == EOF);
}
bool CheckNumber(string& s) {
	return 1;
}

//Transforms and checks string from input to Date type
Date StringToDate(const string& date_string) {

	stringstream stream(date_string);
	int year = 0;
	int month = 0;
	int day = 0;
	string day_s;

	//cout << "date_string: " << stream.str() << endl;

	//Reads year
	stream >> year;
	CheckDelimiter(stream);
	if (isEnd(stream)) CallWrongDate(stream);
	//cout << "Took year(int): " << year << " Next symbol: " << char(stream.peek()) << " EOF: " << (stream.peek() == EOF) << endl;


	//Reads and checks month
	stream >> month;
	CheckDelimiter(stream);
	if (isEnd(stream)) CallWrongDate(stream);
	//cout << "Took month(int): " << month << " Next symbol: " << char(stream.peek()) << " EOF: " << (stream.peek() == EOF) << endl;


	//Checks if month is month-number
	if (month <= 0 || month > 12) {
		stringstream err;
		err << "Month value is invalid: " << month;
		throw runtime_error(err.str());
	}
	//Checks if string continues after YYYY-MM-
	//were here

	//Reads and checks day
	stream >> day_s;
	//cout << "Took day(string): " << day_s << " Next symbol: " << char(stream.peek()) << " EOF: " << (stream.peek() == EOF) << endl;
	//Checks if there is a number
	//with sign
	if (day_s.at(0) == '-' || day_s.at(0) == '+') {
		if (is_number_znak(day_s)) {
			day = stoi(day_s);
		}
		else {
			CallWrongDate(stream);
		}
	}
	//without sign
	else {
		if (is_number(day_s)) {
			day = stoi(day_s);
		}
		else {
			CallWrongDate(stream);
		}
	}
	//Checks if day is month-number
	if (day <= 0 || day > 31) {
		stringstream err;
		err << "Day value is invalid: " << day;
		throw runtime_error(err.str());
	}

	Date date(year, month, day);
	return date;
}


int main() {
	Database db;
	Date date;
	string command, operation, task;
	while (getline(cin, command)) {

		//Checks if line was empty
		if (command.length() == 0) continue;

		//Reads line word by word and puts in vector
		stringstream ss;
		ss.str(command);
		string elem;
		vector<string> v_command;
		while (ss >> elem) v_command.push_back(elem);
		int n = v_command.size();
		operation = v_command[0];

		try {
			if (operation == "Add") {
				if (n == 3) {
					date = StringToDate(v_command[1]);
					task = v_command[2];
					db.AddEvent(date, task);
				}
				v_command.clear();
			}

			if (operation == "Del") {
				if (n == 3) {
					date = StringToDate(v_command[1]);
					task = v_command[2];
					db.DeleteEvent(date, task);
				}
				else if (n == 2) {
					date = StringToDate(v_command[1]);
					db.DeleteDate(date);
				}
				v_command.clear();
			}

			if (operation == "Find") {
				if (n == 2) {
					date = StringToDate(v_command[1]);
					db.Find(date);
				}
				v_command.clear();
			}

			if (operation == "Print") {
				if (n == 1) {
					db.Print();
				}
				v_command.clear();
			}

			if (operation != "Add" && operation != "Del" && operation != "Print" && operation != "Find") {
				stringstream ss;
				ss << "Unknown command: " << operation;
				v_command.clear();
				throw runtime_error(ss.str());
			}

		}
		catch (exception& e) {
			cout << e.what() << endl;
			//break;
		}
	}

	return 0;
}