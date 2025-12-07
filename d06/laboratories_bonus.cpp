
#include <cstddef>
#include <iterator>
#include <ostream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;
typedef size_t number;
typedef unordered_map<int, unordered_set<int>> splitters_map;

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
	unordered_map<number, number> tachyons;
	number num_splits = 1;

	tachyons[start.x] = 1;
	for (int y = 0; y < height; ++y) {
		unordered_map<number, number> next_tachyons;
		auto row_it = splitters.find(y);
		bool has_splitters = (row_it != splitters.end());
		for (auto const& [x, intensity] : tachyons) {
			bool hit_splitters = has_splitters && row_it->second.count(x);
			if (!hit_splitters) {
				next_tachyons[x] += intensity;
				continue;
			}
			next_tachyons[x - 1] += intensity;
			next_tachyons[x + 1] += intensity;
			num_splits += intensity;
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

