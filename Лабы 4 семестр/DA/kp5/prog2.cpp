#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <map>
#include "point.hpp"
#include "edge.hpp"
#include "persistent_tree2.hpp"

// #define PRINT
// #define TREE
#define LOG

using namespace std;

struct Index {

	PersistentTree<Edge, unsigned int> tree;
	vector<double> slabs;

	Index() = default;

	Index(const vector<vector<Point>> figures) {

		multimap<double, pair<Edge, unsigned int>> edges;
		multimap<double, Edge> for_enter;

#ifdef PRINT
		print("[");
		for (int i = 0; i < figures.size(); i++){
			print(" ", figures[i]);
		}
		print("]");
#endif
		// Создание массива рёбер
		for (vector points : figures) {
			static unsigned int figure_number = 1;
			for (size_t i = 0; i < points.size(); i++) {
				if (points[i].x == points[(i+1) % points.size()].x) continue;
				Edge cur = Edge(points[i], points[(i+1) % points.size()]);
				edges.insert({cur.org.x, {cur, figure_number}});
				for_enter.insert({cur.dest.x, cur});
			}
			figure_number++;
		}

		// Создание массива плит
		for (vector points : figures) {
			for (const Point p : points) {
				// if (find(slabs.begin(), slabs.end(), p.x) == slabs.end())
					slabs.push_back(p.x);
			}
		}

		// Сортировка массива плит, ребер на вход и на выход
		sort(slabs.begin(), slabs.end());

		bool flag = false;
		for (int i = 0; i < slabs.size(); i++) {

			// Пока есть отрезки, которые на предыдуще1 плите закончились - удаляем
			while (!for_enter.empty() and (*for_enter.begin()).second.dest.x == slabs[i] and i>0) {  
				tree.Remove((*for_enter.begin()).second, slabs[i-1] + 10E-9, flag);
				for_enter.erase(for_enter.begin());

				if (!flag)
					flag = true;
			}

			// Пока есть отрезки, которые начинаются в данной плите - добавляем 
			while (!edges.empty() and (*edges.begin()).second.first.org.x == slabs[i]) {
				tree.Insert((*edges.begin()).second.first, (*edges.begin()).second.second, slabs[i] + 10E-9, flag);
				edges.erase(edges.begin());

				if (!flag)
					flag = true;
			}

			// Если никакие не добавились и не закончились
			if (!flag)
				tree.NotChange();

			flag = false;
		}


#ifdef PRINT
#ifdef TREE
		tree.Print();
#endif
#endif
	}

	unsigned int NumberOfEdgesAbovePoint(Point p, long* la, long* ra) {

		if (p.x < slabs[0] or p.x > slabs[slabs.size()-1])
			return 0;
		unsigned int l = 0, r = slabs.size();

		bool flag = false;
		while(r  - l > 1) {

			unsigned int mid = (l + r) / 2;

			if (slabs[mid] == p.x) {
				l = mid;
				flag = true; // если точка на границе, то корень нечетный
				break;
			}

			if (p.x < slabs[mid]) {
				r = mid;
			} else {
				l = mid;
			}

		}
		
		long left_ancestor = -1, right_ancestor = -1;
		unsigned int res = tree.FindNumberAbove(l > 0 ? l-flag : l, p, &left_ancestor, &right_ancestor);

		*la = left_ancestor; 
		*ra = right_ancestor;
		return res;
	}

	long inWhichPoligone(Point p) {

		long left_ancestor = -1, right_ancestor = -1;
		unsigned int noeap = NumberOfEdgesAbovePoint(p, &left_ancestor, &right_ancestor);

		if (noeap % 2 == 1) {
			return left_ancestor;
		}

		return -1;
	}

	void Write(string name_of_file) {
		ofstream save_file;
		save_file.open(name_of_file);

		if (!save_file.is_open()) {
			print("Bad record");
		}

		save_file << slabs.size() << "\n";
		for (const double& p : slabs) {
			save_file << p << " ";
		}
		save_file << "\n";
		save_file << tree << "\n";

		save_file.close();
	}

	void Read(string name_of_file) {
		ifstream save_file;
		save_file.open(name_of_file);

		if (!save_file.is_open()) {
			print("Bad reading");
		}

		unsigned int size_of_slabs;
		save_file >> size_of_slabs;

		for (size_t i = 0; i < size_of_slabs; i++) {
			double slab;
			save_file >> slab;
			slabs.push_back(slab);
		}

		save_file >> tree;
		save_file.close();
	}

};


unsigned long long Read(vector<vector<Point>>* figures, istream& from) {
	unsigned int number_of_figures;
	from >> number_of_figures;
	unsigned long long res = 0;

	for (const unsigned int i : range<unsigned int>(0, number_of_figures)) {
		unsigned int number_of_vertexes;
		from >> number_of_vertexes;

		figures->push_back(vector<Point>());

		for(const unsigned int j : range<unsigned int>(0, number_of_vertexes)) {
			double l, r;
			from >> l >> r;
			(*figures)[i].push_back(Point(l, r));
			res++;
		}
	}

	return res;
}

double yy(double x1, double x2, double y1, double y2, double x) {
    if (x1 == x2)
        return (DBL_MAX) * (x-x1) + y1;
    return ((y2-y1)/(x2-x1)) * (x-x1) + y1;
}

bool inPoligone(const Point& p, const vector<vector<Point>>& figures) {
	for (const vector<Point>& figure : figures) {
		bool c = false;
		for (size_t i = 0; i < figure.size(); i++) {
			if (figure[i-1].x == figure[i].x and figure[i].x == p.x and ((figure[i-1].y <= p.y and p.y <= figure[i].y) or (figure[i].y <= p.y and p.y <= figure[i-1].y)))
            	return true;

	        if (((figure[i-1].x <= p.x and p.x <= figure[i].x) or (figure[i].x <= p.x and p.x <= figure[i-1].x)) and yy(figure[i-1].x, figure[i].x, figure[i-1].y, figure[i].y, p.x) == p.y)
	            return true;

	        if (((figure[i].y <= p.y and p.y < figure[i-1].y) or (figure[i-1].y <= p.y and p.y < figure[i].y)) and 
	            (p.x > (figure[i-1].x - figure[i].x) * (p.y - figure[i].y) / (figure[i-1].y - figure[i].y) + figure[i].x))
	             c = !c;
		}
	}

	return false;
}

int main(int args, char** argv) {
	vector<vector<Point>> figures;

#ifdef LOG
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::time_point<std::chrono::system_clock> start1;
	std::chrono::time_point<std::chrono::system_clock> end1;
	ofstream log_file;
	log_file.open("log1.txt", std::fstream::app);
#endif

	if (args == 1) {
		print("Не введен один из ключей: index, search");
	}

	else if (args == 2 and string(argv[1]) == "index") {
		
		Read(&figures, cin);

		Index Poligones(figures);
		Poligones.Write("base_output.txt");
		print("Структура построена и сохранена в файле: base_output.txt");
	}

	else if (args == 4 and string(argv[1]) == "index" and string(argv[2]) == "--input") {

		ifstream file;
		file.open(argv[3]);

		if (!file.is_open()) {
			print("Bad reading");
			return 0;
		}

		Read(&figures, file);

#ifdef LOG
		start = std::chrono::system_clock::now();
		Index Poligones(figures);
		end = std::chrono::system_clock::now();
		Poligones.Write("base_output.txt");
		log_file << figures[0].size() << " " << std::chrono::duration<double>(end-start).count() << "\n";
#else
		Index Poligones(figures);
		Poligones.Write("base_output.txt");
#endif
		print("Структура считана из файла:", argv[3], "и сохранена в файле: base_output.txt");

		file.close();
	}

	else if (args == 4 and string(argv[1]) == "index" and string(argv[2]) == "--output") {

		Read(&figures, cin);

		Index Poligones(figures);
		Poligones.Write(argv[3]);
		print("Структура построена и сохранена в файле:", argv[3]);
	}

	else if (args == 6 and string(argv[1]) == "index" and string(argv[2]) == "--input" and string(argv[4]) == "--output") {

		ifstream file;
		file.open(argv[3]);

		if (!file.is_open()) {
			print("Bad reading");
			return 0;
		}

		unsigned long long edges_count = Read(&figures, file);

#ifdef LOG
		start = std::chrono::system_clock::now();
		Index Poligones(figures);
		end = std::chrono::system_clock::now();
		// Poligones.Write(argv[5]);
		log_file << edges_count << " " << std::chrono::duration<double>(end-start).count() << "\n";
#else
		Index Poligones(figures);
		Poligones.Write(argv[5]);
#endif
		print("Структура считана из файла:", argv[3], "и сохранена в файле:", argv[5]);

		file.close();
	}

	else if (args == 2 and string(argv[1]) == "search") {
		Read(&figures, cin);
		Index Poligones(figures);

		double x,y;
		while (cin >> x >> y) {
			cout << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}
	}

	else if (args == 4 and string(argv[1]) == "search" and string(argv[2]) == "--input") {
		Read(&figures, cin);
		Index Poligones(figures);

		ifstream file;
		file.open(argv[3]);
		
		if (!file.is_open()) {
			print("Bad reading");
			return 0;
		}

		double x,y;
		while (file >> x >> y) {
			cout << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}

		file.close();
	}

	else if (args == 4 and string(argv[1]) == "search" and string(argv[2]) == "--index") {
		Index Poligones;
		Poligones.Read(string(argv[3]));
	
		double x,y;
		while (cin >> x >> y) {
			cout << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}

	}

	else if (args == 4 and string(argv[1]) == "search" and string(argv[2]) == "--output") {
		Read(&figures, cin);
		Index Poligones(figures);
	
		ofstream file;
		file.open(argv[3]);
		
		if (!file.is_open()) {
			print("Bad opening");
			return 0;
		}

		double x,y;
		while (cin >> x >> y) {
			file << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}

		file.close();
	}

	else if (args == 6 and string(argv[1]) == "search" and string(argv[2]) == "--index" and string(argv[4]) == "--input") {
		Index Poligones;
		Poligones.Read(string(argv[3]));

		ifstream file;
		file.open(argv[5]);

		if (!file.is_open()) {
			print("Bad opening");
			return 0;
		}

		double x,y;
		while (file >> x >> y) {
			cout << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}

		file.close();
	}

	else if (args == 6 and string(argv[1]) == "search" and string(argv[2]) == "--input" and string(argv[4]) == "--output") {
		Read(&figures, cin);
		Index Poligones(figures);

		ifstream file;
		file.open(argv[3]);
		ofstream out_file;
		out_file.open(argv[5]);

		if (!file.is_open()) {
			print("Bad opening");
			return 0;
		}

#ifdef LOG
		double all = 0;
		double all1 = 0;

		double x,y;
		unsigned int np = 0;
		while (file >> x >> y) {
			np++;

			start = std::chrono::system_clock::now();
			out_file << Poligones.inWhichPoligone(Point(x, y)) << endl;
			end = std::chrono::system_clock::now();
			all += std::chrono::duration<double>(end-start).count();

			start1 = std::chrono::system_clock::now();
			inPoligone(Point(x, y), figures);
			end1 = std::chrono::system_clock::now();
			all1 += std::chrono::duration<double>(end1-start1).count();
		}
		
		log_file << Poligones.slabs.size() << " " << all << " " << all1 << "\n";
#else
		double x,y;
		while (file >> x >> y) {
			out_file << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}
#endif

		file.close();
		out_file.close();
	}

	else if (args == 8 and string(argv[1]) == "search" and string(argv[2]) == "--index" and string(argv[4]) == "--input" and string(argv[6]) == "--output") {
		Index Poligones;
		Poligones.Read(string(argv[3]));

		ifstream file;
		ofstream out_file;
		file.open(argv[5]);
		out_file.open(argv[7]);

		if (!file.is_open() or !out_file.is_open()) {
			print("Bad opening");
			return 0;
		}

#ifdef LOG
		start = std::chrono::system_clock::now();
		double x,y;
		unsigned int np = 0;
		while (file >> x >> y) {
			np++;
			out_file << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}
		end = std::chrono::system_clock::now();
		log_file << Poligones.slabs.size() << " " << std::chrono::duration<double>(end-start).count() << "\n";
#else
		double x,y;
		while (file >> x >> y) {
			out_file << Poligones.inWhichPoligone(Point(x, y)) << endl;
		}
#endif

		out_file.close();
		file.close();
	} else {
		print("Неправильный ввод");
	}

#ifdef LOG
	log_file.close();
#endif
	
	return 0;
}