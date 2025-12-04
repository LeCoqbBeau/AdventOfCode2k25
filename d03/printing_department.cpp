

#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#define LINE(y) map[y]
#define CHAR(y, x) LINE(y)[x]

int count_neighbour(std::string map[], int y, int x) {
	int count = 0;
	if (y) {
		if (x)
			count += CHAR(y-1, x-1) == CHAR(y, x);
		count += CHAR(y-1, x) == CHAR(y, x);
		if (x + 1 < LINE(y).size())
			count += CHAR(y-1, x+1) == CHAR(y, x);
	}
	if (x)
		count += CHAR(y, x-1) == CHAR(y, x);
	if (x + 1 < LINE(y).size())
		count += CHAR(y, x+1) == CHAR(y, x);
	if (!LINE(y+1).empty()) {
		if (x)
			count += CHAR(y+1, x-1) == CHAR(y, x);
		count += CHAR(y+1, x) == CHAR(y, x);
		if (x + 1 < LINE(y).size())
			count += CHAR(y+1, x+1) == CHAR(y, x);
	}
	return count;
}


int find_accessible(std::string map[]) {
	int count = 0;
	for (int y = 0; !map[y].empty(); ++y) {
		for (int x = 0; CHAR(y, x) != '\0'; ++x) {
			if (CHAR(y, x) != '@')
				continue;
			if (count_neighbour(map, y, x) < 4)
				++count;
		}
	}
	return count;
}


int main(int argc, char *argv[]) {
	std::fstream f(argc == 2 ? argv[1] : "input.txt");
	std::vector<std::string> saves;
	std::string buffer;
	int result = 0;

	while (f.good()) {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		saves.emplace_back(buffer);
	}

	std::string *map;
	map = new std::string[saves.size() + 1];
	map[saves.size()] = "";
	std::copy(saves.begin(), saves.end(), map);
	result = find_accessible(map);
	delete[] map;

	std::cout << result << std::endl;
}
