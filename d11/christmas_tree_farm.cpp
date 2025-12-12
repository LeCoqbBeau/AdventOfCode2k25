
#include <cstddef>
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>
#include <array>

using namespace std;

struct Piece {
	array<array<int, 3>, 3> grid;

	int count() const {
		int result = 0;
		for (auto const& y : grid)
			for (auto const& x : y)
				result += x;
		return result;
	}

	friend ostream& operator << (ostream& os, Piece const& p) {
		for (auto const& y : p.grid) {
			for (auto const& x : y)
				os << (x ? '#' : '.');
			os << '\n';
		}
		return os;
	}
};
array<Piece, 6> pieces_g = {};

struct Region {
	array<int, 6> requierements;
	pair<int, int> dimensions;
	
	int minimum_grid() const {
		int result = 0;

		for (int i = 0; i < requierements.size(); ++i)
			result += pieces_g.at(i).count() * requierements.at(i);
		return result;
	}

	int area() const {
		return dimensions.first * dimensions.second;
	}
	
	int naive_max_pieces() const {
		return area() / 9;
	}

	int num_pieces() const {
		int result = 0;
		for (int const& num : requierements)
			result += num;
		return result;
	}

	friend ostream& operator << (ostream& os, Region const& r) {
		os << r.dimensions.first << 'x' << r.dimensions.second << ":";
		for (auto const& requierement : r.requierements)
			os << " " << requierement;
		return os;
	}
};

vector<string> read_file(string const& path) {
	fstream f(path);
	string buffer;
	vector<string> lines;

	while (f.good()) {
		getline(f, buffer);
		lines.emplace_back(buffer);
	}
	return lines;
}

void register_pieces(vector<string> const& lines) {
	int lastIDX = 0;
	int yIDX = 0;
	for (int i = 1; i < 31; ++i) {
		if (lines[i].empty()) {
			++lastIDX;
			yIDX = 0;
			continue;
		}
		if (lastIDX >= 6)
			break;
		for (int j = 0; j < lines[i].size(); ++j) {
			pieces_g.at(lastIDX).grid[yIDX][j] = lines[i][j] == '#';
		}
		++yIDX;
	}
}

Region register_region(string const& str) {
	size_t idx = 0;
	Region region;
	char const* cstr = str.c_str();

	region.dimensions.first = stol(str);
	idx = str.find('x') + 1;
	region.dimensions.second = strtol(&cstr[idx], 0, 10);
	int i = 0;
	while (true) {
		idx = str.find(' ', idx) + 1;
		if (!idx)
			break;
		region.requierements.at(i++) = strtol(&cstr[idx], 0, 10);
	}
	return region;

}

int main(int argc, char *argv[]) {
	vector lines = read_file(argc == 2 ? argv[1] : "input.txt");
	vector<Region> regions;
	int result = 0;

	for (auto const& line : lines) {
		if (line.find('x') == string::npos)
			continue;
		regions.emplace_back(register_region(line));
	}
	register_pieces(lines);
	for (auto const& region : regions) {
		if (region.num_pieces() <= region.naive_max_pieces()) {
			++result;
		}
	}
	cout << result << endl;
}
