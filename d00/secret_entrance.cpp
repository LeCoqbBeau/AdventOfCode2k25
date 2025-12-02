
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

struct Dial {
	int value;
	Dial(int i) : value(i) {}

	template <typename T>
	Dial operator + (T n) {
		return (value + n) % 100;
	}

	template <typename T>
	Dial operator - (T n) {
		return (value - n) % 100;
	}
};


class Safe {
	public:
		Dial dial = 50;
		int clicks = 0;

		void rotate(int r) {
			dial = dial + r;
			clicks += dial.value == 0;
		}

};


int main() {
	Safe safe;
	std::fstream f("test.txt");
	std::string buffer;
	int value;

	std::cout << safe.dial.value << std::endl;
	do {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		buffer.erase(buffer.length() - 1);
		value = std::strtol(buffer.c_str() + 1, nullptr, 10);
		value *= (buffer.at(0) == 'R' ? 1 : -1);
		safe.rotate(value);
		
	} while (!f.eof());
	std::cout << safe.clicks << std::endl;
}


