
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using device_t	= pair<string, unordered_set<string>>;
using reactor_t	= unordered_map<string, unordered_set<string>>;

device_t register_device(string const& str) {
	device_t device;
	size_t start = str.find(':') + 2;

	device.first = str.substr(0, start - 2);
	stringstream ss(str.substr(start));
	string buffer;

	while (ss >> buffer)
		device.second.insert(buffer);
	return device;
}

int count_paths(reactor_t const& reactor, string const& id = "you") {
	int count = 0;
	for (string const& output : reactor.at(id)) {
		if (output == "out")
			++count;
		else
			count += count_paths(reactor, output);
	}
	return count;
}

int main(int argc, char *argv[]) {
	fstream f(argc == 2 ? argv[1] : "input.txt");
	string buffer;
	reactor_t reactor;
	int result = 0;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.empty())
			break;
		reactor.insert(register_device(buffer));
	}
	result = count_paths(reactor);
	cout << result << endl;
}
