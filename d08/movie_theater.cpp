
#include <cstddef>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef std::ptrdiff_t num;
typedef double num_decimal;

#define CLAMP(value, mini, maxi) max<num>(mini, min<num>(value, maxi))
#define AREA(var) get<0>(var)

struct vec2 {
	template <typename T>
	vec2(T const& x = 0, T const& y = 0) : x(x), y(y) {}
	num x;
	num y;

	friend ostream & operator << (ostream &os, vec2 const& v) {
		os << "(" << v.x << "; " << v.y << ")";
		return os;
	}

	bool operator == (vec2 const& u) const { return x == u.x && y == u.y; }
	bool operator != (vec2 const& u) const { return !(*this == u); }
	vec2 operator - (vec2 const& u) const { return {x - u.x, y - u.y}; }
};


vec2 register_point(string const& s) {
	return { stoul(s), stoul(s.substr(s.find(',') + 1)) };
}

num calculate_area(vec2 const& u, vec2 const& v) {
	num height = max(u.y, v.y) - min(u.y, v.y) + 1;
	num width = max(u.x, v.x) - min(u.x, v.x) + 1;
	return height * width;
}

bool is_in_polygon(vec2 const& point, vector<vec2> const& polygon) {
	bool inside = false;
	num_decimal const& px = point.x;
	num_decimal const& py = point.y;
	num_decimal const EPSILON = 1e-9;
	for (num i = 0, j = polygon.size() - 1; i < polygon.size(); j = i++) {
		num_decimal const& pix = polygon[i].x;
		num_decimal const& piy = polygon[i].y;
		num_decimal const& pjx = polygon[j].x;
		num_decimal const& pjy = polygon[j].y;

		num_decimal cross_product = (py - piy) * (pjx - pix) - (px - pix) * (pjy - piy);
		if (abs(cross_product) <= EPSILON) {
			if (
				px >= min(pix, pjx) - EPSILON && px <= max(pix, pjx) + EPSILON
				&& py >= min(piy, pjy) - EPSILON && py <= max(piy, pjy) + EPSILON
			)
				return true;
		}

		if (	true
			&& ((piy > point.y) != (pjy > point.y))
			&& (point.x < (pjx - pix) * (point.y - piy) / (pjy - piy) + pix)
		)
			inside = !inside;
	}
	return inside;
}

void draw_rectangle(vector<vec2> points) {
	num xMax = (*(max_element(points.begin(), points.end(), [](vec2 const& u, vec2 const& v){ return u.x < v.x; }))).x;
	num yMax = (*(max_element(points.begin(), points.end(), [](vec2 const& u, vec2 const& v){ return u.y < v.y; }))).y;
	for (int y = 0; y <= yMax + 1; ++y) {
		for (int x = 0; x <= xMax + 2; ++x) {
			if (find(points.begin(), points.end(), vec2(x, y)) != points.end())
				cout << '#';
			else if (is_in_polygon(vec2(x, y), points))
				cout << 'X';
			else
				cout << '.';
		}
		cout << endl;
	}
}

int main(int argc, char *argv[]) {
	fstream f(argc == 2 ? argv[1] : "input.txt");
	string buffer;
	num result = 0;
	vector<vec2> points;
	vector<tuple<num, vec2, vec2>> areas;

	while (f.good()) {
		getline(f, buffer);
		if (buffer.empty())
			break;
		points.emplace_back(register_point(buffer));
	}
	for (num i = 0; i < points.size(); ++i) {
		for (num j = i + 1; j < points.size(); ++j) {
			vec2 const& pi = points[i];
			vec2 const& pj = points[j];
			areas.emplace_back(calculate_area(pi, pj), pi, pj);
		}
	}
	result = AREA(*max_element(
		areas.begin(),
		areas.end(),
		[](tuple<num, vec2, vec2> const& a, tuple<num, vec2, vec2> const& b) {
			return AREA(a) < AREA(b);
		}
	));
	
	cout << result << endl;
}
