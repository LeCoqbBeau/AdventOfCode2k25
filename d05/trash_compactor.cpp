
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <numeric>

namespace aoc {

template <typename T1, typename T2 = T1, typename U = T1>
struct binary_function {
	virtual U operator () (T1 const& a, T2 const& b) { return U(); };
};

template <typename T1, typename T2 = T1, typename U = T1>
struct plus : public binary_function<T1, T2, U> {
	virtual U operator () (T1 const& a, T2 const& b) override { return a + b; };
};

template <typename T1, typename T2 = T1, typename U = T1>
struct multiplies : public binary_function<T1, T2, U> {
	virtual U operator () (T1 const& a, T2 const& b) override { return a * b; };
};

}


std::vector<std::size_t> generate_sequence(std::string s) {
	using namespace std;

	string::size_type idx = 0;
	vector<size_t> sequence;
	while (s.at(idx) == ' ')
		++idx;
	while (idx < s.length()) {
		sequence.emplace_back(std::strtol(&s.c_str()[idx], 0, 10));
		while (idx < s.length() && s.at(idx) != ' ')
			++idx;
		while (idx < s.length() && s.at(idx) == ' ')
			++idx;
	}
	return sequence;
}

std::vector<std::vector<std::size_t>> rotate_sequences(std::vector<std::vector<std::size_t>> const& sequences) {
	using namespace std;

	vector<vector<std::size_t>> rotated_sequences;

	for (size_t i = 0; i != sequences.front().size(); ++i) {
		rotated_sequences.push_back({});
		for (size_t j = 0; j != sequences.size(); ++j)
			rotated_sequences[i].push_back(sequences[j][i]);
	}
	return rotated_sequences;
}

void fill_operands(
	std::vector<char> &operands,
	std::string s
) {
	using namespace std;

	string::size_type idx = 0;
	while (idx < s.length()) {
		operands.emplace_back(s.at(idx));
		idx = s.find_first_not_of(' ', idx + 1);
	}
}

int main(int argc, char *argv[]) {
	using namespace std;
	
	fstream f(argc == 2 ? argv[1] : "input.txt");
	string buffer;
	size_t result = 0;
	vector<vector<size_t>> sequences;
	vector<char> operands;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.front() == '*' || buffer.front() == '+')
			break;
		sequences.emplace_back(generate_sequence(buffer));
	}
	sequences = rotate_sequences(sequences);
	fill_operands(operands, buffer);
	for (vector<vector<size_t>>::size_type i = 0; i != sequences.size(); ++i) {
		aoc::binary_function<size_t> operation;
		if (operands[i] == '+')
			result += accumulate(sequences[i].begin() + 1, sequences[i].end(), *sequences[i].begin(), aoc::plus<size_t>());
		else
			result += accumulate(sequences[i].begin() + 1, sequences[i].end(), *sequences[i].begin(), aoc::multiplies<size_t>());
	}
	cout << result << endl;
}
