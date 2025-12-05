
#include <algorithm>
#include <iomanip>
#include <ostream>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

typedef std::size_t t_size;

void save_range(std::vector<t_size> &ranges, std::string const& s) {
	std::string::size_type splitIDX = s.find('-');
	std::string start = s.substr(0, splitIDX);
	std::string finish = s.substr(splitIDX + 1);
	ranges.emplace_back(std::stol(start));
	ranges.emplace_back(std::stol(finish));
}

bool should_expand(t_size first1, t_size last1, t_size first2, t_size last2) {
	if (first2 < first1)
		return false;
	if (last1 < first2)
		return false;
	return true;
}

void simplify_ranges(std::vector<t_size> &ranges) {
	bool has_shrunk = false;

	do {
		has_shrunk = false;
		for (t_size i = 0; i < ranges.size(); i += 2) {
			if (ranges[i] == ranges[i + 1] && !ranges[i])
				continue;
			for (t_size j = 0; j < ranges.size(); j += 2) {
				if (false
					|| i == j
					|| (ranges[j] == ranges[j + 1] && !ranges[j])
					|| !should_expand(ranges[i], ranges[i + 1], ranges[j], ranges[j + 1])
				)
					continue;
				if (ranges[i + 1] < ranges[j + 1])
					ranges[i + 1] = ranges[j + 1];
				ranges[j] = 0;
				ranges[j + 1] = 0;
				has_shrunk = true;
			}
		}
		ranges.erase(std::remove(ranges.begin(), ranges.end(), 0), ranges.end());
	} while (has_shrunk);
}


int main(int argc, char *argv[]) {
	std::fstream f(argc == 2 ? argv[1] : "input.txt");
	std::string buffer;
	std::vector<t_size> ranges;
	t_size result = 0;
	t_size advancement = 0;

	while (f.good()) {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		save_range(ranges, buffer);
	}
	simplify_ranges(ranges);
	for (t_size i = 0; i < ranges.size(); i += 2)
		result += ranges[i + 1] - ranges[i] + 1;
	std::cout << result << std::endl;
}
