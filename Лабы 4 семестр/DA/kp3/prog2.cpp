#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#include "point.hpp"
#include "edge.hpp"
#include "persistent_tree2.hpp"
#include <chrono>

using namespace std;

struct Index {

	PersistentTree<int, Edge> tree;
	vector<int> slabs;

	Index(vector<Point> points) {

		vector<Edge> edges;

		// Создание массива рёбер
		for (size_t i = 0; i < points.size(); i+=2) {
			if (points[i].x == points[i+1].x)
				continue;

			edges.push_back(Edge(points[i], points[i+1]));
		}

		vector<Edge> for_enter = edges;

		// Создание массива плит
		for (const Point p : points) {
			if (find(slabs.begin(), slabs.end(), p.x) == slabs.end())
				slabs.push_back(p.x);
		}

		// Сортировка массива плит, ребер на вход и на выход
		sort(slabs.begin(), slabs.end());
		sort(edges.begin(), edges.end(), [](const Edge& p1, const Edge& p2) {
			return p1.org.x < p2.org.x;
		});
		sort(for_enter.begin(), for_enter.end(), [](const Edge& p1, const Edge& p2) {
			return p1.dest.x < p2.dest.x;
		});

		// print(slabs);
		// print(edges);
		// print(for_enter);

		bool flag = false;
		for (int i = 0; i < slabs.size(); i++) {

			// Пока есть отрезки, которые начинаются в данной плите - добавляем 
			while (!edges.empty() and edges[0].org.x == slabs[i]) {
				tree.Insert(edges[0].org.y, edges[0], flag);
				edges.erase(edges.begin());

				if (!flag)
					flag = true;
			}

			tree.NotChange(); // Для точек на границе плит

			// Пока есть отрезки, которые на предыдуще1 плите закончились - удаляем
			while (!for_enter.empty() and i >= 0 and for_enter[0].dest.x == slabs[i]) {  
				tree.Remove(for_enter[0].dest.y, flag);
				for_enter.erase(for_enter.begin());

				if (!flag)
					flag = true;
			}

			// Если никакие не добавились и не закончились
			if (!flag)
				tree.NotChange();

			flag = false;
		}
		// tree.Print();
	}



	unsigned int NumberOfEdgesAbovePoint(Point p) {

		if (p.x > slabs[slabs.size()-1] or p.x < slabs[0])
			return 0;

		unsigned int l = 0, r = slabs.size();

		bool flag = true;
		while(r  - l > 1) {

			unsigned int mid = (l + r) / 2;

			if (slabs[mid] == p.x) {
				l = mid;
				flag = false; // если точка на границе, то корень нечетный
				break;
			}

			if (p.x < slabs[mid]) {
				r = mid;
			} else {
				l = mid;
			}

		}
		
		unsigned int res = tree.FindNumberAbove(l*2+flag, p.y);

		return res;
	}

};



int main() {

	std::vector<Point> points;

	unsigned int number_of_vertexes;
	cin >> number_of_vertexes;

	for (const unsigned int i : range<unsigned int>(0, number_of_vertexes)) {
		int l, r;
		cin >> l >> r;
		points.push_back(Point(l, r));
	}

	// std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	Index Poligone(points);
	// std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();

	unsigned int number_of_points;
	std::cin >> number_of_points;
	// std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	for (int i = 0; i < number_of_points; i++) {
		int x, y;
		cin >> x >> y;
		// Poligone.NumberOfEdgesAbovePoint(Point(x, y));
		cout << Poligone.NumberOfEdgesAbovePoint(Point(x, y)) << endl;
	}
	// std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();
	// std::cout << number_of_vertexes << " " << std::chrono::duration<double>(end1-start1).count() << "\n";
	// std::cout << "(" << number_of_vertexes << ", " << std::chrono::duration<double>(end1-start1).count() << ")" << "\n";

	return 0;
}