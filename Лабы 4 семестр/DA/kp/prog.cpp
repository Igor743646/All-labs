#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "point.hpp"
#include "edge.hpp"
#include "persistent_tree.hpp"
#include <chrono>
// enum {
// 	INSIDE,
// 	OUTSIDE,
// 	BOUNDARY
// };

// enum {
// 	TOUCHING,
// 	CROSSING,
// 	INESSENTIAL
// };

// Edge RandomHorizontalEdge() {
// 	double y = (std::rand() % 41) - 20;
// 	double x0 = (std::rand() % 41) - 20;
// 	double x1 = x0 + (std::rand() % 21);

// 	if (x1 == x0)
// 		x1 += 1;

// 	return Edge(x0, y, x1, y);
// }

// Point RandomPoint() {
// 	double x = (std::rand() % 41) - 20;
// 	double y = (std::rand() % 41) - 20;
// 	return Point(x, y);
// }

struct Index {

	std::vector<std::pair<double, std::vector<Edge>>> lanes;
	int ll = 0;

	Index(std::vector<Point> points, std::vector<Edge> edges) {

		for (int i = 0; i < points.size() - 1; i++) {
			if (points[i].x != points[i+1].x) {
				std::vector<Edge> cur;

				for (const auto j : edges) {
					if ((j.org.x <= points[i].x and points[i].x <= points[i+1].x and points[i+1].x <= j.dest.x) 
						or j.dest.x == points[i].x) {
						cur.push_back(Edge(points[i].x, j.y(points[i].x), points[i+1].x, j.y(points[i+1].x)));
						//cur.push_back(j);
					}
				}

				std::sort(cur.begin(), cur.end(), [](const Edge& x1, const Edge& x2) -> bool {
					if (x1.min_y() == x2.min_y())
						return x1.max_y() > x2.max_y();
					else
						return x1.min_y() > x2.min_y();
				});

				// std::cout << lanes.size() << ": ";
				// for (auto s : cur)
				// 	std::cout << s << " ";
				// std::cout <<'\n';

				lanes.push_back(std::pair<double, std::vector<Edge>>(points[i].x, cur));
			}
		}

		std::vector<Edge> cur;
		for (const auto j : edges) {
			if (j.dest.x == points[points.size()-1].x) {
				// cur.push_back(Edge(points[i].x, j.y(points[i].x), points[i+1].x, j.y(points[i+1].x)));
				cur.push_back(j);
			}
		}

		std::sort(cur.begin(), cur.end(), [](const Edge& x1, const Edge& x2) -> bool {
			if (x1.min_y() == x2.min_y())
				return x1.max_y() > x2.max_y();
			else
				return x1.min_y() > x2.min_y();
		});

		// std::cout << lanes.size() << ": ";
		// for (auto s : cur)
		// 	std::cout << s << " ";
		// std::cout <<'\n';

		lanes.push_back(std::pair<double, std::vector<Edge>>(points[points.size()-1].x, cur));

	}

	int NumberAboveEdges(const Point p) {
		int result = 0;

		for (int i = 0; i < lanes.size() - 1; i++) {
			if (lanes[i].first <= p.x and p.x < lanes[i + 1].first) {
				for (const auto j : lanes[i].second) {
					if (j.abovePoint(p)) {
						result++; 
					}
				}
				ll = i;
				return result;
			}
		}

		if (lanes[lanes.size() - 1].first == p.x) {
			for (const auto j : lanes[lanes.size() - 1].second) {
				if (j.abovePoint(p)) {
					result++; 
				}
			}
			return result;
		}

		return result;
	}

	int NumberAboveEdges2(const Point p) {
		int result = 0;

		int l = 0, r = lanes.size() - 1;
		// std::cout <<"l: "<< l << std::endl;

		if (p.x < lanes[0].first or p.x > lanes[lanes.size()-1].first)
			return 0;

		while (r - l > 1) {
			int mid = (r + l) / 2;

			if (lanes[mid].first == p.x) {
				l = mid;
				r = mid + 1;
				break;
			}

			if (p.x > lanes[mid].first) {
				l = mid;
			}

			if (p.x < lanes[mid].first) {
				r = mid;
			}

		}

		if (p.x == lanes[lanes.size()-1].first)
			l = lanes.size() - 1;

		// std::cout << lanes[l].second.size() << std::endl;
		for (const auto j : lanes[l].second) {
			//std::cout << j << " " << p << std::endl;
			if (j.abovePoint(p)) {
				result++; 
			} else {
				break;
			}
		}

		//ll = l;
		return result;

		// if (!lanes[l].second[0].abovePoint(p))
		// 	return 0;

		// int l1 = 0, r1 = lanes[l].second.size() - 1;
		// while (r1 - l1 > 1) {
		// 	int mid = (r1 + l1) / 2;

		// 	if (lanes[l].second[mid].min_y() == p.y) {
		// 		l1 = mid;
		// 		r1 = mid + 1;
		// 		break;
		// 	}

		// 	if (p.y > lanes[l].second[mid].min_y()) {
		// 		l1 = mid;
		// 	}

		// 	if (p.y < lanes[l].second[mid].min_y()) {
		// 		r1 = mid;
		// 	}

		// }
		// result = l1 + 1;

		// for (int i = 0; i < l1+1; i++) {
		// 	// if (!lanes[l].second[i].abovePoint(p)) {
		// 	// 	result--;
		// 	// }
		// 	std::cout << lanes[l].second[i] << " ";
		// }

		// while (l1+1 < lanes[l].second.size() and lanes[l].second[l1+1].abovePoint(p)) {
		// 	result++;
		// 	l1++;
		// }


		// ll = l;

		// return result;

	}

};

int main() {

	std::vector<Point> points;
	std::vector<Edge> edges;

	int number_of_edges;
	std::cin >> number_of_edges;

	for (int i = 0; i < number_of_edges; i++) {
		double a,b,c,d;
		std::cin >> a >> b >> c >> d;
		edges.push_back(Edge(a, b, c, d));
	}

	// for (const auto s : edges) {
	// 	std::cout << s << std::endl;
	// }

	for (const auto s : edges) {
		points.push_back(s.org);
		points.push_back(s.dest);
	}

	//std::cout << std::endl;

	std::sort(points.begin(), points.end());

	// for (const auto s : points) {
	// 	std::cout << s << std::endl;
	// }
	//std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	Index A(points, edges);
	//std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();

	int number_of_points;
	std::cin >> number_of_points;

	
	std::chrono::time_point<std::chrono::system_clock>  start1 = std::chrono::system_clock::now();
	double a, b;
	for (int i = 0; i < number_of_points; i++) {
		std::cin >> a >> b;

		// int f = A.NumberAboveEdges(Point(a, b));
		 std::cout << A.NumberAboveEdges2(Point(a, b)) << std::endl;
		//A.NumberAboveEdges2(Point(a, b));

		// if (f != ff) {
		// 	std::cout << i << " bad point: " << "<" << a << ", " << b << ">" << std::endl;
		// 	std::cout << f << " " << ff << std::endl;
		// 	break;
		// }
	}
	std::chrono::time_point<std::chrono::system_clock>  end1 = std::chrono::system_clock::now();


	std::cout << number_of_points << " " << std::chrono::duration<double>(end1-start1).count() << "\n";

	
	return 0;
}