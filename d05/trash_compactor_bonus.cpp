
#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <stdexcept>
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

std::size_t get_digits(char const* operands) {
	int i = 0;
	while (++i)
		if (!operands[i] || operands[i] != ' ')
			return i - 1 + (!operands[i]);
	throw std::runtime_error("never here");
}

std::vector<std::vector<std::size_t>> cephalopod_sequences(std::vector<std::string> const& sequences, std::size_t len) {
	using namespace std;

	vector<vector<size_t>> cephalopod_sequences;
	size_t digits = 0;
	size_t offset = 0;
	for (size_t i = 0; i != len; ++i) {
		cephalopod_sequences.push_back({});
		digits = get_digits(sequences.back().c_str() + offset);

		for (size_t j = 0; j != digits; ++j) {
			string tmp;
			tmp.clear();
			for (size_t k = 0; k != sequences.size() - 1; ++k)
				tmp.append(1, sequences[k][offset + j]);
			cephalopod_sequences.back().push_back(stol(tmp));
		}
		
		do
			++offset;
		while (sequences.back()[offset] && sequences.back()[offset] == ' ');
	}
	return cephalopod_sequences;
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
	vector<string> tmp_sequences;
	vector<vector<size_t>> sequences;
	vector<char> operands;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.empty())
			break;
		if (buffer.front() == '*' || buffer.front() == '+')
			fill_operands(operands, buffer);
		tmp_sequences.emplace_back(buffer);
	}
	sequences = cephalopod_sequences(tmp_sequences, operands.size());
	for (vector<vector<size_t>>::size_type i = 0; i != sequences.size(); ++i) {
		aoc::binary_function<size_t> operation;
		if (operands[i] == '+')
			result += accumulate(sequences[i].begin() + 1, sequences[i].end(), *sequences[i].begin(), aoc::plus<size_t>());
		else
			result += accumulate(sequences[i].begin() + 1, sequences[i].end(), *sequences[i].begin(), aoc::multiplies<size_t>());
	}
	cout << result << endl;
}
