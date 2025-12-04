
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>

typedef std::string str;

int find_n_biggest(std::string const& s, int n) {
	typedef std::vector<char> container;
	typedef container::iterator iterator;
	str final = "";
	final.reserve(n);
	container vec(s.begin(), s.end());
	iterator upperBound = vec.begin();
	iterator lowerBound = vec.end();
	iterator toInsert = vec.begin();
	std::string::iterator insertPos = final.begin();
	int dir = 1; // 1 is forward, -1 is backward
	while (final.length() != n) {
		toInsert = std::max_element(upperBound, lowerBound);
		if (dir == 1 && toInsert + 1 == lowerBound) {
			lowerBound = toInsert;
			dir = -1;
		} else if (dir == 1) {
			upperBound = toInsert + 1;
		}
		else if (dir == -1 && toInsert == upperBound) {
			upperBound = toInsert + 1;
			dir = 1;
		} else if (dir == -1) {
			lowerBound = toInsert;
		}
		final.insert(insertPos, *toInsert);
		if (dir == 1)
			++insertPos;
	}
	return std::strtol(final.c_str(), 0, 10);
}

int main(int argc, char *argv[]) {
	std::fstream f(argc == 2 ? argv[1] : "input.txt");
	std::string buffer;
	std::size_t result = 0;

	while (f.good()) {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		if (buffer.back() == '\r')
			buffer.erase(buffer.rfind('\r'));
		result += find_n_biggest(buffer, 2);
	}
	std::cout << result << std::endl;
}
