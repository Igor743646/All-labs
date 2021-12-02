#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "point.hpp"
#include "edge.hpp"
#include "persistent_tree.hpp"
#include <chrono>

using namespace std;

template<class T>
vector<T> range(T l, T r, T step = 1) {
	vector<T> result;
	for (T i = l; i < r; i += step) {
		result.push_back(i);
	}
	return result;
}

template<class T>
void print(vector<T> objects) {
	for (const T& object : objects) {
		cout << object << " ";
	}

	cout << endl;
}

template<class T>
void print(initializer_list<T> objects) {
	for (const T& object : objects) {
		cout << object << " ";
	}

	cout << endl;
}

template<class T>
void print(T object) {
	cout << object << endl;
}

struct Index {

	PersistentTree<double, Edge> tree;
	vector<double> slabs;
	double min_x = DBL_MAX, max_x = DBL_MIN;
	double min_y = DBL_MAX, max_y = DBL_MIN;
	unsigned int last_slab = 0;
	double last_x = DBL_MIN;

	Index(vector<Point> points) {

		vector<Edge> edges;

		for (size_t i = 0; i < points.size(); i++) {
			if (points[i].x == points[(i+1) % points.size()].x)
				continue;

			edges.push_back(Edge(points[i], points[(i+1) % points.size()]));
		}

		for (const Point p : points) {
			if (find(slabs.begin(), slabs.end(), p.x) == slabs.end())
				slabs.push_back(p.x);

			if (p.x < min_x)
				min_x = p.x;

			if (p.x > max_x)
				max_x = p.x;

			if (p.y < min_y)
				min_y = p.y;

			if (p.y > max_y)
				max_y = p.y;
		}

		sort(slabs.begin(), slabs.end());

		/* 	
			slabs -- [<x>] O(n) + sort -- O(nlogn)
			points -- [<x, y>] O(n); 
			edges -- [{<x, y>, <x, y>}] O(n) 
		*/

		tree.BuildZeroVersion(edges);

		for (unsigned int i = 0 ; i < slabs.size() - 1; i++) {
			tree.BuildNextVersion({});
		}

		for (const Edge& edge : edges) {

			if (edge.org.x == edge.dest.x)
				continue;

			long l = 0, r = slabs.size() - 1;

			while(r  - l > 1) {

				long mid = (l + r) / 2;

				if (slabs[mid] == edge.org.x) {
					l = mid;
					break;
				}

				if (edge.org.x < slabs[mid]) {
					r = mid;
				} else {
					l = mid;
				}

			}

			for (long i = l; (i < slabs.size()-1 and slabs[i+1] <= edge.dest.x); i++) {
				tree.AddInSomeVersion(i+1, edge);
			}

		}

	}

	bool In(Point p) {

		if (p.x > max_x or p.x < min_x or p.y > max_y or p.y < min_y)
			return false;

		unsigned int l = 0, r = slabs.size() - 1;

		if (p.x >= last_x)
			l = last_slab;
		else
			l = 0;

		while(r  - l > 1) {

			unsigned int mid = (l + r) / 2;

			if (slabs[mid] == p.x) {
				l = mid;
				break;
			}

			if (p.x < slabs[mid]) {
				r = mid;
			} else {
				l = mid;
			}

		}

		unsigned int res = tree.NumberOfEdges(p, l+1);

		last_x = p.x;
		last_slab = l;

		if (res % 2 == 0)
			return false;
		else
			return true;

		return false;
	}

};



int main() {

	std::vector<Point> points;

	unsigned int number_of_vertexes;
	cin >> number_of_vertexes;

	for (const unsigned int i : range<unsigned int>(0, number_of_vertexes)) {
		double l, r;
		cin >> l >> r;
		points.push_back(Point(l, r));
	}

	//std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	Index Poligone(points);
	//std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();

	unsigned int number_of_points;
	std::cin >> number_of_points;

	std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	for (int i = 0; i < number_of_points; i++) {
		double x, y;
		cin >> x >> y;
		Poligone.In(Point(x, y));
		//cout << Poligone.In(Point(x, y)) << endl;
	}
	std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();

	std::cout << number_of_vertexes << " " << std::chrono::duration<double>(end1-start1).count() / number_of_points << "\n";

	return 0;
}