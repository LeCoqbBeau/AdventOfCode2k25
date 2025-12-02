
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

std::size_t check_number(std::size_t num) {
	typedef std::string::size_type size_t;
	std::string s = std::to_string(num);
	if (s.length() % 2)
		return 0;
	size_t len2 = s.length() / 2;
	for (size_t i = 0; i != len2; ++i)
		if (s[i] != s[len2 + i])
			return 0;
	return num;
}


std::size_t check_range(std::size_t start, std::size_t end) {
	std::cout << "checking range " << start << "-" << end << std::endl;
	std::size_t sum = 0;
	for (std::size_t i = start; i != end; ++i)
		sum += check_number(i);
	return sum;
}

int main(int argc, char *argv[]) {
	std::string path = "input.txt";
	if (argc == 2)
		path = argv[1];
	std::fstream f(path);
	std::string buffer;
	std::size_t sum = 0;
	do {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		sum += check_range(
			std::strtol(buffer.c_str(), 0, 10),
			std::strtol(buffer.substr(buffer.find('-') + 1).c_str(), 0, 10)
		);
	} while (f.good());
	std::cout << sum << std::endl;

}
