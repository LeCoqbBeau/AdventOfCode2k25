
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

bool is_in_range(std::vector<t_size> &ranges, t_size num) {
	for (std::vector<t_size>::size_type i = 0; i < ranges.size(); i += 2)
		if (ranges[i + 1] >= num && num >= ranges[i]) {
			std::cout << num << " is in [ " << ranges[i] << " - " << ranges[i+1] << " ]" << std::endl;
			return true;
		}
	return false;
}

int main(int argc, char *argv[]) {
	std::fstream f(argc == 2 ? argv[1] : "input.txt");
	std::string buffer;
	std::vector<t_size> ranges;
	t_size result = 0;

	while (f.good()) {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		save_range(ranges, buffer);
	}
	while (f.good()) {
		std::getline(f, buffer);
		if (buffer.empty())
			break;
		result += is_in_range(ranges, std::stol(buffer));
	}
	std::cout << result << std::endl;
}
