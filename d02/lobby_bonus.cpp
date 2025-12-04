
#include <iostream>
#include <vector>
#include <cstddef>
#include <fstream>

typedef std::string str;

std::size_t max12Digits(const std::vector<int> &digits, size_t count) {
	std::vector<int> result;
	size_t start = 0;

	while (result.size() < count) {
		int maxDigit = -1;
		size_t maxPos = start;
		for (size_t i = start; i <= digits.size() - (count - result.size()); ++i) {
			if (digits[i] > maxDigit) {
				maxDigit = digits[i];
				maxPos = i;
			}
		}
		result.push_back(maxDigit);
		start = maxPos + 1;
	}

	std::size_t value = 0;
	for (int d : result)
	value = value * 10 + d;

	return value;
}

std::size_t checkVoltage(str filename) {
	std::ifstream file(filename);
	if (!file.is_open())
		throw std::runtime_error("Can't open file");

	std::size_t total = 0;
	str line;

	while (std::getline(file, line)) {
		if (!line.empty() && line.back() == '\r') line.pop_back();

		std::vector<int> digits;
		for (char c : line)
		if (isdigit(c)) digits.push_back(c - '0');

		if (digits.size() < 12) continue;

		total += max12Digits(digits, 12);
	}

	return total;
}

int main(int argc, char *argv[]) {
	std::size_t result = checkVoltage(argc == 2 ? argv[1] : "input.txt");
	std::cout << result << std::endl;
}
