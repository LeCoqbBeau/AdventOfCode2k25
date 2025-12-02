
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <ostream>
#include <string>
#include <iostream>
#include <set>

bool is_prime(std::size_t num) {
	if (num == 2)
		return true;
	if (num <= 1
		|| num % 2 == 0)
		return false;
	for (std::size_t i = 3; i * i <= num; i += 2)
		if (num % i == 0)
			return false;
	return true;
}


std::size_t get_next_prime(std::size_t num) {
	std::size_t i;
	if (num == 1)
		return 2;
	if (num == 2)
		return 3;
	for (i = num + 2; true; i += 2)
		if (is_prime(i))
			return i;
}


std::set<std::size_t> factor_num(std::size_t num) {
	std::set<std::size_t> factors = { num };
	std::size_t potential_divisor = 2;

	if (num == 2 || num == 3)
		return { num };
	while (potential_divisor * potential_divisor <= num) {
		if (num % potential_divisor == 0) {
			factors.insert(potential_divisor);
			factors.insert(num / potential_divisor);
		}
		potential_divisor = get_next_prime(potential_divisor);
	}
	factors.erase(1);
	return factors;
}


std::size_t check_number(std::size_t num) {
	typedef std::string::size_type size_t;
	std::string s = std::to_string(num);
	std::size_t len = s.length();
	std::set<size_t> factors = factor_num(len);
	for (auto factor : factors) {
		std::size_t tmp_len = len / factor;
		bool has_repeated = true;
		if (len % factor != 0)
			continue;
		for (std::size_t i = 0; i != tmp_len; ++i) {
			for (std::size_t j = 1; j != factor; ++j) {
				char prev_c = s[(j - 1) * tmp_len + i];
				char curr_c = s[j * tmp_len + i];
				if (prev_c == curr_c)
					continue;
				has_repeated = false;
				break;
			}
			if (!has_repeated)
				break;
		}
		if (has_repeated) {
			std::cout << "Flagged: " << num << " with factor " << factor << std::endl;
			return num;
		}	
	}
	return 0;
}


std::size_t check_range(std::size_t start, std::size_t end) {
	std::cout << "checking range " << start << "-" << end << std::endl;
	std::size_t sum = 0;
	for (std::size_t i = start; i <= end; ++i)
		sum += check_number(i);
	return sum;
}


int main(int argc, char *argv[]) {
	factor_num(10);
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
