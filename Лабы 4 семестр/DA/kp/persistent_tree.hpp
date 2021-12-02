#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

template<class K, class V>
struct PersistentTree {

	struct node {

		struct lrh {
			node* l = nullptr;
			node* r = nullptr;
			unsigned int h = 1;

			lrh() = default;
			lrh(node* _l, node* _r, unsigned int _h): l(_l), r(_r), h(_h){}
		};

		K key;
		V value;
		unordered_map<unsigned int, lrh> links;

		node(const K& k, const V& v, const unsigned int version): key(k), value(v) {
			links[version] = lrh(nullptr, nullptr, 1);
		}

		node* RightRotate(node* head, unsigned int version) {
			node* temp = head->links[version].l;
			head->links[version].l = temp->links[version].r;
			temp->links[version].r = head;
			FixHeight(head, version);
			FixHeight(temp, version);
			return temp;
		}

		node* LeftRotate(node* head, unsigned int version) {

			if (head->key == head->links[version].r->key)
				return head;

			node* temp = head->links[version].r;
			head->links[version].r = temp->links[version].l;
			temp->links[version].l = head;
			FixHeight(head, version);
			FixHeight(temp, version);
			return temp;
		}

		node* Balancing(node* head, unsigned int version) {
			FixHeight(head, version);
			if (Balance(head, version)==2) {
				if (Balance(head->links[version].l, version)<0) {
					head->links[version].l = LeftRotate(head->links[version].l, version);
				}
				return RightRotate(head, version); 
			} else if (Balance(head, version)==-2) {
				if (Balance(head->links[version].r, version)>0) {
					head->links[version].r = RightRotate(head->links[version].r, version);
				}
				return LeftRotate(head, version);
			}
			return head;
		}

		node* BalancedAdd(node* head, unsigned int version, const K& k, const V& v) {
			if (head) {

				lrh p = head->links[version];
				// cout << key << " "<< head->key << endl;
				if (k < head->key) {
					// cout << "l" << endl;
					head->links[version].l = BalancedAdd(p.l, version, k, v);
				} else {
					// cout << "r" << endl;
					head->links[version].r = BalancedAdd(p.r, version, k, v);
				}

				return Balancing(head, version);

			}

			return new node(k, v, version);
		}

		node* Add(node* zerohead, node* head, unsigned int version, const K& k, const V& v) {
			if (head) {
				//cout << head->key << "\n";

				lrh p = head->links[version];
				// cout << key << ", " << value << " " 
				// << head->key << ", " << head->value << endl;
				if (k < head->key) {
					// cout << "l" << endl;
					head->links[version].l = Add(zerohead, p.l, version, k, v);
				} else {
					// cout << "r" << endl;
					head->links[version].r = Add(zerohead, p.r, version, k, v);
				}

				return Balancing(head, version);

			}

			node* res = Find(zerohead, 0, k, v);
			res->links[version] = lrh(nullptr, nullptr, 1);
			return res;
		}

		node* Find(node* head, unsigned int version, const K& k, const V& v) const {
			node* temp = head;

			if (temp == nullptr) {
				return nullptr;
			}

			if (k == temp->key and v == temp->value)
				return temp;

		 	if (k >= temp->key) {
				return Find(temp->links[version].r, version, k, v);
			} else if (k < temp->key) {
				return Find(temp->links[version].l, version, k, v);
			} else {
				temp = Find(head->links[version].r, version, k, v);
				if (temp == nullptr) {
					temp = Find(head->links[version].l, version, k, v);
				}

				return temp;
			}

			return temp;
		}

		unsigned int NumberOfVertexes(node* head, const unsigned int version) const {
			if (!head) 
				return 0;

			return 1 + NumberOfVertexes(head->links[version].r, version) + NumberOfVertexes(head->links[version].l, version);
		}

		unsigned int NumberOfEdgesAbovePoint(node* head, const unsigned int version, const Point p, bool* flag) const {

			if (!head)
				return 0;

			if (head->value.underPoint(p)) {
				return NumberOfEdgesAbovePoint(head->links[version].r, version, p, flag);
			} else if (head->value.abovePoint(p)) {
				return NumberOfEdgesAbovePoint(head->links[version].l, version, p, flag) + NumberOfVertexes(head->links[version].r, version) + 1;
			} else if (head->value.crossPoint(p)) {
				*flag = true;
				return 0;
			} 

			throw "what?\n";
			return 0;

		}

		void Print(node* head, unsigned int version, unsigned int n) const {
			if (head) {
				lrh p = head->links[version];
				Print(p.r, version, n+1);
				for (unsigned int i=0; i<n; i++) cout << "\t";
				cout << "(" << head->key << ", " << head->value << ")\n";
				Print(p.l, version, n+1);
			}
		}

		unsigned int Height(node* head, unsigned int version) const {
			return head ? head->links[version].h : 0;
		}

		int Balance(node *head, unsigned int version) const {
			return head ? Height(head->links[version].l, version) - Height(head->links[version].r, version) : 0;
		}

		void FixHeight(node* head, unsigned int version) {
			head->links[version].h = (Height(head->links[version].l, version)>Height(head->links[version].r, version) ? 
				Height(head->links[version].l, version) : Height(head->links[version].r, version))+1;
		}

		~node() {
			if (links[0].l) delete links[0].l;
			if (links[0].r) delete links[0].r;
		}

	};

	unsigned int number_of_versions = 0;
	vector<node*> trees;

	void BuildZeroVersion(vector<V> elems) {

		trees.push_back(nullptr);

		for (const V& elem : elems) {
			trees[number_of_versions] = trees[number_of_versions]->BalancedAdd(trees[number_of_versions], number_of_versions, elem.max_y(), elem);
		}

		number_of_versions++;
	}

	void BuildNextVersion(vector<V> elems) {
		if (elems.empty()) {
			trees.push_back(nullptr);
			number_of_versions++;
			return;
		}

		node* tree = trees[0]->Find(trees[0], 0, elems[0].max_y(), elems[0]);
		tree->links[number_of_versions] = typename PersistentTree<K, V>::node::lrh(nullptr, nullptr, 1);
		trees.push_back(tree);

		for (size_t i = 1; i < elems.size(); i++) {
			trees[number_of_versions] = trees[number_of_versions]->Add(trees[0], trees[number_of_versions], number_of_versions, elems[i].max_y(), elems[i]);

			// trees[number_of_versions] -> Print(trees[number_of_versions], number_of_versions, 0);
		}

		number_of_versions++;
	}

	void AddInSomeVersion(unsigned int version, vector<V> elems) {
		if (elems.empty() or version >= trees.size()) return;
		
		for (const V& elem : elems) {
			trees[version] = trees[version]->Add(trees[0], trees[version], version, elem.max_y(), elem);
		}

	}

	void AddInSomeVersion(unsigned int version, initializer_list<V> elems) {
		if (empty(elems) or version >= trees.size()) return;
		
		for (const V& elem : elems) {
			trees[version] = trees[version]->Add(trees[0], trees[version], version, elem.max_y(), elem);
		}

	}

	void AddInSomeVersion(unsigned int version, V elem) {
		if (version >= trees.size()) return;

		trees[version] = trees[version]->Add(trees[0], trees[version], version, elem.max_y(), elem);
	}

	unsigned int NumberOfEdges(const Point p, const unsigned int version) {

		bool flag = false;
		unsigned int result = trees[version]->NumberOfEdgesAbovePoint(trees[version], version, p, &flag);

		if (flag)
			return 1;

		return result;
	}

	void Print(unsigned int version) {
		if (version >= trees.size()) {
			cout << "|--------------------------------------------------|" << endl;
			cout << "There is no such version of tree" << endl;
			cout << "|--------------------------------------------------|" << endl;
			return;
		}

		cout << "|--------------------------------------------------|" << endl;
		cout << "[" << version << "]" << endl;
		trees[version]->Print(trees[version], version, 0);
		cout << "|--------------------------------------------------|" << endl;
	}

	void Print() {
		unsigned int v = 0;
		cout << number_of_versions << " versions in total:\n";
		for (node* tree : trees) {
			cout << "|--------------------------------------------------|" << endl;
			cout << "[" << v << "]" << endl;
			tree->Print(tree, v, 0);
			cout << "|--------------------------------------------------|" << endl;
			v++;
		}
	}

	~PersistentTree() {
		if (!trees.empty()) delete trees[0];
	}

};