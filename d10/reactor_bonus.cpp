
#include <cstddef>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;
using device_t		= pair<string, unordered_set<string>>;
using reactor_t		= unordered_map<string, unordered_set<string>>;

using cache_key_t	= struct CacheKey {
	CacheKey(string const& id, bool dac, bool fft) : id(id), has_dac(dac), has_fft(fft) {}

	bool operator < (CacheKey const& x) const { return id < x.id; }
	bool operator == (CacheKey const& x) const { return id == x.id && has_dac == x.has_dac && has_fft == x.has_fft; }
	string id;
	bool has_dac = false;
	bool has_fft = false;
};

using hasher_t = struct CacheKeyHasher {
	size_t operator () (cache_key_t const& key) const { return hash<string>()(key.id);}
};

using cache_t		= unordered_map<cache_key_t, size_t, hasher_t>;

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

size_t count_paths(
	reactor_t const& reactor,
	cache_t& cache,
	string const& id = "svr",
	bool has_dac = false,
	bool has_fft = false
) {
	cache_key_t cache_key(id, has_dac, has_fft);
	if (cache.count(cache_key))
		return cache.at(cache_key);
	
	size_t count = 0;
	for (string const& output : reactor.at(id)) {
		if (output == "out")
			count += has_dac && has_fft;
		else if (output == "dac")
			count += count_paths(reactor, cache, output, true, has_fft);
		else if (output == "fft")
			count += count_paths(reactor, cache, output, has_dac, true);
		else
			count += count_paths(reactor, cache, output, has_dac, has_fft);
	}
	cache[cache_key] = count;
	return count;
}

int main(int argc, char *argv[]) {
	fstream f(argc == 2 ? argv[1] : "input.txt");
	string buffer;
	reactor_t reactor;
	size_t result = 0;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.empty())
			break;
		reactor.insert(register_device(buffer));
	}
	cache_t cache = cache_t();
	result = count_paths(reactor, cache);
	cout << result << endl;
}
