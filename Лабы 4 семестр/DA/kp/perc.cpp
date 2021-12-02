// #include <iostream>
// #include <cstdlib>
// #include <ctime>
// #include <vector>
// #include <algorithm>
// #include <unordered_map>

// #include "point.hpp"
// #include "edge.hpp"
// #include "avltree.hpp"
#include "persistent_tree.hpp"



int main() {

	PersistentTree<int, int> t;
	t.AddInSomeVersion(3, {4});

	t.BuildZeroVersion({1,2,3,4,5,6,7,12,23,14});
	t.BuildNextVersion({});
	t.BuildNextVersion({1,12,23,14});
	t.BuildNextVersion({1,2});
	t.AddInSomeVersion(1, {4});
	t.BuildNextVersion({1,2,3,4,5});

	t.Print();

	return 0;
}