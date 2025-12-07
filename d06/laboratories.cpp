
#include <cstddef>
#include <ostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;
typedef size_t number;
typedef unordered_map<number, unordered_set<number>> splitters_map;

struct vec2 {
	vec2(number const& x = 0, number const& y = 0) : x(x), y(y) {}
	number x = 0;
	number y = 0;
	bool operator == (vec2 const& other) const { return x == other.x && y == other.y; }
	friend ostream & operator << (ostream &os, vec2 const& v) { os << "(" << v.x << "; " << v.y << ")"; return os; }
};

splitters_map find_splitters(vector<string> const& map) {
	splitters_map splitters;
	for (number y = 0; y < map.size(); ++y)
		for (number x = 0; x < map.at(y).size(); ++x)
			if (map.at(y).at(x) == '^')
				splitters[y].insert(x);
	return splitters;
}

number tachyon_manifold(vec2 const& start, splitters_map &splitters, number height) {
	unordered_set<number> tachyons({start.x});
	number num_splits = 0;

	for (int y = 0; y < height; ++y) {
		unordered_set<number> next_tachyons;
		bool has_splitters = splitters.count(y);
		auto const& row_splitters = splitters[y];
		for (int x : tachyons) {
			if (!has_splitters || !row_splitters.count(x)) {
				next_tachyons.insert(x);
				continue;
			}
			next_tachyons.insert(x - 1);
			next_tachyons.insert(x + 1);
			num_splits++;
		}
		tachyons = next_tachyons;
		if (tachyons.empty())
			break;
	}
	return num_splits;
}

int main(int argc, char *argv[]) {
	fstream f(argc == 2 ? argv[1] : "input.txt");
	string buffer;
	vector<string> map;
	number result = 0;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.empty())
			break;
		map.emplace_back(buffer);
	}

	vec2 start(map.at(0).find('S'), 0);
	splitters_map splitters = find_splitters(map);
	result = tachyon_manifold(start, splitters, map.size());

	cout << result << endl;
}

